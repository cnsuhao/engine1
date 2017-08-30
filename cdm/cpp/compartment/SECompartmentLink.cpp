/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/SECompartmentLink.h"
#include "circuit/SECircuitManager.h"
PROTO_PUSH
#include "bind/cdm/Compartment.pb.h"
PROTO_POP


SECompartmentLink::SECompartmentLink(const std::string& name, Logger* logger) : Loggable(logger), m_Name(name)
{
  
}

SECompartmentLink::~SECompartmentLink()
{
  Clear();
}

void SECompartmentLink::Clear()
{
 
}

void SECompartmentLink::Serialize(const cdm::CompartmentLinkData& src, SECompartmentLink& dst)
{
  dst.Clear();
  if (!src.name().empty())
    dst.m_Name = src.name();
}

void SECompartmentLink::Serialize(const SECompartmentLink& src, cdm::CompartmentLinkData& dst)
{
  dst.set_name(src.m_Name);
}

std::string SECompartmentLink::GetName() const
{
  return m_Name;
}



