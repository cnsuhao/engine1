/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL FlowComplianceUnit : public CCompoundUnit
{
public:
  FlowComplianceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~FlowComplianceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const FlowComplianceUnit& GetCompoundUnit(const std::string& unit);

  static const FlowComplianceUnit L_Per_cmH2O;
  static const FlowComplianceUnit mL_Per_mmHg;
  static const FlowComplianceUnit mL_Per_cmH2O;
  static const FlowComplianceUnit m3_Per_Pa;
};

class CDM_DECL SEScalarFlowCompliance : public SEScalarQuantity<FlowComplianceUnit>
{
public:
  SEScalarFlowCompliance() {}
  virtual ~SEScalarFlowCompliance() {}

  static void Load(const cdm::ScalarFlowComplianceData& src, SEScalarFlowCompliance& dst);
  static cdm::ScalarFlowComplianceData* Unload(const SEScalarFlowCompliance& src);
protected:
  static void Serialize(const cdm::ScalarFlowComplianceData& src, SEScalarFlowCompliance& dst);
  static void Serialize(const SEScalarFlowCompliance& src, cdm::ScalarFlowComplianceData& dst);
};
