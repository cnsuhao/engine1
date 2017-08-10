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
#include "circuit/SECircuitManager.h"
#include "circuit/electrical/SEElectricalCircuit.h"
#include "circuit/fluid/SEFluidCircuit.h"
#include "circuit/thermal/SEThermalCircuit.h"
#include <google/protobuf/text_format.h>

SECircuitManager::SECircuitManager(Logger* logger) : Loggable(logger)
{

}
SECircuitManager::~SECircuitManager()
{
  Clear();
}

void SECircuitManager::Clear()
{
  m_ElectricalLedger.Clear();
  m_FluidLedger.Clear();
  m_ThermalLedger.Clear();
}

bool SECircuitManager::LoadFile(const std::string& filename)
{
  cdm::CircuitManagerData src;
  std::ifstream file_stream(filename, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  SECircuitManager::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(filename, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

void SECircuitManager::SaveFile(const std::string& filename)
{
  std::string content;
  cdm::CircuitManagerData* src = SECircuitManager::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  delete src;
}

void SECircuitManager::Load(const cdm::CircuitManagerData& src, SECircuitManager& dst)
{
  SECircuitManager::Serialize(src, dst);
  dst.StateChange();
}
void SECircuitManager::Serialize(const cdm::CircuitManagerData& src, SECircuitManager& dst)
{
  dst.Clear();
  // Electrical
  for (int i=0; i<src.electricalnode_size(); i++)
  {
    const cdm::ElectricalCircuitNodeData& n = src.electricalnode(i);
    SEElectricalCircuitNode::Load(n,dst.CreateNode<ELECTRICAL_LEDGER_TYPES>(n.circuitnode().name(), dst.m_ElectricalLedger));
  }
  for (int i = 0; i<src.electricalpath_size(); i++)
  {
    const cdm::ElectricalCircuitPathData& p = src.electricalpath(i);
    SEElectricalCircuitNode* src = dst.GetNode(p.circuitpath().sourcenode(),dst.m_ElectricalLedger);
    if (src == nullptr)
    {
      dst.Error("Could not find source node " + p.circuitpath().sourcenode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEElectricalCircuitNode* tgt = dst.GetNode(p.circuitpath().targetnode(), dst.m_ElectricalLedger);
    if (tgt == nullptr)
    {
      dst.Error("Could not find target node " + p.circuitpath().targetnode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEElectricalCircuitPath::Load(p,dst.CreatePath<ELECTRICAL_LEDGER_TYPES>(*src, *tgt, p.circuitpath().name(), dst.m_ElectricalLedger));
  }
  for (int i = 0; i<src.electricalcircuit_size(); i++)
  {
    const cdm::ElectricalCircuitData& c = src.electricalcircuit(i);
    SEElectricalCircuit::Load(c,dst.CreateCircuit<ELECTRICAL_LEDGER_TYPES>(c.circuit().name(), dst.m_ElectricalLedger), dst.m_ElectricalLedger.nodes, dst.m_ElectricalLedger.paths);
  }

  // Fluid
  for (int i = 0; i<src.fluidnode_size(); i++)
  {
    const cdm::FluidCircuitNodeData& n = src.fluidnode(i);
    SEFluidCircuitNode::Load(n, dst.CreateNode<FLUID_LEDGER_TYPES>(n.circuitnode().name(), dst.m_FluidLedger));
  }
  for (int i = 0; i<src.fluidpath_size(); i++)
  {
    const cdm::FluidCircuitPathData& p = src.fluidpath(i);
    SEFluidCircuitNode* src = dst.GetNode(p.circuitpath().sourcenode(), dst.m_FluidLedger);
    if (src == nullptr)
    {
      dst.Error("Could not find source node " + p.circuitpath().sourcenode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEFluidCircuitNode* tgt = dst.GetNode(p.circuitpath().targetnode(), dst.m_FluidLedger);
    if (tgt == nullptr)
    {
      dst.Error("Could not find target node " + p.circuitpath().targetnode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEFluidCircuitPath::Load(p, dst.CreatePath<FLUID_LEDGER_TYPES>(*src, *tgt, p.circuitpath().name(), dst.m_FluidLedger));
  }
  for (int i = 0; i<src.fluidcircuit_size(); i++)
  {
    const cdm::FluidCircuitData& c = src.fluidcircuit(i);
    SEFluidCircuit::Load(c, dst.CreateCircuit<FLUID_LEDGER_TYPES>(c.circuit().name(), dst.m_FluidLedger), dst.m_FluidLedger.nodes, dst.m_FluidLedger.paths);
  }

  // Thermal
  for (int i = 0; i<src.thermalnode_size(); i++)
  {
    const cdm::ThermalCircuitNodeData& n = src.thermalnode(i);
    SEThermalCircuitNode::Load(n, dst.CreateNode<THERMAL_LEDGER_TYPES>(n.circuitnode().name(), dst.m_ThermalLedger));
  }
  for (int i = 0; i<src.thermalpath_size(); i++)
  {
    const cdm::ThermalCircuitPathData& p = src.thermalpath(i);
    SEThermalCircuitNode* src = dst.GetNode(p.circuitpath().sourcenode(), dst.m_ThermalLedger);
    if (src == nullptr)
    {
      dst.Error("Could not find source node " + p.circuitpath().sourcenode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEThermalCircuitNode* tgt = dst.GetNode(p.circuitpath().targetnode(), dst.m_ThermalLedger);
    if (tgt == nullptr)
    {
      dst.Error("Could not find target node " + p.circuitpath().targetnode() + " from path " + p.circuitpath().name().c_str());
      continue;
    }
    SEThermalCircuitPath::Load(p, dst.CreatePath<THERMAL_LEDGER_TYPES>(*src, *tgt, p.circuitpath().name(), dst.m_ThermalLedger));
  }
  for (int i = 0; i<src.thermalcircuit_size(); i++)
  {
    const cdm::ThermalCircuitData& c = src.thermalcircuit(i);
    SEThermalCircuit::Load(c, dst.CreateCircuit<THERMAL_LEDGER_TYPES>(c.circuit().name(), dst.m_ThermalLedger), dst.m_ThermalLedger.nodes, dst.m_ThermalLedger.paths);
  }
}

cdm::CircuitManagerData* SECircuitManager::Unload(const SECircuitManager& src)
{
  cdm::CircuitManagerData* dst = new cdm::CircuitManagerData();
  SECircuitManager::Serialize(src,*dst);
  return dst;
}
void SECircuitManager::Serialize(const SECircuitManager& src, cdm::CircuitManagerData& dst)
{
  for (auto itr : src.m_ElectricalLedger.nodes)
    dst.mutable_electricalnode()->AddAllocated(SEElectricalCircuitNode::Unload(*itr.second));
  for (auto itr : src.m_ElectricalLedger.paths)
    dst.mutable_electricalpath()->AddAllocated(SEElectricalCircuitPath::Unload(*itr.second));
  for (auto itr : src.m_ElectricalLedger.circuits)
    dst.mutable_electricalcircuit()->AddAllocated(SEElectricalCircuit::Unload(*itr.second));

  for (auto itr : src.m_FluidLedger.nodes)
    dst.mutable_fluidnode()->AddAllocated(SEFluidCircuitNode::Unload(*itr.second));
  for (auto itr : src.m_FluidLedger.paths)
    dst.mutable_fluidpath()->AddAllocated(SEFluidCircuitPath::Unload(*itr.second));
  for (auto itr : src.m_FluidLedger.circuits)
    dst.mutable_fluidcircuit()->AddAllocated(SEFluidCircuit::Unload(*itr.second));

  for (auto itr : src.m_ThermalLedger.nodes)
    dst.mutable_thermalnode()->AddAllocated(SEThermalCircuitNode::Unload(*itr.second));
  for (auto itr : src.m_ThermalLedger.paths)
    dst.mutable_thermalpath()->AddAllocated(SEThermalCircuitPath::Unload(*itr.second));
  for (auto itr : src.m_ThermalLedger.circuits)
    dst.mutable_thermalcircuit()->AddAllocated(SEThermalCircuit::Unload(*itr.second));
}

void SECircuitManager::SetReadOnly(bool b)
{
  SetReadOnlyElectrical(b);
  SetReadOnlyFluid(b);
  SetReadOnlyThermal(b); 
}

void SECircuitManager::SetReadOnlyElectrical(bool b)
{
  for (auto nItr : m_ElectricalLedger.nodes)
  {
    if(nItr.second->HasQuantityBaseline())
      nItr.second->GetQuantityBaseline().SetReadOnly(b);
    if(nItr.second->HasQuantity())
      nItr.second->GetQuantity().SetReadOnly(b);
    
    if(nItr.second->HasPotential())
      nItr.second->GetPotential().SetReadOnly(b);
    if(nItr.second->HasNextPotential())
      nItr.second->GetNextPotential().SetReadOnly(b);
  }
  for (auto pItr : m_ElectricalLedger.paths)
  {
    if (pItr.second->HasCapacitanceBaseline())
    {
      if (pItr.second->GetSourceNode().HasNextQuantity())
        pItr.second->GetSourceNode().GetNextQuantity().SetReadOnly(b);
      if (pItr.second->GetTargetNode().HasNextQuantity())
        pItr.second->GetTargetNode().GetNextQuantity().SetReadOnly(b);
    }
    if (pItr.second->HasFlux())
      pItr.second->GetFlux().SetReadOnly(b);
    if (pItr.second->HasNextFlux())
      pItr.second->GetNextFlux().SetReadOnly(b);
    // Lock all the current values
    if (pItr.second->HasFluxSource())
      pItr.second->GetFluxSource().SetReadOnly(b);
    if (pItr.second->HasResistance())
      pItr.second->GetResistance().SetReadOnly(b);
    if (pItr.second->HasCapacitance())
      pItr.second->GetCapacitance().SetReadOnly(b);
    if (pItr.second->HasInductance())
      pItr.second->GetInductance().SetReadOnly(b);
    if (pItr.second->HasPotentialSource())
      pItr.second->GetPotentialSource().SetReadOnly(b);
  }
}

void SECircuitManager::SetReadOnlyFluid(bool b)
{
  for (auto nItr : m_FluidLedger.nodes)
  {
    if (nItr.second->HasQuantityBaseline())
      nItr.second->GetQuantityBaseline().SetReadOnly(b);
    if (nItr.second->HasQuantity())
      nItr.second->GetQuantity().SetReadOnly(b);

    if (nItr.second->HasPotential())
      nItr.second->GetPotential().SetReadOnly(b);
    if (nItr.second->HasNextPotential())
      nItr.second->GetNextPotential().SetReadOnly(b);
  }
  for (auto pItr : m_FluidLedger.paths)
  {
    if (pItr.second->HasCapacitanceBaseline())
    {
      if (pItr.second->GetSourceNode().HasNextQuantity())
        pItr.second->GetSourceNode().GetNextQuantity().SetReadOnly(b);
      if (pItr.second->GetTargetNode().HasNextQuantity())
        pItr.second->GetTargetNode().GetNextQuantity().SetReadOnly(b);
    }
    if (pItr.second->HasFlux())
      pItr.second->GetFlux().SetReadOnly(b);
    if (pItr.second->HasNextFlux())
      pItr.second->GetNextFlux().SetReadOnly(b);
    // Lock all the current values
    if (pItr.second->HasFluxSource())
      pItr.second->GetFluxSource().SetReadOnly(b);
    if (pItr.second->HasResistance())
      pItr.second->GetResistance().SetReadOnly(b);
    if (pItr.second->HasCapacitance())
      pItr.second->GetCapacitance().SetReadOnly(b);
    if (pItr.second->HasInductance())
      pItr.second->GetInductance().SetReadOnly(b);
    if (pItr.second->HasPotentialSource())
      pItr.second->GetPotentialSource().SetReadOnly(b);
  }
}

void SECircuitManager::SetReadOnlyThermal(bool b)
{
  for (auto nItr : m_ThermalLedger.nodes)
  {
    if (nItr.second->HasQuantityBaseline())
      nItr.second->GetQuantityBaseline().SetReadOnly(b);
    if (nItr.second->HasQuantity())
      nItr.second->GetQuantity().SetReadOnly(b);

    if (nItr.second->HasPotential())
      nItr.second->GetPotential().SetReadOnly(b);
    if (nItr.second->HasNextPotential())
      nItr.second->GetNextPotential().SetReadOnly(b);
  }
  for (auto pItr : m_ThermalLedger.paths)
  {
    if (pItr.second->HasCapacitanceBaseline())
    {
      if (pItr.second->GetSourceNode().HasNextQuantity())
        pItr.second->GetSourceNode().GetNextQuantity().SetReadOnly(b);
      if (pItr.second->GetTargetNode().HasNextQuantity())
        pItr.second->GetTargetNode().GetNextQuantity().SetReadOnly(b);
    }
    if (pItr.second->HasFlux())
      pItr.second->GetFlux().SetReadOnly(b);
    if (pItr.second->HasNextFlux())
      pItr.second->GetNextFlux().SetReadOnly(b);
    // Lock all the current values
    if (pItr.second->HasFluxSource())
      pItr.second->GetFluxSource().SetReadOnly(b);
    if (pItr.second->HasResistance())
      pItr.second->GetResistance().SetReadOnly(b);
    if (pItr.second->HasCapacitance())
      pItr.second->GetCapacitance().SetReadOnly(b);
    if (pItr.second->HasInductance())
      pItr.second->GetInductance().SetReadOnly(b);
    if (pItr.second->HasPotentialSource())
      pItr.second->GetPotentialSource().SetReadOnly(b);
  }
}
