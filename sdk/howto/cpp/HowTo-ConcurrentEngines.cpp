/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "EngineHowTo.h"

// Include the various types you will be using in your code
#include "utils/FileUtils.h"
#include "utils/TaskRunner/TaskRunner.h"

#include "scenario/SEScenarioExec.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// This class derives from Task and implements Run() so it can be used in the TaskRunner.  When run,
/// this class creates a Pulse engine and runs a scenario.
//--------------------------------------------------------------------------------------------------
class RunScenarioTask : public Task
{
public:
    static std::mutex ms_constructionMutex;

    RunScenarioTask(const std::string& scenarioFile)
          :  m_scenarioFile(scenarioFile)
    {
    }

    virtual void Run() override;

private:
    std::string m_scenarioFile;     ///< The scenario file to run when this task is executed
};

std::mutex RunScenarioTask::ms_constructionMutex;

//--------------------------------------------------------------------------------------------------
/// \brief
/// This function is called when the task is executed, it creates a PulseEngine and executes the scenario
//--------------------------------------------------------------------------------------------------
void RunScenarioTask::Run()
{
  // Set up the log file
  std::string logFile = m_scenarioFile;
  logFile = Replace(logFile, "verification", "");
  logFile = Replace(logFile, ".pba", ".log");

  // Set up the verification output file
  std::string dataFile = m_scenarioFile;
  dataFile = Replace(dataFile, "verification", "");
  dataFile = Replace(dataFile, ".pba", "Results.txt");

  // Delete any results file that may be there
  remove(dataFile.c_str());

  // Aquire the constrution mutex before we create the PulseEngine.  Due to some third-party library
  // initialization constructs not being thread safe, we must not construct PulseEngines simultaneously
  // from multiple threads.
  ms_constructionMutex.lock();
  std::unique_ptr<PhysiologyEngine> pe = CreatePulseEngine(logFile.c_str());
  ms_constructionMutex.unlock();
        
  if (!pe)
  {
    std::cerr << "Unable to create PulseEngine\n";
    return;
  }

  // Run the scenario
  SEScenarioExec exec(*pe);
  exec.Execute(m_scenarioFile.c_str(), dataFile.c_str(), nullptr);
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Usage for running concurrent engines
//--------------------------------------------------------------------------------------------------
void HowToConcurrentEngines() 
{
    // Create the task runner, this is the object that will handle running tasks in parallel.
    // By default it attempts to determine the number of cores on the system and creates a thread
    // per core.  If it cannot determine this value, it reverts to single-threaded mode.  Override
    // the thread count by specifying the desired number of threads in the constructor.
    TaskRunner runner;

    // Create tasks to be run and give them to the task runner
    runner.AddTask(std::unique_ptr<RunScenarioTask>(new RunScenarioTask("verification/Scenarios/Patient/BasicStandard.pba")));
    runner.AddTask(std::unique_ptr<RunScenarioTask>(new RunScenarioTask("verification/Scenarios/Patient/BasicStandard.pba")));
    runner.AddTask(std::unique_ptr<RunScenarioTask>(new RunScenarioTask("verification/Scenarios/Patient/BasicStandard.pba")));

    // Run the tasks.  This will launch the desired number of threads which will pull and execute tasks
    // until there are none left.  Run() blocks until all task threads are finished executing.
    runner.Run();
}