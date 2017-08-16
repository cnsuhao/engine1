/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarElectricInductance.h"

const ElectricInductanceUnit ElectricInductanceUnit::H("H");

bool ElectricInductanceUnit::IsValidUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricInductanceUnit& ElectricInductanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return H;
  std::stringstream err;
  err << unit << " is not a valid ElectricInductance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricInductance::Load(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst)
{
  SEScalarElectricInductance::Serialize(src, dst);
}
void SEScalarElectricInductance::Serialize(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst)
{
  SEScalarQuantity<ElectricInductanceUnit>::Serialize(src.scalarelectricinductance(), dst);
}

cdm::ScalarElectricInductanceData* SEScalarElectricInductance::Unload(const SEScalarElectricInductance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricInductanceData* dst = new cdm::ScalarElectricInductanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricInductance::Serialize(const SEScalarElectricInductance& src, cdm::ScalarElectricInductanceData& dst)
{
  SEScalarQuantity<ElectricInductanceUnit>::Serialize(src, *dst.mutable_scalarelectricinductance());
}