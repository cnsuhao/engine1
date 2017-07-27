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

#pragma once
#include "patient/actions/SEPatientAction.h"

class DLL_DECL SEPatientAssessmentRequest : public SEPatientAction
{
public:

  SEPatientAssessmentRequest();
  virtual ~SEPatientAssessmentRequest();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst);
  static cdm::PatientAssessmentRequestData* Unload(const SEPatientAssessmentRequest& src);
protected:
  static void Serialize(const cdm::PatientAssessmentRequestData& src, SEPatientAssessmentRequest& dst);
  static void Serialize(const SEPatientAssessmentRequest& src, cdm::PatientAssessmentRequestData& dst);

public:

  virtual cdm::PatientAssessmentRequestData_eAssessmentType GetType() const;
  virtual void SetType(cdm::PatientAssessmentRequestData_eAssessmentType type);
  virtual bool HasType() const;
  virtual void InvalidateType();

  virtual void ToString(std::ostream &str) const;
  
protected:

  cdm::PatientAssessmentRequestData_eAssessmentType m_Type;
}; 