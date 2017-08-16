/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL LengthPerTimePressureUnit : public CCompoundUnit
{
public:
  LengthPerTimePressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~LengthPerTimePressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const LengthPerTimePressureUnit& GetCompoundUnit(const std::string& unit);

  static const LengthPerTimePressureUnit m_Per_s_mmHg;
  static const LengthPerTimePressureUnit cm_Per_s_mmHg;
  static const LengthPerTimePressureUnit m_Per_min_mmHg;
  static const LengthPerTimePressureUnit cm_Per_min_mmHg;
};

class CDM_DECL SEScalarLengthPerTimePressure : public SEScalarQuantity<LengthPerTimePressureUnit>
{
public:
  SEScalarLengthPerTimePressure() {}
  virtual ~SEScalarLengthPerTimePressure() {}

  static void Load(const cdm::ScalarLengthPerTimePressureData& src, SEScalarLengthPerTimePressure& dst);
  static cdm::ScalarLengthPerTimePressureData* Unload(const SEScalarLengthPerTimePressure& src);
protected:
  static void Serialize(const cdm::ScalarLengthPerTimePressureData& src, SEScalarLengthPerTimePressure& dst);
  static void Serialize(const SEScalarLengthPerTimePressure& src, cdm::ScalarLengthPerTimePressureData& dst);
};
