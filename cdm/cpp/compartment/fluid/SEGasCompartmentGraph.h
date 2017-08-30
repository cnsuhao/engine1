/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/fluid/SEGasCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"
#include "compartment/SECompartmentTransportGraph.h"
CDM_BIND_DECL(GasCompartmentGraphData);
class SECompartmentManager;

class CDM_DECL SEGasCompartmentGraph : public SECompartmentTransportGraph<SEGasTransportGraph, SEGasTransportVertex, SEGasTransportEdge, SEGasCompartment, SEGasCompartmentLink>
{
  friend class SECompartmentManager;
protected:
  SEGasCompartmentGraph(const std::string& name, Logger* logger) : SECompartmentTransportGraph(name, logger) {};
public:  
  virtual ~SEGasCompartmentGraph() {}

  void AddGraph(SEGasCompartmentGraph& graph);

  static void Load(const cdm::GasCompartmentGraphData& src, SEGasCompartmentGraph& dst, SECompartmentManager& cmptMgr);
  static cdm::GasCompartmentGraphData* Unload(const SEGasCompartmentGraph& src);
protected:
  static void Serialize(const cdm::GasCompartmentGraphData& src, SEGasCompartmentGraph& dst, SECompartmentManager& cmptMgr);
  static void Serialize(const SEGasCompartmentGraph& src, cdm::GasCompartmentGraphData& dst);

protected:
  void BalanceByIntensive();
};
