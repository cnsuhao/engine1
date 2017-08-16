/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL HeatInductanceUnit : public CCompoundUnit
{
public:
  HeatInductanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~HeatInductanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const HeatInductanceUnit& GetCompoundUnit(const std::string& unit);

  static const HeatInductanceUnit K_s_Per_W;
};

class CDM_DECL SEScalarHeatInductance : public SEScalarQuantity<HeatInductanceUnit>
{
public:
  SEScalarHeatInductance() {}
  virtual ~SEScalarHeatInductance() {}

  static void Load(const cdm::ScalarHeatInductanceData& src, SEScalarHeatInductance& dst);
  static cdm::ScalarHeatInductanceData* Unload(const SEScalarHeatInductance& src);
protected:
  static void Serialize(const cdm::ScalarHeatInductanceData& src, SEScalarHeatInductance& dst);
  static void Serialize(const SEScalarHeatInductance& src, cdm::ScalarHeatInductanceData& dst);
};
