/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "engine/SEDynamicStabilizationEngineConvergence.h"
PROTO_PUSH
#include "bind/cdm/Engine.pb.h"
PROTO_POP

SEDynamicStabilizationEngineConvergence::SEDynamicStabilizationEngineConvergence(Logger *logger) : Loggable(logger), m_DataRequestMgr(logger)
{
  Clear();
}

SEDynamicStabilizationEngineConvergence::~SEDynamicStabilizationEngineConvergence()
{
  Clear();
}

void SEDynamicStabilizationEngineConvergence::Clear()
{
  m_ConvergenceTime.SetValue(0, TimeUnit::s);
  m_MinimumReactionTime.SetValue(0, TimeUnit::s);
  m_MaximumAllowedStabilizationTime.SetValue(0, TimeUnit::s);
  DELETE_VECTOR(m_PropertyConvergence);
}

void SEDynamicStabilizationEngineConvergence::Load(const cdm::DynamicStabilizationData_EngineConvergenceData& src, SEDynamicStabilizationEngineConvergence& dst)
{
  SEDynamicStabilizationEngineConvergence::Serialize(src, dst);
}
void SEDynamicStabilizationEngineConvergence::Serialize(const cdm::DynamicStabilizationData_EngineConvergenceData& src, SEDynamicStabilizationEngineConvergence& dst)
{
  dst.Clear();
  // TODO Warn if these are not provided
  if (src.has_convergencetime())
    SEScalarTime::Load(src.convergencetime(), dst.GetConvergenceTime());
  if (src.has_minimumreactiontime())
    SEScalarTime::Load(src.minimumreactiontime(), dst.GetMinimumReactionTime());
  if (src.has_maximumallowedstabilizationtime())
    SEScalarTime::Load(src.maximumallowedstabilizationtime(), dst.GetMaximumAllowedStabilizationTime());
  for (int i=0; i<src.propertyconvergence_size(); i++)
  {
    const cdm::DynamicStabilizationData_PropertyConvergenceData& pcData = src.propertyconvergence(i);
    if (pcData.has_datarequest())
    {
      SEDataRequest& dr = dst.m_DataRequestMgr.CreateDataRequest(pcData.datarequest().category());
      SEDataRequest::Load(pcData.datarequest(), dr);
      dst.CreatePropertyConvergence(dr, pcData.percentdifference());
    }
    else
    {
      dst.Error("Ignoring property convergence that has no data request");
    }
  }
}

cdm::DynamicStabilizationData_EngineConvergenceData* SEDynamicStabilizationEngineConvergence::Unload(const SEDynamicStabilizationEngineConvergence& src)
{
  cdm::DynamicStabilizationData_EngineConvergenceData* dst = new cdm::DynamicStabilizationData_EngineConvergenceData();
  SEDynamicStabilizationEngineConvergence::Serialize(src,*dst);
  return dst;
}
void SEDynamicStabilizationEngineConvergence::Serialize(const SEDynamicStabilizationEngineConvergence& src, cdm::DynamicStabilizationData_EngineConvergenceData& dst)
{
  dst.set_allocated_convergencetime(SEScalarTime::Unload(src.m_ConvergenceTime));
  dst.set_allocated_minimumreactiontime(SEScalarTime::Unload(src.m_MinimumReactionTime));
  dst.set_allocated_maximumallowedstabilizationtime(SEScalarTime::Unload(src.m_MaximumAllowedStabilizationTime));
  for (auto pc : src.m_PropertyConvergence)
  {    
    cdm::DynamicStabilizationData_PropertyConvergenceData* pcData = dst.mutable_propertyconvergence()->Add();
    pcData->set_percentdifference(pc->m_Error);
    pcData->set_allocated_datarequest(SEDataRequest::Unload(pc->m_DataRequest));
  }
}

SEDynamicStabilizationPropertyConvergence& SEDynamicStabilizationEngineConvergence::CreatePropertyConvergence(SEDataRequest& dr, double percentError)
{
  SEDynamicStabilizationPropertyConvergence* p = new SEDynamicStabilizationPropertyConvergence(dr, GetLogger());
  p->m_Error = percentError;
  m_PropertyConvergence.push_back(p);
  return *p;
}

const std::vector<SEDynamicStabilizationPropertyConvergence*>& SEDynamicStabilizationEngineConvergence::GetPropertyConvergence() const
{
  return m_PropertyConvergence;
}
