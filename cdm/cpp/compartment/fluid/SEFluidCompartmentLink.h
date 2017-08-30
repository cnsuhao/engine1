/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/SECompartmentLink.h"
#include "substance/SESubstanceTransport.h"
#include "compartment/fluid/SEFluidCompartment.h"
#include "circuit/fluid/SEFluidCircuitPath.h"

#define FLUID_COMPARTMENT_LINK_TEMPLATE typename EdgeType, typename VertexType, typename CompartmentType
#define FLUID_COMPARTMENT_LINK_TYPES EdgeType, VertexType, CompartmentType

template<FLUID_COMPARTMENT_LINK_TEMPLATE>
class SEFluidCompartmentLink : public SECompartmentLink, public EdgeType
{
protected:
  SEFluidCompartmentLink(CompartmentType& src, CompartmentType & tgt, const std::string& name);
public:
  virtual ~SEFluidCompartmentLink();

  virtual void Clear();

protected:
  static void Serialize(const cdm::FluidCompartmentLinkData& src, SEFluidCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static void Serialize(const SEFluidCompartmentLink& src, cdm::FluidCompartmentLinkData& dst);
  
public:
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual std::string GetName() const { return m_Name; }

  virtual bool HasFlow() const;
  virtual SEScalarVolumePerTime& GetFlow();
  virtual double GetFlow(const VolumePerTimeUnit& unit) const;

  virtual CompartmentType& GetSourceCompartment() { return m_SourceCmpt; }
  virtual CompartmentType& GetTargetCompartment() { return m_TargetCmpt; }

  virtual bool HasPath() { return m_Path != nullptr; }  
  virtual SEFluidCircuitPath* GetPath() { return m_Path; }
  virtual void RemovePath() { m_Path = nullptr; }
  virtual void MapPath(SEFluidCircuitPath& path) { Clear();  m_Path = &path; }

protected:
  // For Transport
  virtual bool HasFlux() const { return HasFlow(); }
  virtual SEScalarVolumePerTime& GetFlux() { return GetFlow(); }
  virtual double GetFlux(const VolumePerTimeUnit& unit) const { return GetFlow(unit); }

  virtual VertexType& GetSourceVertex()           { return m_SourceVertex; }
  virtual VertexType& GetTargetVertex()           { return m_TargetVertex; }

  SEScalarVolumePerTime* m_Flow;
  CompartmentType&       m_SourceCmpt;
  CompartmentType&       m_TargetCmpt;
  VertexType&            m_SourceVertex;
  VertexType&            m_TargetVertex;
  SEFluidCircuitPath*    m_Path;
};
#include "compartment/fluid/SEFluidCompartmentLink.inl"
