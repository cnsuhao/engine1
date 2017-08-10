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

#include "patient/actions/SEPatientAction.h"
#include "patient/SENutrition.h"

class CDM_DECL SEConsumeNutrients : public SEPatientAction
{
public:

  SEConsumeNutrients();
  virtual ~SEConsumeNutrients();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsumeNutrientsData& src, SEConsumeNutrients& dst);
  static cdm::ConsumeNutrientsData* Unload(const SEConsumeNutrients& src);
protected:
  static void Serialize(const cdm::ConsumeNutrientsData& src, SEConsumeNutrients& dst);
  static void Serialize(const SEConsumeNutrients& src, cdm::ConsumeNutrientsData& dst);

public:

  bool HasNutrition() const;
  SENutrition& GetNutrition();
  const SENutrition* GetNutrition() const;

  virtual std::string GetNutritionFile() const;
  virtual void SetNutritionFile(const std::string& fileName);
  virtual bool HasNutritionFile() const;
  virtual void InvalidateNutritionFile();

  virtual void ToString(std::ostream &str) const;

protected:
  SENutrition* m_Nutrition;
  std::string  m_NutritionFile;
};      
