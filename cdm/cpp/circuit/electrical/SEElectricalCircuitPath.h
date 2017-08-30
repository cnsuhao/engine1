/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitPath.h"
#include "properties/SEScalarElectricResistance.h"
#include "properties/SEScalarElectricCapacitance.h"
#include "properties/SEScalarElectricInductance.h"
#include "properties/SEScalarElectricCurrent.h"
#include "properties/SEScalarElectricPotential.h"
#include "properties/SEScalarElectricCharge.h"
#include "circuit/electrical/SEElectricalCircuitNode.h"
CDM_BIND_DECL(ElectricalCircuitPathData)

class CDM_DECL SEElectricalCircuitPath : public SECircuitPath<SEScalarElectricCurrent, SEScalarElectricResistance, SEScalarElectricCapacitance, SEScalarElectricInductance, SEScalarElectricPotential, SEScalarElectricCharge>
{
  friend class SECircuitManager;  
protected:
  SEElectricalCircuitPath(SEElectricalCircuitNode& src, SEElectricalCircuitNode& tgt, const std::string& name);
public:
  virtual ~SEElectricalCircuitPath();

  virtual void Clear(); //clear memory

  static void Load(const cdm::ElectricalCircuitPathData& src, SEElectricalCircuitPath& dst);
  static cdm::ElectricalCircuitPathData* Unload(const SEElectricalCircuitPath& src);
protected:
  static void Serialize(const cdm::ElectricalCircuitPathData& src, SEElectricalCircuitPath& dst);
  static void Serialize(const SEElectricalCircuitPath& src, cdm::ElectricalCircuitPathData& dst);


public:
  virtual SEElectricalCircuitNode& GetSourceNode() const { return m_ElectricalSourceNode; }
  virtual SEElectricalCircuitNode& GetTargetNode() const { return m_ElectricalTargetNode; }

  virtual bool HasResistance() const;
  virtual SEScalarElectricResistance& GetResistance();
  virtual double GetResistance(const ElectricResistanceUnit& unit) const;
  virtual bool HasNextResistance() const;
  virtual SEScalarElectricResistance& GetNextResistance();
  virtual double GetNextResistance(const ElectricResistanceUnit& unit) const;
  virtual bool HasResistanceBaseline() const;
  virtual SEScalarElectricResistance& GetResistanceBaseline();
  virtual double GetResistanceBaseline(const ElectricResistanceUnit& unit) const;

  virtual bool HasCapacitance() const;
  virtual SEScalarElectricCapacitance& GetCapacitance();
  virtual double GetCapacitance(const ElectricCapacitanceUnit& unit) const;
  virtual bool HasNextCapacitance() const;
  virtual SEScalarElectricCapacitance& GetNextCapacitance();
  virtual double GetNextCapacitance(const ElectricCapacitanceUnit& unit) const;
  virtual bool HasCapacitanceBaseline() const;
  virtual SEScalarElectricCapacitance& GetCapacitanceBaseline();
  virtual double GetCapacitanceBaseline(const ElectricCapacitanceUnit& unit) const;

  virtual bool HasInductance() const;
  virtual SEScalarElectricInductance& GetInductance();
  virtual double GetInductance(const ElectricInductanceUnit& unit) const;
  virtual bool HasNextInductance() const;
  virtual SEScalarElectricInductance& GetNextInductance();
  virtual double GetNextInductance(const ElectricInductanceUnit& unit) const;
  virtual bool HasInductanceBaseline() const;
  virtual SEScalarElectricInductance& GetInductanceBaseline();
  virtual double GetInductanceBaseline(const ElectricInductanceUnit& unit) const;

  virtual bool HasCurrent() const;
  virtual SEScalarElectricCurrent& GetCurrent();
  virtual double GetCurrent(const ElectricCurrentUnit& unit) const;
  virtual bool HasNextCurrent() const;
  virtual SEScalarElectricCurrent& GetNextCurrent();
  virtual double GetNextCurrent(const ElectricCurrentUnit& unit) const;  
  virtual bool HasCurrentSource() const;
  virtual SEScalarElectricCurrent& GetCurrentSource();
  virtual double GetCurrentSource(const ElectricCurrentUnit& unit) const;
  virtual bool HasNextCurrentSource() const;
  virtual SEScalarElectricCurrent& GetNextCurrentSource();
  virtual double GetNextCurrentSource(const ElectricCurrentUnit& unit) const;
  virtual bool HasCurrentSourceBaseline() const;
  virtual SEScalarElectricCurrent& GetCurrentSourceBaseline();
  virtual double GetCurrentSourceBaseline(const ElectricCurrentUnit& unit) const;

  virtual bool HasVoltageSource() const;
  virtual SEScalarElectricPotential& GetVoltageSource();
  virtual double GetVoltageSource(const ElectricPotentialUnit& unit) const;
  virtual bool HasNextVoltageSource() const;
  virtual SEScalarElectricPotential& GetNextVoltageSource();
  virtual double GetNextVoltageSource(const ElectricPotentialUnit& unit) const;
  virtual bool HasVoltageSourceBaseline() const;
  virtual SEScalarElectricPotential& GetVoltageSourceBaseline();
  virtual double GetVoltageSourceBaseline(const ElectricPotentialUnit& unit) const;
  virtual bool HasValveBreakdownVoltage() const;
  virtual SEScalarElectricPotential& GetValveBreakdownVoltage();
  virtual double GetValveBreakdownVoltage(const ElectricPotentialUnit& unit) const;


protected:
  SEElectricalCircuitNode& m_ElectricalSourceNode;
  SEElectricalCircuitNode& m_ElectricalTargetNode;
};