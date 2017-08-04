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
#include "SEEnvironmentCondition.h"

SEEnvironmentCondition::SEEnvironmentCondition() : SECondition()
{

}

SEEnvironmentCondition::~SEEnvironmentCondition()
{
  Clear();
}

void SEEnvironmentCondition::Clear()
{
  SECondition::Clear();
}

bool SEEnvironmentCondition::IsValid() const
{
  return SECondition::IsValid();
}

void SEEnvironmentCondition::Serialize(const cdm::EnvironmentConditionData& src, SEEnvironmentCondition& dst)
{
  SECondition::Serialize(src.condition(), dst);
}

void SEEnvironmentCondition::Serialize(const SEEnvironmentCondition& src, cdm::EnvironmentConditionData& dst)
{
  SECondition::Serialize(src, *dst.mutable_condition());
}

#include "system/environment/conditions/SEInitialEnvironmentConditions.h"
SEEnvironmentCondition* SEEnvironmentCondition::Load(const cdm::AnyEnvironmentConditionData& any, SESubstanceManager& subMgr)
{
  switch (any.Condition_case())
  {
    case cdm::AnyEnvironmentConditionData::ConditionCase::kInitialEnvironmentConditions:
    {
      SEInitialEnvironmentConditions* a = new SEInitialEnvironmentConditions(subMgr);
      SEInitialEnvironmentConditions::Load(any.initialenvironmentconditions(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown action type : " + any.Condition_case());
  return nullptr;
}
cdm::AnyEnvironmentConditionData* SEEnvironmentCondition::Unload(const SEEnvironmentCondition& action)
{
  cdm::AnyEnvironmentConditionData* any = new cdm::AnyEnvironmentConditionData();
  const SEInitialEnvironmentConditions* cec = dynamic_cast<const SEInitialEnvironmentConditions*>(&action);
  if (cec != nullptr)
  {
    any->set_allocated_initialenvironmentconditions(SEInitialEnvironmentConditions::Unload(*cec));
    return any;
  }
  delete any;
  return nullptr;
}