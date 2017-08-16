/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "TaskProcessor.h"
#include "TaskQueue.h"

#include "Task.h"

//--------------------------------------------------------------------------------------------------
/// \brief
/// Constructor
///
/// \param  pTaskQueue  Pointer to the TaskQueue to draw Tasks from
//--------------------------------------------------------------------------------------------------
TaskProcessor::TaskProcessor(TaskQueue* pTaskQueue)
    : m_pTaskQueue(pTaskQueue)
{
}

//--------------------------------------------------------------------------------------------------
/// \brief
/// Parenthesis operator that draws and runs Tasks until the TaskQueue is empty
//--------------------------------------------------------------------------------------------------
void TaskProcessor::operator()()
{
    while (std::unique_ptr<Task> pTask = m_pTaskQueue->GetNextTask())
    {
        pTask->Run();
        m_pTaskQueue->ReportTaskComplete();
    }
}