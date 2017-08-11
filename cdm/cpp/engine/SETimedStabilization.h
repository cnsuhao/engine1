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

#pragma once
CDM_BIND_DECL(TimedStabilizationData)
#include "engine/SEEngineStabilization.h"
#include "properties/SEScalarTime.h"

class CDM_DECL SETimedStabilization : public SEEngineStabilization
{
public:
  SETimedStabilization(Logger* logger);
  virtual ~SETimedStabilization();

  virtual void Clear();

  static void Load(const cdm::TimedStabilizationData& src, SETimedStabilization& dst);
  static cdm::TimedStabilizationData* Unload(const SETimedStabilization& src);
protected:
  static void Serialize(const cdm::TimedStabilizationData& src, SETimedStabilization& dst);
  static void Serialize(const SETimedStabilization& src, cdm::TimedStabilizationData& dst);

public:

  virtual bool LoadFile(const std::string& file);

  virtual bool StabilizeRestingState(PhysiologyEngine& engine);
  virtual bool StabilizeFeedbackState(PhysiologyEngine& engine);
  virtual bool StabilizeConditions(PhysiologyEngine& engine, const std::vector<const SECondition*>& conditions);

  virtual SEScalarTime& GetRestingStabilizationTime();
  virtual double GetRestingStabilizationTime(const TimeUnit& unit) const;

  virtual bool HasFeedbackStabilizationTime() const;
  virtual SEScalarTime& GetFeedbackStabilizationTime();
  virtual double GetFeedbackStabilizationTime(const TimeUnit& unit) const;

  virtual bool HasConditionTime(const std::string& name) const;
  virtual void RemoveConditionTime(const std::string& name);
  virtual const std::map<std::string,SEScalarTime*>& GetConditionTimes() const;
  virtual SEScalarTime& GetConditionTime(const std::string& name);
  virtual const SEScalarTime* GetConditionTime(const std::string& name) const;

protected:

  virtual bool Stabilize(PhysiologyEngine& engine, const SEScalarTime& time);

  SEScalarTime m_RestingStabilizationTime;
  SEScalarTime* m_FeedbackStabilizationTime;
  std::map<std::string,SEScalarTime*> m_ConditionTimes;
};
