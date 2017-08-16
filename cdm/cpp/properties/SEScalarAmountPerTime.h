/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AmountPerTimeUnit : public CCompoundUnit
{
public:
  AmountPerTimeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AmountPerTimeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AmountPerTimeUnit& GetCompoundUnit(const std::string& unit);


  static AmountPerTimeUnit mol_Per_day;
  static AmountPerTimeUnit mol_Per_s;
  static AmountPerTimeUnit umol_Per_s;
  static AmountPerTimeUnit mmol_Per_min;
  static AmountPerTimeUnit pmol_Per_min;
  static AmountPerTimeUnit umol_Per_min;
};

class CDM_DECL SEScalarAmountPerTime : public SEScalarQuantity<AmountPerTimeUnit>
{

public:
  SEScalarAmountPerTime() {}
  virtual ~SEScalarAmountPerTime() {}

  static void Load(const cdm::ScalarAmountPerTimeData& src, SEScalarAmountPerTime& dst);
  static cdm::ScalarAmountPerTimeData* Unload(const SEScalarAmountPerTime& src);
protected:
  static void Serialize(const cdm::ScalarAmountPerTimeData& src, SEScalarAmountPerTime& dst);
  static void Serialize(const SEScalarAmountPerTime& src, cdm::ScalarAmountPerTimeData& dst);
};
