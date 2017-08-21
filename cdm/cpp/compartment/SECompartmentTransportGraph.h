/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/SECompartmentGraph.h"
#include "substance/SESubstanceTransport.h"

#define COMPARTMENT_TRANSPORT_GRAPH_TEMPLATE typename GraphType, typename GraphVertexType, typename GraphEdgeType, typename CompartmentType, typename CompartmentLinkType
#define COMPARTMENT_TRANSPORT_GRAPH_TYPES GraphType, GraphVertexType, GraphEdgeType, CompartmentType, CompartmentLinkType

template<COMPARTMENT_TRANSPORT_GRAPH_TEMPLATE>
class SECompartmentTransportGraph : public GraphType, public SECompartmentGraph<COMPARTMENT_GRAPH_TYPES>
{
public:
  SECompartmentTransportGraph(const std::string& name, Logger* logger);
  virtual ~SECompartmentTransportGraph();

  virtual void Clear();
/*
  virtual bool Load(const BindType& in);
  virtual BindType* Unload() = 0;
protected:
  virtual void Unload(BindType& data);
*/

public:
  virtual std::string GetName() const { return this->m_Name; }

  virtual void StateChange();

protected:
  virtual void BalanceByIntensive()=0;
  virtual size_t GetVertexIndex(const GraphVertexType& v) const;
  virtual const std::vector<GraphVertexType*>& GetVerticies() const;
  virtual const std::vector<GraphEdgeType*>* GetSourceEdges(const GraphVertexType& v) const;
  virtual const std::vector<GraphEdgeType*>* GetTargetEdges(const GraphVertexType& v) const;

  std::vector<GraphVertexType*>                                  m_Verticies;
  std::map<const GraphVertexType*, size_t>                       m_VertexIndicies;
  std::map<const GraphVertexType*, std::vector<GraphEdgeType*>*> m_SourceEdgeMap;
  std::map<const GraphVertexType*, std::vector<GraphEdgeType*>*> m_TargetEdgeMap;
};
#include "compartment/SECompartmentTransportGraph.inl"
