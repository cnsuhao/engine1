/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarAmountPerMass.h"

AmountPerMassUnit AmountPerMassUnit::ct_Per_g("ct/g");
AmountPerMassUnit AmountPerMassUnit::ct_Per_ug("ct/ug");

bool AmountPerMassUnit::IsValidUnit(const std::string& unit)
{
  if(ct_Per_g.GetString().compare(unit) == 0)
    return true;
  if (ct_Per_ug.GetString().compare(unit) == 0)
    return true;
  return false;
}
const AmountPerMassUnit& AmountPerMassUnit::GetCompoundUnit(const std::string& unit)
{
  if(ct_Per_g.GetString().compare(unit)==0)
    return ct_Per_g;
  if(ct_Per_ug.GetString().compare(unit)==0)
    return ct_Per_ug;
  std::stringstream err;
  err << unit << " is not a valid AmountPerMass unit";
  throw CommonDataModelException(err.str());
}

void SEScalarAmountPerMass::Load(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst)
{
  SEScalarAmountPerMass::Serialize(src, dst);
}
void SEScalarAmountPerMass::Serialize(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst)
{
  SEScalarQuantity<AmountPerMassUnit>::Serialize(src.scalaramountpermass(), dst);
}

cdm::ScalarAmountPerMassData* SEScalarAmountPerMass::Unload(const SEScalarAmountPerMass& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarAmountPerMassData* dst = new cdm::ScalarAmountPerMassData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarAmountPerMass::Serialize(const SEScalarAmountPerMass& src, cdm::ScalarAmountPerMassData& dst)
{
  SEScalarQuantity<AmountPerMassUnit>::Serialize(src, *dst.mutable_scalaramountpermass());
}