/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
#include "properties/SEScalar.h"

class DLL_DECL SEScalarNegative1To1 : public SEScalar
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

