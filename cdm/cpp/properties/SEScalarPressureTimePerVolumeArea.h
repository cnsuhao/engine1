/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PressureTimePerVolumeAreaUnit : public CCompoundUnit
{
public:
  PressureTimePerVolumeAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PressureTimePerVolumeAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PressureTimePerVolumeAreaUnit& GetCompoundUnit(const std::string& unit);

  static const PressureTimePerVolumeAreaUnit mmHg_min_Per_mL_m2;
  static const PressureTimePerVolumeAreaUnit mmHg_s_Per_mL_m2;
  static const PressureTimePerVolumeAreaUnit dyn_s_Per_cm5_m2;
};

class CDM_DECL SEScalarPressureTimePerVolumeArea : public SEScalarQuantity<PressureTimePerVolumeAreaUnit>
{
public:
  SEScalarPressureTimePerVolumeArea() {}
  virtual ~SEScalarPressureTimePerVolumeArea() {}

  static void Load(const cdm::ScalarPressureTimePerVolumeAreaData& src, SEScalarPressureTimePerVolumeArea& dst);
  static cdm::ScalarPressureTimePerVolumeAreaData* Unload(const SEScalarPressureTimePerVolumeArea& src);
protected:
  static void Serialize(const cdm::ScalarPressureTimePerVolumeAreaData& src, SEScalarPressureTimePerVolumeArea& dst);
  static void Serialize(const SEScalarPressureTimePerVolumeArea& src, cdm::ScalarPressureTimePerVolumeAreaData& dst);
};
