/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "compartment/SECompartmentLink.h"
#include "substance/SESubstanceTransport.h"
#include "compartment/thermal/SEThermalCompartment.h"
#include "circuit/thermal/SEThermalCircuitPath.h"

class CDM_DECL SEThermalCompartmentLink : public SECompartmentLink
{
  friend class SECompartmentManager;
protected:
  SEThermalCompartmentLink(SEThermalCompartment& src, SEThermalCompartment & tgt, const std::string& name);
public:
  virtual ~SEThermalCompartmentLink();

  virtual void Clear();
  
  static void Load(const cdm::ThermalCompartmentLinkData& src, SEThermalCompartmentLink& dst, SECircuitManager* circuits=nullptr);
  static cdm::ThermalCompartmentLinkData* Unload(const SEThermalCompartmentLink& src);
protected:
  static void Serialize(const cdm::ThermalCompartmentLinkData& src, SEThermalCompartmentLink& dst, SECircuitManager* circuits = nullptr);
  static void Serialize(const SEThermalCompartmentLink& src, cdm::ThermalCompartmentLinkData& dst);
  
public:
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasHeatTransferRate() const;
  virtual SEScalarPower& GetHeatTransferRate();
  virtual double GetHeatTransferRate(const PowerUnit& unit) const;

  virtual SEThermalCompartment& GetSourceCompartment() { return m_SourceCmpt; }
  virtual SEThermalCompartment& GetTargetCompartment() { return m_TargetCmpt; }

  virtual bool HasPath() { return m_Path != nullptr; }
  virtual SEThermalCircuitPath* GetPath() { return m_Path; }
  virtual void RemovePath() { m_Path = nullptr; }
  virtual void MapPath(SEThermalCircuitPath& path) { Clear();  m_Path = &path; }

protected:
  SEScalarPower*         m_HeatTransferRate;
  SEThermalCompartment&  m_SourceCmpt;
  SEThermalCompartment&  m_TargetCmpt;
  SEThermalCircuitPath*  m_Path;
};

#include "compartment/SECompartmentGraph.h"
class SEThermalCompartmentGraph : public SECompartmentGraph<SEThermalCompartment, SEThermalCompartmentLink>
{
public:
  SEThermalCompartmentGraph(const std::string& name, Logger* logger) : SECompartmentGraph(name, logger) {};
  virtual ~SEThermalCompartmentGraph() {}
};
