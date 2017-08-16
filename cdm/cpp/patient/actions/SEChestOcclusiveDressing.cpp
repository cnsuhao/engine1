/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEChestOcclusiveDressing.h"

SEChestOcclusiveDressing::SEChestOcclusiveDressing() : SEPatientAction()
{
  m_State = cdm::eSwitch::Off;
  m_Side= cdm::eSide::NullSide;
}

SEChestOcclusiveDressing::~SEChestOcclusiveDressing()
{
  Clear();
}

void SEChestOcclusiveDressing::Clear()
{
  SEPatientAction::Clear();
  m_State= cdm::eSwitch::Off;
  m_Side= cdm::eSide::NullSide;
}

bool SEChestOcclusiveDressing::IsValid() const
{
  return SEPatientAction::IsValid() && HasSide();
}

bool SEChestOcclusiveDressing::IsActive() const
{
  return IsValid() && m_State == cdm::eSwitch::On;
}

void SEChestOcclusiveDressing::Load(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst)
{
  SEChestOcclusiveDressing::Serialize(src, dst);
}
void SEChestOcclusiveDressing::Serialize(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetSide(src.side());
  dst.SetState(src.state());
}

cdm::ChestOcclusiveDressingData* SEChestOcclusiveDressing::Unload(const SEChestOcclusiveDressing& src)
{
  cdm::ChestOcclusiveDressingData* dst = new cdm::ChestOcclusiveDressingData();
  SEChestOcclusiveDressing::Serialize(src, *dst);
  return dst;
}
void SEChestOcclusiveDressing::Serialize(const SEChestOcclusiveDressing& src, cdm::ChestOcclusiveDressingData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.set_state(src.m_State);
  if (src.HasSide())
    dst.set_side(src.m_Side);
}

cdm::eSide SEChestOcclusiveDressing::GetSide() const
{
  return m_Side;
}
void SEChestOcclusiveDressing::SetSide(cdm::eSide Side)
{
  m_Side = Side;
}
bool SEChestOcclusiveDressing::HasSide() const
{
  return m_Side== cdm::eSide::NullSide ?false:true;
}
void SEChestOcclusiveDressing::InvalidateSide()
{
  m_Side = cdm::eSide::NullSide;
}

void SEChestOcclusiveDressing::ToString(std::ostream &str) const
{
  str << "Patient Action : Chest Occlusive Dressing"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tState: " << m_State;
  str << "\n\tSide: "; HasSide()? str << GetSide() : str << "Not Set"; 
  str<<std::flush;
}