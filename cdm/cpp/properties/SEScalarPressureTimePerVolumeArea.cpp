/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarPressureTimePerVolumeArea.h"

const PressureTimePerVolumeAreaUnit PressureTimePerVolumeAreaUnit::mmHg_min_Per_mL_m2("mmHg min/mL m^2");
const PressureTimePerVolumeAreaUnit PressureTimePerVolumeAreaUnit::mmHg_s_Per_mL_m2("mmHg s/mL m^2");
const PressureTimePerVolumeAreaUnit PressureTimePerVolumeAreaUnit::dyn_s_Per_cm5_m2("dyn s/cm^5 m^2");

bool PressureTimePerVolumeAreaUnit::IsValidUnit(const std::string& unit)
{
  if (mmHg_min_Per_mL_m2.GetString().compare(unit) == 0)
    return true;
  if (mmHg_s_Per_mL_m2.GetString().compare(unit) == 0)
    return true;
  if (dyn_s_Per_cm5_m2.GetString().compare(unit) == 0)
    return true;
  return false;
}

const PressureTimePerVolumeAreaUnit& PressureTimePerVolumeAreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (mmHg_min_Per_mL_m2.GetString().compare(unit) == 0)
    return mmHg_min_Per_mL_m2;
  if (mmHg_s_Per_mL_m2.GetString().compare(unit) == 0)
    return mmHg_s_Per_mL_m2;
  if (dyn_s_Per_cm5_m2.GetString().compare(unit) == 0)
    return dyn_s_Per_cm5_m2;
  std::stringstream err;
  err << unit << " is not a valid PressureTimePerVolumeArea unit";
  throw CommonDataModelException(err.str());
}

void SEScalarPressureTimePerVolumeArea::Load(const cdm::ScalarPressureTimePerVolumeAreaData& src, SEScalarPressureTimePerVolumeArea& dst)
{
  SEScalarPressureTimePerVolumeArea::Serialize(src, dst);
}
void SEScalarPressureTimePerVolumeArea::Serialize(const cdm::ScalarPressureTimePerVolumeAreaData& src, SEScalarPressureTimePerVolumeArea& dst)
{
  SEScalarQuantity<PressureTimePerVolumeAreaUnit>::Serialize(src.scalarpressuretimepervolumearea(), dst);
}

cdm::ScalarPressureTimePerVolumeAreaData* SEScalarPressureTimePerVolumeArea::Unload(const SEScalarPressureTimePerVolumeArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarPressureTimePerVolumeAreaData* dst = new cdm::ScalarPressureTimePerVolumeAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarPressureTimePerVolumeArea::Serialize(const SEScalarPressureTimePerVolumeArea& src, cdm::ScalarPressureTimePerVolumeAreaData& dst)
{
  SEScalarQuantity<PressureTimePerVolumeAreaUnit>::Serialize(src, *dst.mutable_scalarpressuretimepervolumearea());
}