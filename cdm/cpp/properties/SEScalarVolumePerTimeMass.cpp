/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarVolumePerTimeMass.h"

const VolumePerTimeMassUnit VolumePerTimeMassUnit::L_Per_s_g("L/s g");
const VolumePerTimeMassUnit VolumePerTimeMassUnit::mL_Per_s_g("mL / s g");
const VolumePerTimeMassUnit VolumePerTimeMassUnit::mL_Per_min_kg("mL/min kg");
const VolumePerTimeMassUnit VolumePerTimeMassUnit::mL_Per_s_kg("mL/s kg");
const VolumePerTimeMassUnit VolumePerTimeMassUnit::uL_Per_min_kg("uL/min kg");

bool VolumePerTimeMassUnit::IsValidUnit(const std::string& unit)
{
  if (L_Per_s_g.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_s_g.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_min_kg.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_s_kg.GetString().compare(unit) == 0)
    return true;
  if (uL_Per_min_kg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const VolumePerTimeMassUnit& VolumePerTimeMassUnit::GetCompoundUnit(const std::string& unit)
{
  if (L_Per_s_g.GetString().compare(unit) == 0)
    return L_Per_s_g;
  if (mL_Per_s_g.GetString().compare(unit) == 0)
    return mL_Per_s_g;
  if (mL_Per_min_kg.GetString().compare(unit) == 0)
    return mL_Per_min_kg;
  if (mL_Per_s_kg.GetString().compare(unit) == 0)
    return mL_Per_s_kg;
  if (uL_Per_min_kg.GetString().compare(unit) == 0)
    return uL_Per_min_kg;
  std::stringstream err;
  err << unit << " is not a valid VolumePerTimeMass unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolumePerTimeMass::Load(const cdm::ScalarVolumePerTimeMassData& src, SEScalarVolumePerTimeMass& dst)
{
  SEScalarVolumePerTimeMass::Serialize(src, dst);
}
void SEScalarVolumePerTimeMass::Serialize(const cdm::ScalarVolumePerTimeMassData& src, SEScalarVolumePerTimeMass& dst)
{
  SEScalarQuantity<VolumePerTimeMassUnit>::Serialize(src.scalarvolumepertimemass(), dst);
}

cdm::ScalarVolumePerTimeMassData* SEScalarVolumePerTimeMass::Unload(const SEScalarVolumePerTimeMass& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumePerTimeMassData* dst = new cdm::ScalarVolumePerTimeMassData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolumePerTimeMass::Serialize(const SEScalarVolumePerTimeMass& src, cdm::ScalarVolumePerTimeMassData& dst)
{
  SEScalarQuantity<VolumePerTimeMassUnit>::Serialize(src, *dst.mutable_scalarvolumepertimemass());
}