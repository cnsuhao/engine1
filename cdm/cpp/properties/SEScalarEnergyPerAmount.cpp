/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "stdafx.h"
#include "properties/SEScalarEnergyPerAmount.h"

const EnergyPerAmountUnit EnergyPerAmountUnit::kcal_Per_mol("kcal/mol");
const EnergyPerAmountUnit EnergyPerAmountUnit::kJ_Per_mol("kJ/mol");

bool EnergyPerAmountUnit::IsValidUnit(const std::string& unit)
{
  if (kcal_Per_mol.GetString().compare(unit) == 0)
    return true;
  if (kJ_Per_mol.GetString().compare(unit) == 0)
    return true;
  return false;
}

const EnergyPerAmountUnit& EnergyPerAmountUnit::GetCompoundUnit(const std::string& unit)
{
  if (kcal_Per_mol.GetString().compare(unit) == 0)
    return kcal_Per_mol;
  if (kJ_Per_mol.GetString().compare(unit) == 0)
    return kJ_Per_mol;
  std::stringstream err;
  err << unit << " is not a valid EnergyPerAmount unit";
  throw CommonDataModelException(err.str());
}

void SEScalarEnergyPerAmount::Load(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst)
{
  SEScalarEnergyPerAmount::Serialize(src, dst);
}
void SEScalarEnergyPerAmount::Serialize(const cdm::ScalarEnergyPerAmountData& src, SEScalarEnergyPerAmount& dst)
{
  SEScalarQuantity<EnergyPerAmountUnit>::Serialize(src.scalarenergyperamount(), dst);
}

cdm::ScalarEnergyPerAmountData* SEScalarEnergyPerAmount::Unload(const SEScalarEnergyPerAmount& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarEnergyPerAmountData* dst = new cdm::ScalarEnergyPerAmountData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarEnergyPerAmount::Serialize(const SEScalarEnergyPerAmount& src, cdm::ScalarEnergyPerAmountData& dst)
{
  SEScalarQuantity<EnergyPerAmountUnit>::Serialize(src, *dst.mutable_scalarenergyperamount());
}