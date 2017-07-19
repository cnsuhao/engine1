/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#include "stdafx.h"
#include "compartment/fluid/SELiquidCompartmentGraph.h"
#include "compartment/SECompartmentManager.h"

void SELiquidCompartmentGraph::Load(const cdm::LiquidCompartmentGraphData& src, SELiquidCompartmentGraph& dst, SECompartmentManager& cmptMgr)
{
  SELiquidCompartmentGraph::Serialize(src, dst, cmptMgr);
}
void SELiquidCompartmentGraph::Serialize(const cdm::LiquidCompartmentGraphData& src, SELiquidCompartmentGraph& dst, SECompartmentManager& cmptMgr)
{
  dst.m_Name = src.fluidgraph().graph().name();
  for (int i = 0; i<src.fluidgraph().graph().compartment_size(); i++)
  {
    std::string name = src.fluidgraph().graph().compartment(i);
    SELiquidCompartment* cmpt = cmptMgr.GetLiquidCompartment(name);
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
    SELiquidCompartmentLink* link = cmptMgr.GetLiquidLink(name);
    if (link == nullptr)
    {
      dst.Error("Could not find link " + name + " for graph " + dst.m_Name);
      continue;
    }
    dst.AddLink(*link);
  }
}

cdm::LiquidCompartmentGraphData* SELiquidCompartmentGraph::Unload(const SELiquidCompartmentGraph& src)
{
  cdm::LiquidCompartmentGraphData* dst = new cdm::LiquidCompartmentGraphData();
  SELiquidCompartmentGraph::Serialize(src, *dst);
  return dst;
}
void SELiquidCompartmentGraph::Serialize(const SELiquidCompartmentGraph& src, cdm::LiquidCompartmentGraphData& dst)
{
  dst.mutable_fluidgraph()->mutable_graph()->set_name(src.m_Name);
  for (SELiquidCompartment* cmpt : src.m_Compartments)
    dst.mutable_fluidgraph()->mutable_graph()->add_compartment(cmpt->GetName());
  for (SELiquidCompartmentLink* link : src.m_CompartmentLinks)
    dst.mutable_fluidgraph()->mutable_graph()->add_link(link->GetName());
}

void SELiquidCompartmentGraph::BalanceByIntensive()
{
  for (auto cmpt : GetCompartments())
    cmpt->Balance(BalanceLiquidBy::Concentration);
}

void SELiquidCompartmentGraph::AddGraph(SELiquidCompartmentGraph& graph)
{
  for (SELiquidCompartment* cmpt : graph.GetCompartments())
    AddCompartment(*cmpt);
  for (SELiquidCompartmentLink* lnk : graph.GetLinks())
    AddLink(*lnk);
}