/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatConductancePerAreaUnit : public CCompoundUnit
{
public:
  HeatConductancePerAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatConductancePerAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatConductancePerAreaUnit& GetCompoundUnit(const std::string& unit);

  static const HeatConductancePerAreaUnit W_Per_m2_K;
  static const HeatConductancePerAreaUnit W_Per_m2_C;
  static const HeatConductancePerAreaUnit BTU_Per_hr_ft2_C;
};

class CDM_DECL SEScalarHeatConductancePerArea : public SEScalarQuantity<HeatConductancePerAreaUnit>
{
public:
  SEScalarHeatConductancePerArea() {}
  virtual ~SEScalarHeatConductancePerArea() {}

  static void Load(const cdm::ScalarHeatConductancePerAreaData& src, SEScalarHeatConductancePerArea& dst);
  static cdm::ScalarHeatConductancePerAreaData* Unload(const SEScalarHeatConductancePerArea& src);
protected:
  static void Serialize(const cdm::ScalarHeatConductancePerAreaData& src, SEScalarHeatConductancePerArea& dst);
  static void Serialize(const SEScalarHeatConductancePerArea& src, cdm::ScalarHeatConductancePerAreaData& dst);
};