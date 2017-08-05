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
#include "engine/SEEngineConfiguration.h"
#include <google/protobuf/text_format.h>

SEEngineConfiguration::SEEngineConfiguration(Logger* logger) : Loggable(logger)
{
  m_Merge = false;
  m_TimeStep = nullptr;
  m_TimedStabilization = nullptr;
  m_DynamicStabilization = nullptr;
}

SEEngineConfiguration::~SEEngineConfiguration()
{
  Clear();
}

void SEEngineConfiguration::Clear()
{
  SAFE_DELETE(m_TimeStep);
  RemoveStabilization();
}

void SEEngineConfiguration::Merge(const SEEngineConfiguration& from)
{
  m_Merge = true;
  cdm::EngineConfigurationData* data = SEEngineConfiguration::Unload(from);
  SEEngineConfiguration::Load(*data, *this);
  delete data;
  m_Merge = false;
}

bool SEEngineConfiguration::LoadFile(const std::string& file)
{
  try
  {
    Clear();
    std::ifstream input(file);
    std::string fmsg((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    cdm::EngineConfigurationData c;
    if (!google::protobuf::TextFormat::ParseFromString(fmsg, &c))
      return false;
    SEEngineConfiguration::Load(c, *this);
    return true;
  }
  catch (std::exception ex)
  {
    Error("Unable to read file : " + file);
  }
  return false;
}

void SEEngineConfiguration::Load(const cdm::EngineConfigurationData& src, SEEngineConfiguration& dst)
{
  SEEngineConfiguration::Serialize(src, dst);
}
void SEEngineConfiguration::Serialize(const cdm::EngineConfigurationData& src, SEEngineConfiguration& dst)
{
  if (!dst.m_Merge)
    dst.Clear();// Reset only if we are not merging

  if (src.has_timestep())
    SEScalarTime::Load(src.timestep(), dst.GetTimeStep());
  if (src.has_timedstabilization())
    SETimedStabilization::Load(src.timedstabilization(), dst.GetTimedStabilization());
  else if (src.has_dynamicstabilization())
    SEDynamicStabilization::Load(src.dynamicstabilization(), dst.GetDynamicStabilization());
  else if (!src.stabilizationfilename().empty())
  {
    if (!dst.GetTimedStabilization().LoadFile(src.stabilizationfilename()))
      if (!dst.GetDynamicStabilization().LoadFile(src.stabilizationfilename()))
      {
        dst.Error("Unable to load stabilization file");
        dst.RemoveStabilization();
      }
  }
  if (src.has_customconfig())
    dst.LoadCustomConfig(src.customconfig());
}

cdm::EngineConfigurationData* SEEngineConfiguration::Unload(const SEEngineConfiguration& src)
{
  cdm::EngineConfigurationData* dst =new cdm::EngineConfigurationData();
  SEEngineConfiguration::Serialize(src,*dst);
  return dst;
}
void SEEngineConfiguration::Serialize(const SEEngineConfiguration& src, cdm::EngineConfigurationData& dst)
{
  if (src.HasTimedStabilization())
    dst.set_allocated_timedstabilization(SETimedStabilization::Unload(*src.m_TimedStabilization));
  else if (src.HasDynamicStabilization())
    dst.set_allocated_dynamicstabilization(SEDynamicStabilization::Unload(*src.m_DynamicStabilization));
  if (src.HasTimeStep())
    dst.set_allocated_timestep(SEScalarTime::Unload(*src.m_TimeStep));
  dst.set_allocated_customconfig(src.UnloadCustomConfig());
}

bool SEEngineConfiguration::HasTimeStep() const
{
  return m_TimeStep == nullptr ? false : m_TimeStep->IsValid();
}
SEScalarTime& SEEngineConfiguration::GetTimeStep()
{
  if (m_TimeStep == nullptr)
    m_TimeStep = new SEScalarTime();
  return *m_TimeStep;
}
double SEEngineConfiguration::GetTimeStep(const TimeUnit& unit) const
{
  if (m_TimeStep == nullptr)
    return SEScalar::dNaN();
  return m_TimeStep->GetValue(unit);
}

bool SEEngineConfiguration::HasStabilization() const
{
  return m_TimedStabilization != nullptr || m_DynamicStabilization != nullptr;
}
SEEngineStabilization* SEEngineConfiguration::GetStabilization()
{
  if (m_TimedStabilization != nullptr)
    return m_TimedStabilization;
  if (m_DynamicStabilization != nullptr)
    return m_DynamicStabilization;
  return nullptr;
}
void SEEngineConfiguration::RemoveStabilization()
{
  SAFE_DELETE(m_TimedStabilization);
  SAFE_DELETE(m_DynamicStabilization);
}
bool SEEngineConfiguration::HasTimedStabilization() const
{
  return m_TimedStabilization != nullptr;
}
SETimedStabilization& SEEngineConfiguration::GetTimedStabilization()
{
  RemoveDynamicStabilization();
  if (m_TimedStabilization == nullptr)
    m_TimedStabilization = new SETimedStabilization(GetLogger());
  return *m_TimedStabilization;
}
const SETimedStabilization* SEEngineConfiguration::GetTimedStabilization() const
{
  return m_TimedStabilization;
}
void SEEngineConfiguration::RemoveTimedStabilization()
{
  SAFE_DELETE(m_TimedStabilization);
}
bool SEEngineConfiguration::HasDynamicStabilization() const
{
  return m_DynamicStabilization != nullptr;
}
SEDynamicStabilization& SEEngineConfiguration::GetDynamicStabilization()
{
  RemoveTimedStabilization();
  if (m_DynamicStabilization == nullptr)
    m_DynamicStabilization = new SEDynamicStabilization(GetLogger());
  return *m_DynamicStabilization;
}
const SEDynamicStabilization* SEEngineConfiguration::GetDynamicStabilization() const
{
  return m_DynamicStabilization;
}
void SEEngineConfiguration::RemoveDynamicStabilization()
{
  SAFE_DELETE(m_DynamicStabilization);
}
