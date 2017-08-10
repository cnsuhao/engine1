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
#include "engine/SEAutoSerialization.h"
#include "properties/SEScalarTime.h"

SEAutoSerialization::SEAutoSerialization(Logger* logger) : Loggable(logger)
{
  m_Period = nullptr;
  m_PeriodTimeStamps = cdm::eSwitch::Off;
  m_AfterActions = cdm::eSwitch::Off;
  m_ReloadState  = cdm::eSwitch::Off;
  m_Directory    = "";
  m_FileName     = "";
}

SEAutoSerialization::~SEAutoSerialization()
{
  Clear();
}

void SEAutoSerialization::Clear()
{
  SAFE_DELETE(m_Period);
  m_PeriodTimeStamps = cdm::eSwitch::Off;
  m_AfterActions = cdm::eSwitch::Off;
  m_AfterActions = cdm::eSwitch::Off;
  m_Directory = "";
  m_FileName = "";
}

bool SEAutoSerialization::IsValid() const
{
  if (!HasPeriod())
    return false;
  if (m_Period->IsNegative())
    return false;
  if (!HasDirectory())
    return false;
  if (!HasFileName())
    return false;
  return true;
}

void SEAutoSerialization::Load(const cdm::AutoSerializationData& src, SEAutoSerialization& dst)
{
  SEAutoSerialization::Serialize(src, dst);
}
void SEAutoSerialization::Serialize(const cdm::AutoSerializationData& src, SEAutoSerialization& dst)
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

cdm::AutoSerializationData* SEAutoSerialization::Unload(const SEAutoSerialization& src)
{
  cdm::AutoSerializationData *dst = new cdm::AutoSerializationData();
  SEAutoSerialization::Serialize(src,*dst);
  return dst;
}
void SEAutoSerialization::Serialize(const SEAutoSerialization& src, cdm::AutoSerializationData& dst)
{
  if (src.HasPeriod())
    dst.set_allocated_period(SEScalarTime::Unload(*src.m_Period));
  dst.set_periodtimestamps(src.m_PeriodTimeStamps);
  dst.set_afteractions(src.m_AfterActions);
  dst.set_reloadstate(src.m_ReloadState);
  if (src.HasDirectory())
    dst.set_directory(src.m_Directory);
  if (src.HasFileName())
    dst.set_filename(src.m_FileName);
}

bool SEAutoSerialization::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEAutoSerialization::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}
double SEAutoSerialization::GetPeriod(const TimeUnit& unit) const
{
  if (m_Period == nullptr)
    return SEScalar::dNaN();
  return m_Period->GetValue(unit);
}

cdm::eSwitch SEAutoSerialization::GetPeriodTimeStamps() const
{
  return m_PeriodTimeStamps;
}
void SEAutoSerialization::SetPeriodTimeStamps(cdm::eSwitch v)
{
  m_PeriodTimeStamps = v;
}

cdm::eSwitch SEAutoSerialization::GetAfterActions() const
{
  return m_AfterActions;
}
void SEAutoSerialization::SetAfterActions(cdm::eSwitch v)
{
  m_AfterActions = v;
}

cdm::eSwitch SEAutoSerialization::GetReloadState() const
{
  return m_ReloadState;
}
void SEAutoSerialization::SetReloadState(cdm::eSwitch v)
{
  m_ReloadState = v;
}

std::string SEAutoSerialization::GetDirectory() const
{
  return m_Directory;
}
void SEAutoSerialization::SetDirectory(const std::string& dir)
{
  m_Directory = dir;
}
bool SEAutoSerialization::HasDirectory() const
{
  return m_Directory.empty() ? false : true;
}
void SEAutoSerialization::InvalidateDirectory()
{
  m_Directory = "";
}

std::string SEAutoSerialization::GetFileName() const
{
  return m_FileName;
}
void SEAutoSerialization::SetFileName(const std::string& name)
{
  m_FileName = name;
}
bool SEAutoSerialization::HasFileName() const
{
  return m_FileName.empty() ? false : true;
}
void SEAutoSerialization::InvalidateFileName()
{
  m_FileName = "";
}