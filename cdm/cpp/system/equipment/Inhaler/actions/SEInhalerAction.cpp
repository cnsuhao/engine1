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
#include "system/equipment/Inhaler/actions/SEInhalerAction.h"

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