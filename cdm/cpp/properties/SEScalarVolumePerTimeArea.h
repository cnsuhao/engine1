/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL VolumePerTimeAreaUnit : public CCompoundUnit
{
public:
  VolumePerTimeAreaUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~VolumePerTimeAreaUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const VolumePerTimeAreaUnit& GetCompoundUnit(const std::string& unit);

  static const VolumePerTimeAreaUnit mL_Per_min_m2;
  static const VolumePerTimeAreaUnit mL_Per_s_m2;
  static const VolumePerTimeAreaUnit L_Per_min_m2;
};

class CDM_DECL SEScalarVolumePerTimeArea : public SEScalarQuantity<VolumePerTimeAreaUnit>
{
public:
  SEScalarVolumePerTimeArea() {}
  virtual ~SEScalarVolumePerTimeArea() {}

  static void Load(const cdm::ScalarVolumePerTimeAreaData& src, SEScalarVolumePerTimeArea& dst);
  static cdm::ScalarVolumePerTimeAreaData* Unload(const SEScalarVolumePerTimeArea& src);
protected:
  static void Serialize(const cdm::ScalarVolumePerTimeAreaData& src, SEScalarVolumePerTimeArea& dst);
  static void Serialize(const SEScalarVolumePerTimeArea& src, cdm::ScalarVolumePerTimeAreaData& dst);
};
