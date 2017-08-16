/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarTemperature.h"

const TemperatureUnit TemperatureUnit::F("degF");
const TemperatureUnit TemperatureUnit::C("degC");
const TemperatureUnit TemperatureUnit::K("K");
const TemperatureUnit TemperatureUnit::R("degR");

bool TemperatureUnit::IsValidUnit(const std::string& unit)
{
  if (F.GetString().compare(unit) == 0)
    return true;
  if (C.GetString().compare(unit) == 0)
    return true;
  if (K.GetString().compare(unit) == 0)
    return true;
  if (R.GetString().compare(unit) == 0)
    return true;
  return false;
}

const TemperatureUnit& TemperatureUnit::GetCompoundUnit(const std::string& unit)
{
  if (F.GetString().compare(unit) == 0)
    return F;
  if (C.GetString().compare(unit) == 0)
    return C;
  if (K.GetString().compare(unit) == 0)
    return K;
  if (R.GetString().compare(unit) == 0)
    return R;
  std::stringstream err;
  err << unit << " is not a valid Temperature unit";
  throw CommonDataModelException(err.str());
}

double SEScalarTemperature::GetValue(const TemperatureUnit& unit) const
{
  if (m_isnan)
    throw CommonDataModelException("Value is NaN");
  if (m_isinf)
    return m_value;
  if (m_unit == &unit)
    return m_value;
  return Convert(m_value, *m_unit, unit);
}

void SEScalarTemperature::Load(const cdm::ScalarTemperatureData& src, SEScalarTemperature& dst)
{
  SEScalarTemperature::Serialize(src, dst);
}
void SEScalarTemperature::Serialize(const cdm::ScalarTemperatureData& src, SEScalarTemperature& dst)
{
  SEScalarQuantity<TemperatureUnit>::Serialize(src.scalartemperature(), dst);
}

cdm::ScalarTemperatureData* SEScalarTemperature::Unload(const SEScalarTemperature& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarTemperatureData* dst = new cdm::ScalarTemperatureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarTemperature::Serialize(const SEScalarTemperature& src, cdm::ScalarTemperatureData& dst)
{
  SEScalarQuantity<TemperatureUnit>::Serialize(src, *dst.mutable_scalartemperature());
}