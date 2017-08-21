/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL MassPerMassUnit : public CCompoundUnit
{
public:
  MassPerMassUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~MassPerMassUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const MassPerMassUnit& GetCompoundUnit(const std::string& unit);

  static const MassPerMassUnit ug_Per_kg;
  static const MassPerMassUnit mg_Per_g;
};

class CDM_DECL SEScalarMassPerMass : public SEScalarQuantity<MassPerMassUnit>
{
public:
  SEScalarMassPerMass() {}
  virtual ~SEScalarMassPerMass() {}

  static void Load(const cdm::ScalarMassPerMassData& src, SEScalarMassPerMass& dst);
  static cdm::ScalarMassPerMassData* Unload(const SEScalarMassPerMass& src);
protected:
  static void Serialize(const cdm::ScalarMassPerMassData& src, SEScalarMassPerMass& dst);
  static void Serialize(const SEScalarMassPerMass& src, cdm::ScalarMassPerMassData& dst);
};
