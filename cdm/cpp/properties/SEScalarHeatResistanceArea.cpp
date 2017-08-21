/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarHeatResistanceArea.h"

const HeatResistanceAreaUnit HeatResistanceAreaUnit::rsi("rsi");
const HeatResistanceAreaUnit HeatResistanceAreaUnit::clo("clo");
const HeatResistanceAreaUnit HeatResistanceAreaUnit::rValue("rValue");
const HeatResistanceAreaUnit HeatResistanceAreaUnit::tog("tog");

bool HeatResistanceAreaUnit::IsValidUnit(const std::string& unit)
{
  if (rsi.GetString().compare(unit) == 0)
    return true;
  if (clo.GetString().compare(unit) == 0)
    return true;
  if (rValue.GetString().compare(unit) == 0)
    return true;
  if (tog.GetString().compare(unit) == 0)
    return true;
  return false;
}

const HeatResistanceAreaUnit& HeatResistanceAreaUnit::GetCompoundUnit(const std::string& unit)
{
  if (rsi.GetString().compare(unit) == 0)
    return rsi;
  if (clo.GetString().compare(unit) == 0)
    return clo;
  if (rValue.GetString().compare(unit) == 0)
    return rValue;
  if (tog.GetString().compare(unit) == 0)
    return tog;
  std::stringstream err;
  err << unit << " is not a valid HeatResistanceArea unit";
  throw CommonDataModelException(err.str());
}

void SEScalarHeatResistanceArea::Load(const cdm::ScalarHeatResistanceAreaData& src, SEScalarHeatResistanceArea& dst)
{
  SEScalarHeatResistanceArea::Serialize(src, dst);
}
void SEScalarHeatResistanceArea::Serialize(const cdm::ScalarHeatResistanceAreaData& src, SEScalarHeatResistanceArea& dst)
{
  SEScalarQuantity<HeatResistanceAreaUnit>::Serialize(src.scalarheatresistancearea(), dst);
}

cdm::ScalarHeatResistanceAreaData* SEScalarHeatResistanceArea::Unload(const SEScalarHeatResistanceArea& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarHeatResistanceAreaData* dst = new cdm::ScalarHeatResistanceAreaData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarHeatResistanceArea::Serialize(const SEScalarHeatResistanceArea& src, cdm::ScalarHeatResistanceAreaData& dst)
{
  SEScalarQuantity<HeatResistanceAreaUnit>::Serialize(src, *dst.mutable_scalarheatresistancearea());
}