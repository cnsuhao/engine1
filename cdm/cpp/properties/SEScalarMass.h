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

class DLL_DECL MassUnit : public CCompoundUnit
{
public:
  MassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~MassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const MassUnit& GetCompoundUnit(const std::string& unit);

  static const MassUnit ug;
  static const MassUnit mg;
  static const MassUnit g;
  static const MassUnit kg;
  static const MassUnit lb;
};

class DLL_DECL SEScalarMass : public SEScalarQuantity<MassUnit>
{
public:
  SEScalarMass() {}
  virtual ~SEScalarMass() {}

  static void Load(const cdm::ScalarMassData& src, SEScalarMass& dst);
  static cdm::ScalarMassData* Unload(const SEScalarMass& src);
protected:
  static void Serialize(const cdm::ScalarMassData& src, SEScalarMass& dst);
  static void Serialize(const SEScalarMass& src, cdm::ScalarMassData& dst);
};
