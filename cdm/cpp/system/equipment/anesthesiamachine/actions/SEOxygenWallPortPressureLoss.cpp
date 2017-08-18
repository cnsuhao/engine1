/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#include "stdafx.h"
#include "system/equipment/anesthesiamachine/actions/SEOxygenWallPortPressureLoss.h"
#include "properties/SEScalar0To1.h"

SEOxygenWallPortPressureLoss::SEOxygenWallPortPressureLoss() : SEAnesthesiaMachineAction()
{
  m_State = cdm::eSwitch::Off;
}

SEOxygenWallPortPressureLoss::~SEOxygenWallPortPressureLoss()
{
  Clear();
}

void SEOxygenWallPortPressureLoss::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  m_State = cdm::eSwitch::Off;
}

bool SEOxygenWallPortPressureLoss::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid();
}
bool SEOxygenWallPortPressureLoss::IsActive() const
{
  return m_State == cdm::eSwitch::On;
}
void SEOxygenWallPortPressureLoss::SetActive(bool b)
{
  m_State = b ? cdm::eSwitch::On : cdm::eSwitch::Off;
}

void SEOxygenWallPortPressureLoss::Load(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst)
{
  SEOxygenWallPortPressureLoss::Serialize(src, dst);
}
void SEOxygenWallPortPressureLoss::Serialize(const cdm::OxygenWallPortPressureLossData& src, SEOxygenWallPortPressureLoss& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  dst.SetActive(src.state() == cdm::eSwitch::On ? true : false);
}

cdm::OxygenWallPortPressureLossData* SEOxygenWallPortPressureLoss::Unload(const SEOxygenWallPortPressureLoss& src)
{
  cdm::OxygenWallPortPressureLossData* dst = new cdm::OxygenWallPortPressureLossData();
  SEOxygenWallPortPressureLoss::Serialize(src, *dst);
  return dst;
}
void SEOxygenWallPortPressureLoss::Serialize(const SEOxygenWallPortPressureLoss& src, cdm::OxygenWallPortPressureLossData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  dst.set_state(src.IsActive() ? cdm::eSwitch::On : cdm::eSwitch::Off);
}

void SEOxygenWallPortPressureLoss::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Oxygen Wall Port Pressure Loss"; 
  if(HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tState: " << cdm::eSwitch(m_State);
  str << std::flush;
}