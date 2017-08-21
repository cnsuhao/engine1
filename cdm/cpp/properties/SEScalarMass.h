/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL MassUnit : public CCompoundUnit
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

class CDM_DECL SEScalarMass : public SEScalarQuantity<MassUnit>
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
