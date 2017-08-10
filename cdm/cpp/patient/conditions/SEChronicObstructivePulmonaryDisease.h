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

class CDM_DECL SEChronicObstructivePulmonaryDisease : public SEPatientCondition
{
public:

  SEChronicObstructivePulmonaryDisease();
  virtual ~SEChronicObstructivePulmonaryDisease();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst);
  static cdm::ChronicObstructivePulmonaryDiseaseData* Unload(const SEChronicObstructivePulmonaryDisease& src);
protected:
  static void Serialize(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst);
  static void Serialize(const SEChronicObstructivePulmonaryDisease& src, cdm::ChronicObstructivePulmonaryDiseaseData& dst);

public:
  virtual std::string GetName() const { return "ChronicObstructivePulmonaryDisease"; }

  virtual bool HasBronchitisSeverity() const;
  virtual SEScalar0To1& GetBronchitisSeverity();

  virtual bool HasEmphysemaSeverity() const;
  virtual SEScalar0To1& GetEmphysemaSeverity();

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*     m_BronchitisSeverity;
  SEScalar0To1*     m_EmphysemaSeverity;
};
