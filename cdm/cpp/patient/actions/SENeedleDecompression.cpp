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
#include "patient/actions/SENeedleDecompression.h"

SENeedleDecompression::SENeedleDecompression() : SEPatientAction()
{
  m_State=cdm::eSwitch::Off;
  m_Side=(cdm::eSide)-1;
}

SENeedleDecompression::~SENeedleDecompression()
{
  Clear();
}

void SENeedleDecompression::Clear()
{
  SEPatientAction::Clear();
  m_State = cdm::eSwitch::Off;
  m_Side=(cdm::eSide)-1;
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
  if (src.HasState())
    dst.set_state(src.m_State);
}

cdm::eSwitch SENeedleDecompression::GetState() const
{
  return m_State;
}
void SENeedleDecompression::SetState(cdm::eSwitch state)
{
  m_State = state;
}
bool SENeedleDecompression::HasState() const
{
  return m_State == ((cdm::eSwitch) - 1) ? false : true;
}
void SENeedleDecompression::InvalidateState()
{
  m_State = (cdm::eSwitch) - 1;
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
  return m_Side==((cdm::eSide)-1)?false:true;
}
void SENeedleDecompression::InvalidateSide()
{
  m_Side = (cdm::eSide)-1;
}

void SENeedleDecompression::ToString(std::ostream &str) const
{
  str << "Patient Action : Needle Decompression"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tState: " << IsActive();
  str  << "\n\tSide: "; HasSide()? str << GetSide() : str << "No Side Set";
  str << std::flush;
}