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

