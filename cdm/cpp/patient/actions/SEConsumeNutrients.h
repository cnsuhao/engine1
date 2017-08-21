/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

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
