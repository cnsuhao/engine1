/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/anesthesiamachine/actions/SEYPieceDisconnect.h"
#include "properties/SEScalar0To1.h"

SEYPieceDisconnect::SEYPieceDisconnect() : SEAnesthesiaMachineAction()
{
  m_Severity=nullptr;
}

SEYPieceDisconnect::~SEYPieceDisconnect()
{
  Clear();
}

void SEYPieceDisconnect::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEYPieceDisconnect::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && HasSeverity();
}

bool SEYPieceDisconnect::IsActive() const
{
  return HasSeverity() ? !m_Severity->IsZero() : false;
}

void SEYPieceDisconnect::Load(const cdm::YPieceDisconnectData& src, SEYPieceDisconnect& dst)
{
  SEYPieceDisconnect::Serialize(src, dst);
}
void SEYPieceDisconnect::Serialize(const cdm::YPieceDisconnectData& src, SEYPieceDisconnect& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::YPieceDisconnectData* SEYPieceDisconnect::Unload(const SEYPieceDisconnect& src)
{
  cdm::YPieceDisconnectData* dst = new cdm::YPieceDisconnectData();
  SEYPieceDisconnect::Serialize(src, *dst);
  return dst;
}
void SEYPieceDisconnect::Serialize(const SEYPieceDisconnect& src, cdm::YPieceDisconnectData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SEYPieceDisconnect::HasSeverity() const
{
  return m_Severity != nullptr;
}
SEScalar0To1& SEYPieceDisconnect::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity = new SEScalar0To1();
  return *m_Severity;
}

void SEYPieceDisconnect::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : YPiece Disconnect"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity :"; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << std::flush;
}