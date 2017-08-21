/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL InverseVolumeUnit : public CCompoundUnit
{
public:
  InverseVolumeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~InverseVolumeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const InverseVolumeUnit& GetCompoundUnit(const std::string& unit);

  static const InverseVolumeUnit Inverse_L;
  static const InverseVolumeUnit Inverse_mL;
};

class CDM_DECL SEScalarInverseVolume : public SEScalarQuantity<InverseVolumeUnit>
{
public:
  SEScalarInverseVolume() {}
  virtual ~SEScalarInverseVolume() {}

  static void Load(const cdm::ScalarInverseVolumeData& src, SEScalarInverseVolume& dst);
  static cdm::ScalarInverseVolumeData* Unload(const SEScalarInverseVolume& src);
protected:
  static void Serialize(const cdm::ScalarInverseVolumeData& src, SEScalarInverseVolume& dst);
  static void Serialize(const SEScalarInverseVolume& src, cdm::ScalarInverseVolumeData& dst);
};
