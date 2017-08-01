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
#include "patient/conditions/SEPatientCondition.h"

class DLL_DECL SEChronicHeartFailure : public SEPatientCondition
{
public:

  SEChronicHeartFailure();
  virtual ~SEChronicHeartFailure();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  //jbw - It looks like Heart Failure is missing
  static void Load(const cdm::ChronicHeartFailureData& src, SEChronicHeartFailure& dst);
  static cdm::ChronicHeartFailureData* Unload(const SEChronicHeartFailure& src);
protected:
  static void Serialize(const cdm::ChronicHeartFailureData& src, SEChronicHeartFailure& dst);
  static void Serialize(const SEChronicHeartFailure& src, cdm::ChronicHeartFailureData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;

protected:
};    