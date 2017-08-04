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
#include "system/environment/actions/SEEnvironmentAction.h"

SEEnvironmentAction::SEEnvironmentAction() : SEAction()
{

}

SEEnvironmentAction::~SEEnvironmentAction()
{
  Clear();
}

void SEEnvironmentAction::Clear()
{
  SEAction::Clear();
}

bool SEEnvironmentAction::IsValid() const
{
  return SEAction::IsValid();
}

void SEEnvironmentAction::Serialize(const cdm::EnvironmentActionData& src, SEEnvironmentAction& dst)
{
  SEAction::Serialize(src.action(), dst);
}

void SEEnvironmentAction::Serialize(const SEEnvironmentAction& src, cdm::EnvironmentActionData& dst)
{
  SEAction::Serialize(src, *dst.mutable_action());
}

#include "substance/SESubstanceManager.h"
#include "system/environment/actions/SEChangeEnvironmentConditions.h"
#include "system/environment/actions/SEThermalApplication.h"
SEEnvironmentAction* SEEnvironmentAction::Load(const cdm::AnyEnvironmentActionData& any, SESubstanceManager& subMgr)
{
  switch (any.Action_case())
  {
    case cdm::AnyEnvironmentActionData::ActionCase::kConditions:
    {
      SEChangeEnvironmentConditions* a = new SEChangeEnvironmentConditions(subMgr);
      SEChangeEnvironmentConditions::Load(any.conditions(), *a);
      return a;
    }
    case cdm::AnyEnvironmentActionData::ActionCase::kThermalApplication:
    {
      SEThermalApplication* a = new SEThermalApplication();
      SEThermalApplication::Load(any.thermalapplication(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown action type : " + any.Action_case());
  return nullptr;
}
cdm::AnyEnvironmentActionData* SEEnvironmentAction::Unload(const SEEnvironmentAction& action)
{
  cdm::AnyEnvironmentActionData* any = new cdm::AnyEnvironmentActionData();
  const SEChangeEnvironmentConditions* cec = dynamic_cast<const SEChangeEnvironmentConditions*>(&action);
  if (cec != nullptr)
  {
    any->set_allocated_conditions(SEChangeEnvironmentConditions::Unload(*cec));
    return any;
  }
  const SEThermalApplication* ta = dynamic_cast<const SEThermalApplication*>(&action);
  if (ta != nullptr)
  {
    any->set_allocated_thermalapplication(SEThermalApplication::Unload(*ta));
    return any;
  }
  delete any;
  return nullptr;
}