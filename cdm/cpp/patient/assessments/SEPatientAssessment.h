/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
PROTO_PUSH
#include "bind/cdm/PatientAssessments.pb.h"
PROTO_POP

/**
 * @brief
 * Data formed at a level of a clinicians report. 
 * This is high level data, such as a mean or generalized data 
 * value intended to give a genaral overview of the patient (SEPatientAssessment) or other systems
 */
class CDM_DECL SEPatientAssessment : public Loggable
{
public:

  SEPatientAssessment(Logger* logger);
  virtual ~SEPatientAssessment();

  virtual void Clear();

  virtual std::string Save() const = 0;
  virtual void SaveFile(const std::string& filename) const = 0;

protected:
  static void Serialize(const cdm::PatientAssessmentData& src, SEPatientAssessment& dst);
  static void Serialize(const SEPatientAssessment& src, cdm::PatientAssessmentData& dst);

public:
  
};  