/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarElectricCharge.h"

const ElectricChargeUnit ElectricChargeUnit::C("C");

bool ElectricChargeUnit::IsValidUnit(const std::string& unit)
{
  if (C.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricChargeUnit& ElectricChargeUnit::GetCompoundUnit(const std::string& unit)
{
  if (C.GetString().compare(unit) == 0)
    return C;
  std::stringstream err;
  err << unit << " is not a valid ElectricCharge unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricCharge::Load(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst)
{
  SEScalarElectricCharge::Serialize(src, dst);
}
void SEScalarElectricCharge::Serialize(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst)
{
  SEScalarQuantity<ElectricChargeUnit>::Serialize(src.scalarelectriccharge(), dst);
}

cdm::ScalarElectricChargeData* SEScalarElectricCharge::Unload(const SEScalarElectricCharge& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricChargeData* dst = new cdm::ScalarElectricChargeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricCharge::Serialize(const SEScalarElectricCharge& src, cdm::ScalarElectricChargeData& dst)
{
  SEScalarQuantity<ElectricChargeUnit>::Serialize(src, *dst.mutable_scalarelectriccharge());
}