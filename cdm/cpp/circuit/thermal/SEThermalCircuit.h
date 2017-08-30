/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuit.h"
#include "circuit/thermal/SEThermalCircuitNode.h"
#include "circuit/thermal/SEThermalCircuitPath.h"
CDM_BIND_DECL(ThermalCircuitData)
class SECircuitManager;

class CDM_DECL SEThermalCircuit : public SECircuit<cdm::ThermalCircuitData,SEThermalCircuitNode, cdm::ThermalCircuitNodeData,SEThermalCircuitPath, cdm::ThermalCircuitPathData>
{
  friend class SECircuitManager;
protected:
  SEThermalCircuit(const std::string& name, SECircuitManager& mgr);
public:
  virtual ~SEThermalCircuit();

  SEThermalCircuitNode& CreateNode(const std::string& name);
  SEThermalCircuitPath& CreatePath(SEThermalCircuitNode& src, SEThermalCircuitNode& tgt, const std::string& name);

  void AddCircuit(SEThermalCircuit& circuit);

protected:
  SECircuitManager& m_Mgr;
};