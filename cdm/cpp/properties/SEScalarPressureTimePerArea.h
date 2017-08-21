/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PressureTimePerAreaUnit : public CCompoundUnit
{
public:
  PressureTimePerAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PressureTimePerAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PressureTimePerAreaUnit& GetCompoundUnit(const std::string& unit);

  static const PressureTimePerAreaUnit mmHg_Per_mL_m2;
  static const PressureTimePerAreaUnit cmH2O_Per_mL_m2;
};

class CDM_DECL SEScalarPressureTimePerArea : public SEScalarQuantity<PressureTimePerAreaUnit>
{
public:
  SEScalarPressureTimePerArea() {}
  virtual ~SEScalarPressureTimePerArea() {}

  static void Load(const cdm::ScalarPressureTimePerAreaData& src, SEScalarPressureTimePerArea& dst);
  static cdm::ScalarPressureTimePerAreaData* Unload(const SEScalarPressureTimePerArea& src);
protected:
  static void Serialize(const cdm::ScalarPressureTimePerAreaData& src, SEScalarPressureTimePerArea& dst);
  static void Serialize(const SEScalarPressureTimePerArea& src, cdm::ScalarPressureTimePerAreaData& dst);
};
