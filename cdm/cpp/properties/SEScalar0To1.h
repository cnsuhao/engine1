/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL SEScalar0To1 : public SEScalar
{

public:
  SEScalar0To1();
  virtual ~SEScalar0To1() {}

  static void Load(const cdm::Scalar0To1Data& src, SEScalar0To1& dst);
  static cdm::Scalar0To1Data* Unload(const SEScalar0To1& src);
protected:
  static void Serialize(const cdm::Scalar0To1Data& src, SEScalar0To1& dst);
  static void Serialize(const SEScalar0To1& src, cdm::Scalar0To1Data& dst);

public:
  double GetValue() const { return SEScalar::GetValue(); }
  double GetValue(const NoUnit& unitless) const { return SEScalar::GetValue(); }
  void SetValue(double d);
  void SetValue(double d, const NoUnit& unitless);
};

