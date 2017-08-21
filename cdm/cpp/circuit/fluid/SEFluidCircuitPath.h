/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitPath.h"
#include "properties/SEScalarFlowResistance.h"
#include "properties/SEScalarFlowCompliance.h"
#include "properties/SEScalarFlowInertance.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "circuit/fluid/SEFluidCircuitNode.h"

class CDM_DECL SEFluidCircuitPath : public SECircuitPath<FLUID_CIRCUIT_PATH>
{
  friend class SECircuitManager;  
protected:
  SEFluidCircuitPath(SEFluidCircuitNode& src, SEFluidCircuitNode& tgt, const std::string& name);
public:
  virtual ~SEFluidCircuitPath();

  virtual void Clear(); //clear memory

  static void Load(const cdm::FluidCircuitPathData& src, SEFluidCircuitPath& dst);
  static cdm::FluidCircuitPathData* Unload(const SEFluidCircuitPath& src);
protected:
  static void Serialize(const cdm::FluidCircuitPathData& src, SEFluidCircuitPath& dst);
  static void Serialize(const SEFluidCircuitPath& src, cdm::FluidCircuitPathData& dst);

public:
  virtual SEFluidCircuitNode& GetSourceNode() const { return m_FluidSourceNode; }
  virtual SEFluidCircuitNode& GetTargetNode() const { return m_FluidTargetNode; }

  virtual bool HasResistance() const;
  virtual SEScalarFlowResistance& GetResistance();
  virtual double GetResistance(const FlowResistanceUnit& unit) const;
  virtual bool HasNextResistance() const;
  virtual SEScalarFlowResistance& GetNextResistance();
  virtual double GetNextResistance(const FlowResistanceUnit& unit) const;
  virtual bool HasResistanceBaseline() const;
  virtual SEScalarFlowResistance& GetResistanceBaseline();
  virtual double GetResistanceBaseline(const FlowResistanceUnit& unit) const;

  virtual bool HasCompliance() const;
  virtual SEScalarFlowCompliance& GetCompliance();
  virtual double GetCompliance(const FlowComplianceUnit& unit) const;
  virtual bool HasNextCompliance() const;
  virtual SEScalarFlowCompliance& GetNextCompliance();
  virtual double GetNextCompliance(const FlowComplianceUnit& unit) const;
  virtual bool HasComplianceBaseline() const;
  virtual SEScalarFlowCompliance& GetComplianceBaseline();
  virtual double GetComplianceBaseline(const FlowComplianceUnit& unit) const;

  virtual bool HasInertance() const;
  virtual SEScalarFlowInertance& GetInertance();
  virtual double GetInertance(const FlowInertanceUnit& unit) const;
  virtual bool HasNextInertance() const;
  virtual SEScalarFlowInertance& GetNextInertance();
  virtual double GetNextInertance(const FlowInertanceUnit& unit) const;
  virtual bool HasInertanceBaseline() const;
  virtual SEScalarFlowInertance& GetInertanceBaseline();
  virtual double GetInertanceBaseline(const FlowInertanceUnit& unit) const;

  virtual bool HasFlow() const;
  virtual SEScalarVolumePerTime& GetFlow();
  virtual double GetFlow(const VolumePerTimeUnit& unit) const;
  virtual bool HasNextFlow() const;
  virtual SEScalarVolumePerTime& GetNextFlow();
  virtual double GetNextFlow(const VolumePerTimeUnit& unit) const; 
  virtual bool HasFlowSource() const;
  virtual SEScalarVolumePerTime& GetFlowSource();
  virtual double GetFlowSource(const VolumePerTimeUnit& unit) const;
  virtual bool HasNextFlowSource() const;
  virtual SEScalarVolumePerTime& GetNextFlowSource();
  virtual double GetNextFlowSource(const VolumePerTimeUnit& unit) const;
  virtual bool HasFlowSourceBaseline() const;
  virtual SEScalarVolumePerTime& GetFlowSourceBaseline();
  virtual double GetFlowSourceBaseline(const VolumePerTimeUnit& unit) const;

  virtual bool HasPressureSource() const;
  virtual SEScalarPressure& GetPressureSource();
  virtual double GetPressureSource(const PressureUnit& unit) const;
  virtual bool HasNextPressureSource() const;
  virtual SEScalarPressure& GetNextPressureSource();
  virtual double GetNextPressureSource(const PressureUnit& unit) const;
  virtual bool HasPressureSourceBaseline() const;
  virtual SEScalarPressure& GetPressureSourceBaseline();
  virtual double GetPressureSourceBaseline(const PressureUnit& unit) const;
  virtual bool HasValveBreakdownPressure() const;
  virtual SEScalarPressure& GetValveBreakdownPressure();
  virtual double GetValveBreakdownPressure(const PressureUnit& unit) const;

protected:
  SEFluidCircuitNode& m_FluidSourceNode;
  SEFluidCircuitNode& m_FluidTargetNode;
};