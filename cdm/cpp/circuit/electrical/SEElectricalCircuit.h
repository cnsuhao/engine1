/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuit.h"
#include "circuit/electrical/SEElectricalCircuitNode.h"
#include "circuit/electrical/SEElectricalCircuitPath.h"
class SECircuitManager;

class CDM_DECL SEElectricalCircuit : public SECircuit<cdm::ElectricalCircuitData, SEElectricalCircuitNode, cdm::ElectricalCircuitNodeData, SEElectricalCircuitPath, cdm::ElectricalCircuitPathData>
{
  friend class SECircuitManager;
protected:
  SEElectricalCircuit(const std::string& name, SECircuitManager& mgr);
public:
  virtual ~SEElectricalCircuit();

  SEElectricalCircuitNode& CreateNode(const std::string& name);
  SEElectricalCircuitPath& CreatePath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name);

  void AddCircuit(SEElectricalCircuit& circuit);

protected:
  SECircuitManager& m_Mgr;
};