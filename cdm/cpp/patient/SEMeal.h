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
#include "patient/SENutrition.h"

class DLL_DECL SEMeal : public SENutrition
{
public:

  SEMeal(Logger* logger);
  virtual ~SEMeal();

  virtual void Clear();

  static void Load(const cdm::MealData& src, SEMeal& dst);
  static cdm::MealData* Unload(const SEMeal& src);
protected:
  static void Serialize(const cdm::MealData& src, SEMeal& dst);
  static void Serialize(const SEMeal& src, cdm::MealData& dst);

public:

  bool LoadFile(const std::string& MealFile);
  
  virtual bool HasElapsedTime() const;
  virtual SEScalarTime& GetElapsedTime();
  virtual double GetElapsedTime(const TimeUnit& unit) const;
  
protected:

  SEScalarTime*    m_ElapsedTime;
};