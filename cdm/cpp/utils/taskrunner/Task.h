/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

//--------------------------------------------------------------------------------------------------
/// \brief
/// Interface from which tasks used in the TaskRunner should derive
//--------------------------------------------------------------------------------------------------
class Task
{
public:
    virtual void Run() = 0;
};