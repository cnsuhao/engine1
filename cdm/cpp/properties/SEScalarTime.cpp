/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarTime.h"

#pragma push_macro("Time")
#undef min
const TimeUnit TimeUnit::s("s");
const TimeUnit TimeUnit::min("min");
const TimeUnit TimeUnit::hr("hr");
const TimeUnit TimeUnit::day("day");
const TimeUnit TimeUnit::yr("yr");
#pragma pop_macro("Time")

bool TimeUnit::IsValidUnit(const std::string& unit)
{
  if (s.GetString().compare(unit) == 0)
    return true;
  if (min.GetString().compare(unit) == 0)
    return true;
  if (hr.GetString().compare(unit) == 0)
    return true;
  if (day.GetString().compare(unit) == 0)
    return true;
  if (yr.GetString().compare(unit) == 0)
    return true;
  return false;
}

const TimeUnit& TimeUnit::GetCompoundUnit(const std::string& unit)
{
  if(s.GetString().compare(unit)==0)
    return s;
  if(min.GetString().compare(unit)==0)
    return min;
  if (hr.GetString().compare(unit) == 0)
    return hr;
  if (day.GetString().compare(unit) == 0)
    return day;
  if(yr.GetString().compare(unit)==0)
    return yr;
  std::stringstream err;
  err << unit << " is not a valid Amount unit";
  throw CommonDataModelException(err.str());
}

void SEScalarTime::Load(const cdm::ScalarTimeData& src, SEScalarTime& dst)
{
  SEScalarTime::Serialize(src, dst);
}
void SEScalarTime::Serialize(const cdm::ScalarTimeData& src, SEScalarTime& dst)
{
  SEScalarQuantity<TimeUnit>::Serialize(src.scalartime(), dst);
}

cdm::ScalarTimeData* SEScalarTime::Unload(const SEScalarTime& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarTimeData* dst = new cdm::ScalarTimeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarTime::Serialize(const SEScalarTime& src, cdm::ScalarTimeData& dst)
{
  SEScalarQuantity<TimeUnit>::Serialize(src, *dst.mutable_scalartime());
}