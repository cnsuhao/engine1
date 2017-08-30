/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEPatientAction.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SEPatientAction::SEPatientAction() : SEAction()
{
  
}

SEPatientAction::~SEPatientAction()
{
  Clear();
}

void SEPatientAction::Clear()
{
  SEAction::Clear();
}

bool SEPatientAction::IsValid() const
{
  return SEAction::IsValid();
}

void SEPatientAction::Serialize(const cdm::PatientActionData& src, SEPatientAction& dst)
{
  SEAction::Serialize(src.action(), dst);
}

void SEPatientAction::Serialize(const SEPatientAction& src, cdm::PatientActionData& dst)
{
  SEAction::Serialize(src, *dst.mutable_action());
}

#include "substance/SESubstanceManager.h"
#include "patient/actions/SEPatientAssessmentRequest.h"
#include "patient/actions/SEAcuteStress.h"
#include "patient/actions/SEAirwayObstruction.h"
#include "patient/actions/SEApnea.h"
#include "patient/actions/SEAsthmaAttack.h"
#include "patient/actions/SEBrainInjury.h"
#include "patient/actions/SEBronchoconstriction.h"
#include "patient/actions/SECardiacArrest.h"
#include "patient/actions/SEChestCompressionForce.h"
#include "patient/actions/SEChestCompressionForceScale.h"
#include "patient/actions/SEChestOcclusiveDressing.h"
#include "patient/actions/SEConsciousRespiration.h"
#include "patient/actions/SEConsumeNutrients.h"
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
SEPatientAction* SEPatientAction::Load(const cdm::AnyPatientActionData& any, SESubstanceManager& subMgr)
{
  switch (any.Action_case())
  {
    case cdm::AnyPatientActionData::ActionCase::kAssessment:
    {
      SEPatientAssessmentRequest* a = new SEPatientAssessmentRequest();
      SEPatientAssessmentRequest::Load(any.assessment(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kAcuteStress:
    {
      SEAcuteStress* a = new SEAcuteStress();
      SEAcuteStress::Load(any.acutestress(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kAirwayObstruction:
    {
      SEAirwayObstruction* a = new SEAirwayObstruction();
      SEAirwayObstruction::Load(any.airwayobstruction(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kApnea:
    {
      SEApnea* a = new SEApnea();
      SEApnea::Load(any.apnea(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kAsthmaAttack:
    {
      SEAsthmaAttack* a = new SEAsthmaAttack();
      SEAsthmaAttack::Load(any.asthmaattack(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kBrainInjury:
    {
      SEBrainInjury* a = new SEBrainInjury();
      SEBrainInjury::Load(any.braininjury(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kBronchoconstriction:
    {
      SEBronchoconstriction* a = new SEBronchoconstriction();
      SEBronchoconstriction::Load(any.bronchoconstriction(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kCardiacArrest:
    {
      SECardiacArrest* a = new SECardiacArrest();
      SECardiacArrest::Load(any.cardiacarrest(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kChestCompressionForce:
    {
      SEChestCompressionForce* a = new SEChestCompressionForce();
      SEChestCompressionForce::Load(any.chestcompressionforce(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kChestCompressionForceScale:
    {
      SEChestCompressionForceScale* a = new SEChestCompressionForceScale();
      SEChestCompressionForceScale::Load(any.chestcompressionforcescale(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kChestOcclusiveDressing:
    {
      SEChestOcclusiveDressing* a = new SEChestOcclusiveDressing();
      SEChestOcclusiveDressing::Load(any.chestocclusivedressing(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kConsciousRespiration:
    {
      SEConsciousRespiration* a = new SEConsciousRespiration();
      SEConsciousRespiration::Load(any.consciousrespiration(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kConsumeNutrients:
    {
      SEConsumeNutrients* a = new SEConsumeNutrients();
      SEConsumeNutrients::Load(any.consumenutrients(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kExercise:
    {
      SEExercise* a = new SEExercise();
      SEExercise::Load(any.exercise(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kHemorrhage:
    {
      SEHemorrhage* a = new SEHemorrhage();
      SEHemorrhage::Load(any.hemorrhage(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kIntubation:
    {
      SEIntubation* a = new SEIntubation();
      SEIntubation::Load(any.intubation(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kMechanicalVentilation:
    {
      SEMechanicalVentilation* a = new SEMechanicalVentilation();
      SEMechanicalVentilation::Load(any.mechanicalventilation(), *a, subMgr);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kNeedleDecompression:
    {
      SENeedleDecompression* a = new SENeedleDecompression();
      SENeedleDecompression::Load(any.needledecompression(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kPericardialEffusion:
    {
      SEPericardialEffusion* a = new SEPericardialEffusion();
      SEPericardialEffusion::Load(any.pericardialeffusion(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kSubstanceBolus:
    {
      SESubstance* sub = subMgr.GetSubstance(any.substancebolus().substance());
      if (sub == nullptr)
      {
        subMgr.Error("Unknown substance " + any.substancebolus().substance(), "SEPatientAction::Load");
        return nullptr;
      }
      SESubstanceBolus* a = new SESubstanceBolus(*sub);
      SESubstanceBolus::Load(any.substancebolus(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kSubstanceInfusion:
    {
      SESubstance* sub = subMgr.GetSubstance(any.substanceinfusion().substance());
      if (sub == nullptr)
      {
        subMgr.Error("Unknown substance " + any.substanceinfusion().substance(), "SEPatientAction::Load");
        return nullptr;
      }
      SESubstanceInfusion* a = new SESubstanceInfusion(*sub);
      SESubstanceInfusion::Load(any.substanceinfusion(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kSubstanceCompoundInfusion:
    {
      SESubstanceCompound* subC = subMgr.GetCompound(any.substancecompoundinfusion().substancecompound());
      if (subC == nullptr)
      {
        subMgr.Error("Unknown substance compound " + any.substancecompoundinfusion().substancecompound(), "SEPatientAction::Load");
        return nullptr;
      }
      SESubstanceCompoundInfusion* a = new SESubstanceCompoundInfusion(*subC);
      SESubstanceCompoundInfusion::Load(any.substancecompoundinfusion(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kTensionPneumothorax:
    {
      SETensionPneumothorax* a = new SETensionPneumothorax();
      SETensionPneumothorax::Load(any.tensionpneumothorax(), *a);
      return a;
    }
    case cdm::AnyPatientActionData::ActionCase::kUrinate:
    {
      SEUrinate* a = new SEUrinate();
      SEUrinate::Load(any.urinate(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown action type : " + any.Action_case());
  return nullptr;
}
cdm::AnyPatientActionData* SEPatientAction::Unload(const SEPatientAction& action)
{
  cdm::AnyPatientActionData* any = new cdm::AnyPatientActionData();
  const SEPatientAssessmentRequest* ar = dynamic_cast<const SEPatientAssessmentRequest*>(&action);
  if (ar != nullptr)
  {
    any->set_allocated_assessment(SEPatientAssessmentRequest::Unload(*ar));
    return any;
  }
  const SEAcuteStress* as = dynamic_cast<const SEAcuteStress*>(&action);
  if (as != nullptr)
  {
    any->set_allocated_acutestress(SEAcuteStress::Unload(*as));
    return any;
  }
  const SEAirwayObstruction* ao = dynamic_cast<const SEAirwayObstruction*>(&action);
  if (ao != nullptr)
  {
    any->set_allocated_airwayobstruction(SEAirwayObstruction::Unload(*ao));
    return any;
  }
  const SEApnea* a = dynamic_cast<const SEApnea*>(&action);
  if (a != nullptr)
  {
    any->set_allocated_apnea(SEApnea::Unload(*a));
    return any;
  }
  const SEAsthmaAttack* aa = dynamic_cast<const SEAsthmaAttack*>(&action);
  if (aa != nullptr)
  {
    any->set_allocated_asthmaattack(SEAsthmaAttack::Unload(*aa));
    return any;
  }
  const SEBrainInjury* bi = dynamic_cast<const SEBrainInjury*>(&action);
  if (bi != nullptr)
  {
    any->set_allocated_braininjury(SEBrainInjury::Unload(*bi));
    return any;
  }
  const SEBronchoconstriction* b = dynamic_cast<const SEBronchoconstriction*>(&action);
  if (b != nullptr)
  {
    any->set_allocated_bronchoconstriction(SEBronchoconstriction::Unload(*b));
    return any;
  }
  const SECardiacArrest* ca = dynamic_cast<const SECardiacArrest*>(&action);
  if (ca != nullptr)
  {
    any->set_allocated_cardiacarrest(SECardiacArrest::Unload(*ca));
    return any;
  }
  const SEChestCompressionForce* ccf = dynamic_cast<const SEChestCompressionForce*>(&action);
  if (ccf != nullptr)
  {
    any->set_allocated_chestcompressionforce(SEChestCompressionForce::Unload(*ccf));
    return any;
  }
  const SEChestCompressionForceScale* ccfs = dynamic_cast<const SEChestCompressionForceScale*>(&action);
  if (ccfs != nullptr)
  {
    any->set_allocated_chestcompressionforcescale(SEChestCompressionForceScale::Unload(*ccfs));
    return any;
  }
  const SEChestOcclusiveDressing* chd = dynamic_cast<const SEChestOcclusiveDressing*>(&action);
  if (chd != nullptr)
  {
    any->set_allocated_chestocclusivedressing(SEChestOcclusiveDressing::Unload(*chd));
    return any;
  }
  const SEConsciousRespiration* cr = dynamic_cast<const SEConsciousRespiration*>(&action);
  if (cr != nullptr)
  {
    any->set_allocated_consciousrespiration(SEConsciousRespiration::Unload(*cr));
    return any;
  }
  const SEConsumeNutrients* cn = dynamic_cast<const SEConsumeNutrients*>(&action);
  if (cn != nullptr)
  {
    any->set_allocated_consumenutrients(SEConsumeNutrients::Unload(*cn));
    return any;
  }
  const SEExercise* e = dynamic_cast<const SEExercise*>(&action);
  if (e != nullptr)
  {
    any->set_allocated_exercise(SEExercise::Unload(*e));
    return any;
  }
  const SEHemorrhage* h = dynamic_cast<const SEHemorrhage*>(&action);
  if (h != nullptr)
  {
    any->set_allocated_hemorrhage(SEHemorrhage::Unload(*h));
    return any;
  }
  const SEIntubation* i = dynamic_cast<const SEIntubation*>(&action);
  if (i != nullptr)
  {
    any->set_allocated_intubation(SEIntubation::Unload(*i));
    return any;
  }
  const SEMechanicalVentilation* mv = dynamic_cast<const SEMechanicalVentilation*>(&action);
  if (mv != nullptr)
  {
    any->set_allocated_mechanicalventilation(SEMechanicalVentilation::Unload(*mv));
    return any;
  }
  const SENeedleDecompression* nd = dynamic_cast<const SENeedleDecompression*>(&action);
  if (nd != nullptr)
  {
    any->set_allocated_needledecompression(SENeedleDecompression::Unload(*nd));
    return any;
  }
  const SEPericardialEffusion* pe = dynamic_cast<const SEPericardialEffusion*>(&action);
  if (pe != nullptr)
  {
    any->set_allocated_pericardialeffusion(SEPericardialEffusion::Unload(*pe));
    return any;
  }
  const SESubstanceBolus* sb = dynamic_cast<const SESubstanceBolus*>(&action);
  if (sb != nullptr)
  {
    any->set_allocated_substancebolus(SESubstanceBolus::Unload(*sb));
    return any;
  }
  const SESubstanceInfusion* si = dynamic_cast<const SESubstanceInfusion*>(&action);
  if (si != nullptr)
  {
    any->set_allocated_substanceinfusion(SESubstanceInfusion::Unload(*si));
    return any;
  }
  const SESubstanceCompoundInfusion* sci = dynamic_cast<const SESubstanceCompoundInfusion*>(&action);
  if (sci != nullptr)
  {
    any->set_allocated_substancecompoundinfusion(SESubstanceCompoundInfusion::Unload(*sci));
    return any;
  }
  const SETensionPneumothorax* tp = dynamic_cast<const SETensionPneumothorax*>(&action);
  if (tp != nullptr)
  {
    any->set_allocated_tensionpneumothorax(SETensionPneumothorax::Unload(*tp));
    return any;
  }
  const SEUrinate* u = dynamic_cast<const SEUrinate*>(&action);
  if (u != nullptr)
  {
    any->set_allocated_urinate(SEUrinate::Unload(*u));
    return any;
  }
  delete any;
  return nullptr;
}
