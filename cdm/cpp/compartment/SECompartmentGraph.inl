/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/SECompartmentGraph.h"


template<COMPARTMENT_GRAPH_TEMPLATE>
SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::SECompartmentGraph(const std::string& name, Logger* logger) : Loggable(logger), m_Name(name)
{
  
}
template<COMPARTMENT_GRAPH_TEMPLATE>
SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::~SECompartmentGraph()
{
  Clear();
}

template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::Clear()
{
  m_Compartments.clear();
  m_CompartmentLinks.clear();
}

template<COMPARTMENT_GRAPH_TEMPLATE>
std::string SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetName() const
{
  return m_Name;
}

template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::AddCompartment(CompartmentType& cmpt)
{
  if (GetCompartment(cmpt.GetName()) == nullptr)  
    m_Compartments.push_back(&cmpt); 
}
template<COMPARTMENT_GRAPH_TEMPLATE>
CompartmentType* SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetCompartment(const std::string& name)
{
  for (CompartmentType* c : m_Compartments)
  {
    if (c->GetName() == name)
      return c;
  }
  return nullptr;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
const CompartmentType* SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetCompartment(const std::string& name) const
{
  for (CompartmentType* c : m_Compartments)
  {
    if (c->GetName() == name)
      return c;
  }
  return nullptr;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
const std::vector<CompartmentType*>& SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetCompartments() const
{
  return m_Compartments;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::RemoveCompartment(const CompartmentType& Compartment)
{
  size_t i = 0;
  for (CompartmentType* n : m_Compartments)
  {
    if (n == &Compartment)
    {
      m_Compartments.erase(m_Compartments.begin() + i);
      return;
    }
    i++;
  }
}
template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::RemoveCompartment(const std::string& name)
{
  size_t i = 0;
  for (CompartmentType* n : m_Compartments)
  {
    if (n->GetName() == name)
    {
      m_Compartments.erase(m_Compartments.begin() + i);
      return;
    }
    i++;
  }
}

template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::AddLink(CompartmentLinkType& link)
{
  if (GetLink(link.GetName()) == nullptr)
    m_CompartmentLinks.push_back(&link);
}
template<COMPARTMENT_GRAPH_TEMPLATE>
CompartmentLinkType* SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetLink(const std::string& name)
{
  for (CompartmentLinkType* p : m_CompartmentLinks)
  {
    if (p->GetName() == name)
      return p;
  }
  return nullptr;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
const CompartmentLinkType* SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetLink(const std::string& name) const
{
  for (CompartmentLinkType* p : m_CompartmentLinks)
  {
    if (p->GetName() == name)
      return p;
  }
  return nullptr;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
const std::vector<CompartmentLinkType*>& SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::GetLinks() const
{
  return m_CompartmentLinks;
}
template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::RemoveLink(const CompartmentLinkType& CompartmentLink)
{
  size_t i = 0;
  for (CompartmentLinkType* p : m_CompartmentLinks)
  {
    if (p == &CompartmentLink)
    {
      m_CompartmentLinks.erase(m_CompartmentLinks.begin() + i);
      return;
    }
    i++;
  }
}
template<COMPARTMENT_GRAPH_TEMPLATE>
void SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>::RemoveLink(const std::string& name)
{
  size_t i = 0;
  for (CompartmentLinkType* p : m_CompartmentLinks)
  {
    if (p->GetName() == name)
    {
      m_CompartmentLinks.erase(m_CompartmentLinks.begin() + i);
      return;
    }
    i++;
  }
}

