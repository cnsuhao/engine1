/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "substance/SESubstanceTransport.h"
#include "compartment/SECompartment.h"
#include "circuit/fluid/SEFluidCircuitNode.h"
#include "compartment/SECompartmentNodes.h"
PROTO_PUSH
#include "bind/cdm/Compartment.pb.h"
PROTO_POP

class SESubstance;
template<typename EdgeType, typename VertexType, typename CompartmentType> class SEFluidCompartmentLink;

#define FLUID_COMPARTMENT_TEMPLATE typename LinkType, typename VertexType, typename TransportSubstanceType, typename SubstanceQuantityType
#define FLUID_COMPARTMENT_TYPES LinkType, VertexType, TransportSubstanceType, SubstanceQuantityType

template<FLUID_COMPARTMENT_TEMPLATE>
class SEFluidCompartment : public SECompartment, public VertexType
{
  template<typename CompartmentType, typename CompartmentLinkType> friend class SECompartmentGraph;
protected:
  SEFluidCompartment(const std::string& name, Logger* logger);
public:
  virtual ~SEFluidCompartment();

  virtual void Clear();

protected:
  static void Serialize(const cdm::FluidCompartmentData& src, SEFluidCompartment& dst, SECircuitManager* circuits=nullptr);
  static void Serialize(const SEFluidCompartment& src, cdm::FluidCompartmentData& dst);

public:
  virtual std::string GetName() const { return m_Name; }

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasChildren() const { return !m_FluidChildren.empty(); }

  virtual bool HasNodeMapping() const { return m_Nodes.HasMapping(); }
  virtual  SECompartmentNodes<FLUID_COMPARTMENT_NODE>& GetNodeMapping() { return m_Nodes; }
  virtual void MapNode(SEFluidCircuitNode& node);

  virtual bool HasInFlow() const;
  virtual const SEScalarVolumePerTime& GetInFlow() const;
  virtual double GetInFlow(const VolumePerTimeUnit& unit) const;

  virtual bool HasOutFlow() const;
  virtual const SEScalarVolumePerTime& GetOutFlow() const;
  virtual double GetOutFlow(const VolumePerTimeUnit& unit) const;

  virtual bool HasPressure() const;
  virtual SEScalarPressure& GetPressure();
  virtual double GetPressure(const PressureUnit& unit) const;

  virtual bool HasVolume() const;
  virtual SEScalarVolume& GetVolume();
  virtual double GetVolume(const VolumeUnit& unit) const;

  virtual bool HasSubstanceQuantities() const;
  virtual bool HasSubstanceQuantity(const SESubstance& substance) const;
  virtual SubstanceQuantityType* GetSubstanceQuantity(const SESubstance& substance) const;
  virtual const std::vector<SubstanceQuantityType*>& GetSubstanceQuantities() const;
  virtual void ZeroSubstanceQuantities();

  virtual void AddLink(LinkType& link);
  virtual void RemoveLink(LinkType& link);
  virtual void RemoveLinks();
  virtual const std::vector<LinkType*>& GetLinks();

  virtual bool HasChild(const std::string& name);

protected:
  virtual void RemoveSubstanceQuantity(const SESubstance& substance);

  virtual bool HasQuantity() const { return HasVolume(); }
  virtual SEScalarVolume& GetQuantity() { return GetVolume(); }

  virtual double CalculateInFlow_mL_Per_s() const;
  virtual double CalculateOutFlow_mL_Per_s() const;

  virtual std::vector<TransportSubstanceType*>& GetTransportSubstances() { return m_TransportSubstances; }

  mutable SEScalarVolumePerTime* m_InFlow;
  mutable SEScalarVolumePerTime* m_OutFlow;
  SEScalarPressure*      m_Pressure;
  SEScalarVolume*        m_Volume;

  std::vector<SubstanceQuantityType*>  m_SubstanceQuantities;
  std::vector<TransportSubstanceType*> m_TransportSubstances;

  std::vector<LinkType*> m_Links;
  std::vector<LinkType*> m_IncomingLinks;
  std::vector<LinkType*> m_OutgoingLinks;
  std::vector<SEFluidCompartment*> m_FluidChildren;
  SECompartmentNodes<FLUID_COMPARTMENT_NODE>  m_Nodes;
};
#include "compartment/fluid/SEFluidCompartment.inl"
