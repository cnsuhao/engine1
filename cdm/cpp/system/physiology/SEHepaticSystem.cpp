/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

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
