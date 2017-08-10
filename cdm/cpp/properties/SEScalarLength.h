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

class CDM_DECL LengthUnit : public CCompoundUnit
{
public:
  LengthUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~LengthUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const LengthUnit& GetCompoundUnit(const std::string& unit);

  static const LengthUnit m;
  static const LengthUnit cm;
  static const LengthUnit mm;
  static const LengthUnit um;
  static const LengthUnit in;
  static const LengthUnit ft;
};

class CDM_DECL SEScalarLength : public SEScalarQuantity<LengthUnit>
{
public:
  SEScalarLength() {}
  virtual ~SEScalarLength() {}

  static void Load(const cdm::ScalarLengthData& src, SEScalarLength& dst);
  static cdm::ScalarLengthData* Unload(const SEScalarLength& src);
protected:
  static void Serialize(const cdm::ScalarLengthData& src, SEScalarLength& dst);
  static void Serialize(const SEScalarLength& src, cdm::ScalarLengthData& dst);
};
