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
#include "patient/actions/SEBrainInjury.h"
#include "properties/SEScalar0To1.h"

SEBrainInjury::SEBrainInjury() : SEPatientAction()
{
  m_Severity=nullptr;
  m_Type = cdm::BrainInjuryData_eType_Diffuse;
}

SEBrainInjury::~SEBrainInjury()
{
  Clear();
}

void SEBrainInjury::Clear()
{
  
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
  m_Type = cdm::BrainInjuryData_eType_Diffuse;
}

bool SEBrainInjury::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEBrainInjury::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEBrainInjury::Load(const cdm::BrainInjuryData& src, SEBrainInjury& dst)
{
  SEBrainInjury::Serialize(src, dst);
}
void SEBrainInjury::Serialize(const cdm::BrainInjuryData& src, SEBrainInjury& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
  dst.SetType(src.type());
}

cdm::BrainInjuryData* SEBrainInjury::Unload(const SEBrainInjury& src)
{
  cdm::BrainInjuryData* dst = new cdm::BrainInjuryData();
  SEBrainInjury::Serialize(src, *dst);
  return dst;
}
void SEBrainInjury::Serialize(const SEBrainInjury& src, cdm::BrainInjuryData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
  dst.set_type(src.m_Type);
}

bool SEBrainInjury::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}
SEScalar0To1& SEBrainInjury::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

cdm::BrainInjuryData_eType SEBrainInjury::GetType() const
{
  return m_Type;
}
void SEBrainInjury::SetType(cdm::BrainInjuryData_eType Type)
{
  m_Type = Type;
}
void SEBrainInjury::ToString(std::ostream &str) const
{
  str << "Patient Action : Brain Injury"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "Not Set";
  str << "\n\tType: "<< GetType();
  str << std::flush;
}