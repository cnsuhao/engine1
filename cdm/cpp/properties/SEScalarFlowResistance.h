/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL FlowResistanceUnit : public CCompoundUnit
{
public:
  FlowResistanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~FlowResistanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const FlowResistanceUnit& GetCompoundUnit(const std::string& unit);

  static const FlowResistanceUnit cmH2O_s_Per_L;
  static const FlowResistanceUnit mmHg_s_Per_mL;
  static const FlowResistanceUnit mmHg_min_Per_mL;
  static const FlowResistanceUnit mmHg_min_Per_L;
  static const FlowResistanceUnit Pa_s_Per_m3;
};

class CDM_DECL SEScalarFlowResistance : public SEScalarQuantity<FlowResistanceUnit>
{
public:
  SEScalarFlowResistance() {}
  virtual ~SEScalarFlowResistance() {}

  static void Load(const cdm::ScalarFlowResistanceData& src, SEScalarFlowResistance& dst);
  static cdm::ScalarFlowResistanceData* Unload(const SEScalarFlowResistance& src);
protected:
  static void Serialize(const cdm::ScalarFlowResistanceData& src, SEScalarFlowResistance& dst);
  static void Serialize(const SEScalarFlowResistance& src, cdm::ScalarFlowResistanceData& dst);
};
