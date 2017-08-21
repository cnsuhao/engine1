/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"
#include "patient/SEMeal.h"

class CDM_DECL SEConsumeMeal : public SEPatientCondition
{
public:

  SEConsumeMeal();
  virtual ~SEConsumeMeal();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ConsumeMealData& src, SEConsumeMeal& dst);
  static cdm::ConsumeMealData* Unload(const SEConsumeMeal& src);
protected:
  static void Serialize(const cdm::ConsumeMealData& src, SEConsumeMeal& dst);
  static void Serialize(const SEConsumeMeal& src, cdm::ConsumeMealData& dst);

public:
  virtual std::string GetName() const { return "ConsumeMeal"; }

  bool HasMeal() const;
  SEMeal& GetMeal();
  const SEMeal* GetMeal() const;

  virtual std::string GetMealFile() const;
  virtual void SetMealFile(const std::string& fileName);
  virtual bool HasMealFile() const;
  virtual void InvalidateMealFile();

  virtual void ToString(std::ostream &str) const;

protected:
  SEMeal*      m_Meal;
  std::string  m_MealFile;
};
