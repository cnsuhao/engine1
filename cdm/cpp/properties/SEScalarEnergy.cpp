/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarEnergy.h"

const EnergyUnit EnergyUnit::J("J");
const EnergyUnit EnergyUnit::mJ("mJ");
const EnergyUnit EnergyUnit::kJ("kJ");
const EnergyUnit EnergyUnit::kcal("kcal");

bool EnergyUnit::IsValidUnit(const std::string& unit)
{
  if (J.GetString().compare(unit) == 0)
    return true;
  if (mJ.GetString().compare(unit) == 0)
    return true;
  if (kJ.GetString().compare(unit) == 0)
    return true;
  if (kcal.GetString().compare(unit) == 0)
    return true;
  return false;
}

const EnergyUnit& EnergyUnit::GetCompoundUnit(const std::string& unit)
{
  if (J.GetString().compare(unit) == 0)
    return J;
  if (mJ.GetString().compare(unit) == 0)
    return mJ;
  if (kJ.GetString().compare(unit) == 0)
    return kJ;
  if (kcal.GetString().compare(unit) == 0)
    return kcal;
  std::stringstream err;
  err << unit << " is not a valid Energy unit";
  throw CommonDataModelException(err.str());
}

void SEScalarEnergy::Load(const cdm::ScalarEnergyData& src, SEScalarEnergy& dst)
{
  SEScalarEnergy::Serialize(src, dst);
}
void SEScalarEnergy::Serialize(const cdm::ScalarEnergyData& src, SEScalarEnergy& dst)
{
  SEScalarQuantity<EnergyUnit>::Serialize(src.scalarenergy(), dst);
}

cdm::ScalarEnergyData* SEScalarEnergy::Unload(const SEScalarEnergy& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarEnergyData* dst = new cdm::ScalarEnergyData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarEnergy::Serialize(const SEScalarEnergy& src, cdm::ScalarEnergyData& dst)
{
  SEScalarQuantity<EnergyUnit>::Serialize(src, *dst.mutable_scalarenergy());
}