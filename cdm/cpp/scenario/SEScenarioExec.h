/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

class SEAction;
class SEScenario;
class PhysiologyEngine;
#include "engine/SEEngineConfiguration.h"

class CDM_DECL SEScenarioCustomExec
{
public:
  virtual void CustomExec(double time_s, PhysiologyEngine* engine)=0;
};

class CDM_DECL SEScenarioExec : public Loggable
{
public:
  SEScenarioExec(PhysiologyEngine& engine);
  virtual ~SEScenarioExec();

  virtual PhysiologyEngine& GetEngine(){ return m_Engine; }

  virtual void Cancel();

  virtual bool Execute(const std::string& scenarioFile, const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);
  virtual bool Execute(const SEScenario& scenario,      const std::string& resultsFile, SEScenarioCustomExec* cExec = nullptr);
  
protected:

  virtual bool ProcessActions(const SEScenario& scenario);
  /// This does not include advance time actions
  /// To override default functionality with those 
  /// actions override the ProcessActions method
  virtual bool ProcessAction(const SEAction& action);

  bool                         m_Cancel;
  SEScenarioCustomExec*        m_CustomExec;
  PhysiologyEngine&            m_Engine;
  const SEEngineConfiguration* m_EngineConfiguration;

  std::stringstream     m_ss;
};