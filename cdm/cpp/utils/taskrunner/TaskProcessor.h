/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include <vector>

class Task;
class TaskQueue;

//--------------------------------------------------------------------------------------------------
/// \brief
/// This class is a functor used in threads launched by the TaskRunner.  It's responsibility is to
/// pull and run Tasks from the TaskRunner until the Task queue is empty.
//--------------------------------------------------------------------------------------------------
class TaskProcessor
{
public:
    TaskProcessor(TaskQueue* pTaskQueue);
    ~TaskProcessor() = default;

    void operator()();

protected:
    TaskQueue* m_pTaskQueue = nullptr;  ///< Pointer to the TaskQueue to draw Tasks from
};
