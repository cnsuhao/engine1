/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL SEScalarNegative1To1 : public SEScalar
{

public:
  SEScalarNegative1To1();
  virtual ~SEScalarNegative1To1() {}

  static void Load(const cdm::ScalarNegative1To1Data& src, SEScalarNegative1To1& dst);
  static cdm::ScalarNegative1To1Data* Unload(const SEScalarNegative1To1& src);
protected:
  static void Serialize(const cdm::ScalarNegative1To1Data& src, SEScalarNegative1To1& dst);
  static void Serialize(const SEScalarNegative1To1& src, cdm::ScalarNegative1To1Data& dst);

public:
  double GetValue() const { return SEScalar::GetValue(); }
  double GetValue(const NoUnit& unitless) const { return SEScalar::GetValue(); }
  void SetValue(double d);
  void SetValue(double d, const NoUnit& unitless);
};

