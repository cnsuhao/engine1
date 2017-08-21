/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatCapacitancePerAmountUnit : public CCompoundUnit
{
public:
  HeatCapacitancePerAmountUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatCapacitancePerAmountUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatCapacitancePerAmountUnit& GetCompoundUnit(const std::string& unit);
  
  static const HeatCapacitancePerAmountUnit J_Per_K_mol;
};

class CDM_DECL SEScalarHeatCapacitancePerAmount : public SEScalarQuantity<HeatCapacitancePerAmountUnit>
{
public:
  SEScalarHeatCapacitancePerAmount() {}
  virtual ~SEScalarHeatCapacitancePerAmount() {}

  static void Load(const cdm::ScalarHeatCapacitancePerAmountData& src, SEScalarHeatCapacitancePerAmount& dst);
  static cdm::ScalarHeatCapacitancePerAmountData* Unload(const SEScalarHeatCapacitancePerAmount& src);
protected:
  static void Serialize(const cdm::ScalarHeatCapacitancePerAmountData& src, SEScalarHeatCapacitancePerAmount& dst);
  static void Serialize(const SEScalarHeatCapacitancePerAmount& src, cdm::ScalarHeatCapacitancePerAmountData& dst);
};