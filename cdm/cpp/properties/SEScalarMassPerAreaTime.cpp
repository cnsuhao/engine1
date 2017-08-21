/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarMassPerAreaTime.h"

const MassPerAreaTimeUnit MassPerAreaTimeUnit::g_Per_cm2_s("g/cm^2 s");

bool MassPerAreaTimeUnit::IsValidUnit(const std::string& unit)
{
  if (g_Per_cm2_s.GetString().compare(unit) == 0)
    return true;
  return false;
}

const MassPerAreaTimeUnit& MassPerAreaTimeUnit::GetCompoundUnit(const std::string& unit)
{
  if (g_Per_cm2_s.GetString().compare(unit) == 0)
    return g_Per_cm2_s;
  std::stringstream err;
  err << unit << " is not a valid MassPerAreaTime unit";
  throw CommonDataModelException(err.str());
}

void SEScalarMassPerAreaTime::Load(const cdm::ScalarMassPerAreaTimeData& src, SEScalarMassPerAreaTime& dst)
{
  SEScalarMassPerAreaTime::Serialize(src, dst);
}
void SEScalarMassPerAreaTime::Serialize(const cdm::ScalarMassPerAreaTimeData& src, SEScalarMassPerAreaTime& dst)
{
  SEScalarQuantity<MassPerAreaTimeUnit>::Serialize(src.scalarmassperareatime(), dst);
}

cdm::ScalarMassPerAreaTimeData* SEScalarMassPerAreaTime::Unload(const SEScalarMassPerAreaTime& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarMassPerAreaTimeData* dst = new cdm::ScalarMassPerAreaTimeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarMassPerAreaTime::Serialize(const SEScalarMassPerAreaTime& src, cdm::ScalarMassPerAreaTimeData& dst)
{
  SEScalarQuantity<MassPerAreaTimeUnit>::Serialize(src, *dst.mutable_scalarmassperareatime());
}