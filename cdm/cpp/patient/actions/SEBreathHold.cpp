/*******************************************************cdm::ConsciousRespirationData_BreathHoldData*******************************
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
#include "patient/actions/SEBreathHold.h"
#include "properties/SEScalarTime.h"

SEBreathHold::SEBreathHold() : SEConsciousRespirationCommand()
{
  m_Period = nullptr;
}

SEBreathHold::~SEBreathHold()
{
  Clear();
}

void SEBreathHold::Clear()
{
  SEConsciousRespirationCommand::Clear();
  SAFE_DELETE(m_Period);
}

bool SEBreathHold::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid() && HasPeriod();
}

bool SEBreathHold::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

void SEBreathHold::Load(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst)
{
  SEBreathHold::Serialize(src, dst);
}
void SEBreathHold::Serialize(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst)
{
  dst.Clear();
  if (src.has_period())
    SEScalarTime::Load(src.period(), dst.GetPeriod());
}

cdm::ConsciousRespirationData_BreathHoldData* SEBreathHold::Unload(const SEBreathHold& src)
{
  cdm::ConsciousRespirationData_BreathHoldData* dst = new cdm::ConsciousRespirationData_BreathHoldData();
  SEBreathHold::Serialize(src, *dst);
  return dst;
}
void SEBreathHold::Serialize(const SEBreathHold& src, cdm::ConsciousRespirationData_BreathHoldData& dst)
{
  if (src.HasPeriod())
    dst.set_allocated_period(SEScalarTime::Unload(*src.m_Period));
}

bool SEBreathHold::HasPeriod() const
{
  return m_Period == nullptr ? false : m_Period->IsValid();
}
SEScalarTime& SEBreathHold::GetPeriod()
{
  if (m_Period == nullptr)
    m_Period = new SEScalarTime();
  return *m_Period;
}

void SEBreathHold::ToString(std::ostream &str) const
{
  str << "Breath Hold";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tPeriod: "; HasPeriod() ? str << *m_Period : str << "NaN";
  str << std::flush;
}