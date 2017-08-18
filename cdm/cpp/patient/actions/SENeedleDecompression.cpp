/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SENeedleDecompression.h"

SENeedleDecompression::SENeedleDecompression() : SEPatientAction()
{
  m_State=cdm::eSwitch::Off;
  m_Side= cdm::eSide::NullSide;
}

SENeedleDecompression::~SENeedleDecompression()
{
  Clear();
}

void SENeedleDecompression::Clear()
{
  SEPatientAction::Clear();
  m_State = cdm::eSwitch::Off;
  m_Side= cdm::eSide::NullSide;
}

bool SENeedleDecompression::IsValid() const
{
  return SEPatientAction::IsValid() && HasSide();
}

bool SENeedleDecompression::IsActive() const
{
  return IsValid() && m_State == cdm::eSwitch::On;
}

void SENeedleDecompression::SetActive(bool b)
{
  m_State = b ? cdm::eSwitch::On : cdm::eSwitch::Off;
}

void SENeedleDecompression::Load(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst)
{
  SENeedleDecompression::Serialize(src, dst);
}
void SENeedleDecompression::Serialize(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetSide(src.side());
  if (src.state() != cdm::eSwitch::NullSwitch)
    dst.SetState(src.state());
}

cdm::NeedleDecompressionData* SENeedleDecompression::Unload(const SENeedleDecompression& src)
{
  cdm::NeedleDecompressionData* dst = new cdm::NeedleDecompressionData();
  SENeedleDecompression::Serialize(src, *dst);
  return dst;
}
void SENeedleDecompression::Serialize(const SENeedleDecompression& src, cdm::NeedleDecompressionData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasSide())
    dst.set_side(src.m_Side);
  dst.set_state(src.m_State);
}

cdm::eSwitch SENeedleDecompression::GetState() const
{
  return m_State;
}
void SENeedleDecompression::SetState(cdm::eSwitch state)
{
  m_State = (state == cdm::eSwitch::NullSwitch) ? cdm::eSwitch::Off : state;
}

cdm::eSide SENeedleDecompression::GetSide() const
{
  return m_Side;
}
void SENeedleDecompression::SetSide(cdm::eSide Side)
{
  m_Side = Side;
}
bool SENeedleDecompression::HasSide() const
{
  return m_Side== cdm::eSide::NullSide ?false:true;
}
void SENeedleDecompression::InvalidateSide()
{
  m_Side = cdm::eSide::NullSide;
}

void SENeedleDecompression::ToString(std::ostream &str) const
{
  str << "Patient Action : Needle Decompression"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tState: " << cdm::eSwitch_Name(m_State);
  str  << "\n\tSide: "; HasSide()? str << cdm::eSide_Name(GetSide()) : str << "No Side Set";
  str << std::flush;
}