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
#include "properties/SEScalarHeatInductance.h"

const HeatInductanceUnit HeatInductanceUnit::K_s_Per_W("K s/W");

bool HeatInductanceUnit::IsValidUnit(const std::string& unit)
{
  if (K_s_Per_W.GetString().compare(unit) == 0)
    return true;
  return false;
}

const HeatInductanceUnit& HeatInductanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (K_s_Per_W.GetString().compare(unit) == 0)
    return K_s_Per_W;
  std::stringstream err;
  err << unit << " is not a valid HeatInductance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarHeatInductance::Load(const cdm::ScalarHeatInductanceData& src, SEScalarHeatInductance& dst)
{
  SEScalarHeatInductance::Serialize(src, dst);
}
void SEScalarHeatInductance::Serialize(const cdm::ScalarHeatInductanceData& src, SEScalarHeatInductance& dst)
{
  SEScalarQuantity<HeatInductanceUnit>::Serialize(src.scalarheatinductance(), dst);
}

cdm::ScalarHeatInductanceData* SEScalarHeatInductance::Unload(const SEScalarHeatInductance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarHeatInductanceData* dst = new cdm::ScalarHeatInductanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarHeatInductance::Serialize(const SEScalarHeatInductance& src, cdm::ScalarHeatInductanceData& dst)
{
  SEScalarQuantity<HeatInductanceUnit>::Serialize(src, *dst.mutable_scalarheatinductance());
}