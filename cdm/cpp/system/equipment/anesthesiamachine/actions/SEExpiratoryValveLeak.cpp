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
#include "system/equipment/anesthesiamachine/actions/SEExpiratoryValveLeak.h"
#include "properties/SEScalar0To1.h"

SEExpiratoryValveLeak::SEExpiratoryValveLeak() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SEExpiratoryValveLeak::~SEExpiratoryValveLeak()
{
  Clear();
}

void SEExpiratoryValveLeak::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEExpiratoryValveLeak::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEExpiratoryValveLeak::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEExpiratoryValveLeak::Load(const cdm::ExpiratoryValveLeakData& src, SEExpiratoryValveLeak& dst)
{
  SEExpiratoryValveLeak::Serialize(src, dst);
}
void SEExpiratoryValveLeak::Serialize(const cdm::ExpiratoryValveLeakData& src, SEExpiratoryValveLeak& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::ExpiratoryValveLeakData* SEExpiratoryValveLeak::Unload(const SEExpiratoryValveLeak& src)
{
  cdm::ExpiratoryValveLeakData* dst = new cdm::ExpiratoryValveLeakData();
  SEExpiratoryValveLeak::Serialize(src, *dst);
  return dst;
}
void SEExpiratoryValveLeak::Serialize(const SEExpiratoryValveLeak& src, cdm::ExpiratoryValveLeakData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEExpiratoryValveLeak::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEExpiratoryValveLeak::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEExpiratoryValveLeak::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Expiratory Valve Leak";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}