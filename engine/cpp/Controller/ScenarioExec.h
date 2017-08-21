/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/Engine.h"
#include "scenario/SEScenarioExec.h"
class PulseScenario;

/**
* @brief Overloaded scenario exector to run a %Pulse specific scenario
*/
class PULSE_DECL PulseScenarioExec : public SEScenarioExec
{
public:
  PulseScenarioExec(PulseEngine& engine);
  virtual ~PulseScenarioExec();

  virtual bool Execute(const std::string& scenarioFile, const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);
  virtual bool Execute(const PulseScenario& scenario, const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);

protected:

  virtual bool ProcessActions(const SEScenario& scenario);
  virtual bool ProcessAction(const SEAction& action);
};