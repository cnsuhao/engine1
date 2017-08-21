/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
CDM_BIND_DECL(DynamicStabilizationData)
#include "engine/SEEngineStabilization.h"
#include "engine/SEDynamicStabilizationEngineConvergence.h"

class CDM_DECL SEDynamicStabilization : public SEEngineStabilization
{
public:
  SEDynamicStabilization(Logger* logger);
  virtual ~SEDynamicStabilization();

  virtual void Clear();

  static void Load(const cdm::DynamicStabilizationData& src, SEDynamicStabilization& dst);
  static cdm::DynamicStabilizationData* Unload(const SEDynamicStabilization& src);
protected:
  static void Serialize(const cdm::DynamicStabilizationData& src, SEDynamicStabilization& dst);
  static void Serialize(const SEDynamicStabilization& src, cdm::DynamicStabilizationData& dst);

public:
  virtual bool LoadFile(const std::string& file);

  virtual bool StabilizeRestingState(PhysiologyEngine& engine);
  virtual bool StabilizeFeedbackState(PhysiologyEngine& engine);
  virtual bool StabilizeConditions(PhysiologyEngine& engine, const std::vector<const SECondition*>& conditions);

  virtual SEDynamicStabilizationEngineConvergence& GetRestingConvergence();
  virtual const SEDynamicStabilizationEngineConvergence& GetRestingConvergence() const;

  virtual bool HasFeedbackConvergence() const;
  virtual SEDynamicStabilizationEngineConvergence& GetFeedbackConvergence();
  virtual const SEDynamicStabilizationEngineConvergence* GetFeedbackConvergence() const;

  virtual bool HasConditionConvergence(const std::string& name) const;
  virtual void RemoveConditionConvergence(const std::string& name);
  virtual SEDynamicStabilizationEngineConvergence& GetConditionConvergence(const std::string& name);
  virtual const SEDynamicStabilizationEngineConvergence* GetConditionConvergence(const std::string& name) const;
  virtual const std::map<std::string, SEDynamicStabilizationEngineConvergence*>& GetConditionConvergence() const;

protected:

  virtual bool Stabilize(PhysiologyEngine& engine, const SEDynamicStabilizationEngineConvergence& criteria);

  SEDynamicStabilizationEngineConvergence  m_RestingConvergence;
  SEDynamicStabilizationEngineConvergence  m_FeedbackConvergence;
  std::map<std::string, SEDynamicStabilizationEngineConvergence*> m_ConditionConvergence;

  bool Merge();
  SEDynamicStabilizationEngineConvergence m_MergedConditions;
  std::map<std::string, SEDynamicStabilizationEngineConvergence*> m_ActiveConditions;
};

