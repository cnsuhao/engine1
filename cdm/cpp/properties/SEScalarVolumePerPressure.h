/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerPressureUnit : public CCompoundUnit
{
public:
  VolumePerPressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerPressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerPressureUnit& GetCompoundUnit(const std::string& unit);

  static const VolumePerPressureUnit L_Per_Pa;
  static const VolumePerPressureUnit L_Per_cmH2O;
};

class CDM_DECL SEScalarVolumePerPressure : public SEScalarQuantity<VolumePerPressureUnit>
{
public:
  SEScalarVolumePerPressure() {}
  virtual ~SEScalarVolumePerPressure() {}

  static void Load(const cdm::ScalarVolumePerPressureData& src, SEScalarVolumePerPressure& dst);
  static cdm::ScalarVolumePerPressureData* Unload(const SEScalarVolumePerPressure& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerPressureData& src, SEScalarVolumePerPressure& dst);
  static void Serialize(const SEScalarVolumePerPressure& src, cdm::ScalarVolumePerPressureData& dst);
};
