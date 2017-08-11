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
#include "scenario/SEScenario.h"
#include "PulseConfiguration.h"

/**
* @brief A Pulse specific scenario (i.e. holds a %Pulse configuration object)
*/
class PULSE_DECL PulseScenario : public SEScenario
{
public:

  PulseScenario(SESubstanceManager& subMgr);
  virtual ~PulseScenario();

  virtual void Clear();


  bool LoadFile(const std::string& scenarioFile);
  bool Load(const std::string& str);

  static void Load(const pulse::ScenarioData& src, PulseScenario& dst);
  static pulse::ScenarioData* Unload(const PulseScenario& src);
protected:
  static void Serialize(const pulse::ScenarioData& src, PulseScenario& dst);
  static void Serialize(const PulseScenario& src, pulse::ScenarioData& dst);
  
public:
  virtual PulseConfiguration& GetConfiguration();
  virtual const PulseConfiguration* GetConfiguration() const;
  virtual bool HasConfiguration() const;
  virtual void InvalidateConfiguration();

protected:
  PulseConfiguration*         m_Configuration;
};