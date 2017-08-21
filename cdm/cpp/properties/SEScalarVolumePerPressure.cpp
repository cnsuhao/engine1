/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarVolumePerPressure.h"

const VolumePerPressureUnit VolumePerPressureUnit::L_Per_Pa("L/Pa");
const VolumePerPressureUnit VolumePerPressureUnit::L_Per_cmH2O("L/cmH2O");

bool VolumePerPressureUnit::IsValidUnit(const std::string& unit)
{
  if (L_Per_Pa.GetString().compare(unit) == 0)
    return true;
  if (L_Per_cmH2O.GetString().compare(unit) == 0)
    return true;
  return false;
}

const VolumePerPressureUnit& VolumePerPressureUnit::GetCompoundUnit(const std::string& unit)
{
  if (L_Per_Pa.GetString().compare(unit) == 0)
    return L_Per_Pa;
  if (L_Per_cmH2O.GetString().compare(unit) == 0)
    return L_Per_cmH2O;
  std::stringstream err;
  err << unit << " is not a valid VolumePerPressure unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolumePerPressure::Load(const cdm::ScalarVolumePerPressureData& src, SEScalarVolumePerPressure& dst)
{
  SEScalarVolumePerPressure::Serialize(src, dst);
}
void SEScalarVolumePerPressure::Serialize(const cdm::ScalarVolumePerPressureData& src, SEScalarVolumePerPressure& dst)
{
  SEScalarQuantity<VolumePerPressureUnit>::Serialize(src.scalarvolumeperpressure(), dst);
}

cdm::ScalarVolumePerPressureData* SEScalarVolumePerPressure::Unload(const SEScalarVolumePerPressure& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumePerPressureData* dst = new cdm::ScalarVolumePerPressureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolumePerPressure::Serialize(const SEScalarVolumePerPressure& src, cdm::ScalarVolumePerPressureData& dst)
{
  SEScalarQuantity<VolumePerPressureUnit>::Serialize(src, *dst.mutable_scalarvolumeperpressure());
}