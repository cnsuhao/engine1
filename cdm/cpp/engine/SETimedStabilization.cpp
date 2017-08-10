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
#include "engine/SETimedStabilization.h"
#include "engine/SEEngineTracker.h"
#include "PhysiologyEngine.h"
#include "scenario/SECondition.h"
#include "utils/TimingProfile.h"
#include <google/protobuf/text_format.h>

bool SETimedStabilization::StabilizeRestingState(PhysiologyEngine& engine)
{
  if (!GetRestingStabilizationTime().IsValid())
    return true;//No stabilization time requested
  return Stabilize(engine, GetRestingStabilizationTime());
}
bool SETimedStabilization::StabilizeFeedbackState(PhysiologyEngine& engine)
{
  if (!HasFeedbackStabilizationTime())
    return true;//No stabilization time requested
  return Stabilize(engine, GetFeedbackStabilizationTime());
}
bool SETimedStabilization::StabilizeConditions(PhysiologyEngine& engine, const std::vector<const SECondition*>& conditions)
{
  if (conditions.empty())
    return true;
  double cTime_s;
  double maxTime_s = 0;
  for (const SECondition* c : conditions)
  {
    if(!HasConditionTime(c->GetName()))
    {
      Error("Engine does not support Condition");
      return false;
    }
    const SEScalarTime& time = GetConditionTime(c->GetName());
    cTime_s= time.GetValue(TimeUnit::s);
    if (cTime_s > maxTime_s)
      maxTime_s = cTime_s;
  }
  SEScalarTime time;
  time.SetValue(maxTime_s, TimeUnit::s);
  return Stabilize(engine, time);
}
bool SETimedStabilization::Stabilize(PhysiologyEngine& engine, const SEScalarTime& time)
{  
  double sTime_s = time.GetValue(TimeUnit::s);
  if (sTime_s == 0)
    return true; //No stabilization time requested

  m_Cancelled = false;
  std::stringstream ss;
  TimingProfile profiler;
  Info("Initializing Engine : 0%");
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

  ss.precision(3);
  double statusTime_s = 0;// Current time of this status cycle
  double statusStep_s = 50;//How long did it take to simulate this much time
  double dT_s = engine.GetTimeStep(TimeUnit::s);
  int count = (int)(sTime_s / dT_s);
  int ProgressStep = (int)(count*.1);
  int Progress = ProgressStep;
  if (track)
    tracker->SetupRequests();
  for (int i = 0; i <= count; i++)
  {
    if (m_Cancelled)
      break;
    // Instead of calling AdvanceModelTime
    // We should have a method called AdvanceToRestingState
    // and it will advance time, AND check to see if it is at a Resting state or not
    // if it is we can break our loop. This will allow us to record our stabilization data
    engine.AdvanceModelTime();

    m_currentTime_s += dT_s;
    if (m_currentTime_s == 0)
      tracker->SetupRequests();
    if (track)
      tracker->TrackData(m_currentTime_s);
    if (m_LogProgress)
    {
      statusTime_s += dT_s;
      if (statusTime_s>statusStep_s)
      {
        statusTime_s = 0;
        ss << "Current Time is " << m_currentTime_s << "s, it took "
          << profiler.GetElapsedTime_s("Status") << "s to simulate the past "
          << statusStep_s << "s" << std::flush;
        profiler.Reset("Status");
        Info(ss);
      }
      if (i>Progress)
      {
        Progress += ProgressStep;
        ss << "Initializing Engine : " << (double)i / count * 100 << "% Complete";
        Info(ss);
      }
    }
  }
  if (m_LogProgress)
  {
    ss << "It took " << profiler.GetElapsedTime_s("Total") << "s to get engine to stable state";
    Info(ss);
  }
  // Save off how long it took us to stabilize
  GetStabilizationDuration().SetValue(m_currentTime_s, TimeUnit::s);
  return true;
}

SETimedStabilization::SETimedStabilization(Logger *logger) : SEEngineStabilization(logger)
{
  m_FeedbackStabilizationTime = nullptr;
  GetStabilizationDuration().SetValue(0, TimeUnit::s);
}

SETimedStabilization::~SETimedStabilization()
{
  Clear();
}

void SETimedStabilization::Clear()
{
  SEEngineStabilization::Clear();
  m_RestingStabilizationTime.Invalidate();
  SAFE_DELETE(m_FeedbackStabilizationTime);
  DELETE_MAP_SECOND(m_ConditionTimes);
}

void SETimedStabilization::Load(const cdm::TimedStabilizationData& src, SETimedStabilization& dst)
{
  SETimedStabilization::Serialize(src, dst);
}
void SETimedStabilization::Serialize(const cdm::TimedStabilizationData& src, SETimedStabilization& dst)
{
  dst.Clear();
  dst.m_TrackingStabilization = src.trackingstabilization();
  if(src.has_restingstabilizationtime())
    SEScalarTime::Load(src.restingstabilizationtime(), dst.GetRestingStabilizationTime());
  if(src.has_feedbackstabilizationtime())
    SEScalarTime::Load(src.feedbackstabilizationtime(), dst.GetFeedbackStabilizationTime());
  for (auto itr : src.conditionstabilization())
  {
    SEScalarTime* time = new SEScalarTime();
    SEScalarTime::Load(itr.second, *time);
    dst.m_ConditionTimes[itr.first] = time;
  }
}

cdm::TimedStabilizationData* SETimedStabilization::Unload(const SETimedStabilization& src)
{
  cdm::TimedStabilizationData* dst(new cdm::TimedStabilizationData());
  SETimedStabilization::Serialize(src,*dst);
  return dst;
}
void SETimedStabilization::Serialize(const SETimedStabilization& src, cdm::TimedStabilizationData& dst)
{
  dst.set_trackingstabilization(src.m_TrackingStabilization);
  dst.set_allocated_restingstabilizationtime(SEScalarTime::Unload(src.m_RestingStabilizationTime));
  if (src.HasFeedbackStabilizationTime())
    dst.set_allocated_feedbackstabilizationtime(SEScalarTime::Unload(*src.m_FeedbackStabilizationTime));
  for (auto cc : src.m_ConditionTimes)
  {
    if (cc.second == nullptr)
      continue;
    cdm::ScalarTimeData* time = SEScalarTime::Unload(*cc.second);
    (*dst.mutable_conditionstabilization())[cc.first] = *time;
    delete time;
  }
}

bool SETimedStabilization::LoadFile(const std::string& file)
{
  try
  {
    Clear();
    std::ifstream input(file);
    std::string fmsg((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    cdm::TimedStabilizationData ts;
    if (!google::protobuf::TextFormat::ParseFromString(fmsg, &ts))
      return false;
    SETimedStabilization::Load(ts, *this);
    return true;
  }
  catch (std::exception ex)
  {
    Error("Unable to read file : " + file);
  }
  return false;
}

SEScalarTime& SETimedStabilization::GetRestingStabilizationTime()
{
  return m_RestingStabilizationTime;
}
double SETimedStabilization::GetRestingStabilizationTime(const TimeUnit& unit) const
{
  return m_RestingStabilizationTime.GetValue(unit);
}

bool SETimedStabilization::HasFeedbackStabilizationTime() const
{
  return m_FeedbackStabilizationTime == nullptr ? false : m_FeedbackStabilizationTime->IsValid();
}
SEScalarTime& SETimedStabilization::GetFeedbackStabilizationTime()
{
  if (m_FeedbackStabilizationTime == nullptr)
    m_FeedbackStabilizationTime = new SEScalarTime();
  return *m_FeedbackStabilizationTime;
}
double SETimedStabilization::GetFeedbackStabilizationTime(const TimeUnit& unit) const
{
  if (!HasFeedbackStabilizationTime())
    return SEScalar::dNaN();
  return m_FeedbackStabilizationTime->GetValue(unit);
}

bool SETimedStabilization::HasConditionTime(const std::string& name) const
{
  return m_ConditionTimes.find(name) != m_ConditionTimes.end();
}
void SETimedStabilization::RemoveConditionTime(const std::string& name)
{
  for (auto itr : m_ConditionTimes)
  {
    if (itr.first == name)
    {
      SAFE_DELETE(itr.second);
      m_ConditionTimes.erase(name);
      return;
    }
  }
}
SEScalarTime& SETimedStabilization::GetConditionTime(const std::string& name)
{
  for (auto itr : m_ConditionTimes)
  {
    if (itr.first == name)
      return (*itr.second);
  }
  SEScalarTime* time = new SEScalarTime();
  m_ConditionTimes[name]=time;
  return *time;
}
const SEScalarTime* SETimedStabilization::GetConditionTime(const std::string& name) const
{
  for (auto itr : m_ConditionTimes)
  {
    if (itr.first == name)
      return itr.second;
  }
  return nullptr;
}

const std::map<std::string,SEScalarTime*>& SETimedStabilization::GetConditionTimes() const
{
  return m_ConditionTimes;
}
