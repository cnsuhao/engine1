/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "CommonDataModel.h"

class CDM_DECL ScopedMutex
{
public:
  ScopedMutex();
    ~ScopedMutex();

    ScopedMutex(const ScopedMutex& other) = delete;
    ScopedMutex& operator=(const ScopedMutex& other) = delete;

    ScopedMutex(ScopedMutex&& other) = delete;
    ScopedMutex& operator=(ScopedMutex&& other) = delete;
};
