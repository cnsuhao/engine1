/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "circuit/SECircuitNode.h"

template<CIRCUIT_NODE_TEMPLATE>
SECircuitNode<CIRCUIT_NODE_TYPES>::SECircuitNode(const std::string& name, Logger* logger) : Loggable(logger), m_Name(name)
{
  m_Potential      = nullptr;
  m_NextPotential  = nullptr;
  m_Quantity = nullptr;
  m_NextQuantity = nullptr;
  m_QuantityBaseline = nullptr;
}

template<CIRCUIT_NODE_TEMPLATE>
SECircuitNode<CIRCUIT_NODE_TYPES>::~SECircuitNode()
{
  Clear();
}

template<CIRCUIT_NODE_TEMPLATE>
void SECircuitNode<CIRCUIT_NODE_TYPES>::Clear()
{
  SAFE_DELETE(m_Potential);
  SAFE_DELETE(m_NextPotential);
  SAFE_DELETE(m_Quantity);
  SAFE_DELETE(m_NextQuantity);
  SAFE_DELETE(m_QuantityBaseline);
}

template<CIRCUIT_NODE_TEMPLATE>
void SECircuitNode<CIRCUIT_NODE_TYPES>::Serialize(const cdm::CircuitNodeData& src, SECircuitNode<CIRCUIT_NODE_TYPES>& dst)
{
  dst.Clear();
  if (!src.name().empty())
    dst.m_Name = src.name();
}
template<CIRCUIT_NODE_TEMPLATE>
void SECircuitNode<CIRCUIT_NODE_TYPES>::Serialize(const SECircuitNode<CIRCUIT_NODE_TYPES>& src, cdm::CircuitNodeData& dst)
{
  dst.set_name(src.m_Name);
}

template<CIRCUIT_NODE_TEMPLATE>
std::string SECircuitNode<CIRCUIT_NODE_TYPES>::GetName() const
{
  return m_Name;
}

template<CIRCUIT_NODE_TEMPLATE>
bool SECircuitNode<CIRCUIT_NODE_TYPES>::HasPotential() const
{
  return m_Potential == nullptr ? false : m_Potential->IsValid();
}
template<CIRCUIT_NODE_TEMPLATE>
PotentialScalar& SECircuitNode<CIRCUIT_NODE_TYPES>::GetPotential()
{
  if (m_Potential == nullptr)
    m_Potential = new PotentialScalar();
  return *m_Potential;
}

template<CIRCUIT_NODE_TEMPLATE>
bool SECircuitNode<CIRCUIT_NODE_TYPES>::HasNextPotential() const
{
  return m_NextPotential == nullptr ? false : m_NextPotential->IsValid();
}
template<CIRCUIT_NODE_TEMPLATE>
PotentialScalar& SECircuitNode<CIRCUIT_NODE_TYPES>::GetNextPotential()
{
  if (m_NextPotential == nullptr)
    m_NextPotential = new PotentialScalar();
  return *m_NextPotential;
}

template<CIRCUIT_NODE_TEMPLATE>
bool SECircuitNode<CIRCUIT_NODE_TYPES>::HasQuantity() const
{
  return m_Quantity == nullptr ? false : m_Quantity->IsValid();
}
template<CIRCUIT_NODE_TEMPLATE>
QuantityScalar& SECircuitNode<CIRCUIT_NODE_TYPES>::GetQuantity()
{
  if (m_Quantity == nullptr)
    m_Quantity = new QuantityScalar();
  return *m_Quantity;
}

template<CIRCUIT_NODE_TEMPLATE>
bool SECircuitNode<CIRCUIT_NODE_TYPES>::HasNextQuantity() const
{
  return m_NextQuantity == nullptr ? false : m_NextQuantity->IsValid();
}
template<CIRCUIT_NODE_TEMPLATE>
QuantityScalar& SECircuitNode<CIRCUIT_NODE_TYPES>::GetNextQuantity()
{
  if (m_NextQuantity == nullptr)
    m_NextQuantity = new QuantityScalar();
  return *m_NextQuantity;
}

template<CIRCUIT_NODE_TEMPLATE>
bool SECircuitNode<CIRCUIT_NODE_TYPES>::HasQuantityBaseline() const
{
  return m_QuantityBaseline == nullptr ? false : m_QuantityBaseline->IsValid();
}
template<CIRCUIT_NODE_TEMPLATE>
QuantityScalar& SECircuitNode<CIRCUIT_NODE_TYPES>::GetQuantityBaseline()
{
  if (m_QuantityBaseline == nullptr)
    m_QuantityBaseline = new QuantityScalar();
  return *m_QuantityBaseline;
}