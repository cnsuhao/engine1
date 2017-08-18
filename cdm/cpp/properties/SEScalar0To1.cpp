/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalar0To1.h"

SEScalar0To1::SEScalar0To1() : SEScalar()
{

}

void SEScalar0To1::SetValue(double d)
{ 
  if (d > 1 || d < 0)
    throw CommonDataModelException("SEScalar0To1 must be between [0,1]");
  SEScalar::SetValue(d);
}

void SEScalar0To1::SetValue(double d, const NoUnit& unitless)
{ 
  SEScalar0To1::SetValue(d);
}

void SEScalar0To1::ForceValue(double d)
{
  SEScalar::SetValue(d);
}

void SEScalar0To1::ForceValue(double d, const NoUnit& unitless)
{
  SEScalar::SetValue(d);
}

void SEScalar0To1::Load(const cdm::Scalar0To1Data& src, SEScalar0To1& dst)
{
  SEScalar0To1::Serialize(src, dst);
}
void SEScalar0To1::Serialize(const cdm::Scalar0To1Data& src, SEScalar0To1& dst)
{
  SEScalar::Serialize(src.scalar0to1(), dst);
}

cdm::Scalar0To1Data* SEScalar0To1::Unload(const SEScalar0To1& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::Scalar0To1Data* dst = new cdm::Scalar0To1Data();
  Serialize(src, *dst);
  return dst;
}
void SEScalar0To1::Serialize(const SEScalar0To1& src, cdm::Scalar0To1Data& dst)
{
  SEScalar::Serialize(src, *dst.mutable_scalar0to1());
}
