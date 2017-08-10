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
#include "scenario/SEPatientActionCollection.h"
#include "properties/SEScalarVolumePerTime.h"
#include "substance/SESubstanceCompound.h"
#include "substance/SESubstanceConcentration.h"

SEPatientActionCollection::SEPatientActionCollection(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
  m_AcuteStress = nullptr;
  m_AirwayObstruction = nullptr;
  m_Apnea = nullptr;
  m_AsthmaAttack = nullptr;
  m_BrainInjury = nullptr;
  m_Bronchoconstriction = nullptr;
  m_CardiacArrest = nullptr;
  m_ChestCompression = nullptr;
  m_ConsciousRespiration = nullptr;
  m_ConsumeNutrients = nullptr;
  m_LeftChestOcclusiveDressing = nullptr;
  m_RightChestOcclusiveDressing = nullptr;
  m_Exercise = nullptr;
  m_Intubation = nullptr;
  m_MechanicalVentilation = nullptr;
  m_LeftNeedleDecompression = nullptr;
  m_RightNeedleDecompression = nullptr;
  m_PericardialEffusion = nullptr;
  m_LeftOpenTensionPneumothorax = nullptr;
  m_LeftClosedTensionPneumothorax = nullptr;
  m_RightOpenTensionPneumothorax = nullptr;
  m_RightClosedTensionPneumothorax = nullptr;
  m_Urinate = nullptr;
}

SEPatientActionCollection::~SEPatientActionCollection()
{
  Clear();
}

void SEPatientActionCollection::Clear()
{
  RemoveAcuteStress();
  RemoveAirwayObstruction();
  RemoveApnea();
  RemoveAsthmaAttack();
  RemoveBrainInjury();
  RemoveBronchoconstriction();
  RemoveChestCompression();
  RemoveCardiacArrest();
  RemoveConsciousRespiration();
  RemoveConsumeNutrients();
  RemoveLeftChestOcclusiveDressing();
  RemoveRightChestOcclusiveDressing();
  RemoveExercise();
  RemoveIntubation();
  RemoveMechanicalVentilation();
  RemoveLeftNeedleDecompression();
  RemoveRightNeedleDecompression();
  RemovePericardialEffusion();
  RemoveLeftOpenTensionPneumothorax();
  RemoveLeftClosedTensionPneumothorax();
  RemoveRightOpenTensionPneumothorax();
  RemoveRightClosedTensionPneumothorax();
  RemoveUrinate();

  DELETE_MAP_SECOND(m_Hemorrhages);
  DELETE_MAP_SECOND(m_SubstanceBolus);
  DELETE_MAP_SECOND(m_SubstanceInfusions);
  DELETE_MAP_SECOND(m_SubstanceCompoundInfusions);
}


bool SEPatientActionCollection::ProcessAction(const SEPatientAction& action, cdm::AnyPatientActionData& any)
{
  const SEPatientAssessmentRequest* patientAss = dynamic_cast<const SEPatientAssessmentRequest*>(&action);
  if (patientAss != nullptr)
  {
    // TODO just add this to a list?
    // Not doing anything with this, assessment actions
    // are currently only being handled by the Engine ScenarioExec methods.
    // Which probably just write out the assessment requested to a file
    // Assessments are really a real time API thing, not really a scenario thing
    // If they are a scenario thing, its just to write out the data.
    return true;//?
  }

  // We are creating our own copy of these actions
  // There can be multiple actions in a Scenario that are associated
  // with a specific function, such as hemorrhage, and we only need
  // to have a single action in our list associated with a hemorrhage.
  // We just overwrite our saved action with the current state of that action
  // So if the 4 hemorrhage actions come in, and lower the rate each time for a 
  // certain compartment, we just update the single hemorrhage action associated 
  // with that compartment. 
  // SO, we make our own copy and manage that copy (i.e. by updating a single action)

  const SEAcuteStress* aStress = dynamic_cast<const SEAcuteStress*>(&action);
  if (aStress != nullptr)
  {
    if (m_AcuteStress == nullptr)
      m_AcuteStress = new SEAcuteStress();
    any.set_allocated_acutestress(SEAcuteStress::Unload(*aStress));
    SEAcuteStress::Load(any.acutestress(), *m_AcuteStress);
    if (!m_AcuteStress->IsActive())
      RemoveAcuteStress();
    return true;
  }

  const SEAirwayObstruction* airwayObst = dynamic_cast<const SEAirwayObstruction*>(&action);
  if (airwayObst != nullptr)
  {
    if (m_AirwayObstruction == nullptr)
      m_AirwayObstruction = new SEAirwayObstruction();
    any.set_allocated_airwayobstruction(SEAirwayObstruction::Unload(*airwayObst));
    SEAirwayObstruction::Load(any.airwayobstruction(), *m_AirwayObstruction);
    if (!m_AirwayObstruction->IsActive())
      RemoveAirwayObstruction();
    return true;
  }

  const SEApnea* apnea = dynamic_cast<const SEApnea*>(&action);
  if (apnea != nullptr)
  {
    if (m_Apnea == nullptr)
      m_Apnea = new SEApnea();
    any.set_allocated_apnea(SEApnea::Unload(*apnea));
    SEApnea::Load(any.apnea(), *m_Apnea);
    if (!m_Apnea->IsActive())
      RemoveApnea();
    return true;
  }

  const SEAsthmaAttack* asthmaattack = dynamic_cast<const SEAsthmaAttack*>(&action);
  if (asthmaattack != nullptr)
  {
    if (m_AsthmaAttack == nullptr)
      m_AsthmaAttack = new SEAsthmaAttack();
    any.set_allocated_asthmaattack(SEAsthmaAttack::Unload(*asthmaattack));
    SEAsthmaAttack::Load(any.asthmaattack(), *m_AsthmaAttack);
    if (!m_AsthmaAttack->IsActive())
      RemoveAsthmaAttack();
    return true;
  }

  const SEBrainInjury* brainInjury = dynamic_cast<const SEBrainInjury*>(&action);
  if (brainInjury != nullptr)
  {
    if (m_BrainInjury == nullptr)
      m_BrainInjury = new SEBrainInjury();
    any.set_allocated_braininjury(SEBrainInjury::Unload(*brainInjury));
    SEBrainInjury::Load(any.braininjury(), *m_BrainInjury);
    if (!m_BrainInjury->IsActive())
      RemoveBrainInjury();
    return true;
  }

  const SEBronchoconstriction* bronchoconstr = dynamic_cast<const SEBronchoconstriction*>(&action);
  if (bronchoconstr != nullptr)
  {
    if (m_Bronchoconstriction == nullptr)
      m_Bronchoconstriction = new SEBronchoconstriction();
    any.set_allocated_bronchoconstriction(SEBronchoconstriction::Unload(*bronchoconstr));
    SEBronchoconstriction::Load(any.bronchoconstriction(), *m_Bronchoconstriction);
    if (!m_Bronchoconstriction->IsActive())
      RemoveBronchoconstriction();
    return true;
  }

  const SECardiacArrest* cardiacarrest = dynamic_cast<const SECardiacArrest*>(&action);
  if (cardiacarrest != nullptr)
  {
    if (m_CardiacArrest == nullptr)
      m_CardiacArrest = new SECardiacArrest();
    any.set_allocated_cardiacarrest(SECardiacArrest::Unload(*cardiacarrest));
    SECardiacArrest::Load(any.cardiacarrest(), *m_CardiacArrest);
    if (!m_CardiacArrest->IsActive())
      RemoveCardiacArrest();
    return true;
  }

  const SEChestCompression* chestcomp = dynamic_cast<const SEChestCompression*>(&action);
  if (chestcomp != nullptr)
  {
    const SEChestCompressionForce* cprForce = dynamic_cast<const SEChestCompressionForce*>(chestcomp);
    if (cprForce != nullptr)
    {
      if (HasChestCompressionForceScale())
        RemoveChestCompression();
      if (m_ChestCompression == nullptr)
        m_ChestCompression = new SEChestCompressionForce();
      any.set_allocated_chestcompressionforce(SEChestCompressionForce::Unload(*cprForce));
      SEChestCompressionForce::Load(any.chestcompressionforce(), (SEChestCompressionForce&)*m_ChestCompression);
      if (!m_ChestCompression->IsActive())
        RemoveChestCompression();
      return true;
    }
    const SEChestCompressionForceScale* cprScale = dynamic_cast<const SEChestCompressionForceScale*>(chestcomp);
    if (cprScale != nullptr)
    {
      if (HasChestCompressionForce())
        RemoveChestCompression();
      if (m_ChestCompression == nullptr)
        m_ChestCompression = new SEChestCompressionForceScale();
      any.set_allocated_chestcompressionforcescale(SEChestCompressionForceScale::Unload(*cprScale));
      SEChestCompressionForceScale::Load(any.chestcompressionforcescale(), (SEChestCompressionForceScale&)*m_ChestCompression);
      if (!m_ChestCompression->IsActive())
        RemoveChestCompression();
      return true;
    }
    Error("Unknown Chest Compression Type");
    /// \error Unknown ChestCompression type 
    return false;
  }


  const SEChestOcclusiveDressing* chestOccl = dynamic_cast<const SEChestOcclusiveDressing*>(&action);
  if (chestOccl != nullptr)
  {
    if (chestOccl->GetSide() == cdm::eSide::Left)
    {
      if (m_LeftChestOcclusiveDressing == nullptr)
        m_LeftChestOcclusiveDressing = new SEChestOcclusiveDressing();
      any.set_allocated_chestocclusivedressing(SEChestOcclusiveDressing::Unload(*chestOccl));
      SEChestOcclusiveDressing::Load(any.chestocclusivedressing(), *m_LeftChestOcclusiveDressing);
      if (!m_LeftChestOcclusiveDressing->IsActive())
        RemoveLeftChestOcclusiveDressing();
      return true;
    }
    else if (chestOccl->GetSide() == cdm::eSide::Right)
    {
      if (m_RightChestOcclusiveDressing == nullptr)
        m_RightChestOcclusiveDressing = new SEChestOcclusiveDressing();
      any.set_allocated_chestocclusivedressing(SEChestOcclusiveDressing::Unload(*chestOccl));
      SEChestOcclusiveDressing::Load(any.chestocclusivedressing(), *m_RightChestOcclusiveDressing);
      if (!m_RightChestOcclusiveDressing->IsActive())
        RemoveRightChestOcclusiveDressing();
      return true;
    }
  }

  const SEConsciousRespiration* conResp = dynamic_cast<const SEConsciousRespiration*>(&action);
  if (conResp != nullptr)
  {
    if (m_ConsciousRespiration == nullptr)
      m_ConsciousRespiration = new SEConsciousRespiration();
    any.set_allocated_consciousrespiration(SEConsciousRespiration::Unload(*conResp));
    SEConsciousRespiration::Load(any.consciousrespiration(), *m_ConsciousRespiration);
    if (!m_ConsciousRespiration->IsActive())
      RemoveConsciousRespiration();
    return true;
  }

  const SEConsumeNutrients* consume = dynamic_cast<const SEConsumeNutrients*>(&action);
  if (consume != nullptr)
  {
    if (m_ConsumeNutrients == nullptr)
      m_ConsumeNutrients = new SEConsumeNutrients();
    any.set_allocated_consumenutrients(SEConsumeNutrients::Unload(*consume));
    SEConsumeNutrients::Load(any.consumenutrients(), *m_ConsumeNutrients);
    if (!m_ConsumeNutrients->IsActive())
      RemoveConsumeNutrients();
    return true;
  }

  const SEExercise* exercise = dynamic_cast<const SEExercise*>(&action);
  if (exercise != nullptr)
  {
    if (m_Exercise == nullptr)
      m_Exercise = new SEExercise();
    any.set_allocated_exercise(SEExercise::Unload(*exercise));
    SEExercise::Load(any.exercise(), *m_Exercise);
    if (!m_Exercise->IsActive())
      RemoveExercise();
    return true;
  }

  const SEHemorrhage* hem = dynamic_cast<const SEHemorrhage*>(&action);
  if (hem != nullptr)
  {
    SEHemorrhage* myHem = m_Hemorrhages[hem->GetCompartment()];
    if (myHem == nullptr)
    {
      myHem = new SEHemorrhage();
      m_Hemorrhages[hem->GetCompartment()] = myHem;
    }
    any.set_allocated_hemorrhage(SEHemorrhage::Unload(*hem));
    SEHemorrhage::Load(any.hemorrhage(), *myHem);
    if (!myHem->IsActive())
      RemoveHemorrhage(hem->GetCompartment());
    return true;
  }

  const SEIntubation* intubation = dynamic_cast<const SEIntubation*>(&action);
  if (intubation != nullptr)
  {
    if (m_Intubation == nullptr)
      m_Intubation = new SEIntubation();
    any.set_allocated_intubation(SEIntubation::Unload(*intubation));
    SEIntubation::Load(any.intubation(), *m_Intubation);
    if (!m_Intubation->IsActive())
      RemoveIntubation();
    return true;
  }

  const SEMechanicalVentilation* mvData = dynamic_cast<const SEMechanicalVentilation*>(&action);
  if (mvData != nullptr)
  {
    if (m_MechanicalVentilation == nullptr)
      m_MechanicalVentilation = new SEMechanicalVentilation();
    any.set_allocated_mechanicalventilation(SEMechanicalVentilation::Unload(*mvData));
    SEMechanicalVentilation::Load(any.mechanicalventilation(), *m_MechanicalVentilation, m_Substances);
    if (!m_MechanicalVentilation->IsActive())
      RemoveMechanicalVentilation();
    return true;
  }

  const SENeedleDecompression* needleDecomp = dynamic_cast<const SENeedleDecompression*>(&action);
  if (needleDecomp != nullptr)
  {
    if (needleDecomp->GetSide() == cdm::eSide::Left)
    {
      if (m_LeftNeedleDecompression == nullptr)
        m_LeftNeedleDecompression = new SENeedleDecompression();
      any.set_allocated_needledecompression(SENeedleDecompression::Unload(*needleDecomp));
      SENeedleDecompression::Load(any.needledecompression(), *m_LeftNeedleDecompression);
      if (!m_LeftNeedleDecompression->IsActive())
        RemoveLeftNeedleDecompression();
      return true;
    }
    else if (needleDecomp->GetSide() == cdm::eSide::Right)
    {
      if (m_RightNeedleDecompression == nullptr)
        m_RightNeedleDecompression = new SENeedleDecompression();
      any.set_allocated_needledecompression(SENeedleDecompression::Unload(*needleDecomp));
      SENeedleDecompression::Load(any.needledecompression(), *m_RightNeedleDecompression);
      if (!m_RightNeedleDecompression->IsActive())
        RemoveRightNeedleDecompression();
      return true;
    }
    Error("Unknown Needle Decompression Type");
    return false;
  }

  const SEPericardialEffusion* pericardialEff = dynamic_cast<const SEPericardialEffusion*>(&action);
  if (pericardialEff != nullptr)
  {
    if (m_PericardialEffusion == nullptr)
      m_PericardialEffusion = new SEPericardialEffusion();
    any.set_allocated_pericardialeffusion(SEPericardialEffusion::Unload(*pericardialEff));
    SEPericardialEffusion::Load(any.pericardialeffusion(), *m_PericardialEffusion);
    if (!m_PericardialEffusion->IsActive())
      RemovePericardialEffusion();
    return true;

  }

  const SESubstanceBolus* bolus = dynamic_cast<const SESubstanceBolus*>(&action);
  if (bolus != nullptr)
  {
    SESubstance* sub = m_Substances.GetSubstance(bolus->GetSubstance().GetName());
    if (sub == nullptr)//Make sure this substance manager has it
    {
      Error("Ignoring SESubstanceBolus action due to unknown substance in action: " + bolus->GetSubstance().GetName());
      return false;
    }
    SESubstanceBolus* myBolus = m_SubstanceBolus[sub];
    if (myBolus == nullptr)
    {
      myBolus = new SESubstanceBolus(*sub);
      m_SubstanceBolus[sub] = myBolus;
      m_Substances.AddActiveSubstance(*sub);
    }
    any.set_allocated_substancebolus(SESubstanceBolus::Unload(*bolus));
    SESubstanceBolus::Load(any.substancebolus(), *myBolus);
    if (!myBolus->IsActive())
      RemoveSubstanceBolus(*sub);
    return true;
  }

  const SESubstanceInfusion* subInfusion = dynamic_cast<const SESubstanceInfusion*>(&action);
  if (subInfusion != nullptr)
  {
    SESubstance* sub = m_Substances.GetSubstance(subInfusion->GetSubstance().GetName());
    if (sub == nullptr)//Make sure this substance manager has it
    {
      Error("Ignoring SESubstanceInfusion action due to unknown substance in action: " + subInfusion->GetSubstance().GetName());
      return false;
    }
    SESubstanceInfusion* mySubInfuse = m_SubstanceInfusions[sub];
    if (mySubInfuse == nullptr)
    {
      mySubInfuse = new SESubstanceInfusion(*sub);
      m_SubstanceInfusions[sub] = mySubInfuse;
      m_Substances.AddActiveSubstance(*sub);
    }
    any.set_allocated_substanceinfusion(SESubstanceInfusion::Unload(*subInfusion));
    SESubstanceInfusion::Load(any.substanceinfusion(), *mySubInfuse);
    if (!mySubInfuse->IsActive())
      RemoveSubstanceInfusion(*sub);
    return true;
  }

  const SESubstanceCompoundInfusion* cSubInfusion = dynamic_cast<const SESubstanceCompoundInfusion*>(&action);
  if (cSubInfusion != nullptr)
  {
    SESubstanceCompound* cmpd = m_Substances.GetCompound(cSubInfusion->GetSubstanceCompound().GetName());
    if (cmpd == nullptr)//Make sure this substance manager has it
    {
      Error("Ignoring SESubstanceCompoundInfusion action due to unknown substance in action: " + cSubInfusion->GetSubstanceCompound().GetName());
      return false;
    }
    SESubstanceCompoundInfusion* mySubCompInfuse = m_SubstanceCompoundInfusions[cmpd];
    if (mySubCompInfuse == nullptr)
    {
      mySubCompInfuse = new SESubstanceCompoundInfusion(*cmpd);
      m_SubstanceCompoundInfusions[cmpd] = mySubCompInfuse;
      m_Substances.AddActiveCompound(*cmpd);
      // Activate the compound component substances
      const SESubstanceCompound& sc = mySubCompInfuse->GetSubstanceCompound();
      for (const SESubstanceConcentration* scc : sc.GetComponents())
      {
        m_Substances.AddActiveSubstance(scc->GetSubstance());
      }
    }
    any.set_allocated_substancecompoundinfusion(SESubstanceCompoundInfusion::Unload(*cSubInfusion));
    SESubstanceCompoundInfusion::Load(any.substancecompoundinfusion(), *mySubCompInfuse);
    if (!mySubCompInfuse->IsActive())
      RemoveSubstanceCompoundInfusion(*cmpd);
    return true;
  }

  const SETensionPneumothorax* pneumo = dynamic_cast<const SETensionPneumothorax*>(&action);
  if (pneumo != nullptr)
  {
    if (pneumo->GetSide() == cdm::eSide::Left&&pneumo->GetType() == cdm::eGate::Open)
    {
      if (m_LeftOpenTensionPneumothorax == nullptr)
        m_LeftOpenTensionPneumothorax = new SETensionPneumothorax();
      any.set_allocated_tensionpneumothorax(SETensionPneumothorax::Unload(*pneumo));
      SETensionPneumothorax::Load(any.tensionpneumothorax(), *m_LeftOpenTensionPneumothorax);
      if (!m_LeftOpenTensionPneumothorax->IsActive())
        RemoveLeftOpenTensionPneumothorax();
      return true;
    }
    else if (pneumo->GetSide() == cdm::eSide::Left&&pneumo->GetType() == cdm::eGate::Closed)
    {
      if (m_LeftClosedTensionPneumothorax == nullptr)
        m_LeftClosedTensionPneumothorax = new SETensionPneumothorax();
      any.set_allocated_tensionpneumothorax(SETensionPneumothorax::Unload(*pneumo));
      SETensionPneumothorax::Load(any.tensionpneumothorax(), *m_LeftClosedTensionPneumothorax);
      if (!m_LeftClosedTensionPneumothorax->IsActive())
        RemoveLeftClosedTensionPneumothorax();
      return true;
    }
    else if (pneumo->GetSide() == cdm::eSide::Right&&pneumo->GetType() == cdm::eGate::Open)
    {
      if (m_RightOpenTensionPneumothorax == nullptr)
        m_RightOpenTensionPneumothorax = new SETensionPneumothorax();
      any.set_allocated_tensionpneumothorax(SETensionPneumothorax::Unload(*pneumo));
      SETensionPneumothorax::Load(any.tensionpneumothorax(), *m_RightOpenTensionPneumothorax);
      if (!m_RightOpenTensionPneumothorax->IsActive())
        RemoveRightOpenTensionPneumothorax();
      return true;
    }
    else if (pneumo->GetSide() == cdm::eSide::Right&&pneumo->GetType() == cdm::eGate::Closed)
    {
      if (m_RightClosedTensionPneumothorax == nullptr)
        m_RightClosedTensionPneumothorax = new SETensionPneumothorax();
      any.set_allocated_tensionpneumothorax(SETensionPneumothorax::Unload(*pneumo));
      SETensionPneumothorax::Load(any.tensionpneumothorax(), *m_RightClosedTensionPneumothorax);
      if (!m_RightClosedTensionPneumothorax->IsActive())
        RemoveRightClosedTensionPneumothorax();
      return true;
    }
    Error("Unknown Tension Pnumothorax Type");
    return false;// Duno what this is...
  }

  const SEUrinate* urinate = dynamic_cast<const SEUrinate*>(&action);
  if (urinate != nullptr)
  {
    if (m_Urinate == nullptr)
      m_Urinate = new SEUrinate();
    any.set_allocated_urinate(SEUrinate::Unload(*urinate));
    SEUrinate::Load(any.urinate(), *m_Urinate);
    if (!m_Urinate->IsActive())
      RemoveUrinate();
    return true;
  }

  /// \error Unsupported Action
  Error("Unsupported Action");
  return false;
}

bool SEPatientActionCollection::HasAcuteStress() const
{
  return m_AcuteStress == nullptr ? false : m_AcuteStress->IsActive();
}
SEAcuteStress* SEPatientActionCollection::GetAcuteStress() const
{
  return m_AcuteStress;
}
void SEPatientActionCollection::RemoveAcuteStress()
{
  SAFE_DELETE(m_AcuteStress);
}

bool SEPatientActionCollection::HasAirwayObstruction() const
{
  return m_AirwayObstruction == nullptr ? false : m_AirwayObstruction->IsActive();
}
SEAirwayObstruction* SEPatientActionCollection::GetAirwayObstruction() const
{
  return m_AirwayObstruction;
}
void SEPatientActionCollection::RemoveAirwayObstruction()
{
  SAFE_DELETE(m_AirwayObstruction);
}

bool SEPatientActionCollection::HasApnea() const
{
  return m_Apnea == nullptr ? false : m_Apnea->IsActive();
}
SEApnea* SEPatientActionCollection::GetApnea() const
{
  return m_Apnea;
}
void SEPatientActionCollection::RemoveApnea()
{
  SAFE_DELETE(m_Apnea);
}

bool SEPatientActionCollection::HasAsthmaAttack() const
{
  return m_AsthmaAttack == nullptr ? false : m_AsthmaAttack->IsActive();
}
SEAsthmaAttack* SEPatientActionCollection::GetAsthmaAttack() const
{
  return m_AsthmaAttack;
}
void SEPatientActionCollection::RemoveAsthmaAttack()
{
  SAFE_DELETE(m_AsthmaAttack);
}

bool SEPatientActionCollection::HasBrainInjury() const
{
  return m_BrainInjury == nullptr ? false : m_BrainInjury->IsActive();
}
SEBrainInjury* SEPatientActionCollection::GetBrainInjury() const
{
  return m_BrainInjury;
}
void SEPatientActionCollection::RemoveBrainInjury()
{
  SAFE_DELETE(m_BrainInjury);
}

bool SEPatientActionCollection::HasBronchoconstriction() const
{
  return m_Bronchoconstriction == nullptr ? false : m_Bronchoconstriction->IsActive();
}
SEBronchoconstriction* SEPatientActionCollection::GetBronchoconstriction() const
{
  return m_Bronchoconstriction;
}
void SEPatientActionCollection::RemoveBronchoconstriction()
{
  SAFE_DELETE(m_Bronchoconstriction);
}

bool SEPatientActionCollection::HasCardiacArrest() const
{
  return m_CardiacArrest == nullptr ? false : m_CardiacArrest->IsActive();
}
SECardiacArrest* SEPatientActionCollection::GetCardiacArrest() const
{
  return m_CardiacArrest;
}
void SEPatientActionCollection::RemoveCardiacArrest()
{
  SAFE_DELETE(m_CardiacArrest);
}

bool SEPatientActionCollection::HasChestCompression() const
{
  return m_ChestCompression == nullptr ? false : m_ChestCompression->IsActive();
}
void SEPatientActionCollection::RemoveChestCompression()
{
  SAFE_DELETE(m_ChestCompression);
}
bool SEPatientActionCollection::HasChestCompressionForce() const
{
  return m_ChestCompression == nullptr ? false : m_ChestCompression->IsActive();
}
SEChestCompressionForce* SEPatientActionCollection::GetChestCompressionForce() const
{
  return dynamic_cast<SEChestCompressionForce*>(m_ChestCompression);
}
bool SEPatientActionCollection::HasChestCompressionForceScale() const
{
  return m_ChestCompression == nullptr ? false : m_ChestCompression->IsActive();
}
SEChestCompressionForceScale* SEPatientActionCollection::GetChestCompressionForceScale() const
{
  return dynamic_cast<SEChestCompressionForceScale*>(m_ChestCompression);
}

bool SEPatientActionCollection::HasChestOcclusiveDressing() const
{
  return HasLeftChestOcclusiveDressing() || HasRightChestOcclusiveDressing();
}
bool SEPatientActionCollection::HasLeftChestOcclusiveDressing() const
{
  return m_LeftChestOcclusiveDressing == nullptr ? false : m_LeftChestOcclusiveDressing->IsActive();
}
SEChestOcclusiveDressing* SEPatientActionCollection::GetLeftChestOcclusiveDressing() const
{
  return m_LeftChestOcclusiveDressing;
}
void SEPatientActionCollection::RemoveLeftChestOcclusiveDressing()
{
  SAFE_DELETE(m_LeftChestOcclusiveDressing);
}
bool SEPatientActionCollection::HasRightChestOcclusiveDressing() const
{
  return m_RightChestOcclusiveDressing == nullptr ? false : m_RightChestOcclusiveDressing->IsActive();
}
SEChestOcclusiveDressing* SEPatientActionCollection::GetRightChestOcclusiveDressing() const
{
  return m_RightChestOcclusiveDressing;
}
void SEPatientActionCollection::RemoveRightChestOcclusiveDressing()
{
  SAFE_DELETE(m_RightChestOcclusiveDressing);
}

bool SEPatientActionCollection::HasConsciousRespiration() const
{
  return m_ConsciousRespiration == nullptr ? false : m_ConsciousRespiration->IsActive();
}
SEConsciousRespiration* SEPatientActionCollection::GetConsciousRespiration() const
{
  return m_ConsciousRespiration;
}
void SEPatientActionCollection::RemoveConsciousRespiration()
{
  SAFE_DELETE(m_ConsciousRespiration);
}

bool SEPatientActionCollection::HasConsumeNutrients() const
{
  return m_ConsumeNutrients == nullptr ? false : m_ConsumeNutrients->IsActive();
}
SEConsumeNutrients* SEPatientActionCollection::GetConsumeNutrients() const
{
  return m_ConsumeNutrients;
}
void SEPatientActionCollection::RemoveConsumeNutrients()
{
  SAFE_DELETE(m_ConsumeNutrients);
}

bool SEPatientActionCollection::HasExercise() const
{
  return m_Exercise == nullptr ? false : m_Exercise->IsActive();
}
SEExercise* SEPatientActionCollection::GetExercise() const
{
  return m_Exercise;
}
void SEPatientActionCollection::RemoveExercise()
{
  SAFE_DELETE(m_Exercise);
}

bool SEPatientActionCollection::HasHemorrhage() const
{
  return m_Hemorrhages.empty() ? false : true;
}
const std::map<std::string, SEHemorrhage*>& SEPatientActionCollection::GetHemorrhages() const
{
  return m_Hemorrhages;
}
void SEPatientActionCollection::RemoveHemorrhage(const std::string& cmpt)
{
  SEHemorrhage* h = m_Hemorrhages[cmpt];
  m_Hemorrhages.erase(cmpt);
  SAFE_DELETE(h);
}

bool SEPatientActionCollection::HasIntubation() const
{
  return m_Intubation == nullptr ? false : m_Intubation->IsActive();
}
SEIntubation* SEPatientActionCollection::GetIntubation() const
{
  return m_Intubation;
}
void SEPatientActionCollection::RemoveIntubation()
{
  SAFE_DELETE(m_Intubation);
}

bool SEPatientActionCollection::HasMechanicalVentilation() const
{
  return m_MechanicalVentilation == nullptr ? false : m_MechanicalVentilation->IsActive();
}
SEMechanicalVentilation* SEPatientActionCollection::GetMechanicalVentilation() const
{
  return m_MechanicalVentilation;
}
void SEPatientActionCollection::RemoveMechanicalVentilation()
{
  SAFE_DELETE(m_MechanicalVentilation);
}

bool SEPatientActionCollection::HasNeedleDecompression() const
{
  return HasLeftNeedleDecompression() || HasRightNeedleDecompression();
}
bool SEPatientActionCollection::HasLeftNeedleDecompression() const
{
  return m_LeftNeedleDecompression == nullptr ? false : m_LeftNeedleDecompression->IsActive();
}
SENeedleDecompression* SEPatientActionCollection::GetLeftNeedleDecompression() const
{
  return m_LeftNeedleDecompression;
}
void SEPatientActionCollection::RemoveLeftNeedleDecompression()
{
  SAFE_DELETE(m_LeftNeedleDecompression);
}
bool SEPatientActionCollection::HasRightNeedleDecompression() const
{
  return m_RightNeedleDecompression == nullptr ? false : m_RightNeedleDecompression->IsActive();
}
SENeedleDecompression* SEPatientActionCollection::GetRightNeedleDecompression() const
{
  return m_RightNeedleDecompression;
}
void SEPatientActionCollection::RemoveRightNeedleDecompression()
{
  SAFE_DELETE(m_RightNeedleDecompression);
}

bool SEPatientActionCollection::HasPericardialEffusion() const
{
  return m_PericardialEffusion == nullptr ? false : m_PericardialEffusion->IsActive();
}
SEPericardialEffusion* SEPatientActionCollection::GetPericardialEffusion() const
{
  return m_PericardialEffusion;
}
void SEPatientActionCollection::RemovePericardialEffusion()
{
  SAFE_DELETE(m_PericardialEffusion);
}

bool SEPatientActionCollection::HasTensionPneumothorax() const
{
  if (m_LeftOpenTensionPneumothorax != nullptr&&m_LeftOpenTensionPneumothorax->IsActive())
    return true;
  if (m_LeftClosedTensionPneumothorax != nullptr&&m_LeftClosedTensionPneumothorax->IsActive())
    return true;
  if (m_RightOpenTensionPneumothorax != nullptr&&m_RightOpenTensionPneumothorax->IsActive())
    return true;
  if (m_RightClosedTensionPneumothorax != nullptr&&m_RightClosedTensionPneumothorax->IsActive())
    return true;
  return false;
}
bool SEPatientActionCollection::HasLeftOpenTensionPneumothorax() const
{
  if (m_LeftOpenTensionPneumothorax != nullptr&&m_LeftOpenTensionPneumothorax->IsActive())
    return true;
  return false;
}
SETensionPneumothorax* SEPatientActionCollection::GetLeftOpenTensionPneumothorax() const
{
  return m_LeftOpenTensionPneumothorax;
}
void SEPatientActionCollection::RemoveLeftOpenTensionPneumothorax()
{
  SAFE_DELETE(m_LeftOpenTensionPneumothorax);
}
bool SEPatientActionCollection::HasLeftClosedTensionPneumothorax() const
{
  if (m_LeftClosedTensionPneumothorax != nullptr&&m_LeftClosedTensionPneumothorax->IsActive())
    return true;
  return false;
}
SETensionPneumothorax* SEPatientActionCollection::GetLeftClosedTensionPneumothorax() const
{
  return m_LeftClosedTensionPneumothorax;
}
void SEPatientActionCollection::RemoveLeftClosedTensionPneumothorax()
{
  SAFE_DELETE(m_LeftClosedTensionPneumothorax);
}
bool SEPatientActionCollection::HasRightOpenTensionPneumothorax() const
{
  if (m_RightOpenTensionPneumothorax != nullptr&&m_RightOpenTensionPneumothorax->IsActive())
    return true;
  return false;
}
SETensionPneumothorax* SEPatientActionCollection::GetRightOpenTensionPneumothorax() const
{
  return m_RightOpenTensionPneumothorax;
}
void SEPatientActionCollection::RemoveRightOpenTensionPneumothorax()
{
  SAFE_DELETE(m_RightOpenTensionPneumothorax);
}
bool SEPatientActionCollection::HasRightClosedTensionPneumothorax() const
{
  if (m_RightClosedTensionPneumothorax != nullptr&&m_RightClosedTensionPneumothorax->IsActive())
    return true;
  return false;
}
SETensionPneumothorax* SEPatientActionCollection::GetRightClosedTensionPneumothorax() const
{
  return m_RightClosedTensionPneumothorax;
}
void SEPatientActionCollection::RemoveRightClosedTensionPneumothorax()
{
  SAFE_DELETE(m_RightClosedTensionPneumothorax);
}

const std::map<const SESubstance*, SESubstanceBolus*>& SEPatientActionCollection::GetSubstanceBoluses() const
{
  return m_SubstanceBolus;
}
void SEPatientActionCollection::RemoveSubstanceBolus(const SESubstance& sub)
{
  SESubstanceBolus* b = m_SubstanceBolus[&sub];
  m_SubstanceBolus.erase(&sub);
  SAFE_DELETE(b);
}

const std::map<const SESubstance*, SESubstanceInfusion*>& SEPatientActionCollection::GetSubstanceInfusions() const
{
  return m_SubstanceInfusions;
}
void SEPatientActionCollection::RemoveSubstanceInfusion(const SESubstance& sub)
{
  SESubstanceInfusion* si = m_SubstanceInfusions[&sub];
  m_SubstanceInfusions.erase(&sub);
  SAFE_DELETE(si);
}

const std::map<const SESubstanceCompound*, SESubstanceCompoundInfusion*>& SEPatientActionCollection::GetSubstanceCompoundInfusions() const
{
  return m_SubstanceCompoundInfusions;
}
void SEPatientActionCollection::RemoveSubstanceCompoundInfusion(const SESubstanceCompound& cSub)
{
  SESubstanceCompoundInfusion* sci = m_SubstanceCompoundInfusions[&cSub];
  m_SubstanceCompoundInfusions.erase(&cSub);
  SAFE_DELETE(sci);
}

bool SEPatientActionCollection::HasUrinate() const
{
  return m_Urinate == nullptr ? false : m_Urinate->IsActive();
}
SEUrinate* SEPatientActionCollection::GetUrinate() const
{
  return m_Urinate;
}
void SEPatientActionCollection::RemoveUrinate()
{
  SAFE_DELETE(m_Urinate);
}
