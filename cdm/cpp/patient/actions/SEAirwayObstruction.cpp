/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEAirwayObstruction.h"
#include "properties/SEScalar0To1.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SEAirwayObstruction::SEAirwayObstruction() : SEPatientAction()
{
  m_Severity=nullptr;
}

SEAirwayObstruction::~SEAirwayObstruction()
{
  Clear();
}

void SEAirwayObstruction::Clear()
{
  
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
  
}

bool SEAirwayObstruction::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEAirwayObstruction::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEAirwayObstruction::Load(const cdm::AirwayObstructionData& src, SEAirwayObstruction& dst)
{
  SEAirwayObstruction::Serialize(src, dst);
}
void SEAirwayObstruction::Serialize(const cdm::AirwayObstructionData& src, SEAirwayObstruction& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::AirwayObstructionData* SEAirwayObstruction::Unload(const SEAirwayObstruction& src)
{
  cdm::AirwayObstructionData* dst = new cdm::AirwayObstructionData();
  SEAirwayObstruction::Serialize(src, *dst);
  return dst;
}
void SEAirwayObstruction::Serialize(const SEAirwayObstruction& src, cdm::AirwayObstructionData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}


bool SEAirwayObstruction::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}

SEScalar0To1& SEAirwayObstruction::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SEAirwayObstruction::ToString(std::ostream &str) const
{
  str << "Patient Action : Airway Obstruction"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "Not Set";
  str << std::flush;
}