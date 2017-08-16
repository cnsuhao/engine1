/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarMass.h"

const MassUnit MassUnit::g("g");
const MassUnit MassUnit::ug("ug");
const MassUnit MassUnit::mg("mg");
const MassUnit MassUnit::kg("kg");
const MassUnit MassUnit::lb("lb");

bool MassUnit::IsValidUnit(const std::string& unit)
{
  if (g.GetString().compare(unit) == 0)
    return true;
  if (ug.GetString().compare(unit) == 0)
    return true;
  if (mg.GetString().compare(unit) == 0)
    return true;
  if (kg.GetString().compare(unit) == 0)
    return true;
  if (lb.GetString().compare(unit) == 0)
    return true;
  return false;
}

const MassUnit& MassUnit::GetCompoundUnit(const std::string& unit)
{
  if (g.GetString().compare(unit) == 0)
    return g;
  if (ug.GetString().compare(unit) == 0)
    return ug;
  if (mg.GetString().compare(unit) == 0)
    return mg;
  if (kg.GetString().compare(unit) == 0)
    return kg;
  if (lb.GetString().compare(unit) == 0)
    return lb;
  std::stringstream err;
  err << unit << " is not a valid Mass unit";
  throw CommonDataModelException(err.str());
}

void SEScalarMass::Load(const cdm::ScalarMassData& src, SEScalarMass& dst)
{
  SEScalarMass::Serialize(src, dst);
}
void SEScalarMass::Serialize(const cdm::ScalarMassData& src, SEScalarMass& dst)
{
  SEScalarQuantity<MassUnit>::Serialize(src.scalarmass(), dst);
}

cdm::ScalarMassData* SEScalarMass::Unload(const SEScalarMass& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarMassData* dst = new cdm::ScalarMassData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarMass::Serialize(const SEScalarMass& src, cdm::ScalarMassData& dst)
{
  SEScalarQuantity<MassUnit>::Serialize(src, *dst.mutable_scalarmass());
}