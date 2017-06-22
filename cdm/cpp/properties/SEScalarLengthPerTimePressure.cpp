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
#include "properties/SEScalarLengthPerTimePressure.h"

const LengthPerTimePressureUnit LengthPerTimePressureUnit::m_Per_s_mmHg("m/s mmHg");
const LengthPerTimePressureUnit LengthPerTimePressureUnit::cm_Per_s_mmHg("cm/s mmHg");
const LengthPerTimePressureUnit LengthPerTimePressureUnit::m_Per_min_mmHg("m/min mmHg");
const LengthPerTimePressureUnit LengthPerTimePressureUnit::cm_Per_min_mmHg("cm/min mmHg");

bool LengthPerTimePressureUnit::IsValidUnit(const std::string& unit)
{
  if (m_Per_s_mmHg.GetString().compare(unit) == 0)
    return true;
  if (cm_Per_s_mmHg.GetString().compare(unit) == 0)
    return true;
  if (m_Per_min_mmHg.GetString().compare(unit) == 0)
    return true;
  if (cm_Per_min_mmHg.GetString().compare(unit) == 0)
    return true;
  return false;
}

const LengthPerTimePressureUnit& LengthPerTimePressureUnit::GetCompoundUnit(const std::string& unit)
{
  if (m_Per_s_mmHg.GetString().compare(unit) == 0)
    return m_Per_s_mmHg;
  if (cm_Per_s_mmHg.GetString().compare(unit) == 0)
    return cm_Per_s_mmHg;
  if (m_Per_min_mmHg.GetString().compare(unit) == 0)
    return m_Per_min_mmHg;
  if (cm_Per_min_mmHg.GetString().compare(unit) == 0)
    return cm_Per_min_mmHg;
  std::stringstream err;
  err << unit << " is not a valid LengthPerTimePressure unit";
  throw CommonDataModelException(err.str());
}

void SEScalarLengthPerTimePressure::Load(const cdm::ScalarLengthPerTimePressureData& src, SEScalarLengthPerTimePressure& dst)
{
  SEScalarLengthPerTimePressure::Serialize(src, dst);
}
void SEScalarLengthPerTimePressure::Serialize(const cdm::ScalarLengthPerTimePressureData& src, SEScalarLengthPerTimePressure& dst)
{
  SEScalarQuantity<LengthPerTimePressureUnit>::Serialize(src.scalarlengthpertimepressure(), dst);
}

cdm::ScalarLengthPerTimePressureData* SEScalarLengthPerTimePressure::Unload(const SEScalarLengthPerTimePressure& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarLengthPerTimePressureData* dst = new cdm::ScalarLengthPerTimePressureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarLengthPerTimePressure::Serialize(const SEScalarLengthPerTimePressure& src, cdm::ScalarLengthPerTimePressureData& dst)
{
  SEScalarQuantity<LengthPerTimePressureUnit>::Serialize(src, *dst.mutable_scalarlengthpertimepressure());
}