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
#include "patient/actions/SEForcedExhale.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarTime.h"

SEForcedExhale::SEForcedExhale() : SEConsciousRespirationCommand()
{
  m_ExpiratoryReserveVolumeFraction = nullptr;
  m_Period = nullptr;
}

SEForcedExhale::~SEForcedExhale()
{
  Clear();
}

void SEForcedExhale::Clear()
{
  SEConsciousRespirationCommand::Clear();
  SAFE_DELETE(m_ExpiratoryReserveVolumeFraction);
  SAFE_DELETE(m_Period);
}

bool SEForcedExhale::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid() && HasExpiratoryReserveVolumeFraction() && HasPeriod();
}

bool SEForcedExhale::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

void SEForcedExhale::Load(const cdm::ConsciousRespirationData_ForcedExhaleData& src, SEForcedExhale& dst)
{
  SEForcedExhale::Serialize(src, dst);
}
void SEForcedExhale::Serialize(const cdm::ConsciousRespirationData_ForcedExhaleData& src, SEForcedExhale& dst)
{
  dst.Clear();
  if(src.has_expiratoryreservevolumefraction())
    SEScalar0To1::Load(src.expiratoryreservevolumefraction(), dst.GetExpiratoryReserveVolumeFraction());
  if (src.has_period())
    SEScalarTime::Load(src.period(), dst.GetPeriod());
}

cdm::ConsciousRespirationData_ForcedExhaleData* SEForcedExhale::Unload(const SEForcedExhale& src)
{
  cdm::ConsciousRespirationData_ForcedExhaleData* dst = new cdm::ConsciousRespirationData_ForcedExhaleData();
  SEForcedExhale::Serialize(src, *dst);
  return dst;
}
void SEForcedExhale::Serialize(const SEForcedExhale& src, cdm::ConsciousRespirationData_ForcedExhaleData& dst)
{
  if (src.HasExpiratoryReserveVolumeFraction())
    dst.set_allocated_expiratoryreservevolumefraction(SEScalar0To1::Unload(*src.m_ExpiratoryReserveVolumeFraction));
  if (src.HasPeriod())
    dst.set_allocated_period(SEScalarTime::Unload(*src.m_Period));
}

bool SEForcedExhale::HasExpiratoryReserveVolumeFraction() const
{
  return m_ExpiratoryReserveVolumeFraction == nullptr ? false : m_ExpiratoryReserveVolumeFraction->IsValid();
}
SEScalar0To1& SEForcedExhale::GetExpiratoryReserveVolumeFraction()
{
  if (m_ExpiratoryReserveVolumeFraction == nullptr)
    m_ExpiratoryReserveVolumeFraction = new SEScalar0To1();
  return *m_ExpiratoryReserveVolumeFraction;
}

bool SEForcedExhale::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEForcedExhale::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}

void SEForcedExhale::ToString(std::ostream &str) const
{
  str << "Forced Exhale";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tExpiratoryReserveVolumeFraction: "; HasExpiratoryReserveVolumeFraction() ? str << *m_ExpiratoryReserveVolumeFraction : str << "NaN";
  str << "\n\tPeriod: "; HasPeriod() ? str << *m_Period : str << "NaN";
  str << std::flush;
}