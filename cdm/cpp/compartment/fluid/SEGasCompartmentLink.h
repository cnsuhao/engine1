/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/fluid/SEFluidCompartmentLink.h"
#include "compartment/fluid/SEGasCompartment.h"
CDM_BIND_DECL(GasCompartmentLinkData);
class SEGasCompartment;

class CDM_DECL SEGasCompartmentLink : public SEFluidCompartmentLink<SEGasTransportEdge, SEGasTransportVertex, SEGasCompartment>
{
  friend class SECompartmentManager;
protected:
  SEGasCompartmentLink(SEGasCompartment& src, SEGasCompartment & tgt, const std::string& name) : SEFluidCompartmentLink(src,tgt,name) {}
public:
  ~SEGasCompartmentLink() {}

  static void Load(const cdm::GasCompartmentLinkData& src, SEGasCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static cdm::GasCompartmentLinkData* Unload(const SEGasCompartmentLink& src);
protected:
  static void Serialize(const cdm::GasCompartmentLinkData& src, SEGasCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static void Serialize(const SEGasCompartmentLink& src, cdm::GasCompartmentLinkData& dst);
};
