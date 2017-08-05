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
#include "engine/SEDynamicStabilization.h"
#include "engine/SEDynamicStabilizationLedger.h"
#include "PhysiologyEngine.h"
#include "scenario/SECondition.h"
#include "utils/TimingProfile.h"
#include <google/protobuf/text_format.h>


SEDynamicStabilization::SEDynamicStabilization(Logger *logger) : SEEngineStabilization(logger), 
m_RestingConvergence(logger), m_FeedbackConvergence(logger), m_MergedConditions(logger)
{
  
}

SEDynamicStabilization::~SEDynamicStabilization()
{
  Clear();
}


void SEDynamicStabilization::Clear()
{
  SEEngineStabilization::Clear();
  m_MergedConditions.m_PropertyConvergence.clear();// \todo Make copies of stabilization Convergence
  m_MergedConditions.Clear();
  m_ActiveConditions.clear();
  m_RestingConvergence.Clear();
  m_FeedbackConvergence.Clear();
  DELETE_MAP_SECOND(m_ConditionConvergence);
}

void SEDynamicStabilization::Load(const cdm::DynamicStabilizationData& src, SEDynamicStabilization& dst)
{
  SEDynamicStabilization::Serialize(src, dst);
}
void SEDynamicStabilization::Serialize(const cdm::DynamicStabilizationData& src, SEDynamicStabilization& dst)
{
  dst.Clear();
  dst.m_TrackingStabilization = src.trackingstabilization();
  if(src.has_restingconvergence())
    SEDynamicStabilizationEngineConvergence::Load(src.restingconvergence(), dst.GetRestingConvergence());
  if (src.has_feedbackconvergence())
    SEDynamicStabilizationEngineConvergence::Load(src.feedbackconvergence(), dst.GetFeedbackConvergence());

  for (auto itr : src.conditionconvergence())
  {
    SEDynamicStabilizationEngineConvergence* c = new SEDynamicStabilizationEngineConvergence(dst.GetLogger());
    SEDynamicStabilizationEngineConvergence::Load(itr.second,*c);
    dst.m_ConditionConvergence[itr.first] = c;
  }
}

cdm::DynamicStabilizationData* SEDynamicStabilization::Unload(const SEDynamicStabilization& src)
{
  cdm::DynamicStabilizationData* dst(new cdm::DynamicStabilizationData());
  SEDynamicStabilization::Serialize(src,*dst);
  return dst;
}
void SEDynamicStabilization::Serialize(const SEDynamicStabilization& src, cdm::DynamicStabilizationData& dst)
{
  dst.set_trackingstabilization(src.m_TrackingStabilization);
  dst.set_allocated_restingconvergence(SEDynamicStabilizationEngineConvergence::Unload(src.m_RestingConvergence));
  if (src.HasFeedbackConvergence())
    dst.set_allocated_feedbackconvergence(SEDynamicStabilizationEngineConvergence::Unload(src.m_FeedbackConvergence));
  for (auto &c : src.m_ConditionConvergence)
  {
    cdm::DynamicStabilizationData_EngineConvergenceData* cData = SEDynamicStabilizationEngineConvergence::Unload(*c.second);
    (*dst.mutable_conditionconvergence())[c.first] = *cData;
    delete cData;
  }
}

bool SEDynamicStabilization::LoadFile(const std::string& file)
{
  try
  {
    Clear();
    std::ifstream input(file);
    std::string fmsg((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    cdm::DynamicStabilizationData ds;
    if (!google::protobuf::TextFormat::ParseFromString(fmsg, &ds))
      return false;
    SEDynamicStabilization::Load(ds, *this);
    return true;
  }
  catch (std::exception ex)
  {
    Error("Unable to read file : " + file);
  }
  return false;
}

SEDynamicStabilizationEngineConvergence& SEDynamicStabilization::GetRestingConvergence()
{
  return m_RestingConvergence;
}
const SEDynamicStabilizationEngineConvergence& SEDynamicStabilization::GetRestingConvergence() const
{
  return m_RestingConvergence;
}

bool SEDynamicStabilization::HasFeedbackConvergence() const
{
  return !m_FeedbackConvergence.m_PropertyConvergence.empty();
}
SEDynamicStabilizationEngineConvergence& SEDynamicStabilization::GetFeedbackConvergence()
{
  return m_FeedbackConvergence;
}
const SEDynamicStabilizationEngineConvergence* SEDynamicStabilization::GetFeedbackConvergence() const
{
  return &m_FeedbackConvergence;
}


bool SEDynamicStabilization::HasConditionConvergence(const std::string& name) const
{
  return m_ConditionConvergence.find(name) != m_ConditionConvergence.end();
}
void SEDynamicStabilization::RemoveConditionConvergence(const std::string& name)
{
  for (auto itr : m_ConditionConvergence)
  {
    if (itr.first == name)
    {
      SAFE_DELETE(itr.second);
      m_ConditionConvergence.erase(name);
      return;
    }
  }
}
SEDynamicStabilizationEngineConvergence& SEDynamicStabilization::GetConditionConvergence(const std::string& name)
{
  SEDynamicStabilizationEngineConvergence* c = m_ConditionConvergence[name];
  if (c == nullptr)
  {
    c = new SEDynamicStabilizationEngineConvergence(GetLogger());
    m_ConditionConvergence[name] = c;
  }
  return *c;
}
const SEDynamicStabilizationEngineConvergence* SEDynamicStabilization::GetConditionConvergence(const std::string& name) const
{
  for (auto itr : m_ConditionConvergence)
  {
    if (itr.first == name)
      return itr.second;
  }
  return nullptr;
}

const std::map<std::string, SEDynamicStabilizationEngineConvergence*>& SEDynamicStabilization::GetConditionConvergence() const
{
  return m_ConditionConvergence;
}

bool SEDynamicStabilization::StabilizeRestingState(PhysiologyEngine& engine)
{
  Info("Converging to a steady state");
  return Stabilize(engine, m_RestingConvergence);
}
bool SEDynamicStabilization::StabilizeFeedbackState(PhysiologyEngine& engine)
{
  if (!HasFeedbackConvergence())
    return true;
  Info("Converging feedback to a steady state");
  return Stabilize(engine, m_FeedbackConvergence);
}
bool SEDynamicStabilization::StabilizeConditions(PhysiologyEngine& engine, const std::vector<const SECondition*>& conditions)
{
  if (conditions.empty())
    return true;
  // Grab the Convergence based on the conditions we have
  m_ActiveConditions.clear();
  for (auto c : conditions)
  {
    if (!HasConditionConvergence(c->GetName()))
    {
      Error("Engine does not support Condition");
      return false;
    }
    else
      m_ActiveConditions[c->GetName()]=&GetConditionConvergence(c->GetName());
  }
  if (m_ActiveConditions.size() == 1)
  {
    Info("Converging provided condition to a steady state");
    return Stabilize(engine, *m_ActiveConditions.begin()->second);
  }
  else
  {
    if (!Merge())
    {
      Error("Unable to merge conditions");
      return false;
    }
    Info("Converging provided conditions to a steady state");
    return Stabilize(engine, m_MergedConditions);
  }
}

bool SEDynamicStabilization::Stabilize(PhysiologyEngine& engine, const SEDynamicStabilizationEngineConvergence& Convergence)
{
  const std::vector<SEDynamicStabilizationPropertyConvergence*>& properties = Convergence.GetPropertyConvergence();
  if (properties.empty())
    return true;//nothing to do here...

  m_Cancelled = false;
  std::stringstream ss;
  TimingProfile profiler;
  if (m_LogProgress)
  {
    profiler.Start("Total");
    profiler.Start("Status");
  }
  // Execute System initialization time
  SEEngineTracker* tracker = engine.GetEngineTracker();
  cdm::eSwitch track = m_TrackingStabilization;
  if (track&&tracker == nullptr)
  {
    track = cdm::eSwitch::Off;
    Warning("PhysiologyEngineTrack not provided by engine, not tracking data to file");
  }

  bool   hasOptionalProperties = false;

  // Grab all the convergence properties
  for (SEDynamicStabilizationPropertyConvergence* pc : properties)
  {
    if (pc->IsOptional())
      hasOptionalProperties = true;
    tracker->ConnectRequest(pc->GetDataRequest(), pc->GetDataRequestScalar());
    if (!pc->GetDataRequestScalar().HasScalar())
    {
      ss << "Cannot find convergence property " << pc->GetDataRequest().GetPropertyName();
      throw CommonDataModelException(ss.str());
    }
  }

  ss.precision(3);
  double statusTime_s = 0;// Current time of this status cycle
  double statusStep_s = 10;//How long did it take to simulate this much time
  double stablizationTime_s = 0;
  double dT_s = engine.GetTimeStep(TimeUnit::s);

  SEDynamicStabilizationLedger ledger(dT_s, Convergence);
  while (!(ledger.HasConverged() && ledger.HasConvergedOptional()))
  {
    if (m_Cancelled)
      break;
    if (ledger.HasExceededTime())
      break;

    engine.AdvanceModelTime();
    if (m_currentTime_s == 0)
      tracker->SetupRequests();
    stablizationTime_s += dT_s;
    m_currentTime_s += dT_s;
    if (track)
      tracker->TrackData(m_currentTime_s);
    if (m_LogProgress)
    {
      statusTime_s += dT_s;
      if (statusTime_s>statusStep_s)
      {
        statusTime_s = 0;
        ss << "Converging System... it took "
          << profiler.GetElapsedTime_s("Status") << "s to simulate the past "
          << statusStep_s << "s" << std::flush;
        profiler.Reset("Status");
        Info(ss);
      }
    }
    ledger.TestConvergence();
  }
  double covTime_s = Convergence.GetConvergenceTime(TimeUnit::s);
  if (ledger.HasExceededTime())
  {
    Error("Could not converge to provided Convergence");
    for (SEDynamicStabilizationPropertyConvergence* pc : properties)
    {
      if (stablizationTime_s - pc->GetLastErrorTime_s() < covTime_s)
      {
        m_ss << stablizationTime_s << "s - " << pc->GetDataRequest().GetPropertyName() << " is not converging, last error time was " << pc->GetLastErrorTime_s() << "s setting a target value of " << pc->GetCurrentTarget() << " and the current value is " << pc->GetDataRequestScalar().GetValue();
        Error(m_ss);
      }
      /* else
      {
      m_ss << stablizationTime_s << "s - " << pc->GetDataRequest().GetName() << " is converging, last error time was " << pc->GetLastErrorTime_s() << "s";
      Info(m_ss);
      }*/

    }
    return false;
  }
  else if (m_LogProgress)
  {
    ss << "Convergence took " << profiler.GetElapsedTime_s("Total") << "s to simulate " << stablizationTime_s << "s to get engine to a steady state";
    Info(ss);
    if (hasOptionalProperties && !ledger.HasConvergedOptional())
    {
      ss << "Could not converge optional properties";
      Warning(ss);
      for (SEDynamicStabilizationPropertyConvergence* pc : properties)
      {
        if (stablizationTime_s - pc->GetLastErrorTime_s() < covTime_s)
        {
          m_ss << stablizationTime_s << "s - " << pc->GetDataRequest().GetPropertyName() << " is not converging, last error time was " << pc->GetLastErrorTime_s() << "s setting a target value of " << pc->GetCurrentTarget() << " and the current value is " << pc->GetDataRequestScalar().GetValue();
          Error(m_ss);
        }

      }
    }
  }
  // Save off how long it took us to stabilize
  GetStabilizationDuration().SetValue(stablizationTime_s, TimeUnit::s);
  return true;
}

bool SEDynamicStabilization::Merge()
{
  // Get a std::hash<std::string>()("foo"); for each Property convergence Data Request
  // Don't forget to add hashes of compartments and substance names! if applicable
  // Put it in a map<hash#,vector<PropertyConvergence*>>
  // After this loop, go through the map and remove any 
  // entries where the vector length is < activeConditions.size()
  // We only want convergence objects if ALL active conditions have them
  // From there find the PropertyConvergence with the largest %diff
  // Add that pointer to the m_MergedConditions (will need new friend method as that method should not be public)
  Info("Merging Conditions");
  m_MergedConditions.m_PropertyConvergence.clear();// \todo Make copies of stabilization Convergence
  m_MergedConditions.Clear();
  double time_s;
  double maxConv_s = 0;
  double maxMinStabilize_s = 0;
  double maxMaxStabilize_s = 0;
  const std::vector<SEDynamicStabilizationPropertyConvergence*>* vCondPConv;
  std::map<std::string, std::vector<SEDynamicStabilizationPropertyConvergence*>*> cMap;
  for (auto itr : m_ActiveConditions)
  {
    const SEDynamicStabilizationEngineConvergence* c = itr.second;
    m_ss << "Analyzing " << itr.first;
    Info(m_ss);
    vCondPConv = &c->GetPropertyConvergence();
    for (SEDynamicStabilizationPropertyConvergence* pConv : *vCondPConv)
    {
      auto cMapItr = cMap.find(pConv->GetDataRequest().GetPropertyName());
      if (cMapItr != cMap.end())
        cMapItr->second->push_back(pConv);
      else
      {
        std::vector<SEDynamicStabilizationPropertyConvergence*>* vec =
          new std::vector<SEDynamicStabilizationPropertyConvergence*>();
        vec->push_back(pConv);
        cMap[pConv->GetDataRequest().GetPropertyName()] = vec;
      }
    }

    time_s = c->GetConvergenceTime(TimeUnit::s);
    if (time_s > maxConv_s)
      maxConv_s = time_s;
    time_s = c->GetMinimumReactionTime(TimeUnit::s);
    if (time_s > maxMinStabilize_s)
      maxMinStabilize_s = time_s;
    time_s = c->GetMaximumAllowedStabilizationTime(TimeUnit::s);
    if (time_s > maxMaxStabilize_s)
      maxMaxStabilize_s = time_s;
  }
  double tmpError;
  SEDynamicStabilizationPropertyConvergence* pConv;
  for (auto i = cMap.begin(); i != cMap.end(); i++)
  {
    // Let's find the Convergence that has the largest % difference
    double pErr = 0;
    for (auto j = i->second->begin(); j != i->second->end(); j++)
    {
      tmpError = (*j)->GetPercentError();
      if (tmpError > pErr)
      {
        pErr = tmpError;
        pConv = (*j);
      }
    }
    if (i->second->size() == m_ActiveConditions.size())
    {
      m_ss << "Merged Convergance for property " << pConv->GetDataRequest().GetPropertyName() << " using " << pConv->GetPercentError() << "% error";
      Info(m_ss);
    }
    else
    {
      pConv->SetOptional(true);
      m_ss << "Not all conditions contain " << i->first << " in convergence Convergence. Making convergence on this property optional.";
      Warning(m_ss);
    }
    m_MergedConditions.m_PropertyConvergence.push_back(pConv);
  }

  DELETE_MAP_SECOND(cMap);// Clean up our Map  
  m_MergedConditions.GetConvergenceTime().SetValue(maxConv_s, TimeUnit::s);
  m_ss << "Merged Convergence Time : " << m_MergedConditions.GetConvergenceTime();
  Info(m_ss);
  m_MergedConditions.GetMinimumReactionTime().SetValue(maxMinStabilize_s, TimeUnit::s);
  m_ss << "Merged Minimum Reaction Time : " << m_MergedConditions.GetMinimumReactionTime();
  Info(m_ss);
  m_MergedConditions.GetMaximumAllowedStabilizationTime().SetValue(maxMaxStabilize_s, TimeUnit::s);
  m_ss << "Merged Maximum Allowed Stabilization Time : " << m_MergedConditions.GetMaximumAllowedStabilizationTime();
  Info(m_ss);
  return true;
}


