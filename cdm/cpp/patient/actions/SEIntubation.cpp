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
#include "patient/actions/SEIntubation.h"

SEIntubation::SEIntubation() : SEPatientAction()
{
  m_Type = (cdm::IntubationData_eType) - 1;
}

SEIntubation::~SEIntubation()
{
  Clear();
}

void SEIntubation::Clear()
{
  SEPatientAction::Clear();
  m_Type = (cdm::IntubationData_eType) - 1;
}

bool SEIntubation::IsValid() const
{
  return HasType();
}

bool SEIntubation::IsActive() const
{
  return HasType() && GetType() != cdm::IntubationData_eType_Off;
}

void SEIntubation::Load(const cdm::IntubationData& src, SEIntubation& dst)
{
  SEIntubation::Serialize(src, dst);
}
void SEIntubation::Serialize(const cdm::IntubationData& src, SEIntubation& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetType(src.type());
}

cdm::IntubationData* SEIntubation::Unload(const SEIntubation& src)
{
  cdm::IntubationData* dst = new cdm::IntubationData();
  SEIntubation::Serialize(src, *dst);
  return dst;
}
void SEIntubation::Serialize(const SEIntubation& src, cdm::IntubationData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasType())
    dst.set_type(src.m_Type);
}

cdm::IntubationData_eType SEIntubation::GetType() const
{
  return m_Type;
}
void SEIntubation::SetType(cdm::IntubationData_eType Type)
{
  m_Type = Type;
}
bool SEIntubation::HasType() const
{
  return m_Type == ((cdm::IntubationData_eType) - 1) ? false : true;
}
void SEIntubation::InvalidateType()
{
  m_Type = (cdm::IntubationData_eType) - 1;
}


void SEIntubation::ToString(std::ostream &str) const
{
  str << "Patient Action : Intubation";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tType: "; HasType() ? str << GetType() : str << "Not Set";
  str << std::flush;
}
