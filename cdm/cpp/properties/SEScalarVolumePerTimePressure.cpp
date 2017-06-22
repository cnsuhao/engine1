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
#include "properties/SEScalarVolumePerTimePressure.h"

const VolumePerTimePressureUnit VolumePerTimePressureUnit::L_Per_s_mmHg("L/s mmHg");
const VolumePerTimePressureUnit VolumePerTimePressureUnit::mL_Per_s_mmHg("mL/s mmHg");
const VolumePerTimePressureUnit VolumePerTimePressureUnit::L_Per_min_mmHg("L/min mmHg");
const VolumePerTimePressureUnit VolumePerTimePressureUnit::mL_Per_min_mmHg("mL/min mmHg");

bool VolumePerTimePressureUnit::IsValidUnit(const std::string& unit)
{
  if (L_Per_s_mmHg.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_s_mmHg.GetString().compare(unit) == 0)
    return true;
  if (L_Per_min_mmHg.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_min_mmHg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const VolumePerTimePressureUnit& VolumePerTimePressureUnit::GetCompoundUnit(const std::string& unit)
{
  if (L_Per_s_mmHg.GetString().compare(unit) == 0)
    return L_Per_s_mmHg;
  if (mL_Per_s_mmHg.GetString().compare(unit) == 0)
    return mL_Per_s_mmHg;
  if (L_Per_min_mmHg.GetString().compare(unit) == 0)
    return L_Per_min_mmHg;
  if (mL_Per_min_mmHg.GetString().compare(unit) == 0)
    return mL_Per_min_mmHg;
  std::stringstream err;
  err << unit << " is not a valid VolumePerTimePressure unit";
  throw CommonDataModelException(err.str());
}

void SEScalarVolumePerTimePressure::Load(const cdm::ScalarVolumePerTimePressureData& src, SEScalarVolumePerTimePressure& dst)
{
  SEScalarVolumePerTimePressure::Serialize(src, dst);
}
void SEScalarVolumePerTimePressure::Serialize(const cdm::ScalarVolumePerTimePressureData& src, SEScalarVolumePerTimePressure& dst)
{
  SEScalarQuantity<VolumePerTimePressureUnit>::Serialize(src.scalarvolumepertimepressure(), dst);
}

cdm::ScalarVolumePerTimePressureData* SEScalarVolumePerTimePressure::Unload(const SEScalarVolumePerTimePressure& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarVolumePerTimePressureData* dst = new cdm::ScalarVolumePerTimePressureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarVolumePerTimePressure::Serialize(const SEScalarVolumePerTimePressure& src, cdm::ScalarVolumePerTimePressureData& dst)
{
  SEScalarQuantity<VolumePerTimePressureUnit>::Serialize(src, *dst.mutable_scalarvolumepertimepressure());
}