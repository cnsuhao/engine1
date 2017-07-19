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
#include "patient/SEMeal.h"
#include "properties/SEScalarTime.h"
#include <google/protobuf/text_format.h>

SEMeal::SEMeal(Logger* logger) : SENutrition(logger)
{
  m_ElapsedTime = nullptr;
}

SEMeal::~SEMeal()
{
  Clear();  
}

void SEMeal::Clear()
{
  SENutrition::Clear();
  SAFE_DELETE(m_ElapsedTime);
}


void SEMeal::Load(const cdm::MealData& src, SEMeal& dst)
{
	SEMeal::Serialize(src, dst);
}
void SEMeal::Serialize(const cdm::MealData& src, SEMeal& dst)
{
	SENutrition::Serialize(src.nutrition(), dst);
	dst.Clear();
	if (src.has_elapsedtime())
		SEScalarTime::Load(src.elapsedtime(), dst.GetElapsedTime());
}

cdm::MealData* SEMeal::Unload(const SEMeal& src)
{
	cdm::MealData* dst = new cdm::MealData();
	SEMeal::Serialize(src, *dst);
	return dst;
}
void SEMeal::Serialize(const SEMeal& src, cdm::MealData& dst)
{
	SENutrition::Serialize(src, *dst.mutable_nutrition());
	if (src.HasElapsedTime())
		dst.set_allocated_elapsedtime(SEScalarTime::Unload(*src.m_ElapsedTime));
}

bool SEMeal::LoadFile(const std::string& mealFile)
{
	cdm::MealData src;
	std::ifstream file_stream(mealFile, std::ios::in);
	std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
	google::protobuf::TextFormat::ParseFromString(fmsg, &src);
	SEMeal::Load(src, *this);
	return true;

	// If its a binary string in the file...
	//std::ifstream binary_istream(mealFile, std::ios::in | std::ios::binary);
	//src.ParseFromIstream(&binary_istream);
}

bool SEMeal::HasElapsedTime() const
{
  return m_ElapsedTime == nullptr ? false : m_ElapsedTime->IsValid();
}
SEScalarTime& SEMeal::GetElapsedTime()
{
  if (m_ElapsedTime == nullptr)
    m_ElapsedTime = new SEScalarTime();
  return *m_ElapsedTime;
}
double SEMeal::GetElapsedTime(const TimeUnit& unit) const
{
  if (m_ElapsedTime == nullptr)
    return SEScalar::dNaN();
  return m_ElapsedTime->GetValue(unit);
}