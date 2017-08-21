/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL ElectricChargeUnit : public CCompoundUnit
{
public:
  ElectricChargeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricChargeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricChargeUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricChargeUnit C;
};

class CDM_DECL SEScalarElectricCharge : public SEScalarQuantity<ElectricChargeUnit>
{
public:
  SEScalarElectricCharge() {}
  virtual ~SEScalarElectricCharge() {}

  static void Load(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst);
  static cdm::ScalarElectricChargeData* Unload(const SEScalarElectricCharge& src);
protected:
  static void Serialize(const cdm::ScalarElectricChargeData& src, SEScalarElectricCharge& dst);
  static void Serialize(const SEScalarElectricCharge& src, cdm::ScalarElectricChargeData& dst);
};
