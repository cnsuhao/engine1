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
#include "patient/actions/SEChestOcclusiveDressing.h"

SEChestOcclusiveDressing::SEChestOcclusiveDressing() : SEPatientAction()
{
  m_State = cdm::eSwitch::Off;
  m_Side=(cdm::eSide)-1;
}

SEChestOcclusiveDressing::~SEChestOcclusiveDressing()
{
  Clear();
}

void SEChestOcclusiveDressing::Clear()
{
  SEPatientAction::Clear();
  m_State= cdm::eSwitch::Off;
  m_Side=(cdm::eSide)-1;
}

bool SEChestOcclusiveDressing::IsValid() const
{
  return SEPatientAction::IsValid() && HasSide();
}

bool SEChestOcclusiveDressing::IsActive() const
{
  return IsValid() && m_State == cdm::eSwitch::On;
}

void SEChestOcclusiveDressing::SetActive(bool b)
{
  m_State = b ? cdm::eSwitch::On : cdm::eSwitch::Off;
}

void SEChestOcclusiveDressing::Load(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst)
{
	SEChestOcclusiveDressing::Serialize(src, dst);
}
void SEChestOcclusiveDressing::Serialize(const cdm::ChestOcclusiveDressingData& src, SEChestOcclusiveDressing& dst)
{
	dst.Clear();
	dst.SetSide(src.side());
	//jbw - How to do state?
}

cdm::ChestOcclusiveDressingData* SEChestOcclusiveDressing::Unload(const SEChestOcclusiveDressing& src)
{
	cdm::ChestOcclusiveDressingData* dst = new cdm::ChestOcclusiveDressingData();
	SEChestOcclusiveDressing::Serialize(src, *dst);
	return dst;
}
void SEChestOcclusiveDressing::Serialize(const SEChestOcclusiveDressing& src, cdm::ChestOcclusiveDressingData& dst)
{
	if (src.HasSide())
		dst.set_side(src.m_Side);
	//jbw - How to do state?
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
  return m_Side==((cdm::eSide)-1)?false:true;
}
void SEChestOcclusiveDressing::InvalidateSide()
{
  m_Side = (cdm::eSide)-1;
}

void SEChestOcclusiveDressing::ToString(std::ostream &str) const
{
  str << "Patient Action : Chest Occlusive Dressing"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tState: " << IsActive();
  str << "\n\tSide: "; HasSide()? str << GetSide() : str << "Not Set"; 
  str<<std::flush;
}