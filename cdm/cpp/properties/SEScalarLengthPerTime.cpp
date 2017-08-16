/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarLengthPerTime.h"

const LengthPerTimeUnit LengthPerTimeUnit::m_Per_s("m/s");
const LengthPerTimeUnit LengthPerTimeUnit::cm_Per_s("cm/s");
const LengthPerTimeUnit LengthPerTimeUnit::m_Per_min("m/min");
const LengthPerTimeUnit LengthPerTimeUnit::cm_Per_min("cm/min");
const LengthPerTimeUnit LengthPerTimeUnit::ft_Per_s("ft/s");
const LengthPerTimeUnit LengthPerTimeUnit::ft_Per_min("ft/min");

bool LengthPerTimeUnit::IsValidUnit(const std::string& unit)
{
  if (m_Per_s.GetString().compare(unit) == 0)
    return true;
  if (cm_Per_s.GetString().compare(unit) == 0)
    return true;
  if (m_Per_min.GetString().compare(unit) == 0)
    return true;
  if (cm_Per_min.GetString().compare(unit) == 0)
    return true;
  if (ft_Per_s.GetString().compare(unit) == 0)
    return true;
  if (ft_Per_min.GetString().compare(unit) == 0)
    return true;
  return false;
}

const LengthPerTimeUnit& LengthPerTimeUnit::GetCompoundUnit(const std::string& unit)
{
  if (m_Per_s.GetString().compare(unit) == 0)
    return m_Per_s;
  if (cm_Per_s.GetString().compare(unit) == 0)
    return cm_Per_s;
  if (m_Per_min.GetString().compare(unit) == 0)
    return m_Per_min;
  if (cm_Per_min.GetString().compare(unit) == 0)
    return cm_Per_min;
  if (ft_Per_s.GetString().compare(unit) == 0)
    return ft_Per_s;
  if (ft_Per_min.GetString().compare(unit) == 0)
    return ft_Per_min;
  std::stringstream err;
  err << unit << " is not a valid LengthPerTime unit";
  throw CommonDataModelException(err.str());
}

void SEScalarLengthPerTime::Load(const cdm::ScalarLengthPerTimeData& src, SEScalarLengthPerTime& dst)
{
  SEScalarLengthPerTime::Serialize(src, dst);
}
void SEScalarLengthPerTime::Serialize(const cdm::ScalarLengthPerTimeData& src, SEScalarLengthPerTime& dst)
{
  SEScalarQuantity<LengthPerTimeUnit>::Serialize(src.scalarlengthpertime(), dst);
}

cdm::ScalarLengthPerTimeData* SEScalarLengthPerTime::Unload(const SEScalarLengthPerTime& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarLengthPerTimeData* dst = new cdm::ScalarLengthPerTimeData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarLengthPerTime::Serialize(const SEScalarLengthPerTime& src, cdm::ScalarLengthPerTimeData& dst)
{
  SEScalarQuantity<LengthPerTimeUnit>::Serialize(src, *dst.mutable_scalarlengthpertime());
}