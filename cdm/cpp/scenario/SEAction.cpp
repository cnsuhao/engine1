/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "scenario/SEAction.h"
#include "substance/SESubstanceManager.h"

#include "scenario/SEAdvanceTime.h"
#include "scenario/SESerializeState.h"

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

#include "patient/actions/SEPatientAction.h"
#include "system/environment/actions/SEEnvironmentAction.h"
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"
#include "system/equipment/inhaler/actions/SEInhalerAction.h"
SEAction* SEAction::Load(const cdm::AnyActionData& action, SESubstanceManager& subMgr)
{
  switch (action.Action_case())
  {
    case cdm::AnyActionData::kPatientAction:
      return SEPatientAction::Load(action.patientaction(), subMgr);
    case cdm::AnyActionData::kEnvironmentAction:
      return SEEnvironmentAction::Load(action.environmentaction(), subMgr);
    case cdm::AnyActionData::kAnesthesiaMachineAction:
      return SEAnesthesiaMachineAction::Load(action.anesthesiamachineaction(), subMgr);
    case cdm::AnyActionData::kInhalerAction:
      return SEInhalerAction::Load(action.inhaleraction(), subMgr);
    case cdm::AnyActionData::kAdvanceTime:
    {
      SEAdvanceTime* a = new SEAdvanceTime();
      SEAdvanceTime::Load(action.advancetime(), *a);
      return a;
    }
    case cdm::AnyActionData::kSerialize:
    {
      SESerializeState* a = new SESerializeState();
      SESerializeState::Load(action.serialize(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown Action");
  return nullptr;
}
cdm::AnyActionData* SEAction::Unload(const SEAction& action)
{
  cdm::AnyActionData* any = new cdm::AnyActionData();

  const SEAdvanceTime* adv = dynamic_cast<const SEAdvanceTime*>(&action);
  if (adv != nullptr)
  {
    any->set_allocated_advancetime(SEAdvanceTime::Unload(*adv));
    return any;
  }
  const SESerializeState* ss = dynamic_cast<const SESerializeState*>(&action);
  if (ss != nullptr)
  {
    any->set_allocated_serialize(SESerializeState::Unload(*ss));
    return any;
  }

  const SEPatientAction* pa = dynamic_cast<const SEPatientAction*>(&action);
  if (pa != nullptr)
  {
    any->set_allocated_patientaction(SEPatientAction::Unload(*pa));
    return any;
  }
  const SEEnvironmentAction* ea = dynamic_cast<const SEEnvironmentAction*>(&action);
  if (ea != nullptr)
  {
    any->set_allocated_environmentaction(SEEnvironmentAction::Unload(*ea));
    return any;
  }
  const SEAnesthesiaMachineAction* aa = dynamic_cast<const SEAnesthesiaMachineAction*>(&action);
  if (aa != nullptr)
  {
    any->set_allocated_anesthesiamachineaction(SEAnesthesiaMachineAction::Unload(*aa));
    return any;
  }
  const SEInhalerAction* ia = dynamic_cast<const SEInhalerAction*>(&action);
  if (ia != nullptr)
  {
    any->set_allocated_inhaleraction(SEInhalerAction::Unload(*ia));
    return any;
  }
  action.Error("Unsupported Action");
  delete any;
  return nullptr;
}

void SEAction::Serialize(const cdm::ActionData& src, SEAction& dst)
{
  dst.Clear();
  dst.SetComment(src.comment());
}

void SEAction::Serialize(const SEAction& src, cdm::ActionData& dst)
{
  dst.set_comment(src.m_Comment);
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