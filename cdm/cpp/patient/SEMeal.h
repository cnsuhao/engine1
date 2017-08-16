/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/SENutrition.h"

class CDM_DECL SEMeal : public SENutrition
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