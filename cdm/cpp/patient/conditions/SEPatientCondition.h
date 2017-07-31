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

#pragma once
#include "scenario/SECondition.h"
#include "bind/cdm/PatientConditions.pb.h"

class DLL_DECL SEPatientCondition : public SECondition
{
public:

  SEPatientCondition();
  virtual ~SEPatientCondition();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const = 0;

  static void Load(const cdm::PatientConditionData& src, SEPatientCondition& dst);
  static cdm::PatientConditionData* Unload(const SEPatientCondition& src);
protected:
  static void Serialize(const cdm::PatientConditionData& src, SEPatientCondition& dst);
  static void Serialize(const SEPatientCondition& src, cdm::PatientConditionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
  
};  