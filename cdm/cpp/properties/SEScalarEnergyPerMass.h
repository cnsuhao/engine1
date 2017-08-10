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

class CDM_DECL EnergyPerMassUnit : public CCompoundUnit
{
public:
  EnergyPerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~EnergyPerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const EnergyPerMassUnit& GetCompoundUnit(const std::string& unit);

  static const EnergyPerMassUnit J_Per_kg;
  static const EnergyPerMassUnit kJ_Per_kg;
  static const EnergyPerMassUnit mJ_Per_kg;
  static const EnergyPerMassUnit kcal_Per_kg;
};

class CDM_DECL SEScalarEnergyPerMass : public SEScalarQuantity<EnergyPerMassUnit>
{
public:
  SEScalarEnergyPerMass() {}
  virtual ~SEScalarEnergyPerMass() {}

  static void Load(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst);
  static cdm::ScalarEnergyPerMassData* Unload(const SEScalarEnergyPerMass& src);
protected:
  static void Serialize(const cdm::ScalarEnergyPerMassData& src, SEScalarEnergyPerMass& dst);
  static void Serialize(const SEScalarEnergyPerMass& src, cdm::ScalarEnergyPerMassData& dst);
};
