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
#include "properties/SEScalarElectricCharge.h"

const ElectricChargeUnit ElectricChargeUnit::C("C");

bool ElectricChargeUnit::IsValidUnit(const std::string& unit)
{
  if (C.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricChargeUnit& ElectricChargeUnit::GetCompoundUnit(const std::string& unit)
{
  if (C.GetString().compare(unit) == 0)
    return C;
  std::stringstream err;
  err << unit << " is not a valid ElectricCharge unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricCharge::Load(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst)
{
  SEScalarElectricCharge::Serialize(src, dst);
}
void SEScalarElectricCharge::Serialize(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst)
{
  SEScalarQuantity<ElectricChargeUnit>::Serialize(src.scalarelectriccharge(), dst);
}

cdm::ScalarElectricChargeData* SEScalarElectricCharge::Unload(const SEScalarElectricCharge& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricChargeData* dst = new cdm::ScalarElectricChargeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricCharge::Serialize(const SEScalarElectricCharge& src, cdm::ScalarElectricChargeData& dst)
{
  SEScalarQuantity<ElectricChargeUnit>::Serialize(src, *dst.mutable_scalarelectriccharge());
}