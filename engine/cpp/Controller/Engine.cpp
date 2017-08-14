/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
#include "stdafx.h"
#include "bind/engine/EngineState.pb.h"
#include "Controller/Engine.h"
#include "patient/SEPatient.h"
#include "circuit/SECircuit.h"
#include "compartment/SECompartmentManager.h"
#include "engine/SEEngineStabilization.h"
#include "scenario/SEScenario.h"
#include "scenario/SECondition.h"

#include "utils/FileUtils.h"

#include "scenario/SESerializeState.h"
#include "patient/actions/SEPatientAssessmentRequest.h"
#include "patient/assessments/SEPulmonaryFunctionTest.h"
#include "patient/assessments/SEUrinalysis.h"
#include "patient/assessments/SECompleteBloodCount.h"
#include "patient/assessments/SEComprehensiveMetabolicPanel.h"
#include "substance/SESubstanceCompound.h"
#include <google/protobuf/text_format.h>

#include <memory>

PULSE_DECL std::unique_ptr<PhysiologyEngine> CreatePulseEngine(const std::string& logfile)
{
  return std::unique_ptr<PulseEngine>(new PulseEngine(logfile));
}

PULSE_DECL std::unique_ptr<PhysiologyEngine> CreatePulseEngine(Logger* logger)
{
  return std::unique_ptr<PulseEngine>(new PulseEngine(logger));
}

PulseEngine::PulseEngine(Logger* logger) : PulseController(logger), m_EngineTrack(*this)
{
  m_State = EngineState::NotReady;
  m_EventHandler = nullptr;
  m_DataTrack = &m_EngineTrack.GetDataTrack();
}

PulseEngine::PulseEngine(const std::string& logFileName) : PulseController(logFileName), m_EngineTrack(*this)
{
  m_State = EngineState::NotReady;
  m_EventHandler = nullptr;
  m_DataTrack = &m_EngineTrack.GetDataTrack();
}

PulseEngine::~PulseEngine()
{  
  
}

Logger* PulseEngine::GetLogger()
{
  return Loggable::GetLogger();
}

SEEngineTracker* PulseEngine::GetEngineTracker()
{
  return &m_EngineTrack;
}

bool PulseEngine::LoadStateFile(const std::string& filename, const SEScalarTime* simTime, const SEEngineConfiguration* config)
{
  pulse::StateData src;
  std::ifstream file_stream(filename, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (fmsg.empty() || !google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  LoadState(src, simTime);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

bool PulseEngine::LoadState(const google::protobuf::Message& state, const SEScalarTime* simTime, const SEEngineConfiguration* config)
{
  m_ss.str("");
  
  // We could preserve the tracker, but I think I want to force the user to set it up
  // again, they should have the data tracks (or easily get them), and they should
  // Set it back up, and set or reset the results file they are using
  m_State = EngineState::NotReady;

  const pulse::StateData* peState = dynamic_cast<const pulse::StateData*>(&state);
  if (peState == nullptr)
  {
    Error("State data is not a Pulse StateData object");
    return false;
  }

 
  if (peState->has_datarequestmanager())
  {
    m_EngineTrack.GetDataRequestManager().Clear();
    SEDataRequestManager::Load(peState->datarequestmanager(), m_EngineTrack.GetDataRequestManager(), *m_Substances);
    m_EngineTrack.ForceConnection();// I don't want to rest the file because I would loose all my data      
  }

  if (simTime != nullptr)
  {
    m_CurrentTime->Set(*simTime);
    m_SimulationTime->Set(*simTime);
  }
  else
  {
    if (peState->has_simulationtime())
    {
      SEScalarTime::Load(peState->simulationtime(), *m_CurrentTime);
      SEScalarTime::Load(peState->simulationtime(), *m_SimulationTime);
    }
    else
    {
      m_CurrentTime->SetValue(0, TimeUnit::s);
      m_SimulationTime->SetValue(0, TimeUnit::s);
    }
  }
  m_AirwayMode = peState->airwaymode();
  m_Intubation = peState->intubation();
   
  /// Patient //  
  if (!peState->has_patient())
    m_ss << "PulseState must have a patient" << std::endl;
  else
    SEPatient::Load(peState->patient(), *m_Patient);
  // Conditions //
  m_Conditions->Clear();
  if (peState->has_conditions())
  {
    for (int i=0; i<peState->conditions().anycondition_size(); i++)
    {
      SECondition* c = SECondition::Load(peState->conditions().anycondition()[i],*m_Substances);
      m_Conditions->ProcessCondition(*c);
      delete c;
    }
  }
  // Actions //
  m_Actions->Clear();
  if (peState->has_activeactions())
  {
    for (int i = 0; i<peState->activeactions().anyaction_size(); i++)
    {
      SEAction* a = SEAction::Load(peState->activeactions().anyaction()[i], *m_Substances);
      m_Actions->ProcessAction(*a);
      delete a;
    }
  }
  // Substances //
  for (int i=0; i<peState->activesubstance_size(); i++)
  {
    const cdm::SubstanceData& subData = peState->activesubstance()[i];
    SESubstance* sub = m_Substances->GetSubstance(subData.name());
    if (sub == nullptr)
    {
      sub = new SESubstance(GetLogger());
      m_Substances->AddSubstance(*sub);
    }
    SESubstance::Load(subData, *sub);
    m_Substances->AddActiveSubstance(*sub);
  }
  // Compounds //
  for (int i=0; i<peState->activecompound_size(); i++)
  {
    const cdm::SubstanceData_CompoundData& cmpdData = peState->activecompound()[i];
    SESubstanceCompound* cmpd = m_Substances->GetCompound(cmpdData.name());
    if (cmpd == nullptr)
      cmpd = new SESubstanceCompound(GetLogger());
    SESubstanceCompound::Load(cmpdData, *cmpd, *m_Substances);
    m_Substances->AddActiveCompound(*cmpd);
  }
  // Circuit Manager //
  if (!peState->has_circuitmanager())
    m_ss << "PulseState must have a circuit manager" << std::endl;
  else
    SECircuitManager::Load(peState->circuitmanager(), *m_Circuits);
  // Compartment Manager //
  if (!peState->has_compartmentmanager())
    m_ss << "PulseState must have a compartment manager" << std::endl;
  else
    SECompartmentManager::Load(peState->compartmentmanager(), *m_Compartments, m_Circuits.get());
  // Configuration //
  if (!peState->has_configuration())
    m_ss << "PulseState must have a configuration" << std::endl;
  else
    PulseConfiguration::Load(peState->configuration(), *m_Config);
  if (config != nullptr)
  {// Merge in any provided configuration parameters, I hope you know what you are doing....
    const PulseConfiguration* peConfig = dynamic_cast<const PulseConfiguration*>(config);
    if (peState == nullptr)
    {
      Error("Configuration is not a Pulse configuration object");
      return false;
    }
    m_Config->Merge(*peConfig);
  }

  /////////////
  // Systems //
  /////////////
  if (!peState->has_bloodchemistry())
    m_ss << "Missing Blood Chemistry State" << std::endl;
  else
    BloodChemistry::Load(peState->bloodchemistry(), *m_BloodChemistrySystem);
  if (!peState->has_cardiovascular())
    m_ss << "Missing Cardiovascular State" << std::endl;
  else
    Cardiovascular::Load(peState->cardiovascular(), *m_CardiovascularSystem);
  if (!peState->has_drug())
    m_ss << "Missing Drug State" << std::endl;
  else
    Drugs::Load(peState->drug(), *m_DrugSystem);
  if (!peState->has_endocrine())
    m_ss << "Missing Endocrine State" << std::endl;
  else
    Endocrine::Load(peState->endocrine(), *m_EndocrineSystem);
  if (!peState->has_energy())
    m_ss << "Missing Energy State" << std::endl;
  else
    Energy::Load(peState->energy(), *m_EnergySystem);
  if (!peState->has_gastrointestinal())
    m_ss << "Missing Gastrointestinal State" << std::endl;
  else
    Gastrointestinal::Load(peState->gastrointestinal(), *m_GastrointestinalSystem);
  if (!peState->has_hepatic())
    m_ss << "Missing Hepatic State" << std::endl;
  else
    Hepatic::Load(peState->hepatic(), *m_HepaticSystem);
  if (!peState->has_nervous())
    m_ss << "Missing Nervous State" << std::endl;
  else
    Nervous::Load(peState->nervous(), *m_NervousSystem);
  if (!peState->has_renal())
    m_ss << "Missing Renal State" << std::endl;
  else
    Renal::Load(peState->renal(), *m_RenalSystem);
  if (!peState->has_respiratory())
    m_ss << "Missing Respiratory State" << std::endl;
  else
    Respiratory::Load(peState->respiratory(), *m_RespiratorySystem);
  if (!peState->has_tissue())
    m_ss << "Missing Tissue State" << std::endl;
  else
    Tissue::Load(peState->tissue(), *m_TissueSystem);
  if (!peState->has_environment())
    m_ss << "Missing Environment State" << std::endl;
  else
    Environment::Load(peState->environment(), *m_Environment);
  if (!peState->has_anesthesiamachine())
    m_ss << "Missing Anesthesia Machine State" << std::endl;
  else
    AnesthesiaMachine::Load(peState->anesthesiamachine(), *m_AnesthesiaMachine);
  if (!peState->has_electrocardiogram())
    m_ss << "Missing ECG State" << std::endl;
  else
    ECG::Load(peState->electrocardiogram(), *m_ECG);
  if (!peState->has_inhaler())
    m_ss << "Missing Inhaler State" << std::endl;
  else
    Inhaler::Load(peState->inhaler(), *m_Inhaler);

  if (!m_ss.str().empty())
  {
    Error(m_ss);
    return false;
  }
  // Make sure links are correct with our modes
  m_Compartments->UpdateAirwayGraph();
  m_Compartments->GetActiveRespiratoryGraph();
  m_Compartments->GetActiveAerosolGraph();

  // It helps to unload what you just loaded and to a compare if you have issues
  //SaveState("WhatIJustLoaded.pba");

  // Good to go, save it off and carry on!
  m_State = EngineState::Active;
  return true;// return CheckDataRequirements/IsValid() or something
}

std::unique_ptr<google::protobuf::Message> PulseEngine::SaveState(const std::string& filename)
{
  std::unique_ptr<pulse::StateData> state(new pulse::StateData());

  state->set_airwaymode(m_AirwayMode);
  state->set_intubation(m_Intubation);
  state->set_allocated_simulationtime(SEScalarTime::Unload(*m_SimulationTime));
  if(m_EngineTrack.GetDataRequestManager().HasDataRequests())
    state->set_allocated_datarequestmanager(SEDataRequestManager::Unload(m_EngineTrack.GetDataRequestManager()));
  // Patient
  state->set_allocated_patient(SEPatient::Unload(*m_Patient));
  // Conditions
  state->set_allocated_conditions(SEConditionManager::Unload(*m_Conditions));
  // Actions
  state->set_allocated_activeactions(SEActionManager::Unload(*m_Actions));
 // Active Substances/Compounds
  for (SESubstance* s : m_Substances->GetActiveSubstances())
    state->mutable_activesubstance()->AddAllocated(SESubstance::Unload(*s));
  for (SESubstanceCompound* c : m_Substances->GetActiveCompounds())
    state->mutable_activecompound()->AddAllocated(SESubstanceCompound::Unload(*c));
  // Systems
  state->set_allocated_bloodchemistry(BloodChemistry::Unload(*m_BloodChemistrySystem));
  state->set_allocated_cardiovascular(Cardiovascular::Unload(*m_CardiovascularSystem));
  state->set_allocated_drug(Drugs::Unload(*m_DrugSystem));
  state->set_allocated_endocrine(Endocrine::Unload(*m_EndocrineSystem));
  state->set_allocated_energy(Energy::Unload(*m_EnergySystem));
  state->set_allocated_gastrointestinal(Gastrointestinal::Unload(*m_GastrointestinalSystem));
  state->set_allocated_hepatic(Hepatic::Unload(*m_HepaticSystem));
  state->set_allocated_nervous(Nervous::Unload(*m_NervousSystem));
  state->set_allocated_renal(Renal::Unload(*m_RenalSystem));
  state->set_allocated_respiratory(Respiratory::Unload(*m_RespiratorySystem));
  state->set_allocated_tissue(Tissue::Unload(*m_TissueSystem));
  state->set_allocated_environment(Environment::Unload(*m_Environment));
  state->set_allocated_anesthesiamachine(AnesthesiaMachine::Unload(*m_AnesthesiaMachine));
  state->set_allocated_electrocardiogram(ECG::Unload(*m_ECG));
  state->set_allocated_inhaler(Inhaler::Unload(*m_Inhaler));
  // Compartments
  state->set_allocated_compartmentmanager(SECompartmentManager::Unload(*m_Compartments));
  // Configuration
  state->set_allocated_configuration(PulseConfiguration::Unload(*m_Config));
  // Circuitsk
  state->set_allocated_circuitmanager(SECircuitManager::Unload(*m_Circuits));

  if (!filename.empty())
  {
    CreateFilePath(filename);
    std::string content;
    google::protobuf::TextFormat::PrintToString(*state, &content);
    std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
    ascii_ostream << content;
    ascii_ostream.flush();
    ascii_ostream.close();
  }

  return state;
}

bool PulseEngine::InitializeEngine(const std::string& patientFile, const std::vector<const SECondition*>* conditions, const SEEngineConfiguration* config)
{
  std::string pFile = patientFile;
  if (pFile.find("/patients") == std::string::npos)
  {// Prepend the patient directory if it's not there
    pFile = "./patients/";
    pFile += patientFile;
  }
  if (!m_Patient->LoadFile(pFile))
    return false;
  return InitializeEngine(conditions,config);
}

bool PulseEngine::InitializeEngine(const SEPatient& patient, const std::vector<const SECondition*>* conditions, const SEEngineConfiguration* config)
{ 
  auto* p = SEPatient::Unload(patient);
  SEPatient::Load(*p, *m_Patient);
  delete p;  
  // We need logic here that makes sure we have what we need
  // and notify we are ignoring anything provided we won't use
  return InitializeEngine(conditions,config);
}

bool PulseEngine::InitializeEngine(const std::vector<const SECondition*>* conditions, const SEEngineConfiguration* config)
{
  const PulseConfiguration* pConfig = nullptr;
  if (config != nullptr)
  {
    pConfig = dynamic_cast<const PulseConfiguration*>(config);
    if (pConfig == nullptr)
    {
      Error("Configuration provided is not a Pulse Configuration Object");
      return false;
    }
  }
  m_EngineTrack.ResetFile();
  m_State = EngineState::Initialization;
  if (!PulseController::Initialize(pConfig))
    return false;

  // We don't capture events during initialization
  m_Patient->ForwardEvents(nullptr);
  m_AnesthesiaMachine->ForwardEvents(nullptr);

  // Stabilize the engine to a resting state (with a standard meal and environment)
  if (!m_Config->HasStabilization())
  {
    Error("Pulse needs stabilization criteria, none provided in configuration file");
    return false;
  }

  m_State = EngineState::InitialStabilization;
  if (!m_Config->GetStabilization()->StabilizeRestingState(*this))
    return false;  
  // We need to process conditions here, so systems can prepare for them in their AtSteadyState method
  if (conditions != nullptr && !conditions->empty())
  {
    for (const SECondition* c : *conditions)
    {
      m_ss << "[Condition] " << *c;
      Info(m_ss);
      if (!m_Conditions->ProcessCondition(*c))
        return false;
    }
  }
  AtSteadyState(EngineState::AtInitialStableState);

  m_State = EngineState::SecondaryStabilization;
  // Apply conditions and anything else to the physiology
  // now that it's steady with provided patient, environment, and feedback
  if (conditions != nullptr && !conditions->empty())
  {// Now restabilize the patient with any conditions that were applied
   // Push conditions into condition manager
    if (!m_Config->GetStabilization()->StabilizeConditions(*this, *conditions))
      return false;
  }
  else
  {
    if (!m_Config->GetStabilization()->StabilizeFeedbackState(*this))
      return false;
  }
  AtSteadyState(EngineState::AtSecondaryStableState);

  m_State = EngineState::Active;
  // Hook up the handlers (Note events will still be in the log)
  m_Patient->ForwardEvents(m_EventHandler);
  m_AnesthesiaMachine->ForwardEvents(m_EventHandler);
  Info("Finalizing homeostasis");

  // Run this again to clear out any bumps from systems resetting baselines in the last AtSteadyState call
  AdvanceModelTime(30, TimeUnit::s); // I would rather run Feedback stablization again, but...
  // This does not work for a few patients, they will not stay stable (???)  
  //if (!m_Config->GetStabilizationCriteria()->StabilizeFeedbackState(*this))
  //  return false;

  if (!m_Config->GetStabilization()->IsTrackingStabilization())
    m_SimulationTime->SetValue(0, TimeUnit::s);  
  // Don't allow any changes to Quantity/Potential/Flux values directly
  // Use Quantity/Potential/Flux Sources
  m_Circuits->SetReadOnly(true);

  return true;
}

double PulseEngine::GetTimeStep(const TimeUnit& unit)
{
  return m_Config->GetTimeStep(unit);
}

double PulseEngine::GetSimulationTime(const TimeUnit& unit)
{
  return m_SimulationTime->GetValue(unit);
}

void PulseEngine::AdvanceModelTime()
{
  if (!IsReady())
    return;  
  if(m_Patient->IsEventActive(cdm::PatientData_eEvent_IrreversibleState))
    return;  

  PreProcess();
  Process();
  PostProcess();

  m_Patient->UpdateEvents(m_Config->GetTimeStep());
  m_CurrentTime->Increment(m_Config->GetTimeStep());
  m_SimulationTime->Increment(m_Config->GetTimeStep());
}

void PulseEngine::AdvanceModelTime(double time, const TimeUnit& unit)
{
  double time_s = Convert(time,unit,TimeUnit::s);
  int count = (int)(time_s / m_Config->GetTimeStep(TimeUnit::s));
  for(int i=0;i<count;i++)
    AdvanceModelTime();
}

bool PulseEngine::ProcessAction(const SEAction& action)
{  
  if (!IsReady())
    return false;
  m_ss << "[Action] " << *m_SimulationTime << ", " << action;
  Info(m_ss);

  const SESerializeState* serialize = dynamic_cast<const SESerializeState*>(&action);
  if (serialize != nullptr)
  {
    if (serialize->GetType() == cdm::SerializeStateData_eSerializationType_Save)
    {
      if (serialize->HasFilename())
      {
        SaveState(serialize->GetFilename());
      }
      else
      {
        std::stringstream ss;
        MKDIR("./states");
        ss << "./states/" << m_Patient->GetName() << "@" << GetSimulationTime(TimeUnit::s) << "s.pba";
        Info("Saving " + ss.str());
        SaveState(ss.str());
        // Debug code to make sure things are consistent
        //LoadStateFile(ss.str());
        //SaveState("./states/AfterSave.pba");
      }     
    }
    else
      return LoadStateFile(serialize->GetFilename());
    return true;
  }

  const SEPatientAssessmentRequest* patientAss = dynamic_cast<const SEPatientAssessmentRequest*>(&action);
  if (patientAss != nullptr)
  {
    switch (patientAss->GetType())
    {
      case cdm::PatientAssessmentData_eType_PulmonaryFunctionTest:
      {
        SEPulmonaryFunctionTest pft(m_Logger);
        GetPatientAssessment(pft);

        // Write out the Assessement
        std::string pftFile = GetEngineTracker()->GetDataRequestManager().GetResultFilename();
        if (pftFile.empty())
          pftFile = "PulmonaryFunctionTest";
        m_ss << "PFT@" << GetSimulationTime(TimeUnit::s) << "s";
        pftFile = Replace(pftFile, "Results", m_ss.str());
        pftFile = Replace(pftFile, ".txt", ".pba");
        m_ss << "PulmonaryFunctionTest@" << GetSimulationTime(TimeUnit::s) << "s.pba";
        pft.SaveFile(pftFile);
        break;
      }
      case cdm::PatientAssessmentData_eType_Urinalysis:
      {
        SEUrinalysis upan(m_Logger);
        GetPatientAssessment(upan);

        std::string upanFile = GetEngineTracker()->GetDataRequestManager().GetResultFilename();
        if (upanFile.empty())
          upanFile = "Urinalysis";
        m_ss << "Urinalysis@" << GetSimulationTime(TimeUnit::s) << "s";
        upanFile = Replace(upanFile, "Results", m_ss.str());
        upanFile = Replace(upanFile, ".txt", ".pba");
        m_ss << "Urinalysis@" << GetSimulationTime(TimeUnit::s) << "s.pba";
        upan.SaveFile(upanFile);
        break;
      }

      case cdm::PatientAssessmentData_eType_CompleteBloodCount:
      {
        SECompleteBloodCount cbc(m_Logger);
        GetPatientAssessment(cbc);
        std::string cbcFile = GetEngineTracker()->GetDataRequestManager().GetResultFilename();
        if (cbcFile.empty())
          cbcFile = "CompleteBloodCount";
        m_ss << "CBC@" << GetSimulationTime(TimeUnit::s) << "s";
        cbcFile = Replace(cbcFile, "Results", m_ss.str());
        cbcFile = Replace(cbcFile, ".txt", ".pba");
        m_ss << "CompleteBloodCount@" << GetSimulationTime(TimeUnit::s) << "s.pba";
        cbc.SaveFile(cbcFile);
        break;
      }

      case cdm::PatientAssessmentData_eType_ComprehensiveMetabolicPanel:
      {
        SEComprehensiveMetabolicPanel mp(m_Logger);
        GetPatientAssessment(mp);
        std::string mpFile = GetEngineTracker()->GetDataRequestManager().GetResultFilename();
        if (mpFile.empty())
          mpFile = "ComprehensiveMetabolicPanel";
        m_ss << "CMP@" << GetSimulationTime(TimeUnit::s) << "s";
        mpFile = Replace(mpFile, "Results", m_ss.str());
        mpFile = Replace(mpFile, ".txt", ".pba");
        m_ss << "ComprehensiveMetabolicPanel@" << GetSimulationTime(TimeUnit::s) << "s.pba";
        mp.SaveFile(mpFile);
        break;
      }
      default:
      {
        m_ss << "Unsupported assessment request " << patientAss->GetType();
        Error(m_ss);
        return false;
      }
    }
    return true;
  }

  return GetActions().ProcessAction(action);  
}



bool PulseEngine::IsReady()
{
  if (m_State == EngineState::NotReady)
  {
    Error("Engine is not ready to process, Initialize the engine or Load a state.");
    return false;
  }  
  return true;
}

void PulseEngine::SetEventHandler(SEEventHandler* handler)
{
  m_EventHandler = handler;
  if (m_Patient != nullptr)
    m_Patient->ForwardEvents(m_EventHandler);
  m_AnesthesiaMachine->ForwardEvents(m_EventHandler);
}

const SEEngineConfiguration* PulseEngine::GetConfiguration()
{
  return &PulseController::GetConfiguration();
}

const SEPatient&  PulseEngine::GetPatient()
{
  return PulseController::GetPatient();
}

bool PulseEngine::GetPatientAssessment(SEPatientAssessment& assessment)
{
  if (!IsReady())
    return false;
  return PulseController::GetPatientAssessment(assessment);
}

const SEEnvironment* PulseEngine::GetEnvironment()
{
  return &PulseController::GetEnvironment();
}

SESubstanceManager& PulseEngine::GetSubstanceManager()
{
  return *m_Substances;
}

const SEBloodChemistrySystem* PulseEngine::GetBloodChemistrySystem()
{
  return &PulseController::GetBloodChemistry();
}

const SECardiovascularSystem* PulseEngine::GetCardiovascularSystem()
{
  return &PulseController::GetCardiovascular();
}

const SEDrugSystem* PulseEngine::GetDrugSystem()
{
  return &PulseController::GetDrugs();
}

const SEEndocrineSystem* PulseEngine::GetEndocrineSystem()
{
  return &PulseController::GetEndocrine();
}

const SEEnergySystem* PulseEngine::GetEnergySystem()
{
  return &PulseController::GetEnergy();
}

const SEGastrointestinalSystem* PulseEngine::GetGastrointestinalSystem()
{
  return &PulseController::GetGastrointestinal();
}

const SEHepaticSystem* PulseEngine::GetHepaticSystem()
{
  return &PulseController::GetHepatic();
}

const SENervousSystem* PulseEngine::GetNervousSystem()
{
  return &PulseController::GetNervous();
}

const SERenalSystem* PulseEngine::GetRenalSystem()
{
  return &PulseController::GetRenal();
}

const SERespiratorySystem* PulseEngine::GetRespiratorySystem()
{
  return &PulseController::GetRespiratory();
}

const SETissueSystem* PulseEngine::GetTissueSystem()
{
  return &PulseController::GetTissue();
}


const SEAnesthesiaMachine* PulseEngine::GetAnesthesiaMachine()
{
  return &PulseController::GetAnesthesiaMachine();
}

const SEElectroCardioGram* PulseEngine::GetElectroCardioGram()
{
  return &PulseController::GetECG();
}

const SEInhaler* PulseEngine::GetInhaler()
{
  return &PulseController::GetInhaler();
}

const SECompartmentManager& PulseEngine::GetCompartments()
{
  return PulseController::GetCompartments();
}
