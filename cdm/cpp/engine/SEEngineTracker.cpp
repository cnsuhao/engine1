/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "engine/SEEngineTracker.h"
#include "PhysiologyEngine.h"
#include "patient/SEPatient.h"
// Compartments
#include "compartment/SECompartmentManager.h"
#include "compartment/fluid/SEGasCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"
#include "compartment/thermal/SEThermalCompartment.h"
// Substances
#include "substance/SESubstance.h"
#include "substance/SESubstanceTissuePharmacokinetics.h"
#include "substance/SESubstanceManager.h"
// Patient
#include "patient/SEPatient.h"
// Systems
#include "system/physiology/SEBloodChemistrySystem.h"
#include "system/physiology/SECardiovascularSystem.h"
#include "system/physiology/SEDrugSystem.h"
#include "system/physiology/SEEndocrineSystem.h"
#include "system/physiology/SEEnergySystem.h"
#include "system/physiology/SEGastrointestinalSystem.h"
#include "system/physiology/SENervousSystem.h"
#include "system/physiology/SERenalSystem.h"
#include "system/physiology/SERespiratorySystem.h"
#include "system/physiology/SETissueSystem.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachine.h"
#include "system/equipment/electrocardiogram/SEElectroCardioGram.h"
#include "system/equipment/inhaler/SEInhaler.h"
#include "system/environment/SEEnvironment.h"
// Scalars
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarElectricPotential.h"
#include "utils/DataTrack.h"

std::string Space2Underscore(const std::string& str)
{
  std::string s = str; 
  std::transform(s.begin(), s.end(), s.begin(), [](char ch) {
    return ch == ' ' ? '_' : ch;
  });
  return s;
}

SEEngineTracker::SEEngineTracker(PhysiologyEngine& engine) : Loggable(engine.GetLogger()),
                                                                         m_DataRequestMgr(engine.GetLogger()),
                                                                         m_Patient((SEPatient&)engine.GetPatient()),
                                                                         m_SubMgr((SESubstanceManager&)engine.GetSubstanceManager()),
                                                                         m_CmptMgr((SECompartmentManager&)engine.GetCompartments())
{  

  // TODO We are not handling nullptr well here... 

  SEBloodChemistrySystem* bchem = (SEBloodChemistrySystem*)engine.GetBloodChemistrySystem();
  if(bchem != nullptr)
    m_PhysiologySystems.push_back(bchem);
  SECardiovascularSystem* cv = (SECardiovascularSystem*)engine.GetCardiovascularSystem();
  if (cv != nullptr)
    m_PhysiologySystems.push_back(cv);
  SEEndocrineSystem* endo = (SEEndocrineSystem*)engine.GetEndocrineSystem();
  if (endo != nullptr)
    m_PhysiologySystems.push_back(endo);
  SEEnergySystem* energy = (SEEnergySystem*)engine.GetEnergySystem();
  if (energy != nullptr)
    m_PhysiologySystems.push_back(energy);
  SERenalSystem* renal = (SERenalSystem*)engine.GetRenalSystem();
  if (renal != nullptr)
    m_PhysiologySystems.push_back(renal);
  SEGastrointestinalSystem* gi = (SEGastrointestinalSystem*)engine.GetGastrointestinalSystem();
  if (gi != nullptr)
    m_PhysiologySystems.push_back(gi);
  SERespiratorySystem* resp = (SERespiratorySystem*)engine.GetRespiratorySystem();
  if (resp != nullptr)
    m_PhysiologySystems.push_back(resp);
  SEDrugSystem* drug = (SEDrugSystem*)engine.GetDrugSystem();
  if (drug != nullptr)
    m_PhysiologySystems.push_back(drug);
  SETissueSystem* tissue = (SETissueSystem*)engine.GetTissueSystem();
  if (tissue != nullptr)
    m_PhysiologySystems.push_back(tissue);
  SENervousSystem* nervous = (SENervousSystem*)engine.GetNervousSystem();
  if (nervous != nullptr)
    m_PhysiologySystems.push_back(nervous);

  m_Environment = (SEEnvironment*)engine.GetEnvironment();

  m_AnesthesiaMachine = (SEAnesthesiaMachine*)engine.GetAnesthesiaMachine();
  m_ECG = (SEElectroCardioGram*)engine.GetElectroCardioGram();
  m_Inhaler = (SEInhaler*)engine.GetInhaler();
  m_ForceConnection = false;
}

SEEngineTracker::~SEEngineTracker()
{
  Clear();
}

void SEEngineTracker::Clear()
{
  ResetFile();
  m_ForceConnection = false;
  DELETE_MAP_SECOND(m_Request2Scalar);
}

void SEEngineTracker::ResetFile()
{
  if (m_ResultsStream.is_open())
    m_ResultsStream.close();
}

DataTrack& SEEngineTracker::GetDataTrack()
{
  return m_DataTrack;
}

void SEEngineTracker::SetupRequests()
{
  bool isOpen = m_ResultsStream.is_open();
  if (!isOpen || m_ForceConnection)
  {// Process/Hook up all requests with their associated scalers
    for (SEDataRequest* dr : m_DataRequestMgr.GetDataRequests())
    {
      if (!TrackRequest(*dr))
      {// Could not hook this up, get rid of it
        m_ss << "Unable to find data for " << m_Request2Scalar[dr]->Heading;
        Error(m_ss);
      }
    }
    m_ForceConnection = false;
  }
  // Create the file now that all probes and requests have been added to the track
  // So we get columns for all of our data
  if (!isOpen)
    m_DataTrack.CreateFile(m_DataRequestMgr.GetResultFilename().c_str(), m_ResultsStream);
}

void SEEngineTracker::TrackData(double time_s)
{
  if (!m_DataRequestMgr.HasDataRequests())
    return;// Nothing to do here...

  SetupRequests();
  PullData();
  m_DataTrack.StreamProbesToFile(time_s, m_ResultsStream);
}
void SEEngineTracker::PullData()
{
  SEDataRequestScalar* ds;
  for (SEDataRequest* dr : m_DataRequestMgr.GetDataRequests())
  {
    ds = m_Request2Scalar[dr];
    if (ds == nullptr)
    {
      Error("You cannot modify CSV Results file data requests in the middle of a run.");
      Error("Ignorning data request " + dr->GetPropertyName());
      continue;
    }
    if (!ds->HasScalar())
    {
      m_DataTrack.Probe(ds->Heading, SEScalar::dNaN());
      continue;
    }
    ds->UpdateScalar();// Update compartment if needed
    if (ds->IsValid())
    {
      if (ds->HasUnit())
      {
        if (dr->GetUnit() == nullptr)
          dr->SetUnit(*ds->GetUnit());
        m_DataTrack.Probe(ds->Heading, ds->GetValue(*dr->GetUnit()));
      }
      else
        m_DataTrack.Probe(ds->Heading, ds->GetValue());
    }
    else if (ds->IsInfinity())
      m_DataTrack.Probe(ds->Heading, std::numeric_limits<double>::infinity());
    else
      m_DataTrack.Probe(ds->Heading, SEScalar::dNaN());
  }
}


bool SEEngineTracker::TrackRequest(SEDataRequest& dr)
{  
  SEDataRequestScalar* ds=new SEDataRequestScalar(GetLogger());  
  m_Request2Scalar[&dr]=ds;

  bool success = ConnectRequest(dr, *ds);

  switch (dr.GetCategory())
  {
    case cdm::DataRequestData_eCategory_Patient:
      m_ss << "Patient";
    case cdm::DataRequestData_eCategory_Physiology:
    case cdm::DataRequestData_eCategory_Environment:
    case cdm::DataRequestData_eCategory_AnesthesiaMachine:
    case cdm::DataRequestData_eCategory_ECG:
    case cdm::DataRequestData_eCategory_Inhaler:
    {
      if (!dr.GetUnit())
        m_ss << dr.GetPropertyName();
      else
        m_ss << dr.GetPropertyName() << "(" << *dr.GetUnit() << ")";

      ds->Heading = Space2Underscore(m_ss.str());
      m_ss.str("");//Reset Buffer
      m_DataTrack.Probe(ds->Heading, 0);
      m_DataTrack.SetFormatting(ds->Heading, dr);
      return success;
    }
    case cdm::DataRequestData_eCategory_GasCompartment:
    case cdm::DataRequestData_eCategory_LiquidCompartment:
    case cdm::DataRequestData_eCategory_ThermalCompartment:
    case cdm::DataRequestData_eCategory_TissueCompartment:
    {
      if (dr.HasSubstanceName())
      {
        if (!dr.GetUnit())
          m_ss << dr.GetCompartmentName() << "-" << dr.GetSubstanceName() << "-" << dr.GetPropertyName();
        else
          m_ss << dr.GetCompartmentName() << "-" << dr.GetSubstanceName() << "-" << dr.GetPropertyName() << "(" << *dr.GetUnit() << ")";
      }
      else
      {
        if (!dr.GetUnit())
          m_ss << dr.GetCompartmentName() << "-" << dr.GetPropertyName();
        else
          m_ss << dr.GetCompartmentName() << "-" << dr.GetPropertyName() << "(" << *dr.GetUnit() << ")";
      }
      ds->Heading = Space2Underscore(m_ss.str());
      m_ss.str("");//Reset Buffer
      m_DataTrack.Probe(ds->Heading, 0);
      m_DataTrack.SetFormatting(ds->Heading, dr);
      return success;
    }
    case cdm::DataRequestData_eCategory_Substance:
    {
      if (dr.HasCompartmentName())
      {
        if (!dr.GetUnit())
          m_ss << dr.GetSubstanceName() << "-" << dr.GetCompartmentName() << "-" << dr.GetPropertyName();
        else
          m_ss << dr.GetSubstanceName() << "-" << dr.GetCompartmentName() << "-" << dr.GetPropertyName() << "(" << *dr.GetUnit() << ")";
        ds->Heading = Space2Underscore(m_ss.str());
        m_ss.str("");//Reset Buffer
        m_DataTrack.Probe(ds->Heading, 0);
        m_DataTrack.SetFormatting(ds->Heading, dr);
        return success;
      }
      else
      {
        if (!dr.GetUnit())
          m_ss << dr.GetSubstanceName() << "-" << dr.GetPropertyName();
        else
          m_ss << dr.GetSubstanceName() << "-" << dr.GetPropertyName() << "(" << *dr.GetUnit() << ")";
        ds->Heading = Space2Underscore(m_ss.str());
        m_ss.str("");//Reset Buffer
        m_DataTrack.Probe(ds->Heading, 0);
        m_DataTrack.SetFormatting(ds->Heading, dr);
        return success;
      }
    }
    default:
      m_ss << "Unhandled data request category: " << dr.GetCategory() << std::endl;
      Fatal(m_ss);
  }

  m_ss << "Unhandled data request : " << dr.GetPropertyName() << std::endl;
  Fatal(m_ss);
  return false;
}

bool SEEngineTracker::ConnectRequest(SEDataRequest& dr, SEDataRequestScalar& ds)
{
  std::string propertyName = dr.GetPropertyName();
  switch (dr.GetCategory())
  {
    case cdm::DataRequestData_eCategory_Patient:
    {
      // casting of the const to modify the patient
      ds.SetScalar(m_Patient.GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_Physiology:
    {
      // Make sure we mapped something
      ds.SetScalar(SESystem::GetScalar(propertyName, &m_PhysiologySystems), dr);
      return true;
    }    
    case cdm::DataRequestData_eCategory_Environment:
    {
      // Make sure we mapped something
      ds.SetScalar(m_Environment->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_AnesthesiaMachine:
    {
      ds.SetScalar(m_AnesthesiaMachine->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_ECG:
    {
      ds.SetScalar(m_ECG->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_Inhaler:
    {
      ds.SetScalar(m_Inhaler->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_GasCompartment:
    {
      if (!m_CmptMgr.HasGasCompartment(dr.GetCompartmentName()))
      {
        Error("Unknown gas compartment : " + dr.GetCompartmentName());
        return false;
      }
      // Removing const because I need to create objects in order to track those objects
      SEGasCompartment* gasCmpt = (SEGasCompartment*)m_CmptMgr.GetGasCompartment(dr.GetCompartmentName());
      if (dr.HasSubstanceName())
      {
        SESubstance* sub = m_SubMgr.GetSubstance(dr.GetSubstanceName());
        // Activate this substance so compartments have it
        m_SubMgr.AddActiveSubstance(*sub);
        if (gasCmpt->HasChildren())
        {
          if (propertyName == "Volume")
            ds.UpdateProperty = CompartmentUpdate::Volume;
          else if (propertyName == "VolumeFraction")
            ds.UpdateProperty = CompartmentUpdate::VolumeFraction;
          else if (propertyName == "PartialPressure")
            ds.UpdateProperty = CompartmentUpdate::PartialPressure;
          ds.GasSubstance = gasCmpt->GetSubstanceQuantity(*sub);
        }
        ds.SetScalar(gasCmpt->GetSubstanceQuantity(*sub)->GetScalar(propertyName), dr);
      }
      else
      {
        if (gasCmpt->HasChildren() || gasCmpt->HasNodeMapping())
        {
          if (propertyName == "Volume")
            ds.UpdateProperty = CompartmentUpdate::Volume;
          if (propertyName == "Pressure")
            ds.UpdateProperty = CompartmentUpdate::Pressure;
        }

        {// Always Update these
          if (propertyName == "InFlow")
            ds.UpdateProperty = CompartmentUpdate::InFlow;
          else if (propertyName == "OutFlow")
            ds.UpdateProperty = CompartmentUpdate::OutFlow;
        }
        ds.GasCmpt = gasCmpt;
        ds.SetScalar(gasCmpt->GetScalar(propertyName), dr);
      }
      return true;
    }
    case cdm::DataRequestData_eCategory_LiquidCompartment:
    {
      if (!m_CmptMgr.HasLiquidCompartment(dr.GetCompartmentName()))
      {
        Error("Unknown liquid compartment : " + dr.GetCompartmentName());
        return false;
      }
      // Removing const because I need to create objects in order to track those objects
      SELiquidCompartment* liquidCmpt = (SELiquidCompartment*)m_CmptMgr.GetLiquidCompartment(dr.GetCompartmentName());

      if (dr.HasSubstanceName())
      {
        SESubstance* sub = m_SubMgr.GetSubstance(dr.GetSubstanceName());
        // Activate this substance so compartments have it
        m_SubMgr.AddActiveSubstance(*sub);
        if (liquidCmpt->HasChildren())
        {
          if (propertyName == "Mass")
            ds.UpdateProperty = CompartmentUpdate::Mass;
          else if (propertyName == "Concentration")
            ds.UpdateProperty = CompartmentUpdate::Concentration;
          else if (propertyName == "Molarity")
            ds.UpdateProperty = CompartmentUpdate::Molarity;
          else if (propertyName == "PartialPressure")
            ds.UpdateProperty = CompartmentUpdate::PartialPressure;
          else if (propertyName == "Saturation")
            ds.UpdateProperty = CompartmentUpdate::Saturation;
          ds.LiquidSubstance = liquidCmpt->GetSubstanceQuantity(*sub);
        }
        ds.SetScalar(liquidCmpt->GetSubstanceQuantity(*sub)->GetScalar(propertyName), dr);
      }
      else
      {
        if (liquidCmpt->HasChildren() || liquidCmpt->HasNodeMapping())
        {
          if (propertyName == "Volume")
            ds.UpdateProperty = CompartmentUpdate::Volume;
          if (propertyName == "Pressure")
            ds.UpdateProperty = CompartmentUpdate::Pressure;
        }

        {// Always Update these        
          if (propertyName == "InFlow")
            ds.UpdateProperty = CompartmentUpdate::InFlow;
          else if (propertyName == "OutFlow")
            ds.UpdateProperty = CompartmentUpdate::OutFlow;
        }
        ds.LiquidCmpt = liquidCmpt;
        ds.SetScalar(liquidCmpt->GetScalar(propertyName), dr);
      }
      return true;
    }
    case cdm::DataRequestData_eCategory_ThermalCompartment:
    {
      if (!m_CmptMgr.HasThermalCompartment(dr.GetCompartmentName()))
      {
        Error("Unknown thermal compartment : " + dr.GetCompartmentName());
        return false;
      }
      // Removing const because I need to create objects in order to track those objects
      SEThermalCompartment* thermalCmpt = (SEThermalCompartment*)m_CmptMgr.GetThermalCompartment(dr.GetCompartmentName());

      if (thermalCmpt->HasChildren() || thermalCmpt->HasNodeMapping())
      {
        if (propertyName == "Heat")
          ds.UpdateProperty = CompartmentUpdate::Heat;
        if (propertyName == "Temperature")
          ds.UpdateProperty = CompartmentUpdate::Temperature;
      }

      {// Always Update these       
        if (propertyName == "HeatTransferRateIn")
          ds.UpdateProperty = CompartmentUpdate::HeatTransferRateIn;
        else if (propertyName == "HeatTransferRateOut")
          ds.UpdateProperty = CompartmentUpdate::HeatTransferRateOut;
      }
      ds.ThermalCmpt = thermalCmpt;
      ds.SetScalar(thermalCmpt->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_TissueCompartment:
    {
      if (!m_CmptMgr.HasTissueCompartment(dr.GetCompartmentName()))
      {
        Error("Unknown tissue compartment : " + dr.GetCompartmentName());
        return false;
      }
      // Removing const because I need to create objects in order to track those objects
      SETissueCompartment* tissueCmpt = (SETissueCompartment*)m_CmptMgr.GetTissueCompartment(dr.GetCompartmentName());
      ds.SetScalar(tissueCmpt->GetScalar(propertyName), dr);
      return true;
    }
    case cdm::DataRequestData_eCategory_Substance:
    {
      // Removing const because I want to allocate and grab scalars to track for later
      SESubstance* sub = m_SubMgr.GetSubstance(dr.GetSubstanceName());
      m_SubMgr.AddActiveSubstance(*sub);
      if (dr.HasCompartmentName())
      {// I don't really have a generic/reflexive way of doing this...yet
        if (dr.GetPropertyName() == "PartitionCoefficient")
        {
          SESubstanceTissuePharmacokinetics& tk = sub->GetPK().GetTissueKinetics(dr.GetCompartmentName());
          ds.SetScalar(&tk.GetPartitionCoefficient(), dr);
          return true;
        }
      }
      else
      {
        ds.SetScalar(sub->GetScalar(propertyName), dr);
        return true;
      }
    }
    default:
      m_ss << "Unhandled data request category: " << dr.GetCategory() << std::endl;
      Fatal(m_ss);
  }
  m_ss << "Unhandled data request : " << propertyName << std::endl;
  Fatal(m_ss);
  return false;
}

void SEDataRequestScalar::SetScalar(const SEScalar* s, SEDataRequest& dr)
{
  if (s==nullptr)
  {
    Fatal("Unknown Data Request : " + dr.GetPropertyName());
    return;
  }
  SEGenericScalar::SetScalar(*s);  
  if (HasUnit())
  {
    if (!dr.HasRequestedUnit())// Use set unit if none provide
      dr.SetUnit(*GetUnit());
    else
    {
      const CCompoundUnit* unit = GetCompoundUnit(dr.GetRequestedUnit());
      if (unit==nullptr)
      {
        std::stringstream ss;
        ss << dr.GetRequestedUnit() << " is not compatible with " << dr.GetPropertyName();
        Fatal(ss);
      }
      dr.SetUnit(*unit);
    }
  }
}

void SEDataRequestScalar::UpdateScalar()
{
  if (UpdateProperty == CompartmentUpdate::None)
    return;

  if (GasCmpt != nullptr)
  {
    switch (UpdateProperty)
    {
    case CompartmentUpdate::InFlow:
      GasCmpt->GetInFlow();
      return;
    case CompartmentUpdate::OutFlow:
      GasCmpt->GetOutFlow();
      return;
    case CompartmentUpdate::Volume:
      GasCmpt->GetVolume();
      return;
    case CompartmentUpdate::Pressure:
      GasCmpt->GetPressure();
      return;
    default:    
      Error("Property is not supported on Gas Compartment");    
    }
  }
  else if (GasSubstance != nullptr)
  {
    switch (UpdateProperty)
    {
    case CompartmentUpdate::Volume:
      GasSubstance->GetVolume();
      return;
    case CompartmentUpdate::VolumeFraction:
      GasSubstance->GetVolumeFraction();
      return;
    case CompartmentUpdate::PartialPressure:
      GasSubstance->GetPartialPressure();
      return;
    default:
      Error("Property is not supported on Gas Substance");
    }
  }
  else if (LiquidCmpt != nullptr)
  {
    switch (UpdateProperty)
    {
    case CompartmentUpdate::InFlow:
      LiquidCmpt->GetInFlow();
      return;
    case CompartmentUpdate::OutFlow:
      LiquidCmpt->GetOutFlow();
      return;
    case CompartmentUpdate::Volume:
      LiquidCmpt->GetVolume();
      return;
    case CompartmentUpdate::pH:
      LiquidCmpt->GetPH();
      return;
    case CompartmentUpdate::Pressure:
      LiquidCmpt->GetPressure();
      return;
    default:
      Error("Property is not supported on liquid Compartment");
    }
  }
  else if (LiquidSubstance != nullptr)
  {
    switch (UpdateProperty)
    {
    case CompartmentUpdate::Mass:
      LiquidSubstance->GetMass();
      return;
    case CompartmentUpdate::Molarity:
      LiquidSubstance->GetMolarity();
      return;
    case CompartmentUpdate::Concentration:
      LiquidSubstance->GetConcentration();
      return;
    case CompartmentUpdate::PartialPressure:
      LiquidSubstance->GetPartialPressure();
      return;
    case CompartmentUpdate::Saturation:
      LiquidSubstance->GetSaturation();
      return;
    default:
      Error("Property is not supported on Liquid Substance");
    }
  }
  else if (ThermalCmpt != nullptr)
  {
    switch (UpdateProperty)
    {
    case CompartmentUpdate::HeatTransferRateIn:
      ThermalCmpt->GetHeatTransferRateIn();
      return;
    case CompartmentUpdate::HeatTransferRateOut:
      ThermalCmpt->GetHeatTransferRateOut();
      return;   
    case CompartmentUpdate::Heat:
      ThermalCmpt->GetHeat();
      return;
    case CompartmentUpdate::Temperature:
      ThermalCmpt->GetTemperature();
      return;
    default:
      Error("Property is not supported on Thermal Substance");
    }
  }
  Error("Could not update " + Heading);
}
