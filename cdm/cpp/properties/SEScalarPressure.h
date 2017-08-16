/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL PressureUnit : public CCompoundUnit
{
public:
  PressureUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~PressureUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const PressureUnit& GetCompoundUnit(const std::string& unit);

  static const PressureUnit Pa;
  static const PressureUnit mmHg;
  static const PressureUnit cmH2O;
  static const PressureUnit psi;
  static const PressureUnit atm;
};

class CDM_DECL SEScalarPressure : public SEScalarQuantity<PressureUnit>
{
public:
  SEScalarPressure() {};
  virtual ~SEScalarPressure() {}

  static void Load(const cdm::ScalarPressureData& src, SEScalarPressure& dst);
  static cdm::ScalarPressureData* Unload(const SEScalarPressure& src);
protected:
  static void Serialize(const cdm::ScalarPressureData& src, SEScalarPressure& dst);
  static void Serialize(const SEScalarPressure& src, cdm::ScalarPressureData& dst);
};
