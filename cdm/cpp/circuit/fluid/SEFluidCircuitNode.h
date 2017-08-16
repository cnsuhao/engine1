/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitNode.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"

class CDM_DECL SEFluidCircuitNode : public SECircuitNode<FLUID_CIRCUIT_NODE>
{
  friend class SECircuitManager;  
protected:
  SEFluidCircuitNode(const std::string& name, Logger* logger);
public:
  virtual ~SEFluidCircuitNode();

  virtual void Clear(); //clear memory

  static void Load(const cdm::FluidCircuitNodeData& src, SEFluidCircuitNode& dst);
  static cdm::FluidCircuitNodeData* Unload(const SEFluidCircuitNode& src);
protected:
  static void Serialize(const cdm::FluidCircuitNodeData& src, SEFluidCircuitNode& dst);
  static void Serialize(const SEFluidCircuitNode& src, cdm::FluidCircuitNodeData& dst);

public:
  virtual bool HasPressure() const;
  virtual SEScalarPressure& GetPressure();
  virtual double GetPressure(const PressureUnit& unit) const;

  virtual bool HasNextPressure() const;
  virtual SEScalarPressure& GetNextPressure();
  virtual double GetNextPressure(const PressureUnit& unit) const;

  virtual bool HasVolume() const;
  virtual SEScalarVolume& GetVolume();
  virtual double GetVolume(const VolumeUnit& unit) const;

  virtual bool HasNextVolume() const;
  virtual SEScalarVolume& GetNextVolume();
  virtual double GetNextVolume(const VolumeUnit& unit) const;

  virtual bool HasVolumeBaseline() const;
  virtual SEScalarVolume& GetVolumeBaseline();
  virtual double GetVolumeBaseline(const VolumeUnit& unit) const;
};
