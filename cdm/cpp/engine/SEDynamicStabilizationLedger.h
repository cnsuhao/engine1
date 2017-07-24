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
#include "engine/SEDynamicStabilizationEngineConvergence.h"

// Book keeping class that tracks all the properties and if their convergent state
class DLL_DECL SEDynamicStabilizationLedger : public Loggable
{
public:
  SEDynamicStabilizationLedger(double timeStep_s, const SEDynamicStabilizationEngineConvergence& convergence);
  virtual ~SEDynamicStabilizationLedger() {};

  virtual void TestConvergence();
  virtual bool HasConverged() { return m_converged; }
  virtual bool HasConvergedOptional() { return m_convergedOptional; }
  virtual bool HasExceededTime() { return m_exceededTime; }

protected:

  bool   m_converged;
  bool   m_convergedOptional;
  bool   m_exceededTime;
  bool   m_hasOptionalProperties;
  double m_dT_s;
  double m_totTime_s;// Total time we have been converging
  double m_covTime_s;// Convergence Window Length
  double m_minTime_s;// Minimum amount of time to run before testing
  double m_maxTime_s;// Maximum amount of time to run before we quit
  double m_passTime_s;
  double m_optsPassTime_s;

  const std::vector<SEDynamicStabilizationPropertyConvergence*>& m_properties;
};