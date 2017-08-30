/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEAcuteStress.h"
#include "properties/SEScalar0To1.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SEAcuteStress::SEAcuteStress() : SEPatientAction()
{
  m_Severity=nullptr;
}

SEAcuteStress::~SEAcuteStress()
{
  Clear();
}

void SEAcuteStress::Clear()
{
  
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
  
}

bool SEAcuteStress::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEAcuteStress::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEAcuteStress::Load(const cdm::AcuteStressData& src, SEAcuteStress& dst)
{
  SEAcuteStress::Serialize(src, dst);
}
void SEAcuteStress::Serialize(const cdm::AcuteStressData& src, SEAcuteStress& dst)
{
  SEPatientAction::Serialize(src.patientaction(),dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::AcuteStressData* SEAcuteStress::Unload(const SEAcuteStress& src)
{
  cdm::AcuteStressData* dst = new cdm::AcuteStressData();
  SEAcuteStress::Serialize(src, *dst);
  return dst;
}
void SEAcuteStress::Serialize(const SEAcuteStress& src, cdm::AcuteStressData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}


bool SEAcuteStress::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}

SEScalar0To1& SEAcuteStress::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SEAcuteStress::ToString(std::ostream &str) const
{
  str << "Patient Action : Acute Stress"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "Not Set";
  str << std::flush;
}