/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/fluid/SEGasCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"

void SEGasCompartmentLink::Load(const cdm::GasCompartmentLinkData& src, SEGasCompartmentLink& dst, SECircuitManager* circuits)
{
  SEGasCompartmentLink::Serialize(src, dst,circuits);
}
void SEGasCompartmentLink::Serialize(const cdm::GasCompartmentLinkData& src, SEGasCompartmentLink& dst, SECircuitManager* circuits)
{
  SEFluidCompartmentLink::Serialize(src.fluidlink(), dst, circuits);
}

cdm::GasCompartmentLinkData* SEGasCompartmentLink::Unload(const SEGasCompartmentLink& src)
{
  cdm::GasCompartmentLinkData* dst = new cdm::GasCompartmentLinkData();
  SEGasCompartmentLink::Serialize(src, *dst);
  return dst;
}
void SEGasCompartmentLink::Serialize(const SEGasCompartmentLink& src, cdm::GasCompartmentLinkData& dst)
{
  SEFluidCompartmentLink::Serialize(src, *dst.mutable_fluidlink());
}
