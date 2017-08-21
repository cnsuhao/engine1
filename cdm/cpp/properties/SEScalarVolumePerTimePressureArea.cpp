/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarVolumePerTimePressureArea.h"

const VolumePerTimePressureAreaUnit VolumePerTimePressureAreaUnit::mL_Per_min_mmHg_m2("mL/min mmHg m^2");
const VolumePerTimePressureAreaUnit VolumePerTimePressureAreaUnit::mL_Per_s_mmHg_m2("mL/s mmHg m^2");

bool VolumePerTimePressureAreaUnit::IsValidUnit(const std::string& unit)
{
  if (mL_Per_min_mmHg_m2.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_s_mmHg_m2.GetString().compare(unit) == 0)
    return true; 
  return false;
}

const VolumePerTimePressureAreaUnit& VolumePerTimePressureAreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (mL_Per_min_mmHg_m2.GetString().compare(unit) == 0)
    return mL_Per_min_mmHg_m2;
  if (mL_Per_s_mmHg_m2.GetString().compare(unit) == 0)
    return mL_Per_s_mmHg_m2;  
  std::stringstream err;
  err << unit << " is not a valid VolumePerTimePressureArea unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolumePerTimePressureArea::Load(const cdm::ScalarVolumePerTimePressureAreaData& src, SEScalarVolumePerTimePressureArea& dst)
{
  SEScalarVolumePerTimePressureArea::Serialize(src, dst);
}
void SEScalarVolumePerTimePressureArea::Serialize(const cdm::ScalarVolumePerTimePressureAreaData& src, SEScalarVolumePerTimePressureArea& dst)
{
  SEScalarQuantity<VolumePerTimePressureAreaUnit>::Serialize(src.scalarvolumepertimepressurearea(), dst);
}

cdm::ScalarVolumePerTimePressureAreaData* SEScalarVolumePerTimePressureArea::Unload(const SEScalarVolumePerTimePressureArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumePerTimePressureAreaData* dst = new cdm::ScalarVolumePerTimePressureAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolumePerTimePressureArea::Serialize(const SEScalarVolumePerTimePressureArea& src, cdm::ScalarVolumePerTimePressureAreaData& dst)
{
  SEScalarQuantity<VolumePerTimePressureAreaUnit>::Serialize(src, *dst.mutable_scalarvolumepertimepressurearea());
}