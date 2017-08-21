/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatCapacitanceUnit : public CCompoundUnit
{
public:
  HeatCapacitanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatCapacitanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatCapacitanceUnit& GetCompoundUnit(const std::string& unit);

  static const HeatCapacitanceUnit J_Per_K;
  static const HeatCapacitanceUnit kJ_Per_K;
  static const HeatCapacitanceUnit kcal_Per_K;
  static const HeatCapacitanceUnit kcal_Per_C;
};

class CDM_DECL SEScalarHeatCapacitance : public SEScalarQuantity<HeatCapacitanceUnit>
{
public:
  SEScalarHeatCapacitance() {}
  virtual ~SEScalarHeatCapacitance() {}

  static void Load(const cdm::ScalarHeatCapacitanceData& src, SEScalarHeatCapacitance& dst);
  static cdm::ScalarHeatCapacitanceData* Unload(const SEScalarHeatCapacitance& src);
protected:
  static void Serialize(const cdm::ScalarHeatCapacitanceData& src, SEScalarHeatCapacitance& dst);
  static void Serialize(const SEScalarHeatCapacitance& src, cdm::ScalarHeatCapacitanceData& dst);
};