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
#include "system/equipment/Anesthesia/actions/SEVentilatorPressureLoss.h"
#include "properties/SEScalar0To1.h"

SEVentilatorPressureLoss::SEVentilatorPressureLoss() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SEVentilatorPressureLoss::~SEVentilatorPressureLoss()
{
  Clear();
}

void SEVentilatorPressureLoss::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEVentilatorPressureLoss::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEVentilatorPressureLoss::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEVentilatorPressureLoss::Load(const cdm::VentilatorPressureLossData& src, SEVentilatorPressureLoss& dst)
{
  SEVentilatorPressureLoss::Serialize(src, dst);
}
void SEVentilatorPressureLoss::Serialize(const cdm::VentilatorPressureLossData& src, SEVentilatorPressureLoss& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::VentilatorPressureLossData* SEVentilatorPressureLoss::Unload(const SEVentilatorPressureLoss& src)
{
  cdm::VentilatorPressureLossData* dst = new cdm::VentilatorPressureLossData();
  SEVentilatorPressureLoss::Serialize(src, *dst);
  return dst;
}
void SEVentilatorPressureLoss::Serialize(const SEVentilatorPressureLoss& src, cdm::VentilatorPressureLossData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEVentilatorPressureLoss::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEVentilatorPressureLoss::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEVentilatorPressureLoss::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Ventilator Pressure Loss";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}