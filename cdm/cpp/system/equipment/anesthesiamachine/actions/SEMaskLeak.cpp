/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/anesthesiamachine/actions/SEMaskLeak.h"
#include "properties/SEScalar0To1.h"

SEMaskLeak::SEMaskLeak() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SEMaskLeak::~SEMaskLeak()
{
  Clear();
}

void SEMaskLeak::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEMaskLeak::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEMaskLeak::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEMaskLeak::Load(const cdm::MaskLeakData& src, SEMaskLeak& dst)
{
  SEMaskLeak::Serialize(src, dst);
}
void SEMaskLeak::Serialize(const cdm::MaskLeakData& src, SEMaskLeak& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::MaskLeakData* SEMaskLeak::Unload(const SEMaskLeak& src)
{
  cdm::MaskLeakData* dst = new cdm::MaskLeakData();
  SEMaskLeak::Serialize(src, *dst);
  return dst;
}
void SEMaskLeak::Serialize(const SEMaskLeak& src, cdm::MaskLeakData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEMaskLeak::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEMaskLeak::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEMaskLeak::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Mask Leak";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}