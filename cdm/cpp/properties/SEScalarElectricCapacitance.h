/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL ElectricCapacitanceUnit : public CCompoundUnit
{
public:
  ElectricCapacitanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricCapacitanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricCapacitanceUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricCapacitanceUnit F;
};

class CDM_DECL SEScalarElectricCapacitance : public SEScalarQuantity<ElectricCapacitanceUnit>
{
public:
  SEScalarElectricCapacitance(){}
  virtual ~SEScalarElectricCapacitance() {}

  static void Load(const cdm::ScalarElectricCapacitanceData& src, SEScalarElectricCapacitance& dst);
  static cdm::ScalarElectricCapacitanceData* Unload(const SEScalarElectricCapacitance& src);
protected:
  static void Serialize(const cdm::ScalarElectricCapacitanceData& src, SEScalarElectricCapacitance& dst);
  static void Serialize(const SEScalarElectricCapacitance& src, cdm::ScalarElectricCapacitanceData& dst);
};
