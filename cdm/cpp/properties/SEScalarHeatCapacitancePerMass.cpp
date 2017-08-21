/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarHeatCapacitancePerMass.h"

const HeatCapacitancePerMassUnit HeatCapacitancePerMassUnit::J_Per_K_kg("J/K kg");
const HeatCapacitancePerMassUnit HeatCapacitancePerMassUnit::kJ_Per_K_kg("kJ/K kg");
const HeatCapacitancePerMassUnit HeatCapacitancePerMassUnit::kcal_Per_K_kg("kcal/K kg");
const HeatCapacitancePerMassUnit HeatCapacitancePerMassUnit::kcal_Per_C_kg("kcal/degC kg");

bool HeatCapacitancePerMassUnit::IsValidUnit(const std::string& unit)
{
  if (J_Per_K_kg.GetString().compare(unit) == 0)
    return true;
  if (kJ_Per_K_kg.GetString().compare(unit) == 0)
    return true;
  if (kcal_Per_K_kg.GetString().compare(unit) == 0)
    return true;
  if (kcal_Per_C_kg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const HeatCapacitancePerMassUnit& HeatCapacitancePerMassUnit::GetCompoundUnit(const std::string& unit)
{
  if (J_Per_K_kg.GetString().compare(unit) == 0)
    return J_Per_K_kg;
  if (kJ_Per_K_kg.GetString().compare(unit) == 0)
    return kJ_Per_K_kg;
  if (kcal_Per_K_kg.GetString().compare(unit) == 0)
    return kcal_Per_K_kg;
  if (kcal_Per_C_kg.GetString().compare(unit) == 0)
    return kcal_Per_C_kg;
  std::stringstream err;
  err << unit << " is not a valid HeatCapacitancePerMass unit";
  throw CommonDataModelException(err.str());
}

void SEScalarHeatCapacitancePerMass::Load(const cdm::ScalarHeatCapacitancePerMassData& src, SEScalarHeatCapacitancePerMass& dst)
{
  SEScalarHeatCapacitancePerMass::Serialize(src, dst);
}
void SEScalarHeatCapacitancePerMass::Serialize(const cdm::ScalarHeatCapacitancePerMassData& src, SEScalarHeatCapacitancePerMass& dst)
{
  SEScalarQuantity<HeatCapacitancePerMassUnit>::Serialize(src.scalarheatcapacitancepermass(), dst);
}

cdm::ScalarHeatCapacitancePerMassData* SEScalarHeatCapacitancePerMass::Unload(const SEScalarHeatCapacitancePerMass& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarHeatCapacitancePerMassData* dst = new cdm::ScalarHeatCapacitancePerMassData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarHeatCapacitancePerMass::Serialize(const SEScalarHeatCapacitancePerMass& src, cdm::ScalarHeatCapacitancePerMassData& dst)
{
  SEScalarQuantity<HeatCapacitancePerMassUnit>::Serialize(src, *dst.mutable_scalarheatcapacitancepermass());
}