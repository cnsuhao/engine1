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
#include "properties/SEScalarForce.h"

const ForceUnit ForceUnit::N("N");
const ForceUnit ForceUnit::lbf("lbf");
const ForceUnit ForceUnit::dyn("dyn");

bool ForceUnit::IsValidUnit(const std::string& unit)
{
  if (N.GetString().compare(unit) == 0)
    return true;
  if (lbf.GetString().compare(unit) == 0)
    return true;
  if (dyn.GetString().compare(unit) == 0)
    return true;
  return false;
}

const ForceUnit& ForceUnit::GetCompoundUnit(const std::string& unit)
{
  if (N.GetString().compare(unit) == 0)
    return N;
  if (lbf.GetString().compare(unit) == 0)
    return lbf;
  if (dyn.GetString().compare(unit) == 0)
    return dyn;
  std::stringstream err;
  err << unit << " is not a valid Force unit";
  throw CommonDataModelException(err.str());
}

void SEScalarForce::Load(const cdm::ScalarForceData& src, SEScalarForce& dst)
{
  SEScalarForce::Serialize(src, dst);
}
void SEScalarForce::Serialize(const cdm::ScalarForceData& src, SEScalarForce& dst)
{
  SEScalarQuantity<ForceUnit>::Serialize(src.scalarforce(), dst);
}

cdm::ScalarForceData* SEScalarForce::Unload(const SEScalarForce& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarForceData* dst = new cdm::ScalarForceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarForce::Serialize(const SEScalarForce& src, cdm::ScalarForceData& dst)
{
  SEScalarQuantity<ForceUnit>::Serialize(src, *dst.mutable_scalarforce());
}