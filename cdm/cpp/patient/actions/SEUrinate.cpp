/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEUrinate.h"

SEUrinate::SEUrinate() : SEPatientAction()
{

}

SEUrinate::~SEUrinate()
{
  Clear();
}

void SEUrinate::Clear()
{
  SEPatientAction::Clear();
}

bool SEUrinate::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SEUrinate::IsActive() const
{
  return IsValid();
}

void SEUrinate::Load(const cdm::UrinateData& src, SEUrinate& dst)
{
  SEUrinate::Serialize(src, dst);
}
void SEUrinate::Serialize(const cdm::UrinateData& src, SEUrinate& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
}

cdm::UrinateData* SEUrinate::Unload(const SEUrinate& src)
{
  cdm::UrinateData* dst = new cdm::UrinateData();
  SEUrinate::Serialize(src, *dst);
  return dst;
}
void SEUrinate::Serialize(const SEUrinate& src, cdm::UrinateData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
}

void SEUrinate::ToString(std::ostream &str) const
{
  str << "Patient Action : Urinate"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << std::flush;
}
