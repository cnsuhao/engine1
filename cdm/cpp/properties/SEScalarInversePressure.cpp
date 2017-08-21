/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarInversePressure.h"

const InversePressureUnit InversePressureUnit::Inverse_Pa("1/Pa");
const InversePressureUnit InversePressureUnit::Inverse_mmHg("1/mmHg");
const InversePressureUnit InversePressureUnit::Inverse_cmH2O("1/cmH2O");
const InversePressureUnit InversePressureUnit::Inverse_atm("1/atm");

bool InversePressureUnit::IsValidUnit(const std::string& unit)
{
  if (Inverse_Pa.GetString().compare(unit) == 0)
    return true;
  if (Inverse_mmHg.GetString().compare(unit) == 0)
    return true;
  if (Inverse_cmH2O.GetString().compare(unit) == 0)
    return true;
  if (Inverse_atm.GetString().compare(unit) == 0)
    return true;
  return false;
}

const InversePressureUnit& InversePressureUnit::GetCompoundUnit(const std::string& unit)
{
  if (Inverse_Pa.GetString().compare(unit) == 0)
    return Inverse_Pa;
  if (Inverse_mmHg.GetString().compare(unit) == 0)
    return Inverse_mmHg;
  if (Inverse_cmH2O.GetString().compare(unit) == 0)
    return Inverse_cmH2O;
  if (Inverse_atm.GetString().compare(unit) == 0)
    return Inverse_atm;
  std::stringstream err;
  err << unit << " is not a valid InversePressure unit";
  throw CommonDataModelException(err.str());
}

void SEScalarInversePressure::Load(const cdm::ScalarInversePressureData& src, SEScalarInversePressure& dst)
{
  SEScalarInversePressure::Serialize(src, dst);
}
void SEScalarInversePressure::Serialize(const cdm::ScalarInversePressureData& src, SEScalarInversePressure& dst)
{
  SEScalarQuantity<InversePressureUnit>::Serialize(src.scalarinversepressure(), dst);
}

cdm::ScalarInversePressureData* SEScalarInversePressure::Unload(const SEScalarInversePressure& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarInversePressureData* dst = new cdm::ScalarInversePressureData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarInversePressure::Serialize(const SEScalarInversePressure& src, cdm::ScalarInversePressureData& dst)
{
  SEScalarQuantity<InversePressureUnit>::Serialize(src, *dst.mutable_scalarinversepressure());
}