/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerTimeMassUnit : public CCompoundUnit
{
public:
  VolumePerTimeMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerTimeMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerTimeMassUnit& GetCompoundUnit(const std::string& unit);

  static const VolumePerTimeMassUnit L_Per_s_g;
  static const VolumePerTimeMassUnit mL_Per_s_g;
  static const VolumePerTimeMassUnit mL_Per_min_kg;
  static const VolumePerTimeMassUnit mL_Per_s_kg;
  static const VolumePerTimeMassUnit uL_Per_min_kg;
};

class CDM_DECL SEScalarVolumePerTimeMass : public SEScalarQuantity<VolumePerTimeMassUnit>
{
public:
  SEScalarVolumePerTimeMass() {}
  virtual ~SEScalarVolumePerTimeMass() {}

  static void Load(const cdm::ScalarVolumePerTimeMassData& src, SEScalarVolumePerTimeMass& dst);
  static cdm::ScalarVolumePerTimeMassData* Unload(const SEScalarVolumePerTimeMass& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerTimeMassData& src, SEScalarVolumePerTimeMass& dst);
  static void Serialize(const SEScalarVolumePerTimeMass& src, cdm::ScalarVolumePerTimeMassData& dst);
};
