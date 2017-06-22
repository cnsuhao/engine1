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
#include "properties/SEScalarFlowResistance.h"

const FlowResistanceUnit FlowResistanceUnit::cmH2O_s_Per_L("cmH2O s/L");
const FlowResistanceUnit FlowResistanceUnit::mmHg_s_Per_mL("mmHg s/mL");
const FlowResistanceUnit FlowResistanceUnit::mmHg_min_Per_mL("mmHg min/mL");
const FlowResistanceUnit FlowResistanceUnit::mmHg_min_Per_L("mmHg min/L");
const FlowResistanceUnit FlowResistanceUnit::Pa_s_Per_m3("Pa s/m^3");

bool FlowResistanceUnit::IsValidUnit(const std::string& unit)
{
  if (cmH2O_s_Per_L.GetString().compare(unit) == 0)
    return true;
  if (mmHg_s_Per_mL.GetString().compare(unit) == 0)
    return true;
  if (mmHg_min_Per_mL.GetString().compare(unit) == 0)
    return true;
  if (mmHg_min_Per_L.GetString().compare(unit) == 0)
    return true;
  if (Pa_s_Per_m3.GetString().compare(unit) == 0)
    return true;
  return false;
}

const FlowResistanceUnit& FlowResistanceUnit::GetCompoundUnit(const std::string& unit)
{
  if (cmH2O_s_Per_L.GetString().compare(unit) == 0)
    return cmH2O_s_Per_L;
  if (mmHg_s_Per_mL.GetString().compare(unit) == 0)
    return mmHg_s_Per_mL;
  if (mmHg_min_Per_mL.GetString().compare(unit) == 0)
    return mmHg_min_Per_mL;
  if (mmHg_min_Per_L.GetString().compare(unit) == 0)
    return mmHg_min_Per_L;
  if (Pa_s_Per_m3.GetString().compare(unit) == 0)
    return Pa_s_Per_m3;
  std::stringstream err;
  err << unit << " is not a valid FlowResistance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarFlowResistance::Load(const cdm::ScalarFlowResistanceData& src, SEScalarFlowResistance& dst)
{
  SEScalarFlowResistance::Serialize(src, dst);
}
void SEScalarFlowResistance::Serialize(const cdm::ScalarFlowResistanceData& src, SEScalarFlowResistance& dst)
{
  SEScalarQuantity<FlowResistanceUnit>::Serialize(src.scalarflowresistance(), dst);
}

cdm::ScalarFlowResistanceData* SEScalarFlowResistance::Unload(const SEScalarFlowResistance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarFlowResistanceData* dst = new cdm::ScalarFlowResistanceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarFlowResistance::Serialize(const SEScalarFlowResistance& src, cdm::ScalarFlowResistanceData& dst)
{
  SEScalarQuantity<FlowResistanceUnit>::Serialize(src, *dst.mutable_scalarflowresistance());
}