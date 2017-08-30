/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"
PROTO_PUSH
#include "bind/cdm/Compartment.pb.h"
PROTO_POP

void SELiquidCompartmentLink::Load(const cdm::LiquidCompartmentLinkData& src, SELiquidCompartmentLink& dst, SECircuitManager* circuits)
{
  SELiquidCompartmentLink::Serialize(src, dst, circuits);
}
void SELiquidCompartmentLink::Serialize(const cdm::LiquidCompartmentLinkData& src, SELiquidCompartmentLink& dst, SECircuitManager* circuits)
{
  SEFluidCompartmentLink::Serialize(src.fluidlink(), dst, circuits);
}

cdm::LiquidCompartmentLinkData* SELiquidCompartmentLink::Unload(const SELiquidCompartmentLink& src)
{
  cdm::LiquidCompartmentLinkData* dst = new cdm::LiquidCompartmentLinkData();
  SELiquidCompartmentLink::Serialize(src, *dst);
  return dst;
}
void SELiquidCompartmentLink::Serialize(const SELiquidCompartmentLink& src, cdm::LiquidCompartmentLinkData& dst)
{
  SEFluidCompartmentLink::Serialize(src, *dst.mutable_fluidlink());
}
