/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarVolumePerTimeArea.h"

const VolumePerTimeAreaUnit VolumePerTimeAreaUnit::mL_Per_min_m2("mL/min m^2");
const VolumePerTimeAreaUnit VolumePerTimeAreaUnit::mL_Per_s_m2("mL/s m^2");
const VolumePerTimeAreaUnit VolumePerTimeAreaUnit::L_Per_min_m2("L/min m^2");

bool VolumePerTimeAreaUnit::IsValidUnit(const std::string& unit)
{
  if (mL_Per_min_m2.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_s_m2.GetString().compare(unit) == 0)
    return true;
  if (L_Per_min_m2.GetString().compare(unit) == 0)
    return true;
  return false;
}

const VolumePerTimeAreaUnit& VolumePerTimeAreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (mL_Per_min_m2.GetString().compare(unit) == 0)
    return mL_Per_min_m2;
  if (mL_Per_s_m2.GetString().compare(unit) == 0)
    return mL_Per_s_m2;
  if (L_Per_min_m2.GetString().compare(unit) == 0)
    return L_Per_min_m2;
  std::stringstream err;
  err << unit << " is not a valid VolumePerTimeArea unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolumePerTimeArea::Load(const cdm::ScalarVolumePerTimeAreaData& src, SEScalarVolumePerTimeArea& dst)
{
  SEScalarVolumePerTimeArea::Serialize(src, dst);
}
void SEScalarVolumePerTimeArea::Serialize(const cdm::ScalarVolumePerTimeAreaData& src, SEScalarVolumePerTimeArea& dst)
{
  SEScalarQuantity<VolumePerTimeAreaUnit>::Serialize(src.scalarvolumepertimearea(), dst);
}

cdm::ScalarVolumePerTimeAreaData* SEScalarVolumePerTimeArea::Unload(const SEScalarVolumePerTimeArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumePerTimeAreaData* dst = new cdm::ScalarVolumePerTimeAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolumePerTimeArea::Serialize(const SEScalarVolumePerTimeArea& src, cdm::ScalarVolumePerTimeAreaData& dst)
{
  SEScalarQuantity<VolumePerTimeAreaUnit>::Serialize(src, *dst.mutable_scalarvolumepertimearea());
}