/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/inhaler/actions/SEInhalerAction.h"

SEInhalerAction::SEInhalerAction() : SEAction()
{

}

SEInhalerAction::~SEInhalerAction()
{
  Clear();
}

void SEInhalerAction::Clear()
{
  SEAction::Clear();
}

bool SEInhalerAction::IsValid() const
{
  return SEAction::IsValid();
}

void SEInhalerAction::Serialize(const cdm::InhalerActionData& src, SEInhalerAction& dst)
{
  SEAction::Serialize(src.action(), dst);
}

void SEInhalerAction::Serialize(const SEInhalerAction& src, cdm::InhalerActionData& dst)
{
  SEAction::Serialize(src, *dst.mutable_action());
}

#include "system/equipment/inhaler/actions/SEInhalerConfiguration.h"
SEInhalerAction* SEInhalerAction::Load(const cdm::AnyInhalerActionData& any, SESubstanceManager& subMgr)
{
  switch (any.Action_case())
  {
    case cdm::AnyInhalerActionData::ActionCase::kConfiguration:
    {
      SEInhalerConfiguration* a = new SEInhalerConfiguration(subMgr);
      SEInhalerConfiguration::Load(any.configuration(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown action type : " + any.Action_case());
  return nullptr;
}
cdm::AnyInhalerActionData* SEInhalerAction::Unload(const SEInhalerAction& action)
{
  cdm::AnyInhalerActionData* any = new cdm::AnyInhalerActionData();
  const SEInhalerConfiguration* cec = dynamic_cast<const SEInhalerConfiguration*>(&action);
  if (cec != nullptr)
  {
    any->set_allocated_configuration(SEInhalerConfiguration::Unload(*cec));
    return any;
  }
  delete any;
  return nullptr;
}