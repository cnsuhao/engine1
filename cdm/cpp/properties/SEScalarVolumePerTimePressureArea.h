/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerTimePressureAreaUnit : public CCompoundUnit
{
public:
  VolumePerTimePressureAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerTimePressureAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerTimePressureAreaUnit& GetCompoundUnit(const std::string& unit);

  static const  VolumePerTimePressureAreaUnit mL_Per_min_mmHg_m2;
  static const  VolumePerTimePressureAreaUnit mL_Per_s_mmHg_m2;
};

class CDM_DECL SEScalarVolumePerTimePressureArea : public SEScalarQuantity<VolumePerTimePressureAreaUnit>
{
public:
  SEScalarVolumePerTimePressureArea() {}
  virtual ~SEScalarVolumePerTimePressureArea() {}

  static void Load(const cdm::ScalarVolumePerTimePressureAreaData& src, SEScalarVolumePerTimePressureArea& dst);
  static cdm::ScalarVolumePerTimePressureAreaData* Unload(const SEScalarVolumePerTimePressureArea& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerTimePressureAreaData& src, SEScalarVolumePerTimePressureArea& dst);
  static void Serialize(const SEScalarVolumePerTimePressureArea& src, cdm::ScalarVolumePerTimePressureAreaData& dst);
};