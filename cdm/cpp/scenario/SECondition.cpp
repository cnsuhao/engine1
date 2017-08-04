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
#include "scenario/SECondition.h"
#include "substance/SESubstanceManager.h"
#include "patient/conditions/SEPatientCondition.h"
#include "system/environment/conditions/SEEnvironmentCondition.h"

SECondition::SECondition() : Loggable()
{
  m_Comment="";
}

SECondition::~SECondition()
{
  Clear();
}

void SECondition::Clear()
{
  m_Comment = "";
}

SECondition* SECondition::Load(const cdm::AnyConditionData& condition, SESubstanceManager& subMgr)
{
  switch (condition.Condition_case())
  {
  case cdm::AnyConditionData::kPatientCondition:
    return SEPatientCondition::Load(condition.patientcondition(), subMgr);
  case cdm::AnyConditionData::kEnvironmentCondition:
    return SEEnvironmentCondition::Load(condition.environmentcondition(), subMgr);
  }
  subMgr.Error("Unknown Condition");
  return nullptr;
}
cdm::AnyConditionData* SECondition::Unload(const SECondition& condition)
{
  cdm::AnyConditionData* any = new cdm::AnyConditionData();
  const SEPatientCondition* pc = dynamic_cast<const SEPatientCondition*>(&condition);
  if (pc != nullptr)
  {
    any->set_allocated_patientcondition(SEPatientCondition::Unload(*pc));
    return any;
  }
  const SEEnvironmentCondition* ec = dynamic_cast<const SEEnvironmentCondition*>(&condition);
  if (ec != nullptr)
  {
    any->set_allocated_environmentcondition(SEEnvironmentCondition::Unload(*ec));
    return any;
  }
  condition.Error("Unsupported Condition");
  delete any;
  return nullptr;
}

void SECondition::Serialize(const cdm::ConditionData& src, SECondition& dst)
{
  dst.Clear();
  dst.SetComment(src.comment());
}

void SECondition::Serialize(const SECondition& src, cdm::ConditionData& dst)
{
  dst.set_comment(src.m_Comment);
}


std::string SECondition::GetComment() const
{
  return m_Comment;
}
void SECondition::SetComment(const std::string& comment)
{
  m_Comment = comment;
}
bool SECondition::HasComment() const
{
  return m_Comment.empty()?false:true;
}
void SECondition::InvalidateComment()
{
  m_Comment = "";
}