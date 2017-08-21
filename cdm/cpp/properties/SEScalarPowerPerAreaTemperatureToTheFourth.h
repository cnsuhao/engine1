/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PowerPerAreaTemperatureToTheFourthUnit : public CCompoundUnit
{
public:
  PowerPerAreaTemperatureToTheFourthUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PowerPerAreaTemperatureToTheFourthUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PowerPerAreaTemperatureToTheFourthUnit& GetCompoundUnit(const std::string& unit);

  static const PowerPerAreaTemperatureToTheFourthUnit W_Per_m2_K4;
};

class CDM_DECL SEScalarPowerPerAreaTemperatureToTheFourth : public SEScalarQuantity<PowerPerAreaTemperatureToTheFourthUnit>
{
public:
  SEScalarPowerPerAreaTemperatureToTheFourth() {}
  virtual ~SEScalarPowerPerAreaTemperatureToTheFourth() {}

  static void Load(const cdm::ScalarPowerPerAreaTemperatureToTheFourthData& src, SEScalarPowerPerAreaTemperatureToTheFourth& dst);
  static cdm::ScalarPowerPerAreaTemperatureToTheFourthData* Unload(const SEScalarPowerPerAreaTemperatureToTheFourth& src);
protected:
  static void Serialize(const cdm::ScalarPowerPerAreaTemperatureToTheFourthData& src, SEScalarPowerPerAreaTemperatureToTheFourth& dst);
  static void Serialize(const SEScalarPowerPerAreaTemperatureToTheFourth& src, cdm::ScalarPowerPerAreaTemperatureToTheFourthData& dst);
};
