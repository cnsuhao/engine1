/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "circuit/SECircuitManager.h"
#include "circuit/electrical/SEElectricalCircuit.h"
#include "circuit/fluid/SEFluidCircuit.h"
#include "circuit/thermal/SEThermalCircuit.h"

#include <google/protobuf/text_format.h>

template<CIRCUIT_LEDGER_TEMPLATE>
void SECircuitLedger<CIRCUIT_LEDGER_TYPES>::Clear()
{
  DELETE_MAP_SECOND(nodes);
  DELETE_MAP_SECOND(paths);
  DELETE_MAP_SECOND(circuits);
}

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

template<CIRCUIT_LEDGER_TEMPLATE> NodeType&          SECircuitManager::CreateNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  NodeType* node = ledger.nodes[name];
  if (node != nullptr)
  {
    Error("Node already exists with name " + name + ", not creating a new node, returning the existing node");
    return *node;
  }
  node = new NodeType(name, GetLogger());
  ledger.nodes[name] = node;
  return *node;
}
template<CIRCUIT_LEDGER_TEMPLATE> void               SECircuitManager::DeleteNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  PathType* path;
  NodeType* node = GetNode(name, ledger);
  if (node == nullptr)
    return;
  // Remove this node from any circuits
  for (auto citr : ledger.circuits)
    citr.second->RemoveNode(*node);
  // Search the paths and delete any paths that has this node
  // And remove those paths from any circuits
  for (auto pitr = ledger.paths.begin(); pitr != ledger.paths.end();)
  {
    if (pitr->second->GetSourceNode().GetName() == name)
    {
      path = pitr->second;
      ledger.paths.erase(pitr++);
      for (auto citr : ledger.circuits)
        citr.second->RemovePath(*path);
      SAFE_DELETE(path);
    }
    else
      pitr++;
  }
  ledger.nodes.erase(node->GetName());
  SAFE_DELETE(node);
}
template<CIRCUIT_LEDGER_TEMPLATE> bool               SECircuitManager::HasNode(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  return ledger.nodes.find(name) != ledger.nodes.end();
}
template<CIRCUIT_LEDGER_TEMPLATE> NodeType*          SECircuitManager::GetNode(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  auto itr = ledger.nodes.find(name);
  if (itr != ledger.nodes.end())
    return itr->second;
  return nullptr;
}
template<CIRCUIT_LEDGER_TEMPLATE> const NodeType*    SECircuitManager::GetNode(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  auto itr = ledger.nodes.find(name);
  if (itr != ledger.nodes.end())
    return itr->second;
  return nullptr;
}
template<CIRCUIT_LEDGER_TEMPLATE> PathType&          SECircuitManager::CreatePath(NodeType& src, NodeType& tgt, const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  PathType* path = ledger.paths[name];
  if (path != nullptr)
  {
    Error(" path already exists with name " + name + ", not creating a new path, returning the existing path");
    return *path;
  }
  path = new PathType(src, tgt, name);
  ledger.paths[name] = path;
  return *path;
}
template<CIRCUIT_LEDGER_TEMPLATE> void               SECircuitManager::DeletePath(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  PathType* path = GetPath(name, ledger);
  if (path == nullptr)
    return;
  ledger.paths.erase(name);
  for (auto itr : ledger.circuits)
    itr.second->RemovePath(*path);
  SAFE_DELETE(path);
}
template<CIRCUIT_LEDGER_TEMPLATE> bool               SECircuitManager::HasPath(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  return ledger.paths.find(name) != ledger.paths.end();
}
template<CIRCUIT_LEDGER_TEMPLATE> PathType*          SECircuitManager::GetPath(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  auto itr = ledger.paths.find(name);
  if (itr != ledger.paths.end())
    return itr->second;
  return nullptr;
}
template<CIRCUIT_LEDGER_TEMPLATE> const PathType*    SECircuitManager::GetPath(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  auto itr = ledger.paths.find(name);
  if (itr != ledger.paths.end())
    return itr->second;
  return nullptr;
}
template<CIRCUIT_LEDGER_TEMPLATE> CircuitType&       SECircuitManager::CreateCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  CircuitType* circuit = ledger.circuits[name];
  if (circuit != nullptr)
  {
    Error(" Circuit already exists with name " + name + ", not creating a new circuit, returning the existing circuit");
    return *circuit;
  }
  circuit = new CircuitType(name, *this);
  ledger.circuits[name] = circuit;
  return *circuit;
}
template<CIRCUIT_LEDGER_TEMPLATE> void               SECircuitManager::DeleteCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  CircuitType* circuit = GetCircuit(name, ledger);
  if (circuit == nullptr)
    return;
  ledger.circuits.erase(name);
  SAFE_DELETE(circuit);
}
template<CIRCUIT_LEDGER_TEMPLATE> bool               SECircuitManager::HasCircuit(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  return ledger.circuits.find(name) != ledger.circuits.end();
}
template<CIRCUIT_LEDGER_TEMPLATE> CircuitType*       SECircuitManager::GetCircuit(const std::string& name, SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger)
{
  auto itr = ledger.circuits.find(name);
  if (itr != ledger.circuits.end())
    return itr->second;
  return nullptr;
}
template<CIRCUIT_LEDGER_TEMPLATE> const CircuitType* SECircuitManager::GetCircuit(const std::string& name, const SECircuitLedger<CIRCUIT_LEDGER_TYPES>& ledger) const
{
  auto itr = ledger.circuits.find(name);
  if (itr != ledger.circuits.end())
    return itr->second;
  return nullptr;
}
