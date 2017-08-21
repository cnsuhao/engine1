/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AmountUnit : public CCompoundUnit
{
public:
  AmountUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AmountUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AmountUnit& GetCompoundUnit(const std::string& unit);

  static const AmountUnit mol;
  static const AmountUnit pmol;
};

class CDM_DECL SEScalarAmount : public SEScalarQuantity<AmountUnit>
{
public:
  SEScalarAmount() {}
  virtual ~SEScalarAmount() {}

  static void Load(const cdm::ScalarAmountData& src, SEScalarAmount& dst);
  static cdm::ScalarAmountData* Unload(const SEScalarAmount& src);
protected:
  static void Serialize(const cdm::ScalarAmountData& src, SEScalarAmount& dst);
  static void Serialize(const SEScalarAmount& src, cdm::ScalarAmountData& dst);
};
