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
#include "system/equipment/Anesthesia/actions/SEOxygenWallPortPressureLoss.h"
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
  m_State = (cdm::eSwitch)-1;
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
  str << "\n\tState: " << IsActive();
  str << std::flush;
}