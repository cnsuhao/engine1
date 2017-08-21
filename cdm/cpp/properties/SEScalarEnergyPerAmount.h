/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL EnergyPerAmountUnit : public CCompoundUnit
{
public:
  EnergyPerAmountUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~EnergyPerAmountUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const EnergyPerAmountUnit& GetCompoundUnit(const std::string& unit);

  static const EnergyPerAmountUnit kcal_Per_mol;
  static const EnergyPerAmountUnit kJ_Per_mol;
};

class CDM_DECL SEScalarEnergyPerAmount : public SEScalarQuantity<EnergyPerAmountUnit>
{
public:
  SEScalarEnergyPerAmount() {}
  virtual ~SEScalarEnergyPerAmount() {}

  static void Load(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst);
  static cdm::ScalarEnergyPerAmountData* Unload(const SEScalarEnergyPerAmount& src);
protected:
  static void Serialize(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst);
  static void Serialize(const SEScalarEnergyPerAmount& src, cdm::ScalarEnergyPerAmountData& dst);
};
