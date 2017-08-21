/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/thermal/SEThermalCircuit.h"
#include "circuit/SECircuitManager.h"

SEThermalCircuit::SEThermalCircuit(const std::string& name, SECircuitManager& mgr) : SECircuit<cdm::ThermalCircuitData, SEThermalCircuitNode, cdm::ThermalCircuitNodeData, SEThermalCircuitPath, cdm::ThermalCircuitPathData>(name, mgr.GetLogger()), m_Mgr(mgr)
{

}
SEThermalCircuit::~SEThermalCircuit()
{
  Clear();
}

SEThermalCircuitNode& SEThermalCircuit::CreateNode(const std::string& name)
{
  SEThermalCircuitNode* node = m_Mgr.GetThermalNode(name);
  if (node == nullptr)
    node = &m_Mgr.CreateThermalNode(name);
  AddNode(*node);
  return *node;
}
SEThermalCircuitPath& SEThermalCircuit::CreatePath(SEThermalCircuitNode& src, SEThermalCircuitNode& tgt, const std::string& name)
{
  SEThermalCircuitPath* path = m_Mgr.GetThermalPath(name);
  if (path == nullptr)
    path = &m_Mgr.CreateThermalPath(src, tgt, name);
  AddPath(*path);
  return *path;
}

void SEThermalCircuit::AddCircuit(SEThermalCircuit& circuit)
{
  for (SEThermalCircuitNode* node : circuit.GetNodes())
    AddNode(*node);
  for (SEThermalCircuitPath* path : circuit.GetPaths())
    AddPath(*path); 
  for (SEThermalCircuitNode* node : circuit.GetReferenceNodes())
    AddReferenceNode(*node);
}
