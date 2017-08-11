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
  m_Type=cdm::PatientAssessmentData_eType_CompleteBloodCount;
}

SEPatientAssessmentRequest::~SEPatientAssessmentRequest()
{
  Clear();
}

void SEPatientAssessmentRequest::Clear()
{
  SEPatientAction::Clear();
  m_Type=cdm::PatientAssessmentData_eType_CompleteBloodCount;
}

bool SEPatientAssessmentRequest::IsValid() const
{
  return SEPatientAction::IsValid();
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
  dst.set_type(src.m_Type);
}

cdm::PatientAssessmentData_eType SEPatientAssessmentRequest::GetType() const
{
  return m_Type;
}
void SEPatientAssessmentRequest::SetType(cdm::PatientAssessmentData_eType Type)
{
  m_Type = Type;
}
void SEPatientAssessmentRequest::ToString(std::ostream &str) const
{
  str << "Patient Action : Assessment Request"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str  << "\n\tType: "<<GetType();
  str  << std::flush;
}