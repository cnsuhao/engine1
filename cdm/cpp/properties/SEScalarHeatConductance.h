/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatConductanceUnit : public CCompoundUnit
{
public:
  HeatConductanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatConductanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatConductanceUnit& GetCompoundUnit(const std::string& unit);

  static const HeatConductanceUnit W_Per_K;
  static const HeatConductanceUnit W_Per_C;
  static const HeatConductanceUnit kcal_Per_K_s;
  static const HeatConductanceUnit kcal_Per_C_s;
};

class CDM_DECL SEScalarHeatConductance : public SEScalarQuantity<HeatConductanceUnit>
{
public:
  SEScalarHeatConductance() {}
  virtual ~SEScalarHeatConductance() {}

  static void Load(const cdm::ScalarHeatConductanceData& src, SEScalarHeatConductance& dst);
  static cdm::ScalarHeatConductanceData* Unload(const SEScalarHeatConductance& src);
protected:
  static void Serialize(const cdm::ScalarHeatConductanceData& src, SEScalarHeatConductance& dst);
  static void Serialize(const SEScalarHeatConductance& src, cdm::ScalarHeatConductanceData& dst);
};