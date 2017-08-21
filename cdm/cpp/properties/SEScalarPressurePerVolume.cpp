/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarPressurePerVolume.h"

const PressurePerVolumeUnit PressurePerVolumeUnit::mmHg_Per_mL("mmHg/mL");
const PressurePerVolumeUnit PressurePerVolumeUnit::cmH2O_Per_mL("cmH2O/mL");

bool PressurePerVolumeUnit::IsValidUnit(const std::string& unit)
{
  if (mmHg_Per_mL.GetString().compare(unit) == 0)
    return true;
  if (cmH2O_Per_mL.GetString().compare(unit) == 0)
    return true;
  return false;
}

const PressurePerVolumeUnit& PressurePerVolumeUnit::GetCompoundUnit(const std::string& unit)
{
  if (mmHg_Per_mL.GetString().compare(unit) == 0)
    return mmHg_Per_mL;
  if (cmH2O_Per_mL.GetString().compare(unit) == 0)
    return cmH2O_Per_mL;
  std::stringstream err;
  err << unit << " is not a valid PressurePerVolume unit";
  throw CommonDataModelException(err.str());
}

void SEScalarPressurePerVolume::Load(const cdm::ScalarPressurePerVolumeData& src, SEScalarPressurePerVolume& dst)
{
  SEScalarPressurePerVolume::Serialize(src, dst);
}
void SEScalarPressurePerVolume::Serialize(const cdm::ScalarPressurePerVolumeData& src, SEScalarPressurePerVolume& dst)
{
  SEScalarQuantity<PressurePerVolumeUnit>::Serialize(src.scalarpressurepervolume(), dst);
}

cdm::ScalarPressurePerVolumeData* SEScalarPressurePerVolume::Unload(const SEScalarPressurePerVolume& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarPressurePerVolumeData* dst = new cdm::ScalarPressurePerVolumeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarPressurePerVolume::Serialize(const SEScalarPressurePerVolume& src, cdm::ScalarPressurePerVolumeData& dst)
{
  SEScalarQuantity<PressurePerVolumeUnit>::Serialize(src, *dst.mutable_scalarpressurepervolume());
}