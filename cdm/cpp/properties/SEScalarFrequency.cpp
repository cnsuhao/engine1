/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarFrequency.h"

const FrequencyUnit FrequencyUnit::Per_min("1/min");
const FrequencyUnit FrequencyUnit::Per_s("1/s");
const FrequencyUnit FrequencyUnit::Hz("Hz");

bool FrequencyUnit::IsValidUnit(const std::string& unit)
{
  if (Per_min.GetString().compare(unit) == 0)
    return true;
  if (Per_s.GetString().compare(unit) == 0)
    return true;
  if (Hz.GetString().compare(unit) == 0)
    return true;
  return false;
}

const FrequencyUnit& FrequencyUnit::GetCompoundUnit(const std::string& unit)
{
  if (Per_min.GetString().compare(unit) == 0)
    return Per_min;
  if (Per_s.GetString().compare(unit) == 0)
    return Per_s;
  if (Hz.GetString().compare(unit) == 0)
    return Hz;
  std::stringstream err;
  err << unit << " is not a valid Frequency unit";
  throw CommonDataModelException(err.str());
}

void SEScalarFrequency::Load(const cdm::ScalarFrequencyData& src, SEScalarFrequency& dst)
{
  SEScalarFrequency::Serialize(src, dst);
}
void SEScalarFrequency::Serialize(const cdm::ScalarFrequencyData& src, SEScalarFrequency& dst)
{
  SEScalarQuantity<FrequencyUnit>::Serialize(src.scalarfrequency(), dst);
}

cdm::ScalarFrequencyData* SEScalarFrequency::Unload(const SEScalarFrequency& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarFrequencyData* dst = new cdm::ScalarFrequencyData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarFrequency::Serialize(const SEScalarFrequency& src, cdm::ScalarFrequencyData& dst)
{
  SEScalarQuantity<FrequencyUnit>::Serialize(src, *dst.mutable_scalarfrequency());
}