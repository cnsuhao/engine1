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

class CDM_DECL AmountPerMassUnit : public CCompoundUnit
{
public:
  AmountPerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AmountPerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AmountPerMassUnit& GetCompoundUnit(const std::string& unit);

  static AmountPerMassUnit ct_Per_g;
  static AmountPerMassUnit ct_Per_ug;
};

class CDM_DECL SEScalarAmountPerMass : public SEScalarQuantity<AmountPerMassUnit>
{

public:
  SEScalarAmountPerMass() {}
  virtual ~SEScalarAmountPerMass() {}

  static void Load(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst);
  static cdm::ScalarAmountPerMassData* Unload(const SEScalarAmountPerMass& src);
protected:
  static void Serialize(const cdm::ScalarAmountPerMassData& src, SEScalarAmountPerMass& dst);
  static void Serialize(const SEScalarAmountPerMass& src, cdm::ScalarAmountPerMassData& dst);
};
