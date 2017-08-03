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
#include "system/equipment/Anesthesia/actions/SEExpiratoryValveObstruction.h"
#include "properties/SEScalar0To1.h"

SEExpiratoryValveObstruction::SEExpiratoryValveObstruction() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SEExpiratoryValveObstruction::~SEExpiratoryValveObstruction()
{
  Clear();
}

void SEExpiratoryValveObstruction::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEExpiratoryValveObstruction::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEExpiratoryValveObstruction::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEExpiratoryValveObstruction::Load(const cdm::ExpiratoryValveObstructionData& src, SEExpiratoryValveObstruction& dst)
{
  SEExpiratoryValveObstruction::Serialize(src, dst);
}
void SEExpiratoryValveObstruction::Serialize(const cdm::ExpiratoryValveObstructionData& src, SEExpiratoryValveObstruction& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::ExpiratoryValveObstructionData* SEExpiratoryValveObstruction::Unload(const SEExpiratoryValveObstruction& src)
{
  cdm::ExpiratoryValveObstructionData* dst = new cdm::ExpiratoryValveObstructionData();
  SEExpiratoryValveObstruction::Serialize(src, *dst);
  return dst;
}
void SEExpiratoryValveObstruction::Serialize(const SEExpiratoryValveObstruction& src, cdm::ExpiratoryValveObstructionData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEExpiratoryValveObstruction::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEExpiratoryValveObstruction::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEExpiratoryValveObstruction::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Expiratory Valve Obstruction";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}