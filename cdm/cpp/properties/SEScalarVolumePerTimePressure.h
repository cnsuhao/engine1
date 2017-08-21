/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerTimePressureUnit : public CCompoundUnit
{
public:
  VolumePerTimePressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerTimePressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerTimePressureUnit& GetCompoundUnit(const std::string& unit);

  static const VolumePerTimePressureUnit L_Per_s_mmHg;
  static const VolumePerTimePressureUnit mL_Per_s_mmHg;
  static const VolumePerTimePressureUnit L_Per_min_mmHg;
  static const VolumePerTimePressureUnit mL_Per_min_mmHg;
};

class CDM_DECL SEScalarVolumePerTimePressure : public SEScalarQuantity<VolumePerTimePressureUnit>
{
public:
  SEScalarVolumePerTimePressure() {}
  virtual ~SEScalarVolumePerTimePressure() {}

  static void Load(const cdm::ScalarVolumePerTimePressureData& src, SEScalarVolumePerTimePressure& dst);
  static cdm::ScalarVolumePerTimePressureData* Unload(const SEScalarVolumePerTimePressure& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerTimePressureData& src, SEScalarVolumePerTimePressure& dst);
  static void Serialize(const SEScalarVolumePerTimePressure& src, cdm::ScalarVolumePerTimePressureData& dst);
};
