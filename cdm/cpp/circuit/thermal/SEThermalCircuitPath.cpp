/* Distributed under the Apache License, Version 2.0.
See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/thermal/SEThermalCircuitPath.h"
PROTO_PUSH
#include "bind/cdm/Circuit.pb.h"
PROTO_POP

SEThermalCircuitPath::SEThermalCircuitPath(SEThermalCircuitNode& src, SEThermalCircuitNode& tgt, const std::string& name) :
  SECircuitPath<SEScalarPower, SEScalarHeatResistance, SEScalarHeatCapacitance, SEScalarHeatInductance, SEScalarTemperature, SEScalarEnergy>(src, tgt ,name), 
  m_ThermalSourceNode(src), m_ThermalTargetNode(tgt)
{

}

SEThermalCircuitPath::~SEThermalCircuitPath()
{
  Clear();
}

void SEThermalCircuitPath::Clear()
{
  SECircuitPath::Clear();
}

void SEThermalCircuitPath::Load(const cdm::ThermalCircuitPathData& src, SEThermalCircuitPath& dst)
{
  SEThermalCircuitPath::Serialize(src, dst);
}
void SEThermalCircuitPath::Serialize(const cdm::ThermalCircuitPathData& src, SEThermalCircuitPath& dst)
{
  SECircuitPath::Serialize(src.circuitpath(), dst);
  if (src.has_resistance())
    SEScalarHeatResistance::Load(src.resistance(), dst.GetResistance());
  if (src.has_nextresistance())
    SEScalarHeatResistance::Load(src.nextresistance(), dst.GetNextResistance());
  if (src.has_resistancebaseline())
    SEScalarHeatResistance::Load(src.resistancebaseline(), dst.GetResistanceBaseline());
  if (src.has_capacitance())
    SEScalarHeatCapacitance::Load(src.capacitance(), dst.GetCapacitance());
  if (src.has_nextcapacitance())
    SEScalarHeatCapacitance::Load(src.nextcapacitance(), dst.GetNextCapacitance());
  if (src.has_capacitancebaseline())
    SEScalarHeatCapacitance::Load(src.capacitancebaseline(), dst.GetCapacitanceBaseline());
  if (src.has_inductance())
    SEScalarHeatInductance::Load(src.inductance(), dst.GetInductance());
  if (src.has_nextinductance())
    SEScalarHeatInductance::Load(src.nextinductance(), dst.GetNextInductance());
  if (src.has_inductancebaseline())
    SEScalarHeatInductance::Load(src.inductancebaseline(), dst.GetInductanceBaseline());
  if (src.has_heattransferrate())
    SEScalarPower::Load(src.heattransferrate(), dst.GetHeatTransferRate());
  if (src.has_nextheattransferrate())
    SEScalarPower::Load(src.nextheattransferrate(), dst.GetNextHeatTransferRate());
  if (src.has_heatsource())
    SEScalarPower::Load(src.heatsource(), dst.GetHeatSource());
  if (src.has_nextheatsource())
    SEScalarPower::Load(src.nextheatsource(), dst.GetNextHeatSource());
  if (src.has_heatsourcebaseline())
    SEScalarPower::Load(src.heatsourcebaseline(), dst.GetHeatSourceBaseline());
  if (src.has_temperaturesource())
    SEScalarTemperature::Load(src.temperaturesource(), dst.GetTemperatureSource());
  if (src.has_nexttemperaturesource())
    SEScalarTemperature::Load(src.nexttemperaturesource(), dst.GetNextTemperatureSource());
  if (src.has_temperaturesourcebaseline())
    SEScalarTemperature::Load(src.temperaturesourcebaseline(), dst.GetTemperatureSourceBaseline());
  if (src.has_valvebreakdowntemperature())
    SEScalarTemperature::Load(src.valvebreakdowntemperature(), dst.GetValveBreakdownTemperature());

  if (!dst.HasValidElements())
    dst.Warning("Path does not have valid elements");
}

cdm::ThermalCircuitPathData* SEThermalCircuitPath::Unload(const SEThermalCircuitPath& src)
{
  cdm::ThermalCircuitPathData* dst = new cdm::ThermalCircuitPathData();
  SEThermalCircuitPath::Serialize(src, *dst);
  return dst;
}
void SEThermalCircuitPath::Serialize(const SEThermalCircuitPath& src, cdm::ThermalCircuitPathData& dst)
{
  SECircuitPath::Serialize(src, *dst.mutable_circuitpath());
  if (src.HasResistance())
    dst.set_allocated_resistance(SEScalarHeatResistance::Unload(*src.m_Resistance));
  if (src.HasNextResistance())
    dst.set_allocated_nextresistance(SEScalarHeatResistance::Unload(*src.m_NextResistance));
  if (src.HasResistanceBaseline())
    dst.set_allocated_resistancebaseline(SEScalarHeatResistance::Unload(*src.m_ResistanceBaseline));
  if (src.HasCapacitance())
    dst.set_allocated_capacitance(SEScalarHeatCapacitance::Unload(*src.m_Capacitance));
  if (src.HasNextCapacitance())
    dst.set_allocated_nextcapacitance(SEScalarHeatCapacitance::Unload(*src.m_NextCapacitance));
  if (src.HasCapacitanceBaseline())
    dst.set_allocated_capacitancebaseline(SEScalarHeatCapacitance::Unload(*src.m_CapacitanceBaseline));
  if (src.HasInductance())
    dst.set_allocated_inductance(SEScalarHeatInductance::Unload(*src.m_Inductance));
  if (src.HasNextInductance())
    dst.set_allocated_nextinductance(SEScalarHeatInductance::Unload(*src.m_NextInductance));
  if (src.HasInductanceBaseline())
    dst.set_allocated_inductancebaseline(SEScalarHeatInductance::Unload(*src.m_InductanceBaseline));
  if (src.HasHeatTransferRate())
    dst.set_allocated_heattransferrate(SEScalarPower::Unload(*src.m_Flux));
  if (src.HasNextHeatTransferRate())
    dst.set_allocated_nextheattransferrate(SEScalarPower::Unload(*src.m_NextFlux));
  if (src.HasHeatSource())
    dst.set_allocated_heatsource(SEScalarPower::Unload(*src.m_FluxSource));
  if (src.HasNextHeatSource())
    dst.set_allocated_nextheatsource(SEScalarPower::Unload(*src.m_NextFluxSource));
  if (src.HasHeatSourceBaseline())
    dst.set_allocated_heatsourcebaseline(SEScalarPower::Unload(*src.m_FluxSourceBaseline));
  if (src.HasTemperatureSource())
    dst.set_allocated_temperaturesource(SEScalarTemperature::Unload(*src.m_PotentialSource));
  if (src.HasNextTemperatureSource())
    dst.set_allocated_nexttemperaturesource(SEScalarTemperature::Unload(*src.m_NextPotentialSource));
  if (src.HasTemperatureSourceBaseline())
    dst.set_allocated_temperaturesourcebaseline(SEScalarTemperature::Unload(*src.m_PotentialSourceBaseline));
  if (src.HasValveBreakdownTemperature())
    dst.set_allocated_valvebreakdowntemperature(SEScalarTemperature::Unload(*src.m_ValveBreakdownPotential));
}

////////////////////////////////
// Thermal Resistance Types//
////////////////////////////////

bool SEThermalCircuitPath::HasResistance() const
{
  return SECircuitPath::HasResistance();
}
SEScalarHeatResistance& SEThermalCircuitPath::GetResistance()
{
  return SECircuitPath::GetResistance();
}
double SEThermalCircuitPath::GetResistance(const HeatResistanceUnit& unit) const
{
  if (m_Resistance == nullptr)
    return SEScalar::dNaN();
  return m_Resistance->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextResistance() const
{
  return SECircuitPath::HasNextResistance();
}
SEScalarHeatResistance& SEThermalCircuitPath::GetNextResistance()
{
  return SECircuitPath::GetNextResistance();
}
double SEThermalCircuitPath::GetNextResistance(const HeatResistanceUnit& unit) const
{
  if (m_NextResistance == nullptr)
    return SEScalar::dNaN();
  return m_NextResistance->GetValue(unit);
}
bool SEThermalCircuitPath::HasResistanceBaseline() const
{
  return SECircuitPath::HasResistanceBaseline();
}
SEScalarHeatResistance& SEThermalCircuitPath::GetResistanceBaseline()
{
  return SECircuitPath::GetResistanceBaseline();
}
double SEThermalCircuitPath::GetResistanceBaseline(const HeatResistanceUnit& unit) const
{
  if (m_ResistanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_ResistanceBaseline->GetValue(unit);
}

//////////////////////////////////
// Thermal Capacitance Types //
//////////////////////////////////

bool SEThermalCircuitPath::HasCapacitance() const
{
  return SECircuitPath::HasCapacitance();
}
SEScalarHeatCapacitance& SEThermalCircuitPath::GetCapacitance()
{
  return SECircuitPath::GetCapacitance();
}
double SEThermalCircuitPath::GetCapacitance(const HeatCapacitanceUnit& unit) const
{
  if (m_Capacitance == nullptr)
    return SEScalar::dNaN();
  return m_Capacitance->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextCapacitance() const
{
  return SECircuitPath::HasNextCapacitance();
}
SEScalarHeatCapacitance& SEThermalCircuitPath::GetNextCapacitance()
{
  return SECircuitPath::GetNextCapacitance();
}
double SEThermalCircuitPath::GetNextCapacitance(const HeatCapacitanceUnit& unit) const
{
  if (m_NextCapacitance == nullptr)
    return SEScalar::dNaN();
  return m_NextCapacitance->GetValue(unit);
}
bool SEThermalCircuitPath::HasCapacitanceBaseline() const
{
  return SECircuitPath::HasCapacitanceBaseline();
}
SEScalarHeatCapacitance& SEThermalCircuitPath::GetCapacitanceBaseline()
{
  return SECircuitPath::GetCapacitanceBaseline();
}
double SEThermalCircuitPath::GetCapacitanceBaseline(const HeatCapacitanceUnit& unit) const
{
  if (m_CapacitanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_CapacitanceBaseline->GetValue(unit);
}

/////////////////////////////////
// Thermal Inductance Types //
/////////////////////////////////

bool SEThermalCircuitPath::HasInductance() const
{
  return SECircuitPath::HasInductance();
}
SEScalarHeatInductance& SEThermalCircuitPath::GetInductance()
{
  return SECircuitPath::GetInductance();
}
double SEThermalCircuitPath::GetInductance(const HeatInductanceUnit& unit) const
{
  if (m_Inductance == nullptr)
    return SEScalar::dNaN();
  return m_Inductance->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextInductance() const
{
  return SECircuitPath::HasNextInductance();
}
SEScalarHeatInductance& SEThermalCircuitPath::GetNextInductance()
{
  return SECircuitPath::GetNextInductance();
}
double SEThermalCircuitPath::GetNextInductance(const HeatInductanceUnit& unit) const
{
  if (m_NextInductance == nullptr)
    return SEScalar::dNaN();
  return m_NextInductance->GetValue(unit);
}
bool SEThermalCircuitPath::HasInductanceBaseline() const
{
  return SECircuitPath::HasInductanceBaseline();
}
SEScalarHeatInductance& SEThermalCircuitPath::GetInductanceBaseline()
{
  return SECircuitPath::GetInductanceBaseline();
}
double SEThermalCircuitPath::GetInductanceBaseline(const HeatInductanceUnit& unit) const
{
  if (m_InductanceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_InductanceBaseline->GetValue(unit);
}


///////////////////////////
// Thermal Flux Types //
///////////////////////////
bool SEThermalCircuitPath::HasHeatTransferRate() const
{
  return HasFlux();
}
SEScalarPower& SEThermalCircuitPath::GetHeatTransferRate()
{
  return GetFlux();
}
double SEThermalCircuitPath::GetHeatTransferRate(const PowerUnit& unit) const
{
  if (m_Flux == nullptr)
    return SEScalar::dNaN();
  return m_Flux->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextHeatTransferRate() const
{
  return HasNextFlux();
}
SEScalarPower& SEThermalCircuitPath::GetNextHeatTransferRate()
{
  return GetNextFlux();
}
double SEThermalCircuitPath::GetNextHeatTransferRate(const PowerUnit& unit) const
{
  if (m_NextFlux == nullptr)
    return SEScalar::dNaN();
  return m_NextFlux->GetValue(unit);
}
bool SEThermalCircuitPath::HasHeatSource() const
{
  return HasFluxSource();
}
SEScalarPower& SEThermalCircuitPath::GetHeatSource()
{
  return GetFluxSource();
}
double SEThermalCircuitPath::GetHeatSource(const PowerUnit& unit) const
{
  if (m_FluxSource == nullptr)
    return SEScalar::dNaN();
  return m_FluxSource->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextHeatSource() const
{
  return HasNextFluxSource();
}
SEScalarPower& SEThermalCircuitPath::GetNextHeatSource()
{
  return GetNextFluxSource();
}
double SEThermalCircuitPath::GetNextHeatSource(const PowerUnit& unit) const
{
  if (m_NextFluxSource == nullptr)
    return SEScalar::dNaN();
  return m_NextFluxSource->GetValue(unit);
}
bool SEThermalCircuitPath::HasHeatSourceBaseline() const
{
  return HasFluxSourceBaseline();
}
SEScalarPower& SEThermalCircuitPath::GetHeatSourceBaseline()
{
  return GetFluxSourceBaseline();
}
double SEThermalCircuitPath::GetHeatSourceBaseline(const PowerUnit& unit) const
{
  if (m_FluxSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_FluxSourceBaseline->GetValue(unit);
}

////////////////////////////////
// Thermal Potential Types //
////////////////////////////////
bool SEThermalCircuitPath::HasTemperatureSource() const
{
  return HasPotentialSource();
}
SEScalarTemperature& SEThermalCircuitPath::GetTemperatureSource()
{
  return GetPotentialSource();
}
double SEThermalCircuitPath::GetTemperatureSource(const TemperatureUnit& unit) const
{
  if (m_PotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSource->GetValue(unit);
}
bool SEThermalCircuitPath::HasNextTemperatureSource() const
{
  return HasNextPotentialSource();
}
SEScalarTemperature& SEThermalCircuitPath::GetNextTemperatureSource()
{
  return GetNextPotentialSource();
}
double SEThermalCircuitPath::GetNextTemperatureSource(const TemperatureUnit& unit) const
{
  if (m_NextPotentialSource == nullptr)
    return SEScalar::dNaN();
  return m_NextPotentialSource->GetValue(unit);
}
bool SEThermalCircuitPath::HasTemperatureSourceBaseline() const
{
  return HasPotentialSourceBaseline();
}
SEScalarTemperature& SEThermalCircuitPath::GetTemperatureSourceBaseline()
{
  return GetPotentialSourceBaseline();
}
double SEThermalCircuitPath::GetTemperatureSourceBaseline(const TemperatureUnit& unit) const
{
  if (m_PotentialSourceBaseline == nullptr)
    return SEScalar::dNaN();
  return m_PotentialSourceBaseline->GetValue(unit);
}
bool SEThermalCircuitPath::HasValveBreakdownTemperature() const
{
  return HasValveBreakdownPotential();
}
SEScalarTemperature& SEThermalCircuitPath::GetValveBreakdownTemperature()
{
  return GetValveBreakdownPotential();
}
double SEThermalCircuitPath::GetValveBreakdownTemperature(const TemperatureUnit& unit) const
{
  if (m_ValveBreakdownPotential == nullptr)
    return SEScalar::dNaN();
  return m_ValveBreakdownPotential->GetValue(unit);
}
