/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarEnergyPerMass.h"

const EnergyPerMassUnit EnergyPerMassUnit::J_Per_kg("J/kg");
const EnergyPerMassUnit EnergyPerMassUnit::kJ_Per_kg("kJ/kg");
const EnergyPerMassUnit EnergyPerMassUnit::mJ_Per_kg("mJ/kg");
const EnergyPerMassUnit EnergyPerMassUnit::kcal_Per_kg("kcal/kg");

bool EnergyPerMassUnit::IsValidUnit(const std::string& unit)
{
  if (J_Per_kg.GetString().compare(unit) == 0)
    return true;
  if (kJ_Per_kg.GetString().compare(unit) == 0)
    return true;
  if (mJ_Per_kg.GetString().compare(unit) == 0)
    return true;
  if (kcal_Per_kg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const EnergyPerMassUnit& EnergyPerMassUnit::GetCompoundUnit(const std::string& unit)
{
  if (J_Per_kg.GetString().compare(unit) == 0)
    return J_Per_kg;
  if (kJ_Per_kg.GetString().compare(unit) == 0)
    return kJ_Per_kg;
  if (mJ_Per_kg.GetString().compare(unit) == 0)
    return mJ_Per_kg;
  if (kcal_Per_kg.GetString().compare(unit) == 0)
    return kcal_Per_kg;
  std::stringstream err;
  err << unit << " is not a valid EnergyPerMass unit";
  throw CommonDataModelException(err.str());
}

void SEScalarEnergyPerMass::Load(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst)
{
  SEScalarEnergyPerMass::Serialize(src, dst);
}
void SEScalarEnergyPerMass::Serialize(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst)
{
  SEScalarQuantity<EnergyPerMassUnit>::Serialize(src.scalarenergypermass(), dst);
}

cdm::ScalarEnergyPerMassData* SEScalarEnergyPerMass::Unload(const SEScalarEnergyPerMass& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarEnergyPerMassData* dst = new cdm::ScalarEnergyPerMassData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarEnergyPerMass::Serialize(const SEScalarEnergyPerMass& src, cdm::ScalarEnergyPerMassData& dst)
{
  SEScalarQuantity<EnergyPerMassUnit>::Serialize(src, *dst.mutable_scalarenergypermass());
}