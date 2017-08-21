/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarHeatConductance.h"

const HeatConductanceUnit HeatConductanceUnit::W_Per_K("W/K");
const HeatConductanceUnit HeatConductanceUnit::W_Per_C("W/degC");
const HeatConductanceUnit HeatConductanceUnit::kcal_Per_K_s("kcal/K s");
const HeatConductanceUnit HeatConductanceUnit::kcal_Per_C_s("kcal/degC s");

bool HeatConductanceUnit::IsValidUnit(const std::string& unit)
{
  if (W_Per_K.GetString().compare(unit) == 0)
    return true;
  if (W_Per_C.GetString().compare(unit) == 0)
    return true;
  if (kcal_Per_K_s.GetString().compare(unit) == 0)
    return true;
  if (kcal_Per_C_s.GetString().compare(unit) == 0)
    return true;
  return false;
}

const HeatConductanceUnit& HeatConductanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (W_Per_K.GetString().compare(unit) == 0)
    return W_Per_K;
  if (W_Per_C.GetString().compare(unit) == 0)
    return W_Per_C;
  if (kcal_Per_K_s.GetString().compare(unit) == 0)
    return kcal_Per_K_s;
  if (kcal_Per_C_s.GetString().compare(unit) == 0)
    return kcal_Per_C_s;
  std::stringstream err;
  err << unit << " is not a valid HeatConductance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarHeatConductance::Load(const cdm::ScalarHeatConductanceData& src, SEScalarHeatConductance& dst)
{
  SEScalarHeatConductance::Serialize(src, dst);
}
void SEScalarHeatConductance::Serialize(const cdm::ScalarHeatConductanceData& src, SEScalarHeatConductance& dst)
{
  SEScalarQuantity<HeatConductanceUnit>::Serialize(src.scalarheatconductance(), dst);
}

cdm::ScalarHeatConductanceData* SEScalarHeatConductance::Unload(const SEScalarHeatConductance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarHeatConductanceData* dst = new cdm::ScalarHeatConductanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarHeatConductance::Serialize(const SEScalarHeatConductance& src, cdm::ScalarHeatConductanceData& dst)
{
  SEScalarQuantity<HeatConductanceUnit>::Serialize(src, *dst.mutable_scalarheatconductance());
}