/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarPressureTimePerArea.h"

const PressureTimePerAreaUnit PressureTimePerAreaUnit::mmHg_Per_mL_m2("mmHg/mL m^2");
const PressureTimePerAreaUnit PressureTimePerAreaUnit::cmH2O_Per_mL_m2("cmH2O/mL m^2");

bool PressureTimePerAreaUnit::IsValidUnit(const std::string& unit)
{
  if (mmHg_Per_mL_m2.GetString().compare(unit) == 0)
    return true;
  if (cmH2O_Per_mL_m2.GetString().compare(unit) == 0)
    return true;
  return false;
}

const PressureTimePerAreaUnit& PressureTimePerAreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (mmHg_Per_mL_m2.GetString().compare(unit) == 0)
    return mmHg_Per_mL_m2;
  if (cmH2O_Per_mL_m2.GetString().compare(unit) == 0)
    return cmH2O_Per_mL_m2;
  std::stringstream err;
  err << unit << " is not a valid PressureTimePerArea unit";
  throw CommonDataModelException(err.str());
}

void SEScalarPressureTimePerArea::Load(const cdm::ScalarPressureTimePerAreaData& src, SEScalarPressureTimePerArea& dst)
{
  SEScalarPressureTimePerArea::Serialize(src, dst);
}
void SEScalarPressureTimePerArea::Serialize(const cdm::ScalarPressureTimePerAreaData& src, SEScalarPressureTimePerArea& dst)
{
  SEScalarQuantity<PressureTimePerAreaUnit>::Serialize(src.scalarpressuretimeperarea(), dst);
}

cdm::ScalarPressureTimePerAreaData* SEScalarPressureTimePerArea::Unload(const SEScalarPressureTimePerArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarPressureTimePerAreaData* dst = new cdm::ScalarPressureTimePerAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarPressureTimePerArea::Serialize(const SEScalarPressureTimePerArea& src, cdm::ScalarPressureTimePerAreaData& dst)
{
  SEScalarQuantity<PressureTimePerAreaUnit>::Serialize(src, *dst.mutable_scalarpressuretimeperarea());
}