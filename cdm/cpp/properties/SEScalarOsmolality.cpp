/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "stdafx.h"
#include "properties/SEScalarOsmolality.h"

const OsmolalityUnit OsmolalityUnit::Osm_Per_kg("Osm/kg");
const OsmolalityUnit OsmolalityUnit::mOsm_Per_kg("mOsm/kg");

bool OsmolalityUnit::IsValidUnit(const std::string& unit)
{
  if (Osm_Per_kg.GetString().compare(unit) == 0)
    return true;
  if (mOsm_Per_kg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const OsmolalityUnit& OsmolalityUnit::GetCompoundUnit(const std::string& unit)
{
  if (Osm_Per_kg.GetString().compare(unit) == 0)
    return Osm_Per_kg;
  if (mOsm_Per_kg.GetString().compare(unit) == 0)
    return mOsm_Per_kg;
  std::stringstream err;
  err << unit << " is not a valid Osmolality unit";
  throw CommonDataModelException(err.str());
}

void SEScalarOsmolality::Load(const cdm::ScalarOsmolalityData& src, SEScalarOsmolality& dst)
{
  SEScalarOsmolality::Serialize(src, dst);
}
void SEScalarOsmolality::Serialize(const cdm::ScalarOsmolalityData& src, SEScalarOsmolality& dst)
{
  SEScalarQuantity<OsmolalityUnit>::Serialize(src.scalarosmolality(), dst);
}

cdm::ScalarOsmolalityData* SEScalarOsmolality::Unload(const SEScalarOsmolality& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarOsmolalityData* dst = new cdm::ScalarOsmolalityData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarOsmolality::Serialize(const SEScalarOsmolality& src, cdm::ScalarOsmolalityData& dst)
{
  SEScalarQuantity<OsmolalityUnit>::Serialize(src, *dst.mutable_scalarosmolality());
}