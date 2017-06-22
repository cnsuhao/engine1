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
#include "properties/SEScalarElectricInductance.h"

const ElectricInductanceUnit ElectricInductanceUnit::H("H");

bool ElectricInductanceUnit::IsValidUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ElectricInductanceUnit& ElectricInductanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (H.GetString().compare(unit) == 0)
    return H;
  std::stringstream err;
  err << unit << " is not a valid ElectricInductance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarElectricInductance::Load(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst)
{
  SEScalarElectricInductance::Serialize(src, dst);
}
void SEScalarElectricInductance::Serialize(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst)
{
  SEScalarQuantity<ElectricInductanceUnit>::Serialize(src.scalarelectricinductance(), dst);
}

cdm::ScalarElectricInductanceData* SEScalarElectricInductance::Unload(const SEScalarElectricInductance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarElectricInductanceData* dst = new cdm::ScalarElectricInductanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarElectricInductance::Serialize(const SEScalarElectricInductance& src, cdm::ScalarElectricInductanceData& dst)
{
  SEScalarQuantity<ElectricInductanceUnit>::Serialize(src, *dst.mutable_scalarelectricinductance());
}