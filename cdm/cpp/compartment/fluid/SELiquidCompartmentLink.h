/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/fluid/SEFluidCompartmentLink.h"
CDM_BIND_DECL(LiquidCompartmentLinkData);
class SELiquidCompartment;

class CDM_DECL SELiquidCompartmentLink : public SEFluidCompartmentLink<SELiquidTransportEdge, SELiquidTransportVertex, SELiquidCompartment>
{
  friend class SECompartmentManager;
protected:
  SELiquidCompartmentLink(SELiquidCompartment& src, SELiquidCompartment & tgt, const std::string& name) : SEFluidCompartmentLink(src, tgt, name) {}
public:
  ~SELiquidCompartmentLink() {}

  static void Load(const cdm::LiquidCompartmentLinkData& src, SELiquidCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static cdm::LiquidCompartmentLinkData* Unload(const SELiquidCompartmentLink& src);
protected:
  static void Serialize(const cdm::LiquidCompartmentLinkData& src, SELiquidCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static void Serialize(const SELiquidCompartmentLink& src, cdm::LiquidCompartmentLinkData& dst);
};
