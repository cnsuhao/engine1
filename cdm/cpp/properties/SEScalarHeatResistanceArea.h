/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatResistanceAreaUnit : public CCompoundUnit
{
public:
  HeatResistanceAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatResistanceAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatResistanceAreaUnit& GetCompoundUnit(const std::string& unit);

  static const HeatResistanceAreaUnit rsi;
  static const HeatResistanceAreaUnit clo;
  static const HeatResistanceAreaUnit rValue;
  static const HeatResistanceAreaUnit tog;
};

class CDM_DECL SEScalarHeatResistanceArea : public SEScalarQuantity<HeatResistanceAreaUnit>
{
public:
  SEScalarHeatResistanceArea() {}
  virtual ~SEScalarHeatResistanceArea() {}

  static void Load(const cdm::ScalarHeatResistanceAreaData& src, SEScalarHeatResistanceArea& dst);
  static cdm::ScalarHeatResistanceAreaData* Unload(const SEScalarHeatResistanceArea& src);
protected:
  static void Serialize(const cdm::ScalarHeatResistanceAreaData& src, SEScalarHeatResistanceArea& dst);
  static void Serialize(const SEScalarHeatResistanceArea& src, cdm::ScalarHeatResistanceAreaData& dst);
};