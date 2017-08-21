/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AreaPerTimePressureUnit : public CCompoundUnit
{
public:
  AreaPerTimePressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AreaPerTimePressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AreaPerTimePressureUnit& GetCompoundUnit(const std::string& unit);

  static const AreaPerTimePressureUnit m2_Per_s_mmHg;
  static const AreaPerTimePressureUnit cm2_Per_s_mmHg;
  static const AreaPerTimePressureUnit m2_Per_min_mmHg;
  static const AreaPerTimePressureUnit cm2_Per_min_mmHg;
};

class CDM_DECL SEScalarAreaPerTimePressure : public SEScalarQuantity<AreaPerTimePressureUnit>
{
public:
  SEScalarAreaPerTimePressure() {}
  virtual ~SEScalarAreaPerTimePressure() {}

  static void Load(const cdm::ScalarAreaPerTimePressureData& src, SEScalarAreaPerTimePressure& dst);
  static cdm::ScalarAreaPerTimePressureData* Unload(const SEScalarAreaPerTimePressure& src);
protected:
  static void Serialize(const cdm::ScalarAreaPerTimePressureData& src, SEScalarAreaPerTimePressure& dst);
  static void Serialize(const SEScalarAreaPerTimePressure& src, cdm::ScalarAreaPerTimePressureData& dst);
};
