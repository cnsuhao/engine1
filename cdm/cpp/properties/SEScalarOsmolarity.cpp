/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarOsmolarity.h"

const OsmolarityUnit OsmolarityUnit::Osm_Per_L("Osm/L");
const OsmolarityUnit OsmolarityUnit::mOsm_Per_L("mOsm/L");

bool OsmolarityUnit::IsValidUnit(const std::string& unit)
{
  if (Osm_Per_L.GetString().compare(unit) == 0)
    return true;
  if (mOsm_Per_L.GetString().compare(unit) == 0)
    return true;
  return false;
}

const OsmolarityUnit& OsmolarityUnit::GetCompoundUnit(const std::string& unit)
{
  if (Osm_Per_L.GetString().compare(unit) == 0)
    return Osm_Per_L;
  if (mOsm_Per_L.GetString().compare(unit) == 0)
    return mOsm_Per_L;
  std::stringstream err;
  err << unit << " is not a valid Osmolarity unit";
  throw CommonDataModelException(err.str());
}

void SEScalarOsmolarity::Load(const cdm::ScalarOsmolarityData& src, SEScalarOsmolarity& dst)
{
  SEScalarOsmolarity::Serialize(src, dst);
}
void SEScalarOsmolarity::Serialize(const cdm::ScalarOsmolarityData& src, SEScalarOsmolarity& dst)
{
  SEScalarQuantity<OsmolarityUnit>::Serialize(src.scalarosmolarity(), dst);
}

cdm::ScalarOsmolarityData* SEScalarOsmolarity::Unload(const SEScalarOsmolarity& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarOsmolarityData* dst = new cdm::ScalarOsmolarityData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarOsmolarity::Serialize(const SEScalarOsmolarity& src, cdm::ScalarOsmolarityData& dst)
{
  SEScalarQuantity<OsmolarityUnit>::Serialize(src, *dst.mutable_scalarosmolarity());
}