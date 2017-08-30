/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/fluid/SEFluidCompartment.h"
#include "compartment/fluid/SEGasCompartmentLink.h"
#include "compartment/substances/SEGasSubstanceQuantity.h"
#include "substance/SESubstanceTransport.h"
CDM_BIND_DECL(GasCompartmentData);

enum class BalanceGasBy { Volume, VolumeFraction };

class CDM_DECL SEGasCompartment : public SEFluidCompartment<SEGasCompartmentLink, SEGasTransportVertex, SEGasTransportSubstance, SEGasSubstanceQuantity>
{
  friend class SECompartmentManager;
protected:
  SEGasCompartment(const std::string& name, Logger* logger);
public:
  virtual ~SEGasCompartment();

  static void Load(const cdm::GasCompartmentData& src, SEGasCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits = nullptr);
  static cdm::GasCompartmentData* Unload(const SEGasCompartment& src);
protected:
  static void Serialize(const cdm::GasCompartmentData& src, SEGasCompartment& dst, SESubstanceManager& subMgr, SECircuitManager* circuits = nullptr);
  static void Serialize(const SEGasCompartment& src, cdm::GasCompartmentData& dst);

public:
  virtual void StateChange();

  virtual void Balance(BalanceGasBy e);

  virtual void AddChild(SEGasCompartment& child);
  virtual const std::vector<SEGasCompartment*>& GetChildren() { return m_Children; }
  virtual const std::vector<SEGasCompartment*>& GetLeaves() { return m_Leaves; }

protected:
  virtual SEGasSubstanceQuantity& CreateSubstanceQuantity(SESubstance& substance);
 
  std::vector<SEGasCompartment*> m_Children;
  std::vector<SEGasCompartment*> m_Leaves;
};
