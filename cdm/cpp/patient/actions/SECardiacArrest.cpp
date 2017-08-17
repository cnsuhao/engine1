/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SECardiacArrest.h"

SECardiacArrest::SECardiacArrest() : SEPatientAction()
{
  m_State = cdm::eSwitch::Off;
}

SECardiacArrest::~SECardiacArrest()
{
  Clear();
}

void SECardiacArrest::Clear()
{
  SEPatientAction::Clear();
  m_State = cdm::eSwitch::Off;
}

bool SECardiacArrest::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SECardiacArrest::IsActive() const
{
  return IsValid() && m_State == cdm::eSwitch::On;
}

void SECardiacArrest::Load(const cdm::CardiacArrestData& src, SECardiacArrest& dst)
{
  SECardiacArrest::Serialize(src, dst);
}
void SECardiacArrest::Serialize(const cdm::CardiacArrestData& src, SECardiacArrest& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.state() != cdm::eSwitch::NullSwitch)
    dst.SetState(src.state());
}

cdm::CardiacArrestData* SECardiacArrest::Unload(const SECardiacArrest& src)
{
  cdm::CardiacArrestData* dst = new cdm::CardiacArrestData();
  SECardiacArrest::Serialize(src, *dst);
  return dst;
}
void SECardiacArrest::Serialize(const SECardiacArrest& src, cdm::CardiacArrestData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.set_state(src.m_State);
}

void SECardiacArrest::ToString(std::ostream &str) const
{
  str << "Patient Action : Cardiac Arrest";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tState: " << m_State;
  str << std::flush;
}