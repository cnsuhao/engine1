/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarInverseVolume.h"

const InverseVolumeUnit InverseVolumeUnit::Inverse_L("1/L");
const InverseVolumeUnit InverseVolumeUnit::Inverse_mL("1/mL");

bool InverseVolumeUnit::IsValidUnit(const std::string& unit)
{
  if (Inverse_L.GetString().compare(unit) == 0)
    return true;
  if (Inverse_mL.GetString().compare(unit) == 0)
    return true;
  return false;
}

const InverseVolumeUnit& InverseVolumeUnit::GetCompoundUnit(const std::string& unit)
{
  if (Inverse_L.GetString().compare(unit) == 0)
    return Inverse_L;
  if (Inverse_mL.GetString().compare(unit) == 0)
    return Inverse_mL;
  std::stringstream err;
  err << unit << " is not a valid Volume unit";
  throw CommonDataModelException(err.str());
}

void SEScalarInverseVolume::Load(const cdm::ScalarInverseVolumeData& src, SEScalarInverseVolume& dst)
{
  SEScalarInverseVolume::Serialize(src, dst);
}
void SEScalarInverseVolume::Serialize(const cdm::ScalarInverseVolumeData& src, SEScalarInverseVolume& dst)
{
  SEScalarQuantity<InverseVolumeUnit>::Serialize(src.scalarinversevolume(), dst);
}

cdm::ScalarInverseVolumeData* SEScalarInverseVolume::Unload(const SEScalarInverseVolume& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarInverseVolumeData* dst = new cdm::ScalarInverseVolumeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarInverseVolume::Serialize(const SEScalarInverseVolume& src, cdm::ScalarInverseVolumeData& dst)
{
  SEScalarQuantity<InverseVolumeUnit>::Serialize(src, *dst.mutable_scalarinversevolume());
}