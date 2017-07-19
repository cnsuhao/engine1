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
#include "scenario/SEAdvanceTime.h"
#include "properties/SEScalarTime.h"

SEAdvanceTime::SEAdvanceTime() : SEAction()
{
  m_Time=nullptr;
}

SEAdvanceTime::~SEAdvanceTime()
{
  Clear();
}

void SEAdvanceTime::Clear()
{
  SEAction::Clear();
  SAFE_DELETE(m_Time);
}

bool SEAdvanceTime::IsValid() const
{ 
  return HasTime() && m_Time->IsValid();
}

void SEAdvanceTime::Load(const cdm::AdvanceTimeData& src, SEAdvanceTime& dst)
{
	SEAdvanceTime::Serialize(src, dst);
}
void SEAdvanceTime::Serialize(const cdm::AdvanceTimeData& src, SEAdvanceTime& dst)
{
	dst.Clear();
	if (src.has_time())
		SEScalarTime::Load(src.time(), dst.GetTime());
}

cdm::AdvanceTimeData* SEAdvanceTime::Unload(const SEAdvanceTime& src)
{
	cdm::AdvanceTimeData* dst = new cdm::AdvanceTimeData();
	SEAdvanceTime::Serialize(src, *dst);
	return dst;
}
void SEAdvanceTime::Serialize(const SEAdvanceTime& src, cdm::AdvanceTimeData& dst)
{
	if (src.HasTime())
		dst.set_allocated_time(SEScalarTime::Unload(*src.m_Time));
}

void SEAdvanceTime::ToString(std::ostream &str) const
{  
  if(HasComment())
    str<<"\n\tComment : "<<m_Comment;
  str << "Advance Time : " << m_Time;
}


bool SEAdvanceTime::HasTime() const
{
  return m_Time==nullptr?false:m_Time->IsValid();
}
SEScalarTime& SEAdvanceTime::GetTime()
{
  if(m_Time==nullptr)
    m_Time=new SEScalarTime();
  return *m_Time;
}
double SEAdvanceTime::GetTime(const TimeUnit& unit) const
{
  if (m_Time == nullptr)
    return SEScalar::dNaN();
  return m_Time->GetValue(unit);
}