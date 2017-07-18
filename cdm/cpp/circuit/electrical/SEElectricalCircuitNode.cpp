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
#include "circuit/electrical/SEElectricalCircuitNode.h"

SEElectricalCircuitNode::SEElectricalCircuitNode(const std::string& name, Logger* logger) : SECircuitNode<SEScalarElectricPotential, SEScalarElectricCharge>(name, logger)
{
  
}

SEElectricalCircuitNode::~SEElectricalCircuitNode()
{
  
}

void SEElectricalCircuitNode::Clear()
{
  SECircuitNode::Clear();
}

void SEElectricalCircuitNode::Load(const cdm::ElectricalCircuitNodeData& src, SEElectricalCircuitNode& dst)
{
  SEElectricalCircuitNode::Serialize(src, dst);
}
void SEElectricalCircuitNode::Serialize(const cdm::ElectricalCircuitNodeData& src, SEElectricalCircuitNode& dst)
{
  SECircuitNode::Serialize(src.circuitnode(), dst);
  if (src.has_voltage())
    SEScalarElectricPotential::Load(src.voltage(), dst.GetVoltage());
  if (src.has_nextvoltage())
    SEScalarElectricPotential::Load(src.nextvoltage(), dst.GetNextVoltage());
  if (src.has_charge())
    SEScalarElectricCharge::Load(src.charge(), dst.GetCharge());
  if (src.has_nextcharge())
    SEScalarElectricCharge::Load(src.nextcharge(), dst.GetNextCharge());
  if (src.has_chargebaseline())
    SEScalarElectricCharge::Load(src.chargebaseline(), dst.GetChargeBaseline());
}

cdm::ElectricalCircuitNodeData* SEElectricalCircuitNode::Unload(const SEElectricalCircuitNode& src)
{
  cdm::ElectricalCircuitNodeData* dst = new cdm::ElectricalCircuitNodeData();
  SEElectricalCircuitNode::Serialize(src, *dst);
  return dst;
}
void SEElectricalCircuitNode::Serialize(const SEElectricalCircuitNode& src, cdm::ElectricalCircuitNodeData& dst)
{
  SECircuitNode::Serialize(src, *dst.mutable_circuitnode());
  if (src.HasVoltage())
    dst.set_allocated_voltage(SEScalarElectricPotential::Unload(*src.m_Potential));
  if (src.HasNextVoltage())
    dst.set_allocated_nextvoltage(SEScalarElectricPotential::Unload(*src.m_NextPotential));
  if (src.HasCharge())
    dst.set_allocated_charge(SEScalarElectricCharge::Unload(*src.m_Quantity));
  if (src.HasNextCharge())
    dst.set_allocated_nextcharge(SEScalarElectricCharge::Unload(*src.m_NextQuantity));
  if (src.HasChargeBaseline())
    dst.set_allocated_chargebaseline(SEScalarElectricCharge::Unload(*src.m_QuantityBaseline));
}

bool SEElectricalCircuitNode::HasVoltage() const
{
  return HasPotential();
}
SEScalarElectricPotential& SEElectricalCircuitNode::GetVoltage()
{
  return GetPotential();
}
double SEElectricalCircuitNode::GetVoltage(const ElectricPotentialUnit& unit) const
{
  if (m_Potential == nullptr)
    return SEScalar::dNaN();
  return m_Potential->GetValue(unit);
}

bool SEElectricalCircuitNode::HasNextVoltage() const
{
  return HasNextPotential();
}
SEScalarElectricPotential& SEElectricalCircuitNode::GetNextVoltage()
{
  return GetNextPotential();
}
double SEElectricalCircuitNode::GetNextVoltage(const ElectricPotentialUnit& unit) const
{
  if (m_NextPotential == nullptr)
    return SEScalar::dNaN();
  return m_NextPotential->GetValue(unit);
}

bool SEElectricalCircuitNode::HasCharge() const
{
  return HasQuantity();
}
SEScalarElectricCharge& SEElectricalCircuitNode::GetCharge()
{
  return GetQuantity();
}
double SEElectricalCircuitNode::GetCharge(const ElectricChargeUnit& unit) const
{
  if (m_Quantity == nullptr)
    return SEScalar::dNaN();
  return m_Quantity->GetValue(unit);
}

bool SEElectricalCircuitNode::HasNextCharge() const
{
  return HasNextQuantity();
}
SEScalarElectricCharge& SEElectricalCircuitNode::GetNextCharge()
{
  return GetNextQuantity();
}
double SEElectricalCircuitNode::GetNextCharge(const ElectricChargeUnit& unit) const
{
  if (m_NextQuantity == nullptr)
    return SEScalar::dNaN();
  return m_NextQuantity->GetValue(unit);
}

bool SEElectricalCircuitNode::HasChargeBaseline() const
{
  return HasQuantityBaseline();
}
SEScalarElectricCharge& SEElectricalCircuitNode::GetChargeBaseline()
{
  return GetQuantityBaseline();
}
double SEElectricalCircuitNode::GetChargeBaseline(const ElectricChargeUnit& unit) const
{
  if (m_QuantityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_QuantityBaseline->GetValue(unit);
}