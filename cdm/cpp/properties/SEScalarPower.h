/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PowerUnit : public CCompoundUnit
{
public:
  PowerUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PowerUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PowerUnit& GetCompoundUnit(const std::string& unit);

  static const PowerUnit W;
  static const PowerUnit kcal_Per_s;
  static const PowerUnit kcal_Per_hr;
  static const PowerUnit kcal_Per_day;
  static const PowerUnit J_Per_s;
  static const PowerUnit BTU_Per_hr;
};

class CDM_DECL SEScalarPower : public SEScalarQuantity<PowerUnit>
{
public:
  SEScalarPower() {}
  virtual ~SEScalarPower() {}

  static void Load(const cdm::ScalarPowerData& src, SEScalarPower& dst);
  static cdm::ScalarPowerData* Unload(const SEScalarPower& src);
protected:
  static void Serialize(const cdm::ScalarPowerData& src, SEScalarPower& dst);
  static void Serialize(const SEScalarPower& src, cdm::ScalarPowerData& dst);
};
