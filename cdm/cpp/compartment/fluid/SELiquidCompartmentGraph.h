/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"
#include "compartment/SECompartmentTransportGraph.h"

class SECompartmentManager;

class CDM_DECL SELiquidCompartmentGraph : public SECompartmentTransportGraph<SELiquidTransportGraph, SELiquidTransportVertex, SELiquidTransportEdge, SELiquidCompartment, SELiquidCompartmentLink>
{
  friend class SECompartmentManager;
protected:
  SELiquidCompartmentGraph(const std::string& name, Logger* logger) : SECompartmentTransportGraph(name, logger) {};
public:  
  virtual ~SELiquidCompartmentGraph() {}

  void AddGraph(SELiquidCompartmentGraph& graph);

  static void Load(const cdm::LiquidCompartmentGraphData& src, SELiquidCompartmentGraph& dst, SECompartmentManager& cmptMgr);
  static cdm::LiquidCompartmentGraphData* Unload(const SELiquidCompartmentGraph& src);
protected:
  static void Serialize(const cdm::LiquidCompartmentGraphData& src, SELiquidCompartmentGraph& dst, SECompartmentManager& cmptMgr);
  static void Serialize(const SELiquidCompartmentGraph& src, cdm::LiquidCompartmentGraphData& dst);

protected:
  void BalanceByIntensive();
};