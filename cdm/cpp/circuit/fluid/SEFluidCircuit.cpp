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