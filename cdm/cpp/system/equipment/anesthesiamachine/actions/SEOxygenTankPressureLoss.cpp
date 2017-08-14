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
#include "system/equipment/anesthesiamachine/actions/SEOxygenTankPressureLoss.h"
#include "properties/SEScalar0To1.h"

SEOxygenTankPressureLoss::SEOxygenTankPressureLoss() : SEAnesthesiaMachineAction()
{
  m_State = cdm::eSwitch::Off;
}

SEOxygenTankPressureLoss::~SEOxygenTankPressureLoss()
{
  Clear();
}

void SEOxygenTankPressureLoss::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  m_State = (cdm::eSwitch)-1;
}

bool SEOxygenTankPressureLoss::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid();
}
bool SEOxygenTankPressureLoss::IsActive() const
{
  return m_State == cdm::eSwitch::On;
}
void SEOxygenTankPressureLoss::SetActive(bool b)
{
  m_State = b ? cdm::eSwitch::On : cdm::eSwitch::Off;
}

void SEOxygenTankPressureLoss::Load(const cdm::OxygenTankPressureLossData& src, SEOxygenTankPressureLoss& dst)
{
  SEOxygenTankPressureLoss::Serialize(src, dst);
}
void SEOxygenTankPressureLoss::Serialize(const cdm::OxygenTankPressureLossData& src, SEOxygenTankPressureLoss& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  dst.SetActive(src.state() == cdm::eSwitch::On ? true : false);
}

cdm::OxygenTankPressureLossData* SEOxygenTankPressureLoss::Unload(const SEOxygenTankPressureLoss& src)
{
  cdm::OxygenTankPressureLossData* dst = new cdm::OxygenTankPressureLossData();
  SEOxygenTankPressureLoss::Serialize(src, *dst);
  return dst;
}
void SEOxygenTankPressureLoss::Serialize(const SEOxygenTankPressureLoss& src, cdm::OxygenTankPressureLossData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  dst.set_state(src.IsActive() ? cdm::eSwitch::On : cdm::eSwitch::Off);
}

void SEOxygenTankPressureLoss::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Action : Oxygen Tank Pressure Loss"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str  << "\n\tState: " << IsActive();
  str << std::flush;
}