/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

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
