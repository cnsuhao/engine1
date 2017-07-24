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
#include "patient/actions/SEApnea.h"
#include "properties/SEScalar0To1.h"

SEApnea::SEApnea() : SEPatientAction()
{
  m_Severity=nullptr;
}

SEApnea::~SEApnea()
{
  Clear();
}

void SEApnea::Clear()
{
  
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
  
}

bool SEApnea::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEApnea::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEApnea::Load(const cdm::ApneaData& src, SEApnea& dst)
{
  SEApnea::Serialize(src, dst);
}
void SEApnea::Serialize(const cdm::ApneaData& src, SEApnea& dst)
{
  dst.Clear();
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::ApneaData* SEApnea::Unload(const SEApnea& src)
{
  cdm::ApneaData* dst = new cdm::ApneaData();
  SEApnea::Serialize(src, *dst);
  return dst;
}
void SEApnea::Serialize(const SEApnea& src, cdm::ApneaData& dst)
{
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}


bool SEApnea::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}

SEScalar0To1& SEApnea::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SEApnea::ToString(std::ostream &str) const
{
  str << "Patient Action : Apnea"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "Not Set";
  str << std::flush;
}