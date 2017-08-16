/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL EnergyUnit : public CCompoundUnit
{
public:
  EnergyUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~EnergyUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const EnergyUnit& GetCompoundUnit(const std::string& unit);

  static const EnergyUnit J;
  static const EnergyUnit mJ;
  static const EnergyUnit kJ;
  static const EnergyUnit kcal;
};

class CDM_DECL SEScalarEnergy : public SEScalarQuantity<EnergyUnit>
{
public:
  SEScalarEnergy() {}
  virtual ~SEScalarEnergy() {}

  static void Load(const cdm::ScalarEnergyData& src, SEScalarEnergy& dst);
  static cdm::ScalarEnergyData* Unload(const SEScalarEnergy& src);
protected:
  static void Serialize(const cdm::ScalarEnergyData& src, SEScalarEnergy& dst);
  static void Serialize(const SEScalarEnergy& src, cdm::ScalarEnergyData& dst);
};
