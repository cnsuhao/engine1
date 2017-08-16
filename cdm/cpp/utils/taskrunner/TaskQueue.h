/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "Task.h"
#include <memory>

//--------------------------------------------------------------------------------------------------
/// \brief
/// Interface through which TaskProcessors retrieve Tasks from the TaskRunner
//--------------------------------------------------------------------------------------------------
class TaskQueue
{
public:
    virtual std::unique_ptr<Task> GetNextTask() = 0;
    virtual void ReportTaskComplete() = 0;
};