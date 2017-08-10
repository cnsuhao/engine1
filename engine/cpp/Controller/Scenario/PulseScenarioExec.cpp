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

#include "stdafx.h"
#include "engine/SEAutoSerialization.h"
#include "Controller/PulseConfiguration.h"
#include "Controller/Scenario/PulseScenarioExec.h"
#include "Controller/Scenario/PulseScenario.h"
#include "utils/FileUtils.h"

PulseScenarioExec::PulseScenarioExec(PulseEngine& engine) : SEScenarioExec(engine)
{
  m_EngineConfiguration = engine.GetConfiguration();
}

PulseScenarioExec::~PulseScenarioExec()
{
  
}

bool PulseScenarioExec::Execute(const SEScenario& scenario, const std::string& resultsFile, SEScenarioCustomExec* cExec)
{
  try
  {    
    bool success = SEScenarioExec::Execute(scenario, resultsFile, cExec);
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

bool PulseScenarioExec::Execute(const std::string& scenarioFile, const std::string& resultsFile, SEScenarioCustomExec* cExec)
{
  try
  {
    m_ss << "Executing scenario file : " << scenarioFile << std::endl;
    Info(m_ss);
    m_Cancel = false;
    m_CustomExec = cExec;

    PulseScenario scenario(m_Engine.GetSubstanceManager());
    if (!scenario.LoadFile(scenarioFile))
    {
        Error("Unable to load scenario file : " + scenarioFile);
        return false;
    }
    std::string rFile = resultsFile;
    if (rFile.empty())
    {
      rFile = scenarioFile;
      rFile += ".txt";
    }
    // If any configuration parameters were provided, use them over what we had
    if (scenario.HasConfiguration())
      m_EngineConfiguration = &scenario.GetConfiguration();
    //if (m_PulseConfiguration->HasAutoSerialization())
    //  CreateFilePath(m_PulseConfiguration->GetAutoSerialization()->GetDirectory());// Note method assumes you have a file and it ignores it
    bool success = SEScenarioExec::Execute(scenario, rFile, cExec);
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

bool PulseScenarioExec::ProcessActions(const SEScenario& scenario)
{
  //// Auto serialization
  //bool serializeAction = false;
  //double serializationTime_s = 0;
  //double serializationPeriod_s = 0;
  //std::string actionName;
  //std::string serializationFileNameBase;
  //std::stringstream serializationFileName;
  //const SEScenarioAutoSerialization* serialization = scenario.GetAutoSerialization();
  //if (serialization != nullptr)
  //{
  //  if (!serialization->IsValid())
  //    serialization = nullptr;//ignore it
  //  else
  //  {
  //    serializationFileNameBase = serialization->GetFileName();
  //    // Strip off the pba if it's there
  //    size_t split = serializationFileNameBase.find(".pba");
  //    if (split != serializationFileNameBase.npos)
  //      serializationFileNameBase = serializationFileNameBase.substr(0, split);

  //    serializationPeriod_s = serialization->GetPeriod(TimeUnit::s);
  //    serializationFileName << serialization->GetDirectory() << "/" << serializationFileNameBase;
  //    serializationFileNameBase = serializationFileName.str();
  //  }
  //}
  return SEScenarioExec::ProcessActions(scenario);
}


bool PulseScenarioExec::ProcessAction(const SEAction& action)
{
  //if (serialization != nullptr)
  //{// Auto Serialize
  //  if (serializationPeriod_s > 0)
  //  {
  //    serializationTime_s += dT_s;
  //    if (serializationTime_s > serializationPeriod_s)
  //    {
  //      serializationTime_s = 0;
  //      serializationFileName.str("");
  //      serializationFileName << serializationFileNameBase;
  //      if (serialization->GetPeriodTimeStamps() == cdm::eSwitch::On)
  //        serializationFileName << "@" << m_Engine.GetSimulationTime(TimeUnit::s);
  //      serializationFileName << ".pba";
  //      std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str()));
  //      if (serialization->GetReloadState() == cdm::eSwitch::On)
  //      {
  //        m_Engine.LoadState(*state);
  //        std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str() + ".Reloaded.pba"));
  //      }
  //    }
  //  }
  //  if (serializeAction)
  //  {
  //    serializeAction = false;
  //    serializationFileName.str("");
  //    serializationFileName << serializationFileNameBase << "-" << actionName << "-@" << m_Engine.GetSimulationTime(TimeUnit::s) << ".pba";
  //    std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str()));
  //    if (serialization->GetReloadState() == cdm::eSwitch::On)
  //    {
  //      m_Engine.LoadState(*state);
  //      std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str() + ".Reloaded.pba"));
  //    }
  //  }
  //}
  return SEScenarioExec::ProcessAction(action);
  //if (serialization != nullptr && serialization->GetAfterActions() == cdm::eSwitch::On)
  //{// If we are testing force serialization after any action with this
  // // Pull out the action type/name for file naming
  //  m_ss << *a;
  //  size_t start = m_ss.str().find(": ") + 2;
  //  size_t end = m_ss.str().find('\n');
  //  actionName = m_ss.str().substr(start, end - start);
  //  m_ss.str("");

  //  serializationFileName.str("");
  //  serializationFileName << serializationFileNameBase << "-" << actionName << "-@" << m_Engine.GetSimulationTime(TimeUnit::s) << ".pba";
  //  std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str()));
  //  if (serialization->GetReloadState() == cdm::eSwitch::On)
  //  {
  //    m_Engine.LoadState(*state);
  //    std::unique_ptr<google::protobuf::Message> state(m_Engine.SaveState(serializationFileName.str() + ".Reloaded.pba"));
  //  }
  //  serializeAction = true;// Serialize after the next time step
  //}
}
