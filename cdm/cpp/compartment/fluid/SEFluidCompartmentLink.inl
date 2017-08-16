/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "compartment/fluid/SEFluidCompartmentLink.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "circuit/SECircuitManager.h"

#include "properties/SEScalarVolumePerTime.h"

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::SEFluidCompartmentLink(CompartmentType& src, CompartmentType & tgt, const std::string& name) : SECompartmentLink(name, src.GetLogger()), m_SourceCmpt(src), m_TargetCmpt(tgt), m_SourceVertex(src), m_TargetVertex(tgt)
{
  m_Flow = nullptr;
  m_Path = nullptr;
}
template<FLUID_COMPARTMENT_LINK_TEMPLATE>
SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::~SEFluidCompartmentLink()
{

}

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
void SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::Serialize(const cdm::FluidCompartmentLinkData& src, SEFluidCompartmentLink& dst, SECircuitManager* circuits)
{
  SECompartmentLink::Serialize(src.link(), dst);

  if (!src.link().path().empty())
  {
    if (circuits == nullptr)
    {
      dst.Error("Link is mapped to circuit path, "+ src.link().path() +", but no circuit manager was provided, cannot load");
      return;
    }
    SEFluidCircuitPath* path = circuits->GetFluidPath(src.link().path());
    if (path == nullptr)
    {
      dst.Error("Link is mapped to circuit path, " + src.link().path() + ", but provided circuit manager did not have that path");
      return;
    }
    dst.MapPath(*path);
  }
  else
  {
    if (src.has_flow())
      SEScalarVolumePerTime::Load(src.flow(), dst.GetFlow());
  }
}
template<FLUID_COMPARTMENT_LINK_TEMPLATE>
void SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::Serialize(const SEFluidCompartmentLink& src, cdm::FluidCompartmentLinkData& dst)
{
  SECompartmentLink::Serialize(src,*dst.mutable_link());
  dst.mutable_link()->set_sourcecompartment(src.m_SourceCmpt.GetName());
  dst.mutable_link()->set_targetcompartment(src.m_TargetCmpt.GetName());
  if (src.m_Path != nullptr)
    dst.mutable_link()->set_path(src.m_Path->GetName());
  // Yeah, I know
  // But, these will only modify member variables if they are being used as temporary variables
  // Even if you have a path, I am unloading everything, this makes the pba actually usefull...
  SEFluidCompartmentLink& mutable_src = const_cast<SEFluidCompartmentLink&>(src);
  if (src.HasFlow())
    dst.set_allocated_flow(SEScalarVolumePerTime::Unload(mutable_src.GetFlow()));
}

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
void SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::Clear()
{
  m_Path = nullptr;
  SAFE_DELETE(m_Flow);
}

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
const SEScalar* SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::GetScalar(const std::string& name)
{
  if (name.compare("Flow") == 0)
    return &GetFlow();
  return nullptr;
}

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
bool SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::HasFlow() const
{
  if (m_Path != nullptr)
    return m_Path->HasNextFlow();
  return m_Flow == nullptr ? false : m_Flow->IsValid();
}
template<FLUID_COMPARTMENT_LINK_TEMPLATE>
SEScalarVolumePerTime& SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::GetFlow()
{
  if (m_Path != nullptr)
    return m_Path->GetNextFlow();
  if (m_Flow == nullptr)
    m_Flow = new SEScalarVolumePerTime();
  return *m_Flow;
}
template<FLUID_COMPARTMENT_LINK_TEMPLATE>
double SEFluidCompartmentLink<FLUID_COMPARTMENT_LINK_TYPES>::GetFlow(const VolumePerTimeUnit& unit) const
{
  if (m_Path != nullptr)
    return m_Path->GetNextFlow(unit);
  if (m_Flow == nullptr)
    return SEScalar::dNaN();
  return m_Flow->GetValue(unit);
}