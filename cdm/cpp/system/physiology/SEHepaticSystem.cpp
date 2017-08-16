/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/physiology/SEHepaticSystem.h"

SEHepaticSystem::SEHepaticSystem(Logger* logger) : SESystem(logger)
{
  
}

SEHepaticSystem::~SEHepaticSystem()
{
  Clear();
}

void SEHepaticSystem::Clear()
{
  SESystem::Clear();

}

const SEScalar* SEHepaticSystem::GetScalar(const std::string& name)
{
  return nullptr;
}

void SEHepaticSystem::Load(const cdm::HepaticSystemData& src, SEHepaticSystem& dst)
{
  SEHepaticSystem::Serialize(src, dst);
}
void SEHepaticSystem::Serialize(const cdm::HepaticSystemData& src, SEHepaticSystem& dst)
{
  dst.Clear();
  
}

cdm::HepaticSystemData* SEHepaticSystem::Unload(const SEHepaticSystem& src)
{
  cdm::HepaticSystemData* dst = new cdm::HepaticSystemData();
  SEHepaticSystem::Serialize(src, *dst);
  return dst;
}
void SEHepaticSystem::Serialize(const SEHepaticSystem& src, cdm::HepaticSystemData& dst)
{
  
}
