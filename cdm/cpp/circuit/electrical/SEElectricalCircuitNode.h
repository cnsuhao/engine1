/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitNode.h"
#include "properties/SEScalarElectricCharge.h"
#include "properties/SEScalarElectricPotential.h"

class CDM_DECL SEElectricalCircuitNode : public SECircuitNode<SEScalarElectricPotential, SEScalarElectricCharge>
{
  friend class SECircuitManager;
protected:
  SEElectricalCircuitNode(const std::string& name, Logger* logger);
public:
  virtual ~SEElectricalCircuitNode();

  virtual void Clear(); //clear memory

  static void Load(const cdm::ElectricalCircuitNodeData& src, SEElectricalCircuitNode& dst);
  static cdm::ElectricalCircuitNodeData* Unload(const SEElectricalCircuitNode& src);
protected:
  static void Serialize(const cdm::ElectricalCircuitNodeData& src, SEElectricalCircuitNode& dst);
  static void Serialize(const SEElectricalCircuitNode& src, cdm::ElectricalCircuitNodeData& dst);


public:
  virtual bool HasVoltage() const;
  virtual SEScalarElectricPotential& GetVoltage();
  virtual double GetVoltage(const ElectricPotentialUnit& unit) const;

  virtual bool HasNextVoltage() const;
  virtual SEScalarElectricPotential& GetNextVoltage();
  virtual double GetNextVoltage(const ElectricPotentialUnit& unit) const;


  virtual bool HasCharge() const;
  virtual SEScalarElectricCharge& GetCharge();
  virtual double GetCharge(const ElectricChargeUnit& unit) const;

  virtual bool HasNextCharge() const;
  virtual SEScalarElectricCharge& GetNextCharge();
  virtual double GetNextCharge(const ElectricChargeUnit& unit) const;

  virtual bool HasChargeBaseline() const;
  virtual SEScalarElectricCharge& GetChargeBaseline();
  virtual double GetChargeBaseline(const ElectricChargeUnit& unit) const;
};