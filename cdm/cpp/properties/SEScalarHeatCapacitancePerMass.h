/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatCapacitancePerMassUnit : public CCompoundUnit
{
public:
  HeatCapacitancePerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatCapacitancePerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatCapacitancePerMassUnit& GetCompoundUnit(const std::string& unit);

  static const HeatCapacitancePerMassUnit J_Per_K_kg;
  static const HeatCapacitancePerMassUnit kJ_Per_K_kg;
  static const HeatCapacitancePerMassUnit kcal_Per_K_kg;
  static const HeatCapacitancePerMassUnit kcal_Per_C_kg;
};

class CDM_DECL SEScalarHeatCapacitancePerMass : public SEScalarQuantity<HeatCapacitancePerMassUnit>
{
public:
  SEScalarHeatCapacitancePerMass() {}
  virtual ~SEScalarHeatCapacitancePerMass() {}

  static void Load(const cdm::ScalarHeatCapacitancePerMassData& src, SEScalarHeatCapacitancePerMass& dst);
  static cdm::ScalarHeatCapacitancePerMassData* Unload(const SEScalarHeatCapacitancePerMass& src);
protected:
  static void Serialize(const cdm::ScalarHeatCapacitancePerMassData& src, SEScalarHeatCapacitancePerMass& dst);
  static void Serialize(const SEScalarHeatCapacitancePerMass& src, cdm::ScalarHeatCapacitancePerMassData& dst);
};