/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "TaskQueue.h"

#include "CommonDataModel.h"

#include <queue>
#include <memory>
#include <mutex>

//--------------------------------------------------------------------------------------------------
/// \brief
/// This class handles concurrent execution of tasks
//--------------------------------------------------------------------------------------------------
class CDM_DECL TaskRunner : public TaskQueue
{
public:
    TaskRunner();
    TaskRunner(unsigned int threadCount);
    virtual ~TaskRunner() = default;

    TaskRunner(const TaskRunner& other) = delete;
    TaskRunner& operator=(const TaskRunner& other) = delete;

    void AddTask(std::unique_ptr<Task> task);
    void Run();

    virtual std::unique_ptr<Task> GetNextTask() override;

    void EchoProgress(bool echo) { m_echoPercentComplete = echo; }
    virtual void ReportTaskComplete() override;

protected:
    void PrintProgress();

    mutable std::recursive_mutex m_taskQueueMutex;  ///< Mutex used to synchronize concurrent access to the task queue
    std::queue<std::unique_ptr<Task>> m_tasks;      ///< Queue of tasks to be run

    unsigned int m_threadCount = 1;                 ///< The number of threads to spawn when running tasks

    bool m_echoPercentComplete = false;             ///< Whether or not the task runner should output percent complete as it executes
    size_t m_totalTaskCount = 0;                    ///< Total number of tasks in the queue when the task running begins to execute
    unsigned int m_tasksComplete = 0;               ///< Number of completed tasks
};
