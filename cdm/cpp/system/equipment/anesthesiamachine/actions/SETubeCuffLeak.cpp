/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/anesthesiamachine/actions/SETubeCuffLeak.h"
#include "properties/SEScalar0To1.h"

SETubeCuffLeak::SETubeCuffLeak() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SETubeCuffLeak::~SETubeCuffLeak()
{
  Clear();
}

void SETubeCuffLeak::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SETubeCuffLeak::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SETubeCuffLeak::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SETubeCuffLeak::Load(const cdm::TubeCuffLeakData& src, SETubeCuffLeak& dst)
{
  SETubeCuffLeak::Serialize(src, dst);
}
void SETubeCuffLeak::Serialize(const cdm::TubeCuffLeakData& src, SETubeCuffLeak& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::TubeCuffLeakData* SETubeCuffLeak::Unload(const SETubeCuffLeak& src)
{
  cdm::TubeCuffLeakData* dst = new cdm::TubeCuffLeakData();
  SETubeCuffLeak::Serialize(src, *dst);
  return dst;
}
void SETubeCuffLeak::Serialize(const SETubeCuffLeak& src, cdm::TubeCuffLeakData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SETubeCuffLeak::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SETubeCuffLeak::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SETubeCuffLeak::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Tube Cuff Leak";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}