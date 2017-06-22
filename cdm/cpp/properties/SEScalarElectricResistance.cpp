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
#include "properties/SEScalarElectricResistance.h"

const ElectricResistanceUnit ElectricResistanceUnit::Ohm("ohm");

bool ElectricResistanceUnit::IsValidUnit(const std::string& unit)
{
  if (Ohm.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricResistanceUnit& ElectricResistanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (Ohm.GetString().compare(unit) == 0)
    return Ohm;
  std::stringstream err;
  err << unit << " is not a valid ElectricResistance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricResistance::Load(const cdm::ScalarElectricResistanceData& src, SEScalarElectricResistance& dst)
{
  SEScalarElectricResistance::Serialize(src, dst);
}
void SEScalarElectricResistance::Serialize(const cdm::ScalarElectricResistanceData& src, SEScalarElectricResistance& dst)
{
  SEScalarQuantity<ElectricResistanceUnit>::Serialize(src.scalarelectricresistance(), dst);
}

cdm::ScalarElectricResistanceData* SEScalarElectricResistance::Unload(const SEScalarElectricResistance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricResistanceData* dst = new cdm::ScalarElectricResistanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricResistance::Serialize(const SEScalarElectricResistance& src, cdm::ScalarElectricResistanceData& dst)
{
  SEScalarQuantity<ElectricResistanceUnit>::Serialize(src, *dst.mutable_scalarelectricresistance());
}