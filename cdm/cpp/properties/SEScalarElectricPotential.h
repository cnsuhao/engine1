/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL ElectricPotentialUnit : public CCompoundUnit
{
public:
  ElectricPotentialUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricPotentialUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricPotentialUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricPotentialUnit V;
  static const ElectricPotentialUnit mV;
};

class CDM_DECL SEScalarElectricPotential : public SEScalarQuantity<ElectricPotentialUnit>
{
public:
  SEScalarElectricPotential() {}
  virtual ~SEScalarElectricPotential() {}

  static void Load(const cdm::ScalarElectricPotentialData& src, SEScalarElectricPotential& dst);
  static cdm::ScalarElectricPotentialData* Unload(const SEScalarElectricPotential& src);
protected:
  static void Serialize(const cdm::ScalarElectricPotentialData& src, SEScalarElectricPotential& dst);
  static void Serialize(const SEScalarElectricPotential& src, cdm::ScalarElectricPotentialData& dst);
};
