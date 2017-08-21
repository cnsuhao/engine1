/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarVolume.h"

const VolumeUnit VolumeUnit::L("L");
const VolumeUnit VolumeUnit::dL("dL");
const VolumeUnit VolumeUnit::mL("mL");
const VolumeUnit VolumeUnit::uL("uL");
const VolumeUnit VolumeUnit::m3("m^3");

bool VolumeUnit::IsValidUnit(const std::string& unit)
{
  if (L.GetString().compare(unit) == 0)
    return true;
  if (dL.GetString().compare(unit) == 0)
    return true;
  if (mL.GetString().compare(unit) == 0)
    return true;
  if (uL.GetString().compare(unit) == 0)
    return true;
  if (m3.GetString().compare(unit) == 0)
    return true;
  return false;
}

const VolumeUnit& VolumeUnit::GetCompoundUnit(const std::string& unit)
{
  if(L.GetString().compare(unit)==0)
    return L;
  if(mL.GetString().compare(unit)==0)
    return mL;
  if(m3.GetString().compare(unit)==0)
    return m3;
  if (dL.GetString().compare(unit) == 0)
    return dL;
  if (uL.GetString().compare(unit) == 0)
    return uL;
  std::stringstream err;
  err << unit << " is not a valid Volume unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolume::Load(const cdm::ScalarVolumeData& src, SEScalarVolume& dst)
{
  SEScalarVolume::Serialize(src, dst);
}
void SEScalarVolume::Serialize(const cdm::ScalarVolumeData& src, SEScalarVolume& dst)
{
  SEScalarQuantity<VolumeUnit>::Serialize(src.scalarvolume(), dst);
}

cdm::ScalarVolumeData* SEScalarVolume::Unload(const SEScalarVolume& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumeData* dst = new cdm::ScalarVolumeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolume::Serialize(const SEScalarVolume& src, cdm::ScalarVolumeData& dst)
{
  SEScalarQuantity<VolumeUnit>::Serialize(src, *dst.mutable_scalarvolume());
}