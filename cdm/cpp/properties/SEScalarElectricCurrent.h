/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL ElectricCurrentUnit : public CCompoundUnit
{
public:
  ElectricCurrentUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricCurrentUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricCurrentUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricCurrentUnit A;
};

class CDM_DECL SEScalarElectricCurrent : public SEScalarQuantity<ElectricCurrentUnit>
{
public:
  SEScalarElectricCurrent() {}
  virtual ~SEScalarElectricCurrent() {}

  static void Load(const cdm::ScalarElectricCurrentData& src, SEScalarElectricCurrent& dst);
  static cdm::ScalarElectricCurrentData* Unload(const SEScalarElectricCurrent& src);
protected:
  static void Serialize(const cdm::ScalarElectricCurrentData& src, SEScalarElectricCurrent& dst);
  static void Serialize(const SEScalarElectricCurrent& src, cdm::ScalarElectricCurrentData& dst);
};
