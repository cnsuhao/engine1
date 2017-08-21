/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "circuit/fluid/SEFluidCircuit.h"
#include "circuit/SECircuitManager.h"

SEFluidCircuit::SEFluidCircuit(const std::string& name, SECircuitManager& mgr) : SECircuit<cdm::FluidCircuitData, SEFluidCircuitNode, cdm::FluidCircuitNodeData, SEFluidCircuitPath, cdm::FluidCircuitPathData>(name, mgr.GetLogger()), m_Mgr(mgr)
{

}
SEFluidCircuit::~SEFluidCircuit()
{
  Clear();
}

SEFluidCircuitNode& SEFluidCircuit::CreateNode(const std::string& name)
{
  SEFluidCircuitNode* node = m_Mgr.GetFluidNode(name);
  if (node == nullptr)  
    node = &m_Mgr.CreateFluidNode(name);
  AddNode(*node);
  return *node;
}
SEFluidCircuitPath& SEFluidCircuit::CreatePath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name)
{
  SEFluidCircuitPath* path = m_Mgr.GetFluidPath(name);
  if (path == nullptr)
    path = &m_Mgr.CreateFluidPath(src,tgt,name);
  AddPath(*path);
  return *path;
}

void SEFluidCircuit::AddCircuit(SEFluidCircuit& circuit)
{
  for (SEFluidCircuitNode* node : circuit.GetNodes())
    AddNode(*node);
  for (SEFluidCircuitPath* path : circuit.GetPaths())
    AddPath(*path);
  for (SEFluidCircuitNode* node : circuit.GetReferenceNodes())
    AddReferenceNode(*node);
}