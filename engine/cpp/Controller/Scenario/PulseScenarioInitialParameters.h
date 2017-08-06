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

#include "Controller/PulseConfiguration.h"
#include "scenario/SEScenarioInitialParameters.h"
class PulseScenario;

/**
* @brief Overloaded scenario that creates a %Pulse configuration as its configuration object
*/
class PULSE_API PulseScenarioInitialParameters : public SEScenarioInitialParameters
{
protected:
  friend PulseScenario;

  PulseScenarioInitialParameters(SESubstanceManager& subMgr);
  virtual ~PulseScenarioInitialParameters();

  virtual PulseConfiguration& GetConfiguration();
  virtual const PulseConfiguration* GetConfiguration() const;
  virtual void SetConfiguration(const PulseConfiguration& config);
protected:
};