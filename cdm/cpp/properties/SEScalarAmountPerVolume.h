/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL AmountPerVolumeUnit : public CCompoundUnit
{
public:
  AmountPerVolumeUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~AmountPerVolumeUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const AmountPerVolumeUnit& GetCompoundUnit(const std::string& unit);

  static AmountPerVolumeUnit mol_Per_L;
  static AmountPerVolumeUnit mol_Per_mL;
  static AmountPerVolumeUnit mmol_Per_L;
  static AmountPerVolumeUnit mmol_Per_mL;
  static AmountPerVolumeUnit ct_Per_L;
  static AmountPerVolumeUnit ct_Per_uL;
};

class CDM_DECL SEScalarAmountPerVolume : public SEScalarQuantity<AmountPerVolumeUnit>
{

public:
  SEScalarAmountPerVolume() {}
  virtual ~SEScalarAmountPerVolume() {}

  static void Load(const cdm::ScalarAmountPerVolumeData& src, SEScalarAmountPerVolume& dst);
  static cdm::ScalarAmountPerVolumeData* Unload(const SEScalarAmountPerVolume& src);
protected:
  static void Serialize(const cdm::ScalarAmountPerVolumeData& src, SEScalarAmountPerVolume& dst);
  static void Serialize(const SEScalarAmountPerVolume& src, cdm::ScalarAmountPerVolumeData& dst);
};
