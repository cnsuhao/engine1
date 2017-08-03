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
#include "scenario/SEAction.h"
#include "substance/SESubstanceManager.h"

#include "scenario/SEAdvanceTime.h"

#include "scenario/SESerializeState.h"
// Environment Actions
#include "system/environment/actions/SEChangeEnvironmentConditions.h"
#include "system/environment/actions/SEThermalApplication.h"
// Anesthesia Actions
#include "system/equipment/Anesthesia/actions/SEAnesthesiaMachineConfiguration.h"
#include "system/equipment/Anesthesia/actions/SEOxygenWallPortPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEOxygenTankPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEExpiratoryValveLeak.h"
#include "system/equipment/Anesthesia/actions/SEExpiratoryValveObstruction.h"
#include "system/equipment/Anesthesia/actions/SEInspiratoryValveLeak.h"
#include "system/equipment/Anesthesia/actions/SEInspiratoryValveObstruction.h"
#include "system/equipment/Anesthesia/actions/SEMaskLeak.h"
#include "system/equipment/Anesthesia/actions/SESodaLimeFailure.h"
#include "system/equipment/Anesthesia/actions/SETubeCuffLeak.h"
#include "system/equipment/Anesthesia/actions/SEVaporizerFailure.h"
#include "system/equipment/Anesthesia/actions/SEVentilatorPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEYPieceDisconnect.h"
// Inhaler Actions
#include "system/equipment/Inhaler/actions/SEInhalerConfiguration.h"
// Patient Actions
#include "patient/actions/SEPatientAssessmentRequest.h"
#include "patient/actions/SEAcuteStress.h"
#include "patient/actions/SEAirwayObstruction.h"
#include "patient/actions/SEApnea.h"
#include "patient/actions/SEAsthmaAttack.h"
#include "patient/actions/SEBrainInjury.h"
#include "patient/actions/SEBronchoconstriction.h"
#include "patient/actions/SECardiacArrest.h"
#include "patient/actions/SEChestCompression.h"
#include "patient/actions/SEChestCompressionForce.h"
#include "patient/actions/SEChestCompressionForceScale.h"
#include "patient/actions/SEChestOcclusiveDressing.h"
#include "patient/actions/SEConsciousRespiration.h"
#include "patient/actions/SEConsumeNutrients.h"
#include "patient/actions/SEIntubation.h"
#include "patient/actions/SEExercise.h"
#include "patient/actions/SEHemorrhage.h"
#include "patient/actions/SEIntubation.h"
#include "patient/actions/SEMechanicalVentilation.h"
#include "patient/actions/SENeedleDecompression.h"
#include "patient/actions/SEPericardialEffusion.h"
#include "patient/actions/SESubstanceBolus.h"
#include "patient/actions/SESubstanceInfusion.h"
#include "patient/actions/SESubstanceCompoundInfusion.h"
#include "patient/actions/SETensionPneumothorax.h"
#include "patient/actions/SEUrinate.h"

SEAction::SEAction() : Loggable()
{
  m_Comment="";
}

SEAction::~SEAction()
{
  Clear();
}

void SEAction::Clear()
{
  m_Comment="";
}

SEAction* SEAction::newFromBind(const cdm::ActionData& data, SESubstanceManager& substances)
{
  std::stringstream ss;
  SESubstance* substance;
  SESubstanceCompound* compound;

  // Anesthesia Machine Actions
  cdm::AnesthesiaMachineConfigurationData* anConfig;
  // Anesthesia Machine Failure Action
  cdm::ExpiratoryValveLeakData* anExLeak;
  cdm::ExpiratoryValveObstructionData* anExObs;
  cdm::InspiratoryValveLeakData* anInLeak;
  cdm::InspiratoryValveObstructionData* anInObs;
  cdm::MaskLeakData* anMskLeak;
  cdm::SodaLimeFailureData* anSodaFail;
  cdm::TubeCuffLeakData* anTubLeak;
  cdm::VaporizerFailureData* anVapFail;
  cdm::VentilatorPressureLossData* anVentLoss;
  cdm::YPieceDisconnectData* anYDisc;
  // Anesthesia Machine Incidents
  cdm::OxygenWallPortPressureLossData* anO2WallLoss;
  cdm::OxygenTankPressureLossData* anO2TankLoss;


  cdm::ActionData* action = (cdm::ActionData*)&data;
  cdm::AdvanceTimeData* advData = dynamic_cast<cdm::AdvanceTimeData*>(action);
  if (advData != nullptr)
  {
    SEAdvanceTime* a = new SEAdvanceTime();
    a->Load(*advData);
    return a;
  }

  cdm::SerializeStateData* stData = dynamic_cast<cdm::SerializeStateData*>(action);
  if (stData != nullptr)
  {
    SESerializeState* a = new SESerializeState();
    a->Load(*stData);
    return a;
  }

  if (dynamic_cast<cdm::EnvironmentActionData*>(action) != nullptr)
  {
    if (dynamic_cast<cdm::EnvironmentChangeData*>(action) != nullptr)
    {
      SEEnvironmentChange* a = new SEEnvironmentChange(substances);
      a->Load(*(cdm::EnvironmentChangeData*)action);
      return a;
    }
    if (dynamic_cast<cdm::ThermalApplicationData*>(action) != nullptr)
    {
      SEThermalApplication* a = new SEThermalApplication();
      a->Load(*(cdm::ThermalApplicationData*)action);
      return a;
    }
    substances.GetLogger()->Error("Unsupported Environment Action Received", "SEScenario::Load");
  }

  if (dynamic_cast<cdm::PatientActionData*>(action) != nullptr)
  {
    if (dynamic_cast<cdm::PatientAssessmentRequestData*>(action) != nullptr)
    {
      SEPatientAssessmentRequest* a = new SEPatientAssessmentRequest();
      a->Load(*(cdm::PatientAssessmentRequestData*)action);
      return a;
    }

    cdm::AcuteStressData* aStressData = dynamic_cast<cdm::AcuteStressData*>(action);
    if (aStressData != nullptr)
    {
      SEAcuteStress* a = new SEAcuteStress();
      a->Load(*aStressData);
      return a;
    }

    cdm::AirwayObstructionData* airObData = dynamic_cast<cdm::AirwayObstructionData*>(action);
    if (airObData != nullptr)
    {
      SEAirwayObstruction* a = new SEAirwayObstruction();
      a->Load(*airObData);
      return a;
    }

    cdm::ApneaData* apneaData = dynamic_cast<cdm::ApneaData*>(action);
    if (apneaData != nullptr)
    {
      SEApnea* a = new SEApnea();
      a->Load(*apneaData);
      return a;
    }

    cdm::BrainInjuryData* brainInjData = dynamic_cast<cdm::BrainInjuryData*>(action);
    if (brainInjData != nullptr)
    {
      SEBrainInjury* a = new SEBrainInjury();
      a->Load(*brainInjData);
      return a;
    }

    cdm::BronchoconstrictionData* bconData = dynamic_cast<cdm::BronchoconstrictionData*>(action);
    if (bconData != nullptr)
    {
      SEBronchoconstriction* a = new SEBronchoconstriction();
      a->Load(*bconData);
      return a;
    }

    cdm::CardiacArrestData* carrestData = dynamic_cast<cdm::CardiacArrestData*>(action);
    if (carrestData != nullptr)
    {
      SECardiacArrest* a = new SECardiacArrest();
      a->Load(*carrestData);
      return a;
    }

    cdm::AsthmaAttackData* asthmaData = dynamic_cast<cdm::AsthmaAttackData*>(action);
    if (asthmaData != nullptr)
    {
      SEAsthmaAttack* a = new SEAsthmaAttack();
      a->Load(*asthmaData);
      return a;
    }

    cdm::ChestCompressionData* cprData = dynamic_cast<cdm::ChestCompressionData*>(action);
    if (cprData != nullptr)
    {
      cdm::ChestCompressionForceData* cprForce = dynamic_cast<cdm::ChestCompressionForceData*>(cprData);
      if (cprForce != nullptr)
      {
        SEChestCompressionForce* a = new SEChestCompressionForce();
        a->Load(*cprForce);
        return a;
      }
      cdm::ChestCompressionForceScaleData* cprScale = dynamic_cast<cdm::ChestCompressionForceScaleData*>(cprData);
      if (cprScale != nullptr)
      {
        SEChestCompressionForceScale* a = new SEChestCompressionForceScale();
        a->Load(*cprScale);
        return a;
      }
    }

    cdm::ChestOcclusiveDressingData* codData = dynamic_cast<cdm::ChestOcclusiveDressingData*>(action);
    if (codData != nullptr)
    {
      SEChestOcclusiveDressing* a = new SEChestOcclusiveDressing();
      a->Load(*codData);
      return a;
    }

    cdm::ConsciousRespirationData* conRespData = dynamic_cast<cdm::ConsciousRespirationData*>(action);
    if (conRespData != nullptr)
    {
      SEConsciousRespiration* a = new SEConsciousRespiration();
      a->Load(*conRespData, substances);
      return a;
    }

    cdm::ConsumeNutrientsData* consumeData = dynamic_cast<cdm::ConsumeNutrientsData*>(action);
    if (consumeData != nullptr)
    {
      SEConsumeNutrients* a = new SEConsumeNutrients();
      a->Load(*consumeData);
      return a;
    }

    cdm::ExerciseData* exerciseData = dynamic_cast<cdm::ExerciseData*>(action);
    if (exerciseData != nullptr)
    {
      SEExercise* a = new SEExercise();
      a->Load(*exerciseData);
      return a;
    }

    cdm::IntubationData* intub8Data = dynamic_cast<cdm::IntubationData*>(action);
    if (intub8Data != nullptr)
    {
      SEIntubation* a = new SEIntubation();
      a->Load(*intub8Data);
      return a;
    }

    cdm::MechanicalVentilationData* mechVentData = dynamic_cast<cdm::MechanicalVentilationData*>(action);
    if (mechVentData != nullptr)
    {
      SEMechanicalVentilation* a = new SEMechanicalVentilation();
      a->Load(*mechVentData, substances);
      return a;
    }

    cdm::NeedleDecompressionData* needlData = dynamic_cast<cdm::NeedleDecompressionData*>(action);
    if (needlData != nullptr)
    {
      SENeedleDecompression* a = new SENeedleDecompression();
      a->Load(*needlData);
      return a;
    }

    cdm::HemorrhageData* hemData = dynamic_cast<cdm::HemorrhageData*>(action);
    if (hemData != nullptr)
    {
      SEHemorrhage* a = new SEHemorrhage();
      a->Load(*hemData);
      return a;
    }

    cdm::PericardialEffusionData* pericData = dynamic_cast<cdm::PericardialEffusionData*>(action);
    if (pericData != nullptr)
    {
      SEPericardialEffusion* a = new SEPericardialEffusion();
      a->Load(*pericData);
      return a;
    }

    cdm::TensionPneumothoraxData* pneumoData = dynamic_cast<cdm::TensionPneumothoraxData*>(action);
    if (pneumoData != nullptr)
    {
      SETensionPneumothorax* a = new SETensionPneumothorax();
      a->Load(*pneumoData);
      return a;
    }

    cdm::SubstanceBolusData* bolusData = dynamic_cast<cdm::SubstanceBolusData*>(action);
    if (bolusData != nullptr)
    {
      substance = substances.GetSubstance(bolusData->Substance());
      if (substance == nullptr)
      {
        ss << "Unknown substance : " << bolusData->Substance();
        substances.GetLogger()->Fatal(ss, "SEScenario::Load");
      }
      SESubstanceBolus* a = new SESubstanceBolus(*substance);
      a->Load(*bolusData);
      return a;
    }

    cdm::SubstanceInfusionData* subInfuzData = dynamic_cast<cdm::SubstanceInfusionData*>(action);
    if (subInfuzData != nullptr)
    {
      substance = substances.GetSubstance(subInfuzData->Substance());
      if (substance == nullptr)
      {
        ss << "Unknown substance : " << subInfuzData->Substance();
        substances.GetLogger()->Fatal(ss, "SEScenario::Load");
      }
      SESubstanceInfusion* a = new SESubstanceInfusion(*substance);
      a->Load(*subInfuzData);
      return a;
    }

    cdm::SubstanceCompoundInfusionData* subCInfuzData = dynamic_cast<cdm::SubstanceCompoundInfusionData*>(action);
    if (subCInfuzData != nullptr)
    {
      compound = substances.GetCompound(subCInfuzData->SubstanceCompound());
      if (compound == nullptr)
      {
        ss << "Unknown substance : " << subCInfuzData->SubstanceCompound();
        substances.GetLogger()->Fatal(ss, "SEScenario::Load");
      }
      SESubstanceCompoundInfusion* a = new SESubstanceCompoundInfusion(*compound);
      a->Load(*subCInfuzData);
      return a;
    }

    cdm::UrinateData* urinateData = dynamic_cast<cdm::UrinateData*>(action);
    if (urinateData != nullptr)
    {
      SEUrinate* a = new SEUrinate();
      a->Load(*urinateData);
      return a;
    }
    substances.GetLogger()->Error("Unsupported Patient Action Received", "SEScenario::Load");
  }
  else if (dynamic_cast<cdm::AnesthesiaMachineActionData*>(action) != nullptr)
  {
    anConfig = dynamic_cast<cdm::AnesthesiaMachineConfigurationData*>(action);
    if (anConfig != nullptr)
    {
      SEAnesthesiaMachineConfiguration* a = new SEAnesthesiaMachineConfiguration(substances);
      a->Load(*anConfig);
      return a;
    }

    anO2WallLoss = dynamic_cast<cdm::OxygenWallPortPressureLossData*>(action);
    if (anO2WallLoss != nullptr)
    {
      SEOxygenWallPortPressureLoss* a = new SEOxygenWallPortPressureLoss();
      a->Load(*anO2WallLoss);
      return a;
    }

    anO2TankLoss = dynamic_cast<cdm::OxygenTankPressureLossData*>(action);
    if (anO2TankLoss != nullptr)
    {
      SEOxygenTankPressureLoss* a = new SEOxygenTankPressureLoss();
      a->Load(*anO2TankLoss);
      return a;
    }

    anExLeak = dynamic_cast<cdm::ExpiratoryValveLeakData*>(action);
    if (anExLeak != nullptr)
    {
      SEExpiratoryValveLeak* a = new SEExpiratoryValveLeak();
      a->Load(*anExLeak);
      return a;
    }

    anExObs = dynamic_cast<cdm::ExpiratoryValveObstructionData*>(action);
    if (anExObs != nullptr)
    {
      SEExpiratoryValveObstruction* a = new SEExpiratoryValveObstruction();
      a->Load(*anExObs);
      return a;
    }

    anInLeak = dynamic_cast<cdm::InspiratoryValveLeakData*>(action);
    if (anInLeak != nullptr)
    {
      SEInspiratoryValveLeak* a = new SEInspiratoryValveLeak();
      a->Load(*anInLeak);
      return a;
    }

    anInObs = dynamic_cast<cdm::InspiratoryValveObstructionData*>(action);
    if (anInObs != nullptr)
    {
      SEInspiratoryValveObstruction* a = new SEInspiratoryValveObstruction();
      a->Load(*anInObs);
      return a;
    }

    anMskLeak = dynamic_cast<cdm::MaskLeakData*>(action);
    if (anMskLeak != nullptr)
    {
      SEMaskLeak* a = new SEMaskLeak();
      a->Load(*anMskLeak);
      return a;
    }

    anSodaFail = dynamic_cast<cdm::SodaLimeFailureData*>(action);
    if (anSodaFail != nullptr)
    {
      SESodaLimeFailure* a = new SESodaLimeFailure();
      a->Load(*anSodaFail);
      return a;
    }

    anTubLeak = dynamic_cast<cdm::TubeCuffLeakData*>(action);
    if (anTubLeak != nullptr)
    {
      SETubeCuffLeak* a = new SETubeCuffLeak();
      a->Load(*anTubLeak);
      return a;
    }

    anVapFail = dynamic_cast<cdm::VaporizerFailureData*>(action);
    if (anVapFail != nullptr)
    {
      SEVaporizerFailure* a = new SEVaporizerFailure();
      a->Load(*anVapFail);
      return a;
    }

    anVentLoss = dynamic_cast<cdm::VentilatorPressureLossData*>(action);
    if (anVentLoss != nullptr)
    {
      SEVentilatorPressureLoss* a = new SEVentilatorPressureLoss();
      a->Load(*anVentLoss);
      return a;
    }

    anYDisc = dynamic_cast<cdm::YPieceDisconnectData*>(action);
    if (anYDisc != nullptr)
    {
      SEYPieceDisconnect* a = new SEYPieceDisconnect();
      a->Load(*anYDisc);
      return a;
    }
    substances.GetLogger()->Error("Unsupported Anesthesia Machine Action Received", "SEScenario::Load");
  }
  else if (dynamic_cast<cdm::InhalerActionData*>(action) != nullptr)
  {
    cdm::InhalerConfigurationData* inhaleConfig = dynamic_cast<cdm::InhalerConfigurationData*>(action);
    if (inhaleConfig != nullptr)
    {
      SEInhalerConfiguration* a = new SEInhalerConfiguration(substances);
      a->Load(*inhaleConfig); 
      return a;
    }
  }
  
  if (substances.GetLogger() != nullptr)
    substances.GetLogger()->Error("Unsupported Action Received", "SEAction::newFromBind");
  return nullptr;
}

void SEAction::Load(const cdm::ActionData& src, SEAction& dst)
{
  SEAction::Serialize(src, dst);
}
void SEAction::Serialize(const cdm::ActionData& src, SEAction& dst)
{
  dst.Clear();
  
  //jbw - how does this work?
  if (!src.comment().empty())
    dst.GetComment().empty();
}

cdm::ActionData* SEAction::Unload(const SEAction& src)
{
  cdm::ActionData* dst = new cdm::ActionData();
  SEAction::Serialize(src, *dst);
  return dst;
}

void SEAction::Serialize(const SEAction& src, cdm::ActionData& dst)
{
  //jbw - how does this work?
  //if (HasComment())
  //  src.GetComment(m_Comment);
}


std::string SEAction::GetComment() const
{
  return m_Comment;
}
void SEAction::SetComment(const std::string& comment)
{
  m_Comment = comment;
}
bool SEAction::HasComment() const
{
  return m_Comment.empty()?false:true;
}
void SEAction::InvalidateComment()
{
  m_Comment = "";
}