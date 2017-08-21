/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL InversePressureUnit : public CCompoundUnit
{
public:
  InversePressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~InversePressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const InversePressureUnit& GetCompoundUnit(const std::string& unit);

  static const InversePressureUnit Inverse_Pa;
  static const InversePressureUnit Inverse_mmHg;
  static const InversePressureUnit Inverse_cmH2O;
  static const InversePressureUnit Inverse_atm;
};

class CDM_DECL SEScalarInversePressure : public SEScalarQuantity<InversePressureUnit>
{
public:
  SEScalarInversePressure() {}
  virtual ~SEScalarInversePressure() {}

  static void Load(const cdm::ScalarInversePressureData& src, SEScalarInversePressure& dst);
  static cdm::ScalarInversePressureData* Unload(const SEScalarInversePressure& src);
protected:
  static void Serialize(const cdm::ScalarInversePressureData& src, SEScalarInversePressure& dst);
  static void Serialize(const SEScalarInversePressure& src, cdm::ScalarInversePressureData& dst);
};
