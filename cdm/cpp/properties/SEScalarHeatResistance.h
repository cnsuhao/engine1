/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatResistanceUnit : public CCompoundUnit
{
public:
  HeatResistanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatResistanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatResistanceUnit& GetCompoundUnit(const std::string& unit);

  static const HeatResistanceUnit K_Per_W;
  static const HeatResistanceUnit C_Per_W;
  static const HeatResistanceUnit K_s_Per_kcal;
  static const HeatResistanceUnit C_s_Per_kcal;
};

class CDM_DECL SEScalarHeatResistance : public SEScalarQuantity<HeatResistanceUnit>
{
public:
  SEScalarHeatResistance() {}
  virtual ~SEScalarHeatResistance() {}

  static void Load(const cdm::ScalarHeatResistanceData& src, SEScalarHeatResistance& dst);
  static cdm::ScalarHeatResistanceData* Unload(const SEScalarHeatResistance& src);
protected:
  static void Serialize(const cdm::ScalarHeatResistanceData& src, SEScalarHeatResistance& dst);
  static void Serialize(const SEScalarHeatResistance& src, cdm::ScalarHeatResistanceData& dst);
};