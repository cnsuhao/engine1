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
#include "SEPatientCondition.h"

SEPatientCondition::SEPatientCondition() : SECondition()
{
  
}

SEPatientCondition::~SEPatientCondition()
{
  Clear();
}

void SEPatientCondition::Clear()
{
  SECondition::Clear();
}

bool SEPatientCondition::IsValid() const
{
  return SECondition::IsValid();
}

void SEPatientCondition::Load(const cdm::PatientConditionData& src, SEPatientCondition& dst)
{
  SEPatientCondition::Serialize(src, dst);
}
void SEPatientCondition::Serialize(const cdm::PatientConditionData& src, SEPatientCondition& dst)
{
  dst.Clear();
}

cdm::PatientConditionData* SEPatientCondition::Unload(const SEPatientCondition& src)
{
  cdm::PatientConditionData* dst = new cdm::PatientConditionData();
  SEPatientCondition::Serialize(src, *dst);
  return dst;
}
void SEPatientCondition::Serialize(const SEPatientCondition& src, cdm::PatientConditionData& dst)
{

}
