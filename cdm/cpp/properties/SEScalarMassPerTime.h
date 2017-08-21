/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL MassPerTimeUnit : public CCompoundUnit
{
public:
  MassPerTimeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~MassPerTimeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const MassPerTimeUnit& GetCompoundUnit(const std::string& unit);

  static const MassPerTimeUnit g_Per_s;
  static const MassPerTimeUnit g_Per_min;
  static const MassPerTimeUnit g_Per_day;
  static const MassPerTimeUnit mg_Per_s;
  static const MassPerTimeUnit mg_Per_min;
  static const MassPerTimeUnit ug_Per_min;
  static const MassPerTimeUnit ug_Per_s;
  static const MassPerTimeUnit kg_Per_s;
};

class CDM_DECL SEScalarMassPerTime : public SEScalarQuantity<MassPerTimeUnit>
{
public:
  SEScalarMassPerTime() {}
  virtual ~SEScalarMassPerTime() {}

  static void Load(const cdm::ScalarMassPerTimeData& src, SEScalarMassPerTime& dst);
  static cdm::ScalarMassPerTimeData* Unload(const SEScalarMassPerTime& src);
protected:
  static void Serialize(const cdm::ScalarMassPerTimeData& src, SEScalarMassPerTime& dst);
  static void Serialize(const SEScalarMassPerTime& src, cdm::ScalarMassPerTimeData& dst);
};
