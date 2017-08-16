/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarEnergyPerAmount.h"

const EnergyPerAmountUnit EnergyPerAmountUnit::kcal_Per_mol("kcal/mol");
const EnergyPerAmountUnit EnergyPerAmountUnit::kJ_Per_mol("kJ/mol");

bool EnergyPerAmountUnit::IsValidUnit(const std::string& unit)
{
  if (kcal_Per_mol.GetString().compare(unit) == 0)
    return true;
  if (kJ_Per_mol.GetString().compare(unit) == 0)
    return true;
  return false;
}

const EnergyPerAmountUnit& EnergyPerAmountUnit::GetCompoundUnit(const std::string& unit)
{
  if (kcal_Per_mol.GetString().compare(unit) == 0)
    return kcal_Per_mol;
  if (kJ_Per_mol.GetString().compare(unit) == 0)
    return kJ_Per_mol;
  std::stringstream err;
  err << unit << " is not a valid EnergyPerAmount unit";
  throw CommonDataModelException(err.str());
}

void SEScalarEnergyPerAmount::Load(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst)
{
  SEScalarEnergyPerAmount::Serialize(src, dst);
}
void SEScalarEnergyPerAmount::Serialize(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst)
{
  SEScalarQuantity<EnergyPerAmountUnit>::Serialize(src.scalarenergyperamount(), dst);
}

cdm::ScalarEnergyPerAmountData* SEScalarEnergyPerAmount::Unload(const SEScalarEnergyPerAmount& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarEnergyPerAmountData* dst = new cdm::ScalarEnergyPerAmountData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarEnergyPerAmount::Serialize(const SEScalarEnergyPerAmount& src, cdm::ScalarEnergyPerAmountData& dst)
{
  SEScalarQuantity<EnergyPerAmountUnit>::Serialize(src, *dst.mutable_scalarenergyperamount());
}