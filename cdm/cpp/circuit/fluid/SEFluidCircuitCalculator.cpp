/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/fluid/SEFluidCircuitCalculator.h"


SEFluidCircuitCalculator::SEFluidCircuitCalculator(Logger* logger) : SECircuitCalculator<SEFluidCircuit,SEFluidCircuitNode,SEFluidCircuitPath, FlowComplianceUnit, VolumePerTimeUnit, FlowInertanceUnit, PressureUnit, VolumeUnit, FlowResistanceUnit>(
  FlowComplianceUnit::m3_Per_Pa,VolumePerTimeUnit::m3_Per_s, FlowInertanceUnit::Pa_s2_Per_m3,PressureUnit::Pa,VolumeUnit::m3,FlowResistanceUnit::Pa_s_Per_m3,logger)
{

}
SEFluidCircuitCalculator::SEFluidCircuitCalculator(const FlowComplianceUnit& c, const VolumePerTimeUnit& f, const FlowInertanceUnit& i, const PressureUnit& p, const VolumeUnit& q, const FlowResistanceUnit& r, Logger* logger) : SECircuitCalculator<SEFluidCircuit, SEFluidCircuitNode, SEFluidCircuitPath, FlowComplianceUnit, VolumePerTimeUnit, FlowInertanceUnit, PressureUnit, VolumeUnit, FlowResistanceUnit>(c, f, i, p, q, r, logger)
{

}
SEFluidCircuitCalculator::~SEFluidCircuitCalculator()
{
  
}
