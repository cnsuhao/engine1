/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL ElectricInductanceUnit : public CCompoundUnit
{
public:
  ElectricInductanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricInductanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricInductanceUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricInductanceUnit H;
};

class CDM_DECL SEScalarElectricInductance : public SEScalarQuantity<ElectricInductanceUnit>
{
public:
  SEScalarElectricInductance() {}
  virtual ~SEScalarElectricInductance() {}

  static void Load(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst);
  static cdm::ScalarElectricInductanceData* Unload(const SEScalarElectricInductance& src);
protected:
  static void Serialize(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst);
  static void Serialize(const SEScalarElectricInductance& src, cdm::ScalarElectricInductanceData& dst);
};
