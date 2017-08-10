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
#include "engine/SEEngineTracker.h"
#include "engine/SEDynamicStabilizationPropertyConvergence.h"
#include "properties/SEScalarTime.h"
#include "bind/cdm/Engine.pb.h"

class CDM_DECL SEDynamicStabilizationEngineConvergence : public Loggable
{
  friend class SEDynamicStabilization;
protected:
  SEDynamicStabilizationEngineConvergence(Logger* logger);

public:
  virtual ~SEDynamicStabilizationEngineConvergence();

  virtual void Clear();

  static void Load(const cdm::DynamicStabilizationData_EngineConvergenceData& src, SEDynamicStabilizationEngineConvergence& dst);
  static cdm::DynamicStabilizationData_EngineConvergenceData* Unload(const SEDynamicStabilizationEngineConvergence& src);
protected:
  static void Serialize(const cdm::DynamicStabilizationData_EngineConvergenceData& src, SEDynamicStabilizationEngineConvergence& dst);
  static void Serialize(const SEDynamicStabilizationEngineConvergence& src, cdm::DynamicStabilizationData_EngineConvergenceData& dst);

public:

  virtual SEScalarTime& GetConvergenceTime() { return m_ConvergenceTime; }
  virtual double GetConvergenceTime(const TimeUnit& unit) const { return m_ConvergenceTime.GetValue(unit); }

  virtual SEScalarTime& GetMinimumReactionTime() { return m_MinimumReactionTime; }
  virtual double GetMinimumReactionTime(const TimeUnit& unit) const { return m_MinimumReactionTime.GetValue(unit); }

  virtual SEScalarTime& GetMaximumAllowedStabilizationTime() { return m_MaximumAllowedStabilizationTime; }
  virtual double GetMaximumAllowedStabilizationTime(const TimeUnit& unit) const { return m_MaximumAllowedStabilizationTime.GetValue(unit); }

  virtual const std::vector<SEDynamicStabilizationPropertyConvergence*>& GetPropertyConvergence() const;
  virtual SEDynamicStabilizationPropertyConvergence& CreatePropertyConvergence(SEDataRequest& dr, double percentError);

protected:
  SEScalarTime                                            m_ConvergenceTime;
  SEScalarTime                                            m_MinimumReactionTime;
  SEScalarTime                                            m_MaximumAllowedStabilizationTime;

  SEDataRequestManager                                    m_DataRequestMgr;
  std::vector<SEDynamicStabilizationPropertyConvergence*> m_PropertyConvergence;
};

