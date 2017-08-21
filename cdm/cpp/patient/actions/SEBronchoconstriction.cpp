/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEBronchoconstriction.h"
#include "properties/SEScalar0To1.h"

SEBronchoconstriction::SEBronchoconstriction() : SEPatientAction()
{
  m_Severity=nullptr;
}

SEBronchoconstriction::~SEBronchoconstriction()
{
  Clear();
}

void SEBronchoconstriction::Clear()
{
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEBronchoconstriction::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEBronchoconstriction::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEBronchoconstriction::Load(const cdm::BronchoconstrictionData& src, SEBronchoconstriction& dst)
{
  SEBronchoconstriction::Serialize(src, dst);
}
void SEBronchoconstriction::Serialize(const cdm::BronchoconstrictionData& src, SEBronchoconstriction& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::BronchoconstrictionData* SEBronchoconstriction::Unload(const SEBronchoconstriction& src)
{
  cdm::BronchoconstrictionData* dst = new cdm::BronchoconstrictionData();
  SEBronchoconstriction::Serialize(src, *dst);
  return dst;
}
void SEBronchoconstriction::Serialize(const SEBronchoconstriction& src, cdm::BronchoconstrictionData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}


bool SEBronchoconstriction::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}
SEScalar0To1& SEBronchoconstriction::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SEBronchoconstriction::ToString(std::ostream &str) const
{
  str << "Patient Action : Bronchoconstriction"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "NaN";
  str <<std::flush;
}