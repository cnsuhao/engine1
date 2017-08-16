/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h" 
#include "circuit/thermal/SEThermalCircuitNode.h"

SEThermalCircuitNode::SEThermalCircuitNode(const std::string& name, Logger* logger) : SECircuitNode<THERMAL_CIRCUIT_NODE>(name,logger)
{
  
}

SEThermalCircuitNode::~SEThermalCircuitNode()
{
  Clear();
}

void SEThermalCircuitNode::Clear()
{
  SECircuitNode::Clear();
}

void SEThermalCircuitNode::Load(const cdm::ThermalCircuitNodeData& src, SEThermalCircuitNode& dst)
{
  SEThermalCircuitNode::Serialize(src, dst);
}
void SEThermalCircuitNode::Serialize(const cdm::ThermalCircuitNodeData& src, SEThermalCircuitNode& dst)
{
  SECircuitNode::Serialize(src.circuitnode(), dst);
  if (src.has_temperature())
    SEScalarTemperature::Load(src.temperature(), dst.GetTemperature());
  if (src.has_nexttemperature())
    SEScalarTemperature::Load(src.nexttemperature(), dst.GetNextTemperature());
  if (src.has_heat())
    SEScalarEnergy::Load(src.heat(), dst.GetHeat());
  if (src.has_nextheat())
    SEScalarEnergy::Load(src.nextheat(), dst.GetNextHeat());
  if (src.has_heatbaseline())
    SEScalarEnergy::Load(src.heatbaseline(), dst.GetHeatBaseline());
}

cdm::ThermalCircuitNodeData* SEThermalCircuitNode::Unload(const SEThermalCircuitNode& src)
{
  cdm::ThermalCircuitNodeData* dst = new cdm::ThermalCircuitNodeData();
  SEThermalCircuitNode::Serialize(src, *dst);
  return dst;
}
void SEThermalCircuitNode::Serialize(const SEThermalCircuitNode& src, cdm::ThermalCircuitNodeData& dst)
{
  SECircuitNode::Serialize(src, *dst.mutable_circuitnode());
  if (src.HasTemperature())
    dst.set_allocated_temperature(SEScalarTemperature::Unload(*src.m_Potential));
  if (src.HasNextTemperature())
    dst.set_allocated_nexttemperature(SEScalarTemperature::Unload(*src.m_NextPotential));
  if (src.HasHeat())
    dst.set_allocated_heat(SEScalarEnergy::Unload(*src.m_Quantity));
  if (src.HasNextHeat())
    dst.set_allocated_nextheat(SEScalarEnergy::Unload(*src.m_NextQuantity));
  if (src.HasHeatBaseline())
    dst.set_allocated_heatbaseline(SEScalarEnergy::Unload(*src.m_QuantityBaseline));
}

bool SEThermalCircuitNode::HasTemperature() const
{
  return HasPotential();
}
SEScalarTemperature& SEThermalCircuitNode::GetTemperature()
{
  return GetPotential();
}
double SEThermalCircuitNode::GetTemperature(const TemperatureUnit& unit) const
{
  if (m_Potential == nullptr)
    return SEScalar::dNaN();
  return m_Potential->GetValue(unit);
}

bool SEThermalCircuitNode::HasNextTemperature() const
{
  return HasNextPotential();
}
SEScalarTemperature& SEThermalCircuitNode::GetNextTemperature()
{
  return GetNextPotential();
}
double SEThermalCircuitNode::GetNextTemperature(const TemperatureUnit& unit) const
{
  if (m_NextPotential == nullptr)
    return SEScalar::dNaN();
  return m_NextPotential->GetValue(unit);
}

bool SEThermalCircuitNode::HasHeat() const
{
  return HasQuantity();
}
SEScalarEnergy& SEThermalCircuitNode::GetHeat()
{
  return GetQuantity();
}
double SEThermalCircuitNode::GetHeat(const EnergyUnit& unit) const
{
  if (m_Quantity == nullptr)
    return SEScalar::dNaN();
  return m_Quantity->GetValue(unit);
}

bool SEThermalCircuitNode::HasNextHeat() const
{
  return HasNextQuantity();
}
SEScalarEnergy& SEThermalCircuitNode::GetNextHeat()
{
  return GetNextQuantity();
}
double SEThermalCircuitNode::GetNextHeat(const EnergyUnit& unit) const
{
  if (m_NextQuantity == nullptr)
    return SEScalar::dNaN();
  return m_NextQuantity->GetValue(unit);
}

bool SEThermalCircuitNode::HasHeatBaseline() const
{
  return HasQuantityBaseline();
}
SEScalarEnergy& SEThermalCircuitNode::GetHeatBaseline()
{
  return GetQuantityBaseline();
}
double SEThermalCircuitNode::GetHeatBaseline(const EnergyUnit& unit) const
{
  if (m_QuantityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_QuantityBaseline->GetValue(unit);
}