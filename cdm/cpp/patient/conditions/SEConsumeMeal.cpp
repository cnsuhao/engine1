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
#include "SEConsumeMeal.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerTime.h"
#include "properties/SEScalarVolume.h"

SEConsumeMeal::SEConsumeMeal() : SEPatientCondition()
{
  m_Meal = nullptr;
  InvalidateMealFile();
}

SEConsumeMeal::~SEConsumeMeal()
{
  Clear();
}

void SEConsumeMeal::Clear()
{
  SEPatientCondition::Clear();
  SAFE_DELETE(m_Meal);
  InvalidateMealFile();
}

bool SEConsumeMeal::IsValid() const
{
  return SEPatientCondition::IsValid() && (HasMeal() || HasMealFile());
}

void SEConsumeMeal::Load(const cdm::ConsumeMealData& src, SEConsumeMeal& dst)
{
  SEConsumeMeal::Serialize(src, dst);
}
void SEConsumeMeal::Serialize(const cdm::ConsumeMealData& src, SEConsumeMeal& dst)
{
  dst.Clear();
  if (src.has_meal())
    SEMeal::Load(src.meal(), dst.GetMeal());
  if(src.has_mealfile())
    dst.SetMealFile(src.mealfile());
}

cdm::ConsumeMealData* SEConsumeMeal::Unload(const SEConsumeMeal& src)
{
  cdm::ConsumeMealData* dst = new cdm::ConsumeMealData();
  SEConsumeMeal::Serialize(src, *dst);
  return dst;
}
void SEConsumeMeal::Serialize(const SEConsumeMeal& src, cdm::ConsumeMealData& dst)
{
  if (src.HasMeal())
    dst.set_allocated_meal(SEMeal::Unload(*src.m_Meal));
  if (src.HasMealFile())
    dst.set_mealfile(src.m_MealFile);
}

bool SEConsumeMeal::HasMeal() const
{
  return m_Meal != nullptr;
}
SEMeal& SEConsumeMeal::GetMeal()
{
  m_MealFile = "";
  if (m_Meal == nullptr)
    m_Meal = new SEMeal(nullptr);
  return *m_Meal;
}
const SEMeal* SEConsumeMeal::GetMeal() const
{
  return m_Meal;
}

std::string SEConsumeMeal::GetMealFile() const
{
  return m_MealFile;
}
void SEConsumeMeal::SetMealFile(const std::string& fileName)
{
  if (m_Meal != nullptr)
    SAFE_DELETE(m_Meal);
  m_MealFile = fileName;
}
bool SEConsumeMeal::HasMealFile() const
{
  return m_MealFile.empty() ? false : true;
}
void SEConsumeMeal::InvalidateMealFile()
{
  m_MealFile = "";
}

void SEConsumeMeal::ToString(std::ostream &str) const
{
  str << "Patient Condition :  Consume Meal";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  if (HasMeal())
  {
    str << "\n\tCharbohydrates: "; m_Meal->HasCarbohydrate() ? str << m_Meal->GetCarbohydrate() : str << "None";
    str << "\n\tCharbohydrates Digestion Rate: "; m_Meal->HasCarbohydrateDigestionRate() ? str << m_Meal->GetCarbohydrateDigestionRate() : str << "None";
    str << "\n\tFat: "; m_Meal->HasFat() ? str << m_Meal->GetFat() : str << "None";
    str << "\n\tFat Digestion Rate: "; m_Meal->HasFatDigestionRate() ? str << m_Meal->GetFatDigestionRate() : str << "None";
    str << "\n\tProtein: "; m_Meal->HasProtein() ? str << m_Meal->GetProtein() : str << "None";
    str << "\n\tProtein Digestion Rate: "; m_Meal->HasProteinDigestionRate() ? str << m_Meal->GetProteinDigestionRate() : str << "None";
    str << "\n\tCalcium: "; m_Meal->HasCalcium() ? str << m_Meal->GetCalcium() : str << "None";
    str << "\n\tSodium: "; m_Meal->HasSodium() ? str << m_Meal->GetSodium() : str << "None";
    str << "\n\tWater: "; m_Meal->HasWater() ? str << m_Meal->GetWater() : str << "None";
  }
  if (HasMealFile())
    str << "\n\tMeal File: "; str << m_MealFile;
  str << std::flush;
}
