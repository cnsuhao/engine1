/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
//CDM_BIND_DECL(FluidCircuitData)
#include "circuit/SECircuitCalculator.h"
#include "circuit/fluid/SEFluidCircuit.h"

#include "properties/SEScalarFlowCompliance.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarFlowInertance.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarFlowResistance.h"

class CDM_DECL SEFluidCircuitCalculator : public SECircuitCalculator<SEFluidCircuit, SEFluidCircuitNode, SEFluidCircuitPath, FlowComplianceUnit, VolumePerTimeUnit, FlowInertanceUnit, PressureUnit, VolumeUnit, FlowResistanceUnit>
{
public:

  SEFluidCircuitCalculator(Logger* logger);
  SEFluidCircuitCalculator(const FlowComplianceUnit&, const VolumePerTimeUnit&, const FlowInertanceUnit&, const PressureUnit&, const VolumeUnit&, const FlowResistanceUnit&, Logger* logger);
  virtual ~SEFluidCircuitCalculator();
};