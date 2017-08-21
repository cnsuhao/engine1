/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PressurePerVolumeUnit : public CCompoundUnit
{
public:
  PressurePerVolumeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PressurePerVolumeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PressurePerVolumeUnit& GetCompoundUnit(const std::string& unit);

  static const PressurePerVolumeUnit mmHg_Per_mL;
  static const PressurePerVolumeUnit cmH2O_Per_mL;
};

class CDM_DECL SEScalarPressurePerVolume : public SEScalarQuantity<PressurePerVolumeUnit>
{
public:
  SEScalarPressurePerVolume() {}
  virtual ~SEScalarPressurePerVolume() {}

  static void Load(const cdm::ScalarPressurePerVolumeData& src, SEScalarPressurePerVolume& dst);
  static cdm::ScalarPressurePerVolumeData* Unload(const SEScalarPressurePerVolume& src);
protected:
  static void Serialize(const cdm::ScalarPressurePerVolumeData& src, SEScalarPressurePerVolume& dst);
  static void Serialize(const SEScalarPressurePerVolume& src, cdm::ScalarPressurePerVolumeData& dst);
};
