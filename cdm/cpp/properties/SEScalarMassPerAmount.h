/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL MassPerAmountUnit : public CCompoundUnit
{
public:
  MassPerAmountUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~MassPerAmountUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const MassPerAmountUnit& GetCompoundUnit(const std::string& unit);

  static const MassPerAmountUnit g_Per_ct;
  static const MassPerAmountUnit g_Per_mol;
  static const MassPerAmountUnit g_Per_mmol;
  static const MassPerAmountUnit g_Per_umol;
  static const MassPerAmountUnit mg_Per_mol;
  static const MassPerAmountUnit mg_Per_mmol;
  static const MassPerAmountUnit kg_Per_mol;
  static const MassPerAmountUnit ug_Per_mol;
  static const MassPerAmountUnit ug_Per_mmol;
  static const MassPerAmountUnit ug_Per_ct;
  static const MassPerAmountUnit pg_Per_ct;
};

class CDM_DECL SEScalarMassPerAmount : public SEScalarQuantity<MassPerAmountUnit>
{
public:
  SEScalarMassPerAmount() {}
  virtual ~SEScalarMassPerAmount() {}

  static void Load(const cdm::ScalarMassPerAmountData& src, SEScalarMassPerAmount& dst);
  static cdm::ScalarMassPerAmountData* Unload(const SEScalarMassPerAmount& src);
protected:
  static void Serialize(const cdm::ScalarMassPerAmountData& src, SEScalarMassPerAmount& dst);
  static void Serialize(const SEScalarMassPerAmount& src, cdm::ScalarMassPerAmountData& dst);
};

