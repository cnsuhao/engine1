/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "circuit/SECircuitNode.h"

#define CIRCUIT_PATH_TEMPLATE typename FluxScalar, typename ResistanceScalar, typename CapacitanceScalar, typename InductanceScalar, typename PotentialScalar, typename QuantityScalar
#define CIRCUIT_PATH_TYPES FluxScalar,ResistanceScalar,CapacitanceScalar,InductanceScalar,PotentialScalar,QuantityScalar
#define ELECTRICAL_CIRCUIT_PATH SEScalarElectricCurrent, SEScalarElectricResistance, SEScalarElectricCapacitance, SEScalarElectricInductance, SEScalarElectricPotential, SEScalarElectricCharge
#define FLUID_CIRCUIT_PATH SEScalarVolumePerTime, SEScalarFlowResistance, SEScalarFlowCompliance, SEScalarFlowInertance, SEScalarPressure, SEScalarVolume
#define THERMAL_CIRCUIT_PATH SEScalarPower, SEScalarHeatResistance, SEScalarHeatCapacitance, SEScalarHeatInductance, SEScalarTemperature, SEScalarEnergy

template<CIRCUIT_PATH_TEMPLATE>
class SECircuitPath : public Loggable
{
  template< typename CircuitBindType, typename NodeType, typename CircuitNodeBindType, typename PathType, typename CircuitPathBindType> friend class SECircuit;
protected:
  SECircuitPath(SECircuitNode<PotentialScalar, QuantityScalar>& src, SECircuitNode<PotentialScalar, QuantityScalar>& tgt, const std::string& name);
public:
  virtual ~SECircuitPath();

  virtual void Clear();

protected:
  static void Serialize(const cdm::CircuitPathData& src, SECircuitPath& dst);
  static void Serialize(const SECircuitPath& src, cdm::CircuitPathData& dst);

public:
  virtual std::string GetName() const;

  virtual SECircuitNode<CIRCUIT_NODE_TYPES>& GetSourceNode() const;
  virtual SECircuitNode<CIRCUIT_NODE_TYPES>& GetTargetNode() const;

  virtual bool HasFlux() const;
  virtual FluxScalar& GetFlux();
  virtual bool HasNextFlux() const;
  virtual FluxScalar& GetNextFlux();
  virtual bool HasFluxSource() const;
  virtual FluxScalar& GetFluxSource();
  virtual bool HasNextFluxSource() const;
  virtual FluxScalar& GetNextFluxSource();
  virtual bool HasFluxSourceBaseline() const;
  virtual FluxScalar& GetFluxSourceBaseline();

  virtual bool HasResistance() const;
  virtual ResistanceScalar& GetResistance();
  virtual bool HasNextResistance() const;
  virtual ResistanceScalar& GetNextResistance();
  virtual bool HasResistanceBaseline() const;
  virtual ResistanceScalar& GetResistanceBaseline();

  virtual bool HasCapacitance() const;
  virtual CapacitanceScalar& GetCapacitance();
  virtual bool HasNextCapacitance() const;
  virtual CapacitanceScalar& GetNextCapacitance();
  virtual bool HasCapacitanceBaseline() const;
  virtual CapacitanceScalar& GetCapacitanceBaseline();

  virtual bool HasInductance() const;
  virtual InductanceScalar& GetInductance();
  virtual bool HasNextInductance() const;
  virtual InductanceScalar& GetNextInductance();
  virtual bool HasInductanceBaseline() const;
  virtual InductanceScalar& GetInductanceBaseline();

  virtual bool HasPotentialSource() const;
  virtual PotentialScalar& GetPotentialSource();
  virtual bool HasNextPotentialSource() const;
  virtual PotentialScalar& GetNextPotentialSource();
  virtual bool HasPotentialSourceBaseline() const;
  virtual PotentialScalar& GetPotentialSourceBaseline();
  virtual bool HasValveBreakdownPotential() const;
  virtual PotentialScalar& GetValveBreakdownPotential();
  
  virtual bool HasValidElements() const;
  virtual unsigned short NumberOfElements() const { return m_NumElements; }
  virtual unsigned short NumberOfNextElements() const { return m_NumNextElements; }

  virtual cdm::eGate GetSwitch() const;
  virtual void SetSwitch(cdm::eGate state);
  virtual void FlipSwitch();
  virtual bool HasSwitch() const;
  virtual void InvalidateSwitch();

  virtual cdm::eGate GetNextSwitch() const;
  virtual void SetNextSwitch(cdm::eGate state);
  virtual void FlipNextSwitch();
  virtual bool HasNextSwitch() const;
  virtual void InvalidateNextSwitch();

  virtual cdm::eGate GetValve() const;
  virtual void SetValve(cdm::eGate state);
  virtual void FlipValve();
  virtual bool HasValve() const;
  virtual void InvalidateValve();

  virtual cdm::eGate GetNextValve() const;
  virtual void SetNextValve(cdm::eGate state);
  virtual void FlipNextValve();
  virtual bool HasNextValve() const;
  virtual void InvalidateNextValve();

  virtual cdm::eGate GetPolarizedState() const;
  virtual void SetPolarizedState(cdm::eGate state);
  virtual void FlipPolarizedState();
  virtual bool HasPolarizedState() const;
  virtual void InvalidatePolarizedState();

  virtual cdm::eGate GetNextPolarizedState() const;
  virtual void SetNextPolarizedState(cdm::eGate state);
  virtual void FlipNextPolarizedState();
  virtual bool HasNextPolarizedState() const;
  virtual void InvalidateNextPolarizedState();

protected:
  std::string                         m_Name;
  SECircuitNode<CIRCUIT_NODE_TYPES>&  m_SourceNode;
  SECircuitNode<CIRCUIT_NODE_TYPES>&  m_TargetNode;
  mutable unsigned short              m_NumElements;
  mutable unsigned short              m_NumNextElements;
  /////////////////////////    
  // Valves and Switches //    
  /////////////////////////    
  cdm::eGate                   m_Switch;
  cdm::eGate                   m_NextSwitch;
  cdm::eGate                   m_Valve;
  cdm::eGate                   m_NextValve;
  cdm::eGate                   m_PolarizedState;
  cdm::eGate                   m_NextPolarizedState;

  ResistanceScalar*            m_Resistance;
  ResistanceScalar*            m_NextResistance;
  ResistanceScalar*            m_ResistanceBaseline;
                 
  CapacitanceScalar*           m_Capacitance;
  CapacitanceScalar*           m_NextCapacitance;
  CapacitanceScalar*           m_CapacitanceBaseline;

  InductanceScalar*            m_Inductance;
  InductanceScalar*            m_NextInductance;
  InductanceScalar*            m_InductanceBaseline;

  FluxScalar*                  m_Flux;
  FluxScalar*                  m_NextFlux;
  FluxScalar*                  m_FluxSource;
  FluxScalar*                  m_NextFluxSource;
  FluxScalar*                  m_FluxSourceBaseline;
                   
  PotentialScalar*             m_PotentialSource;
  PotentialScalar*             m_NextPotentialSource;
  PotentialScalar*             m_PotentialSourceBaseline;
  PotentialScalar*             m_ValveBreakdownPotential;
};
#include "circuit/SECircuitPath.inl"