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
#include "scenario/SESerializeState.h"

SESerializeState::SESerializeState() : SEAction()
{
  m_Filename="";
  m_Type = (cdm::SerializeStateData_eSerializationType)-1;
}

SESerializeState::~SESerializeState()
{
  Clear();
}

void SESerializeState::Clear()
{
  SEAction::Clear();
  m_Filename = "";
  m_Type = (cdm::SerializeStateData_eSerializationType)-1;
}

bool SESerializeState::IsValid() const
{ 
  return HasFilename() && HasType();
}

void SESerializeState::Load(const cdm::SerializeStateData& src, SESerializeState& dst)
{
  SESerializeState::Serialize(src, dst);
}
void SESerializeState::Serialize(const cdm::SerializeStateData& src, SESerializeState& dst)
{
  dst.Clear();
  dst.SetType(src.type());
  dst.SetFilename(src.filename());
}

cdm::SerializeStateData* SESerializeState::Unload(const SESerializeState& src)
{
  cdm::SerializeStateData* dst = new cdm::SerializeStateData();
  SESerializeState::Serialize(src, *dst);
  return dst;
}
void SESerializeState::Serialize(const SESerializeState& src, cdm::SerializeStateData& dst)
{
  if (src.HasType())
    dst.set_type(src.m_Type);
  if (src.HasFilename())
    dst.set_filename(src.m_Filename);
}


void SESerializeState::ToString(std::ostream &str) const
{  
  if(HasComment())
    str<<"\n\tComment : "<<m_Comment;
  str << "Type : " << m_Type;
  str << "Filename : " << m_Filename;
}

cdm::SerializeStateData_eSerializationType SESerializeState::GetType() const
{
  return m_Type;
}
void SESerializeState::SetType(cdm::SerializeStateData_eSerializationType Type)
{
  m_Type = Type;
}
bool SESerializeState::HasType() const
{
  return m_Type == ((cdm::SerializeStateData_eSerializationType) - 1) ? false : true;
}
void SESerializeState::InvalidateType()
{
  m_Type = (cdm::SerializeStateData_eSerializationType) - 1;
}

bool SESerializeState::HasFilename() const
{
  return !(m_Filename.empty());
}
std::string SESerializeState::GetFilename() const
{
  return m_Filename;
}
void SESerializeState::SetFilename(const std::string& filename)
{
  m_Filename = filename;
}
void SESerializeState::InvalidateFilename()
{
  m_Filename = "";
}