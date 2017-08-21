/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerTimeUnit : public CCompoundUnit
{
public:
  VolumePerTimeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerTimeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerTimeUnit& GetCompoundUnit(const std::string& unit);

  static const VolumePerTimeUnit L_Per_s;
  static const VolumePerTimeUnit L_Per_day;
  static const VolumePerTimeUnit mL_Per_s;
  static const VolumePerTimeUnit mL_Per_day;
  static const VolumePerTimeUnit L_Per_min;
  static const VolumePerTimeUnit m3_Per_s;
  static const VolumePerTimeUnit mL_Per_min;
  static const VolumePerTimeUnit mL_Per_hr;
};

class CDM_DECL SEScalarVolumePerTime : public SEScalarQuantity<VolumePerTimeUnit>
{
public:
  SEScalarVolumePerTime() {}
  virtual ~SEScalarVolumePerTime() {}

  static void Load(const cdm::ScalarVolumePerTimeData& src, SEScalarVolumePerTime& dst);
  static cdm::ScalarVolumePerTimeData* Unload(const SEScalarVolumePerTime& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerTimeData& src, SEScalarVolumePerTime& dst);
  static void Serialize(const SEScalarVolumePerTime& src, cdm::ScalarVolumePerTimeData& dst);
};
