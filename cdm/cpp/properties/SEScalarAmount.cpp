/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarAmount.h"

const AmountUnit AmountUnit::mol("mol");
const AmountUnit AmountUnit::pmol("pmol");

bool AmountUnit::IsValidUnit(const std::string& unit)
{
  if (mol.GetString().compare(unit) == 0)
    return true;
  if (pmol.GetString().compare(unit) == 0)
    return true;
  return false;
}
const AmountUnit& AmountUnit::GetCompoundUnit(const std::string& unit)
{
  if(mol.GetString().compare(unit)==0)
    return mol;
  if (pmol.GetString().compare(unit) == 0)
    return pmol;
  std::stringstream err;
  err << unit << " is not a valid Amount unit";
  throw CommonDataModelException(err.str());
}

void SEScalarAmount::Load(const cdm::ScalarAmountData& src, SEScalarAmount& dst)
{
  SEScalarAmount::Serialize(src, dst);
}
void SEScalarAmount::Serialize(const cdm::ScalarAmountData& src, SEScalarAmount& dst)
{
  SEScalarQuantity<AmountUnit>::Serialize(src.scalaramount(), dst);
}

cdm::ScalarAmountData* SEScalarAmount::Unload(const SEScalarAmount& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarAmountData* dst = new cdm::ScalarAmountData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarAmount::Serialize(const SEScalarAmount& src, cdm::ScalarAmountData& dst)
{
  SEScalarQuantity<AmountUnit>::Serialize(src, *dst.mutable_scalaramount());
}