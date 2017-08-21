/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL FlowInertanceUnit : public CCompoundUnit
{
public:
  FlowInertanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~FlowInertanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const FlowInertanceUnit& GetCompoundUnit(const std::string& unit);

  static const FlowInertanceUnit mmHg_s2_Per_mL;
  static const FlowInertanceUnit mmHg_s2_Per_L;
  static const FlowInertanceUnit cmH2O_s2_Per_mL;
  static const FlowInertanceUnit cmH2O_s2_Per_L;
  static const FlowInertanceUnit Pa_s2_Per_m3;
};

class CDM_DECL SEScalarFlowInertance : public SEScalarQuantity<FlowInertanceUnit>
{
public:
  SEScalarFlowInertance() {}
  virtual ~SEScalarFlowInertance() {}

  static void Load(const cdm::ScalarFlowInertanceData& src, SEScalarFlowInertance& dst);
  static cdm::ScalarFlowInertanceData* Unload(const SEScalarFlowInertance& src);
protected:
  static void Serialize(const cdm::ScalarFlowInertanceData& src, SEScalarFlowInertance& dst);
  static void Serialize(const SEScalarFlowInertance& src, cdm::ScalarFlowInertanceData& dst);
};
