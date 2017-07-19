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
