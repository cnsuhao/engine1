/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/fluid/SEGasCompartmentGraph.h"
#include "compartment/substances/SEGasSubstanceQuantity.h"
#include "compartment/SECompartmentManager.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalar0To1.h"
PROTO_PUSH
#include "bind/cdm/Compartment.pb.h"
PROTO_POP

void SEGasCompartmentGraph::Load(const cdm::GasCompartmentGraphData& src, SEGasCompartmentGraph& dst, SECompartmentManager& cmptMgr)
{
  SEGasCompartmentGraph::Serialize(src, dst, cmptMgr);
}
void SEGasCompartmentGraph::Serialize(const cdm::GasCompartmentGraphData& src, SEGasCompartmentGraph& dst, SECompartmentManager& cmptMgr)
{
  dst.m_Name = src.fluidgraph().graph().name();
  for (int i=0; i<src.fluidgraph().graph().compartment_size(); i++)
  {
    std::string name = src.fluidgraph().graph().compartment(i);
    SEGasCompartment* cmpt = cmptMgr.GetGasCompartment(name);
    if (cmpt == nullptr)
    {
      dst.Error("Could not find compartment " + name + " for graph " + dst.m_Name);
      continue;
    }
    dst.AddCompartment(*cmpt);
  }
  for (int i = 0; i<src.fluidgraph().graph().link_size(); i++)
  {
    std::string name = src.fluidgraph().graph().link(i);
    SEGasCompartmentLink* link = cmptMgr.GetGasLink(name);
    if (link == nullptr)
    {
      dst.Error("Could not find link " + name + " for graph " + dst.m_Name);
      continue;
    }
    dst.AddLink(*link);
  }
}

cdm::GasCompartmentGraphData* SEGasCompartmentGraph::Unload(const SEGasCompartmentGraph& src)
{
  cdm::GasCompartmentGraphData* dst = new cdm::GasCompartmentGraphData();
  SEGasCompartmentGraph::Serialize(src, *dst);
  return dst;
}
void SEGasCompartmentGraph::Serialize(const SEGasCompartmentGraph& src, cdm::GasCompartmentGraphData& dst)
{
  dst.mutable_fluidgraph()->mutable_graph()->set_name(src.m_Name);
  for (SEGasCompartment* cmpt : src.m_Compartments)
    dst.mutable_fluidgraph()->mutable_graph()->add_compartment(cmpt->GetName());
  for (SEGasCompartmentLink* link : src.m_CompartmentLinks)
    dst.mutable_fluidgraph()->mutable_graph()->add_link(link->GetName());
}

void SEGasCompartmentGraph::BalanceByIntensive()
{
  for (auto cmpt : GetCompartments())
  {
    // Make sure Volume Fractions sum to 1.0 and adjust accordingly
    double totalVolumeFraction = 0;
    for (SEGasSubstanceQuantity* subQ : cmpt->GetSubstanceQuantities())
    {
      if (subQ->HasVolumeFraction())
        totalVolumeFraction += subQ->GetVolumeFraction().GetValue();
    }
    if (totalVolumeFraction == 0.0)
    {
      for (SEGasSubstanceQuantity* subQ : cmpt->GetSubstanceQuantities())
      {
        if (subQ->HasVolumeFraction())
          subQ->SetToZero();
      }
      continue;
    }
    else
    {
      //Adjust to keep the volume fractions making sense
    //Make it a little more sensitive than the error check later just to be safe
      if (std::abs(1.0 - totalVolumeFraction) > (ZERO_APPROX / 10.0))
      {
        for (SEGasSubstanceQuantity* subQ : cmpt->GetSubstanceQuantities())
        {
          //Adjust everything the same amount to make sure the volume fraction is 1.0
      double volumeFractionErrorFraction = 1.0 / totalVolumeFraction;  //<1 = too high; >1 = too low
          subQ->GetVolumeFraction().SetValue(subQ->GetVolumeFraction().GetValue() * volumeFractionErrorFraction);
        }
      }
    }
    cmpt->Balance(BalanceGasBy::VolumeFraction);
  }
}

void SEGasCompartmentGraph::AddGraph(SEGasCompartmentGraph& graph)
{
  for (SEGasCompartment* cmpt : graph.GetCompartments())
    AddCompartment(*cmpt);
  for (SEGasCompartmentLink* lnk : graph.GetLinks())
    AddLink(*lnk);
}
