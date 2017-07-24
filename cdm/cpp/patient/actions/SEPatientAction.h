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
#include "scenario/SEAction.h"
#include "bind/cdm/PatientActions.pb.h"

class DLL_DECL SEPatientAction : public SEAction
{
public:

  SEPatientAction();
  virtual ~SEPatientAction();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::PatientActionData& src, SEPatientAction& dst);
  static cdm::PatientActionData* Unload(const SEPatientAction& src);
protected:
  static void Serialize(const cdm::PatientActionData& src, SEPatientAction& dst);
  static void Serialize(const SEPatientAction& src, cdm::PatientActionData& dst);

public:
  virtual void ToString(std::ostream &str) const = 0;
  
};  