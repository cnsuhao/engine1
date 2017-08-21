/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h" 
#include "circuit/fluid/SEFluidCircuitNode.h"

SEFluidCircuitNode::SEFluidCircuitNode(const std::string& name, Logger* logger) : SECircuitNode<SEScalarPressure,SEScalarVolume>(name,logger)
{
  
}

SEFluidCircuitNode::~SEFluidCircuitNode()
{
  Clear();
}

void SEFluidCircuitNode::Clear()
{
  SECircuitNode::Clear();
}

void SEFluidCircuitNode::Load(const cdm::FluidCircuitNodeData& src, SEFluidCircuitNode& dst)
{
  SEFluidCircuitNode::Serialize(src, dst);
}
void SEFluidCircuitNode::Serialize(const cdm::FluidCircuitNodeData& src, SEFluidCircuitNode& dst)
{
  SECircuitNode::Serialize(src.circuitnode(),dst);
  if (src.has_pressure())
    SEScalarPressure::Load(src.pressure(),dst.GetPressure());
  if (src.has_nextpressure())
    SEScalarPressure::Load(src.nextpressure(), dst.GetNextPressure());
  if (src.has_volume())
    SEScalarVolume::Load(src.volume(), dst.GetVolume());
  if (src.has_nextvolume())
    SEScalarVolume::Load(src.nextvolume(), dst.GetNextVolume());
  if (src.has_volumebaseline())
    SEScalarVolume::Load(src.volumebaseline(), dst.GetVolumeBaseline());
}

cdm::FluidCircuitNodeData* SEFluidCircuitNode::Unload(const SEFluidCircuitNode& src)
{
  cdm::FluidCircuitNodeData* dst = new cdm::FluidCircuitNodeData();
  SEFluidCircuitNode::Serialize(src, *dst);
  return dst;
}
void SEFluidCircuitNode::Serialize(const SEFluidCircuitNode& src, cdm::FluidCircuitNodeData& dst)
{
  SECircuitNode::Serialize(src,*dst.mutable_circuitnode());
  if (src.HasPressure())
    dst.set_allocated_pressure(SEScalarPressure::Unload(*src.m_Potential));
  if (src.HasNextPressure())
    dst.set_allocated_nextpressure(SEScalarPressure::Unload(*src.m_NextPotential));
  if (src.HasVolume())
    dst.set_allocated_volume(SEScalarVolume::Unload(*src.m_Quantity));
  if (src.HasNextVolume())
    dst.set_allocated_nextvolume(SEScalarVolume::Unload(*src.m_NextQuantity));
  if (src.HasVolumeBaseline())
    dst.set_allocated_volumebaseline(SEScalarVolume::Unload(*src.m_QuantityBaseline));
}

bool SEFluidCircuitNode::HasPressure() const
{
  return HasPotential();
}
SEScalarPressure& SEFluidCircuitNode::GetPressure()
{
  return GetPotential();
}
double SEFluidCircuitNode::GetPressure(const PressureUnit& unit) const
{
  if (m_Potential == nullptr)
    return SEScalar::dNaN();
  return m_Potential->GetValue(unit);
}

bool SEFluidCircuitNode::HasNextPressure() const
{
  return HasNextPotential();
}
SEScalarPressure& SEFluidCircuitNode::GetNextPressure()
{
  return GetNextPotential();
}
double SEFluidCircuitNode::GetNextPressure(const PressureUnit& unit) const
{
  if (m_NextPotential == nullptr)
    return SEScalar::dNaN();
  return m_NextPotential->GetValue(unit);
}

bool SEFluidCircuitNode::HasVolume() const
{
  return HasQuantity();
}
SEScalarVolume& SEFluidCircuitNode::GetVolume()
{
  return GetQuantity();
}
double SEFluidCircuitNode::GetVolume(const VolumeUnit& unit) const
{
  if (m_Quantity == nullptr)
    return SEScalar::dNaN();
  return m_Quantity->GetValue(unit);
}

bool SEFluidCircuitNode::HasNextVolume() const
{
  return HasNextQuantity();
}
SEScalarVolume& SEFluidCircuitNode::GetNextVolume()
{
  return GetNextQuantity();
}
double SEFluidCircuitNode::GetNextVolume(const VolumeUnit& unit) const
{
  if (m_NextQuantity == nullptr)
    return SEScalar::dNaN();
  return m_NextQuantity->GetValue(unit);
}

bool SEFluidCircuitNode::HasVolumeBaseline() const
{
  return HasQuantityBaseline();
}
SEScalarVolume& SEFluidCircuitNode::GetVolumeBaseline()
{
  return GetQuantityBaseline();
}
double SEFluidCircuitNode::GetVolumeBaseline(const VolumeUnit& unit) const
{
  if (m_QuantityBaseline == nullptr)
    return SEScalar::dNaN();
  return m_QuantityBaseline->GetValue(unit);
}
