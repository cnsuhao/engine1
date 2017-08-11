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
#include "Controller/Engine.h"
#include "scenario/SEScenarioExec.h"

/**
* @brief Overloaded scenario exector to run a %Pulse specific scenario
*/
class PULSE_DECL PulseScenarioExec : public SEScenarioExec
{
public:
  PulseScenarioExec(PulseEngine& engine);
  virtual ~PulseScenarioExec();

  virtual bool Execute(const std::string& scenarioFile, const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);
  virtual bool Execute(const SEScenario& scenario, const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);

protected:

  virtual bool ProcessActions(const SEScenario& scenario);
  virtual bool ProcessAction(const SEAction& action);
};