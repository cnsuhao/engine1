/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitPath.h"
#include "properties/SEScalarHeatResistance.h"
#include "properties/SEScalarHeatCapacitance.h"
#include "properties/SEScalarHeatInductance.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarTemperature.h"
#include "properties/SEScalarEnergy.h"
#include "circuit/thermal/SEThermalCircuitNode.h"

class CDM_DECL SEThermalCircuitPath : public SECircuitPath<THERMAL_CIRCUIT_PATH>
{
  friend class SECircuitManager;  
protected:
  SEThermalCircuitPath(SEThermalCircuitNode& src, SEThermalCircuitNode& tgt, const std::string& name);
public:  
  virtual ~SEThermalCircuitPath();

  virtual void Clear(); //clear memory

  static void Load(const cdm::ThermalCircuitPathData& src, SEThermalCircuitPath& dst);
  static cdm::ThermalCircuitPathData* Unload(const SEThermalCircuitPath& src);
protected:
  static void Serialize(const cdm::ThermalCircuitPathData& src, SEThermalCircuitPath& dst);
  static void Serialize(const SEThermalCircuitPath& src, cdm::ThermalCircuitPathData& dst);


public:
  virtual SEThermalCircuitNode& GetSourceNode() const { return m_ThermalSourceNode; }
  virtual SEThermalCircuitNode& GetTargetNode() const { return m_ThermalTargetNode; }

  virtual bool HasResistance() const;
  virtual SEScalarHeatResistance& GetResistance();
  virtual double GetResistance(const HeatResistanceUnit& unit) const;
  virtual bool HasNextResistance() const;
  virtual SEScalarHeatResistance& GetNextResistance();
  virtual double GetNextResistance(const HeatResistanceUnit& unit) const;
  virtual bool HasResistanceBaseline() const;
  virtual SEScalarHeatResistance& GetResistanceBaseline();
  virtual double GetResistanceBaseline(const HeatResistanceUnit& unit) const;

  virtual bool HasCapacitance() const;
  virtual SEScalarHeatCapacitance& GetCapacitance();
  virtual double GetCapacitance(const HeatCapacitanceUnit& unit) const;
  virtual bool HasNextCapacitance() const;
  virtual SEScalarHeatCapacitance& GetNextCapacitance();
  virtual double GetNextCapacitance(const HeatCapacitanceUnit& unit) const;
  virtual bool HasCapacitanceBaseline() const;
  virtual SEScalarHeatCapacitance& GetCapacitanceBaseline();
  virtual double GetCapacitanceBaseline(const HeatCapacitanceUnit& unit) const;

  virtual bool HasInductance() const;
  virtual SEScalarHeatInductance& GetInductance();
  virtual double GetInductance(const HeatInductanceUnit& unit) const;
  virtual bool HasNextInductance() const;
  virtual SEScalarHeatInductance& GetNextInductance();
  virtual double GetNextInductance(const HeatInductanceUnit& unit) const;
  virtual bool HasInductanceBaseline() const;
  virtual SEScalarHeatInductance& GetInductanceBaseline();
  virtual double GetInductanceBaseline(const HeatInductanceUnit& unit) const;

  virtual bool HasHeatTransferRate() const;
  virtual SEScalarPower& GetHeatTransferRate();
  virtual double GetHeatTransferRate(const PowerUnit& unit) const;
  virtual bool HasNextHeatTransferRate() const;
  virtual SEScalarPower& GetNextHeatTransferRate();
  virtual double GetNextHeatTransferRate(const PowerUnit& unit) const; 
  virtual bool HasHeatSource() const;
  virtual SEScalarPower& GetHeatSource();
  virtual double GetHeatSource(const PowerUnit& unit) const;
  virtual bool HasNextHeatSource() const;
  virtual SEScalarPower& GetNextHeatSource();
  virtual double GetNextHeatSource(const PowerUnit& unit) const;
  virtual bool HasHeatSourceBaseline() const;
  virtual SEScalarPower& GetHeatSourceBaseline();
  virtual double GetHeatSourceBaseline(const PowerUnit& unit) const;

  virtual bool HasTemperatureSource() const;
  virtual SEScalarTemperature& GetTemperatureSource();
  virtual double GetTemperatureSource(const TemperatureUnit& unit) const;
  virtual bool HasNextTemperatureSource() const;
  virtual SEScalarTemperature& GetNextTemperatureSource();
  virtual double GetNextTemperatureSource(const TemperatureUnit& unit) const;
  virtual bool HasTemperatureSourceBaseline() const;
  virtual SEScalarTemperature& GetTemperatureSourceBaseline();
  virtual double GetTemperatureSourceBaseline(const TemperatureUnit& unit) const;
  virtual bool HasValveBreakdownTemperature() const;
  virtual SEScalarTemperature& GetValveBreakdownTemperature();
  virtual double GetValveBreakdownTemperature(const TemperatureUnit& unit) const;

protected:
  SEThermalCircuitNode& m_ThermalSourceNode;
  SEThermalCircuitNode& m_ThermalTargetNode;
};