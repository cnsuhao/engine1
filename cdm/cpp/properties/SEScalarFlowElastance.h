/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "properties/SEScalar.h"

class CDM_DECL FlowElastanceUnit : public CCompoundUnit
{
public:
  FlowElastanceUnit(const std::string& u) : CCompoundUnit(u) {}
  virtual ~FlowElastanceUnit() {}

  static bool IsValidUnit(const std::string& unit);
  static const FlowElastanceUnit& GetCompoundUnit(const std::string& unit);

  static const FlowElastanceUnit cmH2O_Per_L;
  static const FlowElastanceUnit mmHg_Per_mL;
  static const FlowElastanceUnit Pa_Per_m3;
};

class CDM_DECL SEScalarFlowElastance : public SEScalarQuantity<FlowElastanceUnit>
{
public:
  SEScalarFlowElastance() {}
  virtual ~SEScalarFlowElastance() {}

  static void Load(const cdm::ScalarFlowElastanceData& src, SEScalarFlowElastance& dst);
  static cdm::ScalarFlowElastanceData* Unload(const SEScalarFlowElastance& src);
protected:
  static void Serialize(const cdm::ScalarFlowElastanceData& src, SEScalarFlowElastance& dst);
  static void Serialize(const SEScalarFlowElastance& src, cdm::ScalarFlowElastanceData& dst);
};
