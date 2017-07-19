/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "stdafx.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"

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
