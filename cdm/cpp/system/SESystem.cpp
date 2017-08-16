/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/SESystem.h"

SESystem::SESystem(Logger* logger) : Loggable(logger)
{
  
}

SESystem::~SESystem()
{
  Clear();
}

void SESystem::Clear()
{

}

const SEScalar* SESystem::GetScalar(const std::string& name, std::vector<SESystem*>* systems)
{
  const SEScalar* s;
  for (auto itr = systems->begin(); itr != systems->end(); itr++)
  {
    if (*itr == nullptr)
      continue;
    s = (*itr)->GetScalar(name);
    if (s != nullptr)
      return s;
  }  
  return nullptr;
}




