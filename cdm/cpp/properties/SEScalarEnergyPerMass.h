/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL EnergyPerMassUnit : public CCompoundUnit
{
public:
  EnergyPerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~EnergyPerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const EnergyPerMassUnit& GetCompoundUnit(const std::string& unit);

  static const EnergyPerMassUnit J_Per_kg;
  static const EnergyPerMassUnit kJ_Per_kg;
  static const EnergyPerMassUnit mJ_Per_kg;
  static const EnergyPerMassUnit kcal_Per_kg;
};

class CDM_DECL SEScalarEnergyPerMass : public SEScalarQuantity<EnergyPerMassUnit>
{
public:
  SEScalarEnergyPerMass() {}
  virtual ~SEScalarEnergyPerMass() {}

  static void Load(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst);
  static cdm::ScalarEnergyPerMassData* Unload(const SEScalarEnergyPerMass& src);
protected:
  static void Serialize(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst);
  static void Serialize(const SEScalarEnergyPerMass& src, cdm::ScalarEnergyPerMassData& dst);
};
