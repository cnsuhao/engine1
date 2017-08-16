/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/electrical/SEElectricalCircuit.h"
#include "circuit/SECircuitManager.h"

SEElectricalCircuit::SEElectricalCircuit(const std::string& name, SECircuitManager& mgr) : SECircuit<cdm::ElectricalCircuitData, SEElectricalCircuitNode, cdm::ElectricalCircuitNodeData, SEElectricalCircuitPath, cdm::ElectricalCircuitPathData>(name, mgr.GetLogger()), m_Mgr(mgr)
{

}
SEElectricalCircuit::~SEElectricalCircuit()
{

}

SEElectricalCircuitNode& SEElectricalCircuit::CreateNode(const std::string& name)
{
  SEElectricalCircuitNode* node = m_Mgr.GetElectricalNode(name);
  if (node == nullptr)
    node = &m_Mgr.CreateElectricalNode(name);
  AddNode(*node);
  return *node;
}
SEElectricalCircuitPath& SEElectricalCircuit::CreatePath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name)
{
  SEElectricalCircuitPath* path = m_Mgr.GetElectricalPath(name);
  if (path == nullptr)
    path = &m_Mgr.CreateElectricalPath(src, tgt, name);
  AddPath(*path);
  return *path;
}

void SEElectricalCircuit::AddCircuit(SEElectricalCircuit& circuit)
{
  for (SEElectricalCircuitNode* node : circuit.GetNodes())
    AddNode(*node);
  for (SEElectricalCircuitPath* path : circuit.GetPaths())
    AddPath(*path);
  for (SEElectricalCircuitNode* node : circuit.GetReferenceNodes())
    AddReferenceNode(*node);
}

