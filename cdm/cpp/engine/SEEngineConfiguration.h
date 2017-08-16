/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "CommonDataModel.h"

class CDM_DECL SEEngineConfiguration : public Loggable
{
public:
  SEEngineConfiguration(Logger* logger) : Loggable(logger) {}
  virtual ~SEEngineConfiguration() { }
};