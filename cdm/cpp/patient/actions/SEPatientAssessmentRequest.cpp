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
#include "patient/actions/SEPatientAssessmentRequest.h"

SEPatientAssessmentRequest::SEPatientAssessmentRequest() : SEPatientAction()
{
  m_Type=(cdm::PatientAssessmentRequestData_eAssessmentType)-1;
}

SEPatientAssessmentRequest::~SEPatientAssessmentRequest()
{
  Clear();
}

void SEPatientAssessmentRequest::Clear()
{
  SEPatientAction::Clear();
  m_Type=(cdm::PatientAssessmentRequestData_eAssessmentType)-1;
}

bool SEPatientAssessmentRequest::IsValid() const
{
  return SEPatientAction::IsValid() && HasType();
}

bool SEPatientAssessmentRequest::IsActive() const
{
  return IsValid();
}

void SEPatientAssessmentRequest::Load(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst)
{
  SEPatientAssessmentRequest::Serialize(src, dst);
}
void SEPatientAssessmentRequest::Serialize(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetType(src.type());
}

cdm::PatientAssessmentRequestData* SEPatientAssessmentRequest::Unload(const SEPatientAssessmentRequest& src)
{
  cdm::PatientAssessmentRequestData* dst = new cdm::PatientAssessmentRequestData();
  SEPatientAssessmentRequest::Serialize(src, *dst);
  return dst;
}
void SEPatientAssessmentRequest::Serialize(const SEPatientAssessmentRequest& src, cdm::PatientAssessmentRequestData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasType())
    dst.set_type(src.m_Type);
}

cdm::PatientAssessmentRequestData_eAssessmentType SEPatientAssessmentRequest::GetType() const
{
  return m_Type;
}
void SEPatientAssessmentRequest::SetType(cdm::PatientAssessmentRequestData_eAssessmentType Type)
{
  m_Type = Type;
}
bool SEPatientAssessmentRequest::HasType() const
{
  return m_Type==((cdm::PatientAssessmentRequestData_eAssessmentType)-1)?false:true;
}
void SEPatientAssessmentRequest::InvalidateType()
{
  m_Type = (cdm::PatientAssessmentRequestData_eAssessmentType)-1;
}

void SEPatientAssessmentRequest::ToString(std::ostream &str) const
{
  str << "Patient Action : Assessment Request"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str  << "\n\tType: "; HasType()? str << GetType() : str << "Not Set";
  str << std::flush;
}