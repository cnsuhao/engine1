/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "scenario/SEScenarioExec.h"
#include "scenario/SEAction.h"
#include "scenario/SECondition.h"
#include "scenario/SEScenario.h"
#include "scenario/SEScenarioInitialParameters.h"
#include "scenario/SEAdvanceTime.h"
#include "PhysiologyEngine.h"
#include "engine/SEEngineTracker.h"
#include "engine/SEEngineConfiguration.h"
#include "patient/SEPatient.h"
#include "properties/SEScalarTime.h"
#include "utils/TimingProfile.h"
#include "utils/FileUtils.h"

SEScenarioExec::SEScenarioExec(PhysiologyEngine& engine) : Loggable(engine.GetLogger()), m_Engine(engine)
{
  m_Cancel     = false;
  m_CustomExec = nullptr; 
  m_EngineConfiguration = nullptr;//Derived class will manage this pointer
}

SEScenarioExec::~SEScenarioExec()
{
  
}

bool SEScenarioExec::Execute(const std::string& scenarioFile, const std::string& resultsFile, SEScenarioCustomExec* cExec)
{
  try
  {
    m_ss << "Executing scenario file : " << scenarioFile << std::endl;
    Info(m_ss);
    m_Cancel = false;
    m_CustomExec = cExec;

    SEScenario scenario(m_Engine.GetSubstanceManager());
    try
    {
      scenario.LoadFile(scenarioFile);
    }
    catch (CommonDataModelException& ex)
    {
      Error("Error reading scenario file " + scenarioFile + " " + ex.what());
      return false;
    }
    std::string rFile = resultsFile;
    if (rFile.empty())
    {
      rFile = scenarioFile;
      rFile += ".out";
    }
    bool success = Execute(scenario, rFile, cExec);
    return success;
  }
  catch (CommonDataModelException& ex)
  {
    Error(ex.what());
  }
  catch (...)
  {
    Error("Caught unknown exception, ending simulation");
  }
  return false;
}

bool SEScenarioExec::Execute(const SEScenario& scenario, const std::string& resultsFile, SEScenarioCustomExec* cExec)
{
  if (!scenario.IsValid())
  {
    Error("Invalid Scenario");
    return false;
  }
  
  try
  {
    m_CustomExec = cExec;    
        
    // Initialize the engine with a state or initial parameters
    if (scenario.HasEngineStateFile())
    {
      m_Engine.LoadStateFile(scenario.GetEngineStateFile());
      // WE ARE OVERWRITING ANY DATA REQUESTS IN THE STATE WITH WHATS IN THE SCENARIO!!!
      // Make a copy of the data requests, note this clears out data requests from the engine
      cdm::DataRequestManagerData* drData = SEDataRequestManager::Unload(scenario.GetDataRequestManager());
      SEDataRequestManager::Load(*drData, m_Engine.GetEngineTracker()->GetDataRequestManager(), m_Engine.GetSubstanceManager());
      delete drData;
      if (!m_Engine.GetEngineTracker()->GetDataRequestManager().HasResultsFilename())
        m_Engine.GetEngineTracker()->GetDataRequestManager().SetResultsFilename(resultsFile);
    }
    else if (scenario.HasInitialParameters())
    {
      // Make a copy of the data requests, not this clears out data requests from the engine
      cdm::DataRequestManagerData* drData = SEDataRequestManager::Unload(scenario.GetDataRequestManager());
      SEDataRequestManager::Load(*drData, m_Engine.GetEngineTracker()->GetDataRequestManager(), m_Engine.GetSubstanceManager());
      delete drData;
      if (!m_Engine.GetEngineTracker()->GetDataRequestManager().HasResultsFilename())
        m_Engine.GetEngineTracker()->GetDataRequestManager().SetResultsFilename(resultsFile);

      const SEScenarioInitialParameters* params = scenario.GetInitialParameters();
      // Do we have any conditions
      std::vector<const SECondition*> conditions;
      for (SECondition* c : params->GetConditions())
        conditions.push_back(c);      

      if (params->HasPatientFile())
      {
        // Set up the patient
        std::string pFile = "./patients/";
        pFile += params->GetPatientFile();
        if (!m_Engine.InitializeEngine(pFile.c_str(), &conditions, m_EngineConfiguration))
        {
          Error("Unable to initialize engine");
          return false;
        }
      }
      else if (params->HasPatient())
      {
        if (!m_Engine.InitializeEngine(*params->GetPatient(), &conditions, m_EngineConfiguration))
        {
          Error("Unable to initialize engine");
          return false;
        }
      }
      else
      {
        Error("No patient provided");
        return false;
      }
    }
    else
    {
      Error("No initial engine parameters set");
      return false;
    }

    return ProcessActions(scenario);
  }
  catch (CommonDataModelException& ex)
  {
    Error(ex.what());
  }
  catch (std::exception& ex)
  {
    Error(ex.what());
  }
  catch (...)
  {
    Error("Caught unknown exception, ending simulation");
  }
  return false;
}

void SEScenarioExec::Cancel()
{
  m_Cancel=true;
}

bool SEScenarioExec::ProcessActions(const SEScenario& scenario)
{
  Info("Executing Scenario");

  double dT_s=m_Engine.GetTimeStep(TimeUnit::s);
  double scenarioTime_s;
  double statusTime_s = 0;// Current time of this status cycle
  double statusStep_s = 60;//How long did it take to simulate this much time

  double sampleTime_s = scenario.GetDataRequestManager().GetSamplesPerSecond();
  if (sampleTime_s != 0)
    sampleTime_s = 1 / sampleTime_s;
  double currentSampleTime_s = sampleTime_s;//Sample the first step

  TimingProfile profiler;
  profiler.Start("Total");
  profiler.Start("Status");

  m_Engine.GetEngineTracker()->SetupRequests();

  bool err=false;
  SEAdvanceTime* adv;
  for (SEAction* a : scenario.GetActions())
  {
    if(m_Cancel)
      break;
    // We override advance time actions in order to advance and 
    // pull requested data at each time step, all other actions 
    // will be processed by the engine
    adv=dynamic_cast<SEAdvanceTime*>(a);
    if(adv!=nullptr)
    {
      double time_s = adv->GetTime(TimeUnit::s);
      int count = (int)(time_s/dT_s);
      for(int i=0;i<=count;i++)
      {      
        if(m_Cancel)
          break;

        m_Engine.AdvanceModelTime();

        // Pull data from the engine
        scenarioTime_s = m_Engine.GetSimulationTime(TimeUnit::s);
        currentSampleTime_s += dT_s;
        if (currentSampleTime_s >= sampleTime_s)
        {
          currentSampleTime_s = 0;
          m_Engine.GetEngineTracker()->TrackData(scenarioTime_s);
        }       
        // Call any custom callback provided
        if (m_CustomExec!=nullptr)
          m_CustomExec->CustomExec(scenarioTime_s, &m_Engine);
        statusTime_s += dT_s;
        // How are we running?
        if (statusTime_s>statusStep_s)
        {
          statusTime_s = 0;
          m_ss << "Current Time is " << scenarioTime_s << "s, it took " << profiler.GetElapsedTime_s("Status") << "s to simulate the past " << statusStep_s << "s" << std::flush;
          profiler.Reset("Status");
          Info(m_ss);
        }
        if(m_Engine.GetPatient().IsEventActive(cdm::PatientData_eEvent_IrreversibleState))
          return false;// Patient is for all intents and purposes dead, or out at least out of its methodology bounds, quit running
      }
      continue;
    }

    if(!ProcessAction(*a))
    {
      err=true;
      break;
    }
    if(m_Engine.GetPatient().IsEventActive(cdm::PatientData_eEvent_IrreversibleState))
      return false;// Patient is for all intents and purposes dead, or out at least out of its methodology bounds, quit running
  }
  m_ss << "It took " << profiler.GetElapsedTime_s("Total") << "s to run this simulation";
  profiler.Clear();
    Info(m_ss);

  return !err;
}

bool SEScenarioExec::ProcessAction(const SEAction& action)
{
  return m_Engine.ProcessAction(action);
}
