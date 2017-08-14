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
#include "system/equipment/anesthesiamachine/actions/SESodaLimeFailure.h"
#include "properties/SEScalar0To1.h"

SESodaLimeFailure::SESodaLimeFailure() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SESodaLimeFailure::~SESodaLimeFailure()
{
  Clear();
}

void SESodaLimeFailure::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SESodaLimeFailure::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SESodaLimeFailure::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SESodaLimeFailure::Load(const cdm::SodaLimeFailureData& src, SESodaLimeFailure& dst)
{
  SESodaLimeFailure::Serialize(src, dst);
}
void SESodaLimeFailure::Serialize(const cdm::SodaLimeFailureData& src, SESodaLimeFailure& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::SodaLimeFailureData* SESodaLimeFailure::Unload(const SESodaLimeFailure& src)
{
  cdm::SodaLimeFailureData* dst = new cdm::SodaLimeFailureData();
  SESodaLimeFailure::Serialize(src, *dst);
  return dst;
}
void SESodaLimeFailure::Serialize(const SESodaLimeFailure& src, cdm::SodaLimeFailureData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SESodaLimeFailure::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SESodaLimeFailure::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SESodaLimeFailure::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Soda Lime Failure";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}