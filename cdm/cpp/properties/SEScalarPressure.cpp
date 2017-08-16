/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarPressure.h"

const PressureUnit PressureUnit::Pa("Pa");
const PressureUnit PressureUnit::mmHg("mmHg");
const PressureUnit PressureUnit::cmH2O("cmH2O");
const PressureUnit PressureUnit::psi("psi");
const PressureUnit PressureUnit::atm("atm");

bool PressureUnit::IsValidUnit(const std::string& unit)
{
  if (Pa.GetString().compare(unit) == 0)
    return true;
  if (mmHg.GetString().compare(unit) == 0)
    return true;
  if (cmH2O.GetString().compare(unit) == 0)
    return true;
  if (psi.GetString().compare(unit) == 0)
    return true;
  if (atm.GetString().compare(unit) == 0)
    return true;
  return false;
}

const PressureUnit& PressureUnit::GetCompoundUnit(const std::string& unit)
{
  if (Pa.GetString().compare(unit) == 0)
    return Pa;
  if (mmHg.GetString().compare(unit) == 0)
    return mmHg;
  if (cmH2O.GetString().compare(unit) == 0)
    return cmH2O;
  if (psi.GetString().compare(unit) == 0)
    return psi;
  if (atm.GetString().compare(unit) == 0)
    return atm;
  std::stringstream err;
  err << unit << " is not a valid Pressure unit";
  throw CommonDataModelException(err.str());
}

void SEScalarPressure::Load(const cdm::ScalarPressureData& src, SEScalarPressure& dst)
{
  SEScalarPressure::Serialize(src, dst);
}
void SEScalarPressure::Serialize(const cdm::ScalarPressureData& src, SEScalarPressure& dst)
{
  SEScalarQuantity<PressureUnit>::Serialize(src.scalarpressure(), dst);
}

cdm::ScalarPressureData* SEScalarPressure::Unload(const SEScalarPressure& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarPressureData* dst = new cdm::ScalarPressureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarPressure::Serialize(const SEScalarPressure& src, cdm::ScalarPressureData& dst)
{
  SEScalarQuantity<PressureUnit>::Serialize(src, *dst.mutable_scalarpressure());
}