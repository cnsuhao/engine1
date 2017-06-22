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

class DLL_DECL PressureUnit : public CCompoundUnit
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

class DLL_DECL SEScalarPressure : public SEScalarQuantity<PressureUnit>
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
