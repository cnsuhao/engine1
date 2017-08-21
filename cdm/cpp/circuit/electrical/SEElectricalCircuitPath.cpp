/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/electrical/SEElectricalCircuitPath.h"

SEElectricalCircuitPath::SEElectricalCircuitPath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name) :
  SECircuitPath<SEScalarElectricCurrent, SEScalarElectricResistance, SEScalarElectricCapacitance, SEScalarElectricInductance, SEScalarElectricPotential, SEScalarElectricCharge>(src,tgt,name),
  m_ElectricalSourceNode(src), m_ElectricalTargetNode(tgt)
{

}

SEElectricalCircuitPath::~SEElectricalCircuitPath()
{
  
}

void SEElectricalCircuitPath::Clear()
{
  SECircuitPath::Clear();
}

void SEElectricalCircuitPath::Load(const cdm::ElectricalCircuitPathData& src, SEElectricalCircuitPath& dst)
{
  SEElectricalCircuitPath::Serialize(src, dst);
}
void SEElectricalCircuitPath::Serialize(const cdm::ElectricalCircuitPathData& src, SEElectricalCircuitPath& dst)
{
  SECircuitPath::Serialize(src.circuitpath(), dst);
  if (src.has_resistance())
    SEScalarElectricResistance::Load(src.resistance(), dst.GetResistance());
  if (src.has_nextresistance())
    SEScalarElectricResistance::Load(src.nextresistance(), dst.GetNextResistance());
  if (src.has_resistancebaseline())
    SEScalarElectricResistance::Load(src.resistancebaseline(), dst.GetResistanceBaseline());
  if (src.has_capacitance())
    SEScalarElectricCapacitance::Load(src.capacitance(), dst.GetCapacitance());
  if (src.has_nextcapacitance())
    SEScalarElectricCapacitance::Load(src.nextcapacitance(), dst.GetNextCapacitance());
  if (src.has_capacitancebaseline())
    SEScalarElectricCapacitance::Load(src.capacitancebaseline(), dst.GetCapacitanceBaseline());
  if (src.has_inductance())
    SEScalarElectricInductance::Load(src.inductance(), dst.GetInductance());
  if (src.has_nextinductance())
    SEScalarElectricInductance::Load(src.nextinductance(), dst.GetNextInductance());
  if (src.has_inductancebaseline())
    SEScalarElectricInductance::Load(src.inductancebaseline(), dst.GetInductanceBaseline());
  if (src.has_current())
    SEScalarElectricCurrent::Load(src.current(), dst.GetCurrent());
  if (src.has_nextcurrent())
    SEScalarElectricCurrent::Load(src.nextcurrent(), dst.GetNextCurrent());
  if (src.has_currentsource())
    SEScalarElectricCurrent::Load(src.currentsource(), dst.GetCurrentSource());
  if (src.has_nextcurrentsource())
    SEScalarElectricCurrent::Load(src.nextcurrentsource(), dst.GetNextCurrentSource());
  if (src.has_currentsourcebaseline())
    SEScalarElectricCurrent::Load(src.currentsourcebaseline(), dst.GetCurrentSourceBaseline());
  if (src.has_voltagesource())
    SEScalarElectricPotential::Load(src.voltagesource(), dst.GetVoltageSource());
  if (src.has_nextvoltagesource())
    SEScalarElectricPotential::Load(src.nextvoltagesource(), dst.GetNextVoltageSource());
  if (src.has_voltagesourcebaseline())
    SEScalarElectricPotential::Load(src.voltagesourcebaseline(), dst.GetVoltageSourceBaseline());
  if (src.has_valvebreakdownvoltage())
    SEScalarElectricPotential::Load(src.valvebreakdownvoltage(), dst.GetValveBreakdownVoltage());

  if (!dst.HasValidElements())
    dst.Warning("Path does not have valid elements");
}

cdm::ElectricalCircuitPathData* SEElectricalCircuitPath::Unload(const SEElectricalCircuitPath& src)
{
  cdm::ElectricalCircuitPathData* dst = new cdm::ElectricalCircuitPathData();
  SEElectricalCircuitPath::Serialize(src, *dst);
  return dst;
}
void SEElectricalCircuitPath::Serialize(const SEElectricalCircuitPath& src, cdm::ElectricalCircuitPathData& dst)
{
  SECircuitPath::Serialize(src, *dst.mutable_circuitpath());
  if (src.HasResistance())
    dst.set_allocated_resistance(SEScalarElectricResistance::Unload(*src.m_Resistance));
  if (src.HasNextResistance())
    dst.set_allocated_nextresistance(SEScalarElectricResistance::Unload(*src.m_NextResistance));
  if (src.HasResistanceBaseline())
    dst.set_allocated_resistancebaseline(SEScalarElectricResistance::Unload(*src.m_ResistanceBaseline));
  if (src.HasCapacitance())
    dst.set_allocated_capacitance(SEScalarElectricCapacitance::Unload(*src.m_Capacitance));
  if (src.HasNextCapacitance())
    dst.set_allocated_nextcapacitance(SEScalarElectricCapacitance::Unload(*src.m_NextCapacitance));
  if (src.HasCapacitanceBaseline())
    dst.set_allocated_capacitancebaseline(SEScalarElectricCapacitance::Unload(*src.m_CapacitanceBaseline));
  if (src.HasInductance())
    dst.set_allocated_inductance(SEScalarElectricInductance::Unload(*src.m_Inductance));
  if (src.HasNextInductance())
    dst.set_allocated_nextinductance(SEScalarElectricInductance::Unload(*src.m_NextInductance));
  if (src.HasInductanceBaseline())
    dst.set_allocated_inductancebaseline(SEScalarElectricInductance::Unload(*src.m_InductanceBaseline));
  if (src.HasCurrent())
    dst.set_allocated_current(SEScalarElectricCurrent::Unload(*src.m_Flux));
  if (src.HasNextCurrent())
    dst.set_allocated_nextcurrent(SEScalarElectricCurrent::Unload(*src.m_NextFlux));
  if (src.HasCurrentSource())
    dst.set_allocated_currentsource(SEScalarElectricCurrent::Unload(*src.m_FluxSource));
  if (src.HasNextCurrentSource())
    dst.set_allocated_nextcurrentsource(SEScalarElectricCurrent::Unload(*src.m_NextFluxSource));
  if (src.HasCurrentSourceBaseline())
    dst.set_allocated_currentsourcebaseline(SEScalarElectricCurrent::Unload(*src.m_FluxSourceBaseline));
  if (src.HasVoltageSource())
    dst.set_allocated_voltagesource(SEScalarElectricPotential::Unload(*src.m_PotentialSource));
  if (src.HasNextVoltageSource())
    dst.set_allocated_nextvoltagesource(SEScalarElectricPotential::Unload(*src.m_NextPotentialSource));
  if (src.HasVoltageSourceBaseline())
    dst.set_allocated_voltagesourcebaseline(SEScalarElectricPotential::Unload(*src.m_PotentialSourceBaseline));
  if (src.HasValveBreakdownVoltage())
    dst.set_allocated_valvebreakdownvoltage(SEScalarElectricPotential::Unload(*src.m_ValveBreakdownPotential));
}

////////////////////////////////
// Electrical Resistance Types//
////////////////////////////////

bool SEElectricalCircuitPath::HasResistance() const
{
  return SECircuitPath::HasResistance();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetResistance()
{
  return SECircuitPath::GetResistance();
}
double SEElectricalCircuitPath::GetResistance(const ElectricResistanceUnit& unit) const
{
  if (m_Resistance == nullptr)
    return SEScalar::dNaN();
  return m_Resistance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextResistance() const
{
  return SECircuitPath::HasNextResistance();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetNextResistance()
{
  return SECircuitPath::GetNextResistance();
}
double SEElectricalCircuitPath::GetNextResistance(const ElectricResistanceUnit& unit) const
{
  if (m_NextResistance == nullptr)
    return SEScalar::dNaN();
  return m_NextResistance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasResistanceBaseline() const
{
  return SECircuitPath::HasResistanceBaseline();
}
SEScalarElectricResistance& SEElectricalCircuitPath::GetResistanceBaseline()
{
  return SECircuitPath::GetResistanceBaseline();
}
double SEElectricalCircuitPath::GetResistanceBaseline(const ElectricResistanceUnit& unit) const
{
  if (m_ResistanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_ResistanceBaseline->GetValue(unit);
}

//////////////////////////////////
// Electrical Capacitance Types //
//////////////////////////////////

bool SEElectricalCircuitPath::HasCapacitance() const
{
  return SECircuitPath::HasCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetCapacitance()
{
  return SECircuitPath::GetCapacitance();
}
double SEElectricalCircuitPath::GetCapacitance(const ElectricCapacitanceUnit& unit) const
{
  if (m_Capacitance == nullptr)
    return SEScalar::dNaN();
  return m_Capacitance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCapacitance() const
{
  return SECircuitPath::HasNextCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetNextCapacitance()
{
  return SECircuitPath::GetNextCapacitance();
}
double SEElectricalCircuitPath::GetNextCapacitance(const ElectricCapacitanceUnit& unit) const
{
  if (m_NextCapacitance == nullptr)
    return SEScalar::dNaN();
  return m_NextCapacitance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCapacitanceBaseline() const
{
  return SECircuitPath::HasCapacitance();
}
SEScalarElectricCapacitance& SEElectricalCircuitPath::GetCapacitanceBaseline()
{
  return SECircuitPath::GetCapacitance();
}
double SEElectricalCircuitPath::GetCapacitanceBaseline(const ElectricCapacitanceUnit& unit) const
{
  if (m_CapacitanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_CapacitanceBaseline->GetValue(unit);
}

/////////////////////////////////
// Electrical Inductance Types //
/////////////////////////////////

bool SEElectricalCircuitPath::HasInductance() const
{
  return SECircuitPath::HasInductance();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetInductance()
{
  return SECircuitPath::GetInductance();
}
double SEElectricalCircuitPath::GetInductance(const ElectricInductanceUnit& unit) const
{
  if (m_Inductance == nullptr)
    return SEScalar::dNaN();
  return m_Inductance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextInductance() const
{
  return SECircuitPath::HasNextInductance();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetNextInductance()
{
  return SECircuitPath::GetNextInductance();
}
double SEElectricalCircuitPath::GetNextInductance(const ElectricInductanceUnit& unit) const
{
  if (m_NextInductance == nullptr)
    return SEScalar::dNaN();
  return m_NextInductance->GetValue(unit);
}
bool SEElectricalCircuitPath::HasInductanceBaseline() const
{
  return SECircuitPath::HasInductanceBaseline();
}
SEScalarElectricInductance& SEElectricalCircuitPath::GetInductanceBaseline()
{
  return SECircuitPath::GetInductanceBaseline();
}
double SEElectricalCircuitPath::GetInductanceBaseline(const ElectricInductanceUnit& unit) const
{
  if (m_InductanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_InductanceBaseline->GetValue(unit);
}


///////////////////////////
// Electrical Flux Types //
///////////////////////////
bool SEElectricalCircuitPath::HasCurrent() const
{
  return HasFlux();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrent()
{
  return GetFlux();
}
double SEElectricalCircuitPath::GetCurrent(const ElectricCurrentUnit& unit) const
{
  if (m_Flux == nullptr)
    return SEScalar::dNaN();
  return m_Flux->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCurrent() const
{
  return HasNextFlux();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetNextCurrent()
{
  return GetNextFlux();
}
double SEElectricalCircuitPath::GetNextCurrent(const ElectricCurrentUnit& unit) const
{
  if (m_NextFlux == nullptr)
    return SEScalar::dNaN();
  return m_NextFlux->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCurrentSource() const
{
  return HasFluxSource();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrentSource()
{
  return GetFluxSource();
}
double SEElectricalCircuitPath::GetCurrentSource(const ElectricCurrentUnit& unit) const
{
  if (m_FluxSource == nullptr)
    return SEScalar::dNaN();
  return m_FluxSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextCurrentSource() const
{
  return HasNextFluxSource();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetNextCurrentSource()
{
  return GetNextFluxSource();
}
double SEElectricalCircuitPath::GetNextCurrentSource(const ElectricCurrentUnit& unit) const
{
  if (m_NextFluxSource == nullptr)
    return SEScalar::dNaN();
  return m_NextFluxSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasCurrentSourceBaseline() const
{
  return HasFluxSourceBaseline();
}
SEScalarElectricCurrent& SEElectricalCircuitPath::GetCurrentSourceBaseline()
{
  return GetFluxSourceBaseline();
}
double SEElectricalCircuitPath::GetCurrentSourceBaseline(const ElectricCurrentUnit& unit) const
{
  if (m_FluxSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_FluxSourceBaseline->GetValue(unit);
}

////////////////////////////////
// Electrical Potential Types //
////////////////////////////////
bool SEElectricalCircuitPath::HasVoltageSource() const
{
  return HasPotentialSource();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetVoltageSource()
{
  return GetPotentialSource();
}
double SEElectricalCircuitPath::GetVoltageSource(const ElectricPotentialUnit& unit) const
{
  if (m_PotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasNextVoltageSource() const
{
  return HasNextPotentialSource();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetNextVoltageSource()
{
  return GetNextPotentialSource();
}
double SEElectricalCircuitPath::GetNextVoltageSource(const ElectricPotentialUnit& unit) const
{
  if (m_NextPotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_NextPotentialSource->GetValue(unit);
}
bool SEElectricalCircuitPath::HasVoltageSourceBaseline() const
{
  return HasPotentialSourceBaseline();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetVoltageSourceBaseline()
{
  return GetPotentialSourceBaseline();
}
double SEElectricalCircuitPath::GetVoltageSourceBaseline(const ElectricPotentialUnit& unit) const
{
  if (m_PotentialSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSourceBaseline->GetValue(unit);
}
bool SEElectricalCircuitPath::HasValveBreakdownVoltage() const
{
  return HasValveBreakdownPotential();
}
SEScalarElectricPotential& SEElectricalCircuitPath::GetValveBreakdownVoltage()
{
  return GetValveBreakdownPotential();
}
double SEElectricalCircuitPath::GetValveBreakdownVoltage(const ElectricPotentialUnit& unit) const
{
  if (m_ValveBreakdownPotential == nullptr)
    return SEScalar::dNaN();
  return m_ValveBreakdownPotential->GetValue(unit);
}