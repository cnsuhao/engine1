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
#include "properties/SEScalarArea.h"

const AreaUnit AreaUnit::cm2("cm^2");
const AreaUnit AreaUnit::m2("m^2");

bool AreaUnit::IsValidUnit(const std::string& unit)
{
  if (cm2.GetString().compare(unit) == 0)
    return true;
  if (m2.GetString().compare(unit) == 0)
    return true;
  return false;
}

const AreaUnit& AreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (cm2.GetString().compare(unit) == 0)
    return cm2;
  if (m2.GetString().compare(unit) == 0)
    return m2;
  std::stringstream err;
  err << unit << " is not a valid Area unit";
  throw CommonDataModelException(err.str());
}

void SEScalarArea::Load(const cdm::ScalarAreaData& src, SEScalarArea& dst)
{
  SEScalarArea::Serialize(src, dst);
}
void SEScalarArea::Serialize(const cdm::ScalarAreaData& src, SEScalarArea& dst)
{
  SEScalarQuantity<AreaUnit>::Serialize(src.scalararea(), dst);
}

cdm::ScalarAreaData* SEScalarArea::Unload(const SEScalarArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarAreaData* dst = new cdm::ScalarAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarArea::Serialize(const SEScalarArea& src, cdm::ScalarAreaData& dst)
{
  SEScalarQuantity<AreaUnit>::Serialize(src, *dst.mutable_scalararea());
}