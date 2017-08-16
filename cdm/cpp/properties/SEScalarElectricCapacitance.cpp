/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarElectricCapacitance.h"

const ElectricCapacitanceUnit ElectricCapacitanceUnit::F("F");

bool ElectricCapacitanceUnit::IsValidUnit(const std::string& unit)
{
  if (F.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricCapacitanceUnit& ElectricCapacitanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (F.GetString().compare(unit) == 0)
    return F;
  std::stringstream err;
  err << unit << " is not a valid ElectricCapacitance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricCapacitance::Load(const cdm::ScalarElectricCapacitanceData& src, SEScalarElectricCapacitance& dst)
{
  SEScalarElectricCapacitance::Serialize(src, dst);
}
void SEScalarElectricCapacitance::Serialize(const cdm::ScalarElectricCapacitanceData& src, SEScalarElectricCapacitance& dst)
{
  SEScalarQuantity<ElectricCapacitanceUnit>::Serialize(src.scalarelectriccapacitance(), dst);
}

cdm::ScalarElectricCapacitanceData* SEScalarElectricCapacitance::Unload(const SEScalarElectricCapacitance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricCapacitanceData* dst = new cdm::ScalarElectricCapacitanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricCapacitance::Serialize(const SEScalarElectricCapacitance& src, cdm::ScalarElectricCapacitanceData& dst)
{
  SEScalarQuantity<ElectricCapacitanceUnit>::Serialize(src, *dst.mutable_scalarelectriccapacitance());
}