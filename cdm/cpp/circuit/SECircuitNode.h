/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "bind/cdm/Circuit.pb.h"

#define CIRCUIT_NODE_TEMPLATE typename PotentialScalar, typename QuantityScalar
#define CIRCUIT_NODE_TYPES PotentialScalar,QuantityScalar
#define ELECTRICAL_CIRCUIT_NODE SEScalarElectricPotential, SEScalarElectricCharge
#define FLUID_CIRCUIT_NODE SEScalarPressure, SEScalarVolume
#define THERMAL_CIRCUIT_NODE SEScalarTemperature, SEScalarEnergy

template<CIRCUIT_NODE_TEMPLATE>
class SECircuitNode : public Loggable
{
  template< typename CircuitBindType, typename NodeType, typename CircuitNodeBindType, typename PathType, typename CircuitPathBindType> friend class SECircuit;
protected:
  SECircuitNode(const std::string& name, Logger* logger);
public:
  virtual ~SECircuitNode();

  virtual void Clear(); //clear memory

protected:
  static void Serialize(const cdm::CircuitNodeData& src, SECircuitNode& dst);
  static void Serialize(const SECircuitNode& src, cdm::CircuitNodeData& dst);

public:
  virtual std::string GetName() const;

  virtual bool HasPotential() const;
  virtual PotentialScalar& GetPotential();
  virtual bool HasNextPotential() const;
  virtual PotentialScalar& GetNextPotential();

  virtual bool HasQuantity() const;
  virtual QuantityScalar& GetQuantity();
  virtual bool HasNextQuantity() const;
  virtual QuantityScalar& GetNextQuantity();
  virtual bool HasQuantityBaseline() const;
  virtual QuantityScalar& GetQuantityBaseline();

protected:
  std::string             m_Name;

  PotentialScalar*       m_Potential;
  PotentialScalar*       m_NextPotential;

  ////////////////////
  // Quantity Types //
  ////////////////////
  QuantityScalar*         m_Quantity;
  QuantityScalar*         m_NextQuantity;
  QuantityScalar*         m_QuantityBaseline;
};
#include "circuit/SECircuitNode.inl"