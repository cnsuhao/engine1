/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/anesthesiamachine/actions/SEInspiratoryValveObstruction.h"
#include "properties/SEScalar0To1.h"

SEInspiratoryValveObstruction::SEInspiratoryValveObstruction() : SEAnesthesiaMachineAction()
{
  m_Severity = nullptr;
}

SEInspiratoryValveObstruction::~SEInspiratoryValveObstruction()
{
  Clear();
}

void SEInspiratoryValveObstruction::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEInspiratoryValveObstruction::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEInspiratoryValveObstruction::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEInspiratoryValveObstruction::Load(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst)
{
  SEInspiratoryValveObstruction::Serialize(src, dst);
}
void SEInspiratoryValveObstruction::Serialize(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::InspiratoryValveObstructionData* SEInspiratoryValveObstruction::Unload(const SEInspiratoryValveObstruction& src)
{
  cdm::InspiratoryValveObstructionData* dst = new cdm::InspiratoryValveObstructionData();
  SEInspiratoryValveObstruction::Serialize(src, *dst);
  return dst;
}
void SEInspiratoryValveObstruction::Serialize(const SEInspiratoryValveObstruction& src, cdm::InspiratoryValveObstructionData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEInspiratoryValveObstruction::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEInspiratoryValveObstruction::GetSeverity()
{
  if (m_Severity == nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEInspiratoryValveObstruction::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Inspiratory Valve Obstruction";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}