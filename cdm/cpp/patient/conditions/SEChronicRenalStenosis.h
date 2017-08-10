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

class CDM_DECL SEChronicRenalStenosis : public SEPatientCondition
{
public:

  SEChronicRenalStenosis();
  virtual ~SEChronicRenalStenosis();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicRenalStenosisData& src, SEChronicRenalStenosis& dst);
  static cdm::ChronicRenalStenosisData* Unload(const SEChronicRenalStenosis& src);
protected:
  static void Serialize(const cdm::ChronicRenalStenosisData& src, SEChronicRenalStenosis& dst);
  static void Serialize(const SEChronicRenalStenosis& src, cdm::ChronicRenalStenosisData& dst);

public:
  virtual std::string GetName() const { return "ChronicRenalStenosis"; }

  virtual bool HasLeftKidneySeverity() const;
  virtual SEScalar0To1& GetLeftKidneySeverity();

  virtual bool HasRightKidneySeverity() const;
  virtual SEScalar0To1& GetRightKidneySeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*           m_LeftKidneySeverity;
  SEScalar0To1*           m_RightKidneySeverity;
};