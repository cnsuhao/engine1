/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/fluid/SEFluidCircuitPath.h"
PROTO_PUSH
#include "bind/cdm/Circuit.pb.h"
PROTO_POP

SEFluidCircuitPath::SEFluidCircuitPath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name) :
  SECircuitPath<SEScalarVolumePerTime, SEScalarFlowResistance, SEScalarFlowCompliance, SEScalarFlowInertance, SEScalarPressure, SEScalarVolume>(src, tgt, name),
  m_FluidSourceNode(src), m_FluidTargetNode(tgt)
{

}
SEFluidCircuitPath::~SEFluidCircuitPath()
{
  Clear();
}

void SEFluidCircuitPath::Clear()
{
  SECircuitPath::Clear();
}

void SEFluidCircuitPath::Load(const cdm::FluidCircuitPathData& src, SEFluidCircuitPath& dst)
{
  SEFluidCircuitPath::Serialize(src, dst);
}
void SEFluidCircuitPath::Serialize(const cdm::FluidCircuitPathData& src, SEFluidCircuitPath& dst)
{
  SECircuitPath::Serialize(src.circuitpath(),dst);
  if (src.has_resistance())
    SEScalarFlowResistance::Load(src.resistance(), dst.GetResistance());
  if (src.has_nextresistance())
    SEScalarFlowResistance::Load(src.nextresistance(), dst.GetNextResistance());
  if (src.has_resistancebaseline())
    SEScalarFlowResistance::Load(src.resistancebaseline(), dst.GetResistanceBaseline());
  if (src.has_compliance())
    SEScalarFlowCompliance::Load(src.compliance(), dst.GetCompliance());
  if (src.has_nextcompliance())
    SEScalarFlowCompliance::Load(src.nextcompliance(), dst.GetNextCompliance());
  if (src.has_compliancebaseline())
    SEScalarFlowCompliance::Load(src.compliancebaseline(), dst.GetComplianceBaseline());
  if (src.has_inertance())
    SEScalarFlowInertance::Load(src.inertance(), dst.GetInertance());
  if (src.has_nextinertance())
    SEScalarFlowInertance::Load(src.nextinertance(), dst.GetNextInertance());
  if (src.has_inertancebaseline())
    SEScalarFlowInertance::Load(src.inertancebaseline(), dst.GetInertanceBaseline());
  if (src.has_flow())
    SEScalarVolumePerTime::Load(src.flow(), dst.GetFlow());
  if (src.has_nextflow())
    SEScalarVolumePerTime::Load(src.nextflow(), dst.GetNextFlow());
  if (src.has_flowsource())
    SEScalarVolumePerTime::Load(src.flowsource(), dst.GetFlowSource());
  if (src.has_nextflowsource())
    SEScalarVolumePerTime::Load(src.nextflowsource(), dst.GetNextFlowSource());
  if (src.has_flowsourcebaseline())
    SEScalarVolumePerTime::Load(src.flowsourcebaseline(), dst.GetFlowSourceBaseline());
  if (src.has_pressuresource())
    SEScalarPressure::Load(src.pressuresource(), dst.GetPressureSource());
  if (src.has_nextpressuresource())
    SEScalarPressure::Load(src.nextpressuresource(), dst.GetNextPressureSource());
  if (src.has_pressuresourcebaseline())
    SEScalarPressure::Load(src.pressuresourcebaseline(), dst.GetPressureSourceBaseline());
  if (src.has_valvebreakdownpressure())
    SEScalarPressure::Load(src.valvebreakdownpressure(), dst.GetValveBreakdownPressure());

  if(!dst.HasValidElements())
    dst.Warning("Path does not have valid elements");
}

cdm::FluidCircuitPathData* SEFluidCircuitPath::Unload(const SEFluidCircuitPath& src)
{
  cdm::FluidCircuitPathData* dst = new cdm::FluidCircuitPathData();
  SEFluidCircuitPath::Serialize(src, *dst);
  return dst;
}
void SEFluidCircuitPath::Serialize(const SEFluidCircuitPath& src, cdm::FluidCircuitPathData& dst)
{
  SECircuitPath::Serialize(src,*dst.mutable_circuitpath());
  if (src.HasResistance())
    dst.set_allocated_resistance(SEScalarFlowResistance::Unload(*src.m_Resistance));
  if (src.HasNextResistance())
    dst.set_allocated_nextresistance(SEScalarFlowResistance::Unload(*src.m_NextResistance));
  if (src.HasResistanceBaseline())
    dst.set_allocated_resistancebaseline(SEScalarFlowResistance::Unload(*src.m_ResistanceBaseline));
  if (src.HasCompliance())
    dst.set_allocated_compliance(SEScalarFlowCompliance::Unload(*src.m_Capacitance));
  if (src.HasNextCompliance())
    dst.set_allocated_nextcompliance(SEScalarFlowCompliance::Unload(*src.m_NextCapacitance));
  if (src.HasComplianceBaseline())
    dst.set_allocated_compliancebaseline(SEScalarFlowCompliance::Unload(*src.m_CapacitanceBaseline));
  if (src.HasInertance())
    dst.set_allocated_inertance(SEScalarFlowInertance::Unload(*src.m_Inductance));
  if (src.HasNextInertance())
    dst.set_allocated_nextinertance(SEScalarFlowInertance::Unload(*src.m_NextInductance));
  if (src.HasInertanceBaseline())
    dst.set_allocated_inertancebaseline(SEScalarFlowInertance::Unload(*src.m_InductanceBaseline));
  if (src.HasFlow())
    dst.set_allocated_flow(SEScalarVolumePerTime::Unload(*src.m_Flux));
  if (src.HasNextFlow())
    dst.set_allocated_nextflow(SEScalarVolumePerTime::Unload(*src.m_NextFlux));
  if (src.HasFlowSource())
    dst.set_allocated_flowsource(SEScalarVolumePerTime::Unload(*src.m_FluxSource));
  if (src.HasNextFlowSource())
    dst.set_allocated_nextflowsource(SEScalarVolumePerTime::Unload(*src.m_NextFluxSource));
  if (src.HasFlowSourceBaseline())
    dst.set_allocated_flowsourcebaseline(SEScalarVolumePerTime::Unload(*src.m_FluxSourceBaseline));
  if (src.HasPressureSource())
    dst.set_allocated_pressuresource(SEScalarPressure::Unload(*src.m_PotentialSource));
  if (src.HasNextPressureSource())
    dst.set_allocated_nextpressuresource(SEScalarPressure::Unload(*src.m_NextPotentialSource));
  if (src.HasPressureSourceBaseline())
    dst.set_allocated_pressuresourcebaseline(SEScalarPressure::Unload(*src.m_PotentialSourceBaseline));
  if (src.HasValveBreakdownPressure())
    dst.set_allocated_valvebreakdownpressure(SEScalarPressure::Unload(*src.m_ValveBreakdownPotential));
}

////////////////////////////////
// Fluid Resistance Types//
////////////////////////////////

bool SEFluidCircuitPath::HasResistance() const
{
  return SECircuitPath::HasResistance();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetResistance()
{
  return SECircuitPath::GetResistance();
}
double SEFluidCircuitPath::GetResistance(const FlowResistanceUnit& unit) const
{
  if (m_Resistance == nullptr)
    return SEScalar::dNaN();
  return m_Resistance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextResistance() const
{
  return SECircuitPath::HasNextResistance();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetNextResistance()
{
  return SECircuitPath::GetNextResistance();
}
double SEFluidCircuitPath::GetNextResistance(const FlowResistanceUnit& unit) const
{
  if (m_NextResistance == nullptr)
    return SEScalar::dNaN();
  return m_NextResistance->GetValue(unit);
}
bool SEFluidCircuitPath::HasResistanceBaseline() const
{
  return SECircuitPath::HasResistanceBaseline();
}
SEScalarFlowResistance& SEFluidCircuitPath::GetResistanceBaseline()
{
  return SECircuitPath::GetResistanceBaseline();
}
double SEFluidCircuitPath::GetResistanceBaseline(const FlowResistanceUnit& unit) const
{
  if (m_ResistanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_ResistanceBaseline->GetValue(unit);
}

//////////////////////////////////
// Fluid Capacitance Types //
//////////////////////////////////

bool SEFluidCircuitPath::HasCompliance() const
{
  return HasCapacitance();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetCompliance()
{
  return GetCapacitance();
}
double SEFluidCircuitPath::GetCompliance(const FlowComplianceUnit& unit) const
{
  if (m_Capacitance == nullptr)
    return SEScalar::dNaN();
  return m_Capacitance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextCompliance() const
{
  return HasNextCapacitance();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetNextCompliance()
{
  return GetNextCapacitance();
}
double SEFluidCircuitPath::GetNextCompliance(const FlowComplianceUnit& unit) const
{
  if (m_NextCapacitance == nullptr)
    return SEScalar::dNaN();
  return m_NextCapacitance->GetValue(unit);
}
bool SEFluidCircuitPath::HasComplianceBaseline() const
{
  return HasCapacitanceBaseline();
}
SEScalarFlowCompliance& SEFluidCircuitPath::GetComplianceBaseline()
{
  return GetCapacitanceBaseline();
}
double SEFluidCircuitPath::GetComplianceBaseline(const FlowComplianceUnit& unit) const
{
  if (m_CapacitanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_CapacitanceBaseline->GetValue(unit);
}

/////////////////////////////////
// Fluid Inductance Types //
/////////////////////////////////

bool SEFluidCircuitPath::HasInertance() const
{
  return HasInductance();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetInertance()
{
  return GetInductance();
}
double SEFluidCircuitPath::GetInertance(const FlowInertanceUnit& unit) const
{
  if (m_Inductance == nullptr)
    return SEScalar::dNaN();
  return m_Inductance->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextInertance() const
{
  return HasNextInductance();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetNextInertance()
{
  return GetNextInductance();
}
double SEFluidCircuitPath::GetNextInertance(const FlowInertanceUnit& unit) const
{
  if (m_NextInductance == nullptr)
    return SEScalar::dNaN();
  return m_NextInductance->GetValue(unit);
}
bool SEFluidCircuitPath::HasInertanceBaseline() const
{
  return HasInductanceBaseline();
}
SEScalarFlowInertance& SEFluidCircuitPath::GetInertanceBaseline()
{
  return GetInductanceBaseline();
}
double SEFluidCircuitPath::GetInertanceBaseline(const FlowInertanceUnit& unit) const
{
  if (m_InductanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_InductanceBaseline->GetValue(unit);
}


///////////////////////////
// Fluid Flux Types //
///////////////////////////
bool SEFluidCircuitPath::HasFlow() const
{
  return HasFlux();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlow()
{
  return GetFlux();
}
double SEFluidCircuitPath::GetFlow(const VolumePerTimeUnit& unit) const
{
  if (m_Flux == nullptr)
    return SEScalar::dNaN();
  return m_Flux->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextFlow() const
{
  return HasNextFlux();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetNextFlow()
{
  return GetNextFlux();
}
double SEFluidCircuitPath::GetNextFlow(const VolumePerTimeUnit& unit) const
{
  if (m_NextFlux == nullptr)
    return SEScalar::dNaN();
  return m_NextFlux->GetValue(unit);
}
bool SEFluidCircuitPath::HasFlowSource() const
{
  return HasFluxSource();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlowSource()
{
  return GetFluxSource();
}
double SEFluidCircuitPath::GetFlowSource(const VolumePerTimeUnit& unit) const
{
  if (m_FluxSource == nullptr)
    return SEScalar::dNaN();
  return m_FluxSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextFlowSource() const
{
  return HasNextFluxSource();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetNextFlowSource()
{
  return GetNextFluxSource();
}
double SEFluidCircuitPath::GetNextFlowSource(const VolumePerTimeUnit& unit) const
{
  if (m_NextFluxSource == nullptr)
    return SEScalar::dNaN();
  return m_NextFluxSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasFlowSourceBaseline() const
{
  return HasFluxSourceBaseline();
}
SEScalarVolumePerTime& SEFluidCircuitPath::GetFlowSourceBaseline()
{
  return GetFluxSourceBaseline();
}
double SEFluidCircuitPath::GetFlowSourceBaseline(const VolumePerTimeUnit& unit) const
{
  if (m_FluxSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_FluxSourceBaseline->GetValue(unit);
}

////////////////////////////////
// Fluid Potential Types //
////////////////////////////////
bool SEFluidCircuitPath::HasPressureSource() const
{
  return HasPotentialSource();
}
SEScalarPressure& SEFluidCircuitPath::GetPressureSource()
{
  return GetPotentialSource();
}
double SEFluidCircuitPath::GetPressureSource(const PressureUnit& unit) const
{
  if (m_PotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasNextPressureSource() const
{
  return HasNextPotentialSource();
}
SEScalarPressure& SEFluidCircuitPath::GetNextPressureSource()
{
  return GetNextPotentialSource();
}
double SEFluidCircuitPath::GetNextPressureSource(const PressureUnit& unit) const
{
  if (m_NextPotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_NextPotentialSource->GetValue(unit);
}
bool SEFluidCircuitPath::HasPressureSourceBaseline() const
{
  return HasPotentialSourceBaseline();
}
SEScalarPressure& SEFluidCircuitPath::GetPressureSourceBaseline()
{
  return GetPotentialSourceBaseline();
}
double SEFluidCircuitPath::GetPressureSourceBaseline(const PressureUnit& unit) const
{
  if (m_PotentialSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSourceBaseline->GetValue(unit);
}
bool SEFluidCircuitPath::HasValveBreakdownPressure() const
{
  return HasValveBreakdownPotential();
}
SEScalarPressure& SEFluidCircuitPath::GetValveBreakdownPressure()
{
  return GetValveBreakdownPotential();
}
double SEFluidCircuitPath::GetValveBreakdownPressure(const PressureUnit& unit) const
{
  if (m_ValveBreakdownPotential == nullptr)
    return SEScalar::dNaN();
  return m_ValveBreakdownPotential->GetValue(unit);
}
