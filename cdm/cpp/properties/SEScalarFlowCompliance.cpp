/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "properties/SEScalarFlowCompliance.h"

const FlowComplianceUnit FlowComplianceUnit::L_Per_cmH2O("L/cmH2O");
const FlowComplianceUnit FlowComplianceUnit::mL_Per_mmHg("mL/mmHg");
const FlowComplianceUnit FlowComplianceUnit::mL_Per_cmH2O("mL/cmH2O");
const FlowComplianceUnit FlowComplianceUnit::m3_Per_Pa("m^3/Pa");

bool FlowComplianceUnit::IsValidUnit(const std::string& unit)
{
  if (L_Per_cmH2O.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_mmHg.GetString().compare(unit) == 0)
    return true;
  if (mL_Per_cmH2O.GetString().compare(unit) == 0)
    return true;
  if (m3_Per_Pa.GetString().compare(unit) == 0)
    return true;
  return false;
}

const FlowComplianceUnit& FlowComplianceUnit::GetCompoundUnit(const std::string& unit)
{
  if (L_Per_cmH2O.GetString().compare(unit) == 0)
    return L_Per_cmH2O;
  if (mL_Per_mmHg.GetString().compare(unit) == 0)
    return mL_Per_mmHg;
  if (mL_Per_cmH2O.GetString().compare(unit) == 0)
    return mL_Per_cmH2O;
  if (m3_Per_Pa.GetString().compare(unit) == 0)
    return m3_Per_Pa;
 std::stringstream err;
  err << unit << " is not a valid FlowCompliance unit";
  throw CommonDataModelException(err.str());
}

void SEScalarFlowCompliance::Load(const cdm::ScalarFlowComplianceData& src, SEScalarFlowCompliance& dst)
{
  SEScalarFlowCompliance::Serialize(src, dst);
}
void SEScalarFlowCompliance::Serialize(const cdm::ScalarFlowComplianceData& src, SEScalarFlowCompliance& dst)
{
  SEScalarQuantity<FlowComplianceUnit>::Serialize(src.scalarflowcompliance(), dst);
}

cdm::ScalarFlowComplianceData* SEScalarFlowCompliance::Unload(const SEScalarFlowCompliance& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::ScalarFlowComplianceData* dst = new cdm::ScalarFlowComplianceData();
  Serialize(src, *dst);
  return dst;
}
void SEScalarFlowCompliance::Serialize(const SEScalarFlowCompliance& src, cdm::ScalarFlowComplianceData& dst)
{
  SEScalarQuantity<FlowComplianceUnit>::Serialize(src, *dst.mutable_scalarflowcompliance());
}