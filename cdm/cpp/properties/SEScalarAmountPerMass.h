/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AmountPerMassUnit : public CCompoundUnit
{
public:
  AmountPerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AmountPerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AmountPerMassUnit& GetCompoundUnit(const std::string& unit);

  static AmountPerMassUnit ct_Per_g;
  static AmountPerMassUnit ct_Per_ug;
};

class CDM_DECL SEScalarAmountPerMass : public SEScalarQuantity<AmountPerMassUnit>
{

public:
  SEScalarAmountPerMass() {}
  virtual ~SEScalarAmountPerMass() {}

  static void Load(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst);
  static cdm::ScalarAmountPerMassData* Unload(const SEScalarAmountPerMass& src);
protected:
  static void Serialize(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst);
  static void Serialize(const SEScalarAmountPerMass& src, cdm::ScalarAmountPerMassData& dst);
};
