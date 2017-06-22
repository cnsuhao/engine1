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
#include "properties/SEScalarNegative1To1.h"

SEScalarNegative1To1::SEScalarNegative1To1() : SEScalar()
{

}

void SEScalarNegative1To1::SetValue(double d)
{ 
  if (d > 1 || d < -1)
    throw CommonDataModelException("SEScalarNegative1To1 must be between [-1,1]");
  SEScalar::SetValue(d);
}

void SEScalarNegative1To1::SetValue(double d, const NoUnit& unitless)
{ 
  SEScalarNegative1To1::SetValue(d);
}

void SEScalarNegative1To1::Load(const cdm::ScalarNegative1To1Data& src, SEScalarNegative1To1& dst)
{
  SEScalarNegative1To1::Serialize(src, dst);
}
void SEScalarNegative1To1::Serialize(const cdm::ScalarNegative1To1Data& src, SEScalarNegative1To1& dst)
{
  SEScalar::Serialize(src.scalarnegative1to1(), dst);
}

cdm::ScalarNegative1To1Data* SEScalarNegative1To1::Unload(const SEScalarNegative1To1& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarNegative1To1Data* dst = new cdm::ScalarNegative1To1Data();
  Serialize(src, *dst);
  return dst;
}
void SEScalarNegative1To1::Serialize(const SEScalarNegative1To1& src, cdm::ScalarNegative1To1Data& dst)
{
  SEScalar::Serialize(src, *dst.mutable_scalarnegative1to1());
}                                       