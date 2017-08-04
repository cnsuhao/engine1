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
#include "scenario/SEScenarioAutoSerialization.h"
#include "properties/SEScalarTime.h"

SEScenarioAutoSerialization::SEScenarioAutoSerialization(Logger* logger) : Loggable(logger)
{
  m_Period = nullptr;
  m_PeriodTimeStamps = (cdm::eSwitch)-1;
  m_AfterActions = (cdm::eSwitch)-1;
  m_ReloadState  = (cdm::eSwitch)-1;
  m_Directory    = "";
  m_FileName     = "";
}

SEScenarioAutoSerialization::~SEScenarioAutoSerialization()
{
  Clear();
}

void SEScenarioAutoSerialization::Clear()
{
  SAFE_DELETE(m_Period);
  m_PeriodTimeStamps = (cdm::eSwitch)-1;
  m_AfterActions = (cdm::eSwitch)-1;
  m_AfterActions = (cdm::eSwitch)-1;
  m_Directory = "";
  m_FileName = "";
}

bool SEScenarioAutoSerialization::IsValid() const
{
  if (!HasPeriod())
    return false;
  if (m_Period->IsNegative())
    return false;
  if (!HasPeriodTimeStamps())
    return false;
  if (!HasAfterActions())
    return false;
  if (!HasReloadState())
    return false;
  if (!HasDirectory())
    return false;
  if (!HasFileName())
    return false;
  return true;
}

void SEScenarioAutoSerialization::Load(const cdm::ScenarioData_AutoSerializationData& src, SEScenarioAutoSerialization& dst)
{
  SEScenarioAutoSerialization::Serialize(src, dst);
}
void SEScenarioAutoSerialization::Serialize(const cdm::ScenarioData_AutoSerializationData& src, SEScenarioAutoSerialization& dst)
{
  dst.Clear();
  if (src.has_period())
    SEScalarTime::Load(src.period(), dst.GetPeriod());
  dst.SetPeriodTimeStamps(src.periodtimestamps());
  dst.SetAfterActions(src.afteractions());
  dst.SetReloadState(src.reloadstate());
  dst.SetDirectory(src.directory());
  dst.SetFileName(src.filename());
}

cdm::ScenarioData_AutoSerializationData* SEScenarioAutoSerialization::Unload(const SEScenarioAutoSerialization& src)
{
  cdm::ScenarioData_AutoSerializationData *dst = new cdm::ScenarioData_AutoSerializationData();
  SEScenarioAutoSerialization::Serialize(src,*dst);
  return dst;
}
void SEScenarioAutoSerialization::Serialize(const SEScenarioAutoSerialization& src, cdm::ScenarioData_AutoSerializationData& dst)
{
  if (src.HasPeriod())
    dst.set_allocated_period(SEScalarTime::Unload(*src.m_Period));
  if (src.HasPeriodTimeStamps())
    dst.set_periodtimestamps(src.m_PeriodTimeStamps);
  if (src.HasAfterActions())
    dst.set_afteractions(src.m_AfterActions);
  if (src.HasReloadState())
    dst.set_reloadstate(src.m_ReloadState);
  if (src.HasDirectory())
    dst.set_directory(src.m_Directory);
  if (src.HasFileName())
    dst.set_filename(src.m_FileName);
}

bool SEScenarioAutoSerialization::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEScenarioAutoSerialization::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}
double SEScenarioAutoSerialization::GetPeriod(const TimeUnit& unit) const
{
  if (m_Period == nullptr)
    return SEScalar::dNaN();
  return m_Period->GetValue(unit);
}

cdm::eSwitch SEScenarioAutoSerialization::GetPeriodTimeStamps() const
{
  return m_PeriodTimeStamps;
}
void SEScenarioAutoSerialization::SetPeriodTimeStamps(cdm::eSwitch v)
{
  m_PeriodTimeStamps = v;
}
bool SEScenarioAutoSerialization::HasPeriodTimeStamps() const
{
  return m_PeriodTimeStamps == ((cdm::eSwitch)-1) ? false : true;
}
void SEScenarioAutoSerialization::InvalidatePeriodTimeStamps()
{
  m_PeriodTimeStamps = (cdm::eSwitch)-1;
}

cdm::eSwitch SEScenarioAutoSerialization::GetAfterActions() const
{
  return m_AfterActions;
}
void SEScenarioAutoSerialization::SetAfterActions(cdm::eSwitch v)
{
  m_AfterActions = v;
}
bool SEScenarioAutoSerialization::HasAfterActions() const
{
  return m_AfterActions == ((cdm::eSwitch) - 1) ? false : true;
}
void SEScenarioAutoSerialization::InvalidateAfterActions()
{
  m_AfterActions = (cdm::eSwitch) - 1;
}

cdm::eSwitch SEScenarioAutoSerialization::GetReloadState() const
{
  return m_ReloadState;
}
void SEScenarioAutoSerialization::SetReloadState(cdm::eSwitch v)
{
  m_ReloadState = v;
}
bool SEScenarioAutoSerialization::HasReloadState() const
{
  return m_ReloadState == ((cdm::eSwitch) - 1) ? false : true;
}
void SEScenarioAutoSerialization::InvalidateReloadState()
{
  m_ReloadState = (cdm::eSwitch) - 1;
}

std::string SEScenarioAutoSerialization::GetDirectory() const
{
  return m_Directory;
}
void SEScenarioAutoSerialization::SetDirectory(const std::string& dir)
{
  m_Directory = dir;
}
bool SEScenarioAutoSerialization::HasDirectory() const
{
  return m_Directory.empty() ? false : true;
}
void SEScenarioAutoSerialization::InvalidateDirectory()
{
  m_Directory = "";
}

std::string SEScenarioAutoSerialization::GetFileName() const
{
  return m_FileName;
}
void SEScenarioAutoSerialization::SetFileName(const std::string& name)
{
  m_FileName = name;
}
bool SEScenarioAutoSerialization::HasFileName() const
{
  return m_FileName.empty() ? false : true;
}
void SEScenarioAutoSerialization::InvalidateFileName()
{
  m_FileName = "";
}