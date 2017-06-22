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

class DLL_DECL ElectricInductanceUnit : public CCompoundUnit
{
public:
  ElectricInductanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~ElectricInductanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const ElectricInductanceUnit& GetCompoundUnit(const std::string& unit);

  static const ElectricInductanceUnit H;
};

class DLL_DECL SEScalarElectricInductance : public SEScalarQuantity<ElectricInductanceUnit>
{
public:
  SEScalarElectricInductance() {}
  virtual ~SEScalarElectricInductance() {}

  static void Load(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst);
  static cdm::ScalarElectricInductanceData* Unload(const SEScalarElectricInductance& src);
protected:
  static void Serialize(const cdm::ScalarElectricInductanceData& src, SEScalarElectricInductance& dst);
  static void Serialize(const SEScalarElectricInductance& src, cdm::ScalarElectricInductanceData& dst);
};
