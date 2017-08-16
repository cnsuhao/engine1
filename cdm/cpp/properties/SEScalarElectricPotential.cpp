/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarElectricPotential.h"

const ElectricPotentialUnit ElectricPotentialUnit::V("V");
const ElectricPotentialUnit ElectricPotentialUnit::mV("mV");

bool ElectricPotentialUnit::IsValidUnit(const std::string& unit)
{
  if (V.GetString().compare(unit) == 0)
    return true;
  if (mV.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricPotentialUnit& ElectricPotentialUnit::GetCompoundUnit(const std::string& unit)
{
  if(V.GetString().compare(unit)==0)
    return V;
  if(mV.GetString().compare(unit)==0)
    return mV;
  std::stringstream err;
  err << unit << " is not a valid Electric Potential unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricPotential::Load(const cdm::ScalarElectricPotentialData& src, SEScalarElectricPotential& dst)
{
  SEScalarElectricPotential::Serialize(src, dst);
}
void SEScalarElectricPotential::Serialize(const cdm::ScalarElectricPotentialData& src, SEScalarElectricPotential& dst)
{
  SEScalarQuantity<ElectricPotentialUnit>::Serialize(src.scalarelectricpotential(), dst);
}

cdm::ScalarElectricPotentialData* SEScalarElectricPotential::Unload(const SEScalarElectricPotential& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricPotentialData* dst = new cdm::ScalarElectricPotentialData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricPotential::Serialize(const SEScalarElectricPotential& src, cdm::ScalarElectricPotentialData& dst)
{
  SEScalarQuantity<ElectricPotentialUnit>::Serialize(src, *dst.mutable_scalarelectricpotential());
}