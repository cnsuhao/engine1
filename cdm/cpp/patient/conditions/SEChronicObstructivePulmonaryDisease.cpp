/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/conditions/SEChronicObstructivePulmonaryDisease.h"
#include "properties/SEScalar0To1.h"


SEChronicObstructivePulmonaryDisease::SEChronicObstructivePulmonaryDisease() : SEPatientCondition()
{
  m_BronchitisSeverity = nullptr;
  m_EmphysemaSeverity = nullptr;
}

SEChronicObstructivePulmonaryDisease::~SEChronicObstructivePulmonaryDisease()
{
  Clear();
}

void SEChronicObstructivePulmonaryDisease::Clear()
{
  SEPatientCondition::Clear();
  SAFE_DELETE(m_BronchitisSeverity);
  SAFE_DELETE(m_EmphysemaSeverity);
}

bool SEChronicObstructivePulmonaryDisease::IsValid() const
{
  return SEPatientCondition::IsValid() && HasBronchitisSeverity() && HasEmphysemaSeverity();
}

void SEChronicObstructivePulmonaryDisease::Load(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst)
{
  SEChronicObstructivePulmonaryDisease::Serialize(src, dst);
}
void SEChronicObstructivePulmonaryDisease::Serialize(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
  if (src.has_bronchitisseverity())
    SEScalar0To1::Load(src.bronchitisseverity(), dst.GetBronchitisSeverity());
  if (src.has_emphysemaseverity())
    SEScalar0To1::Load(src.emphysemaseverity(), dst.GetEmphysemaSeverity());
}

cdm::ChronicObstructivePulmonaryDiseaseData* SEChronicObstructivePulmonaryDisease::Unload(const SEChronicObstructivePulmonaryDisease& src)
{
  cdm::ChronicObstructivePulmonaryDiseaseData* dst = new cdm::ChronicObstructivePulmonaryDiseaseData();
  SEChronicObstructivePulmonaryDisease::Serialize(src, *dst);
  return dst;
}
void SEChronicObstructivePulmonaryDisease::Serialize(const SEChronicObstructivePulmonaryDisease& src, cdm::ChronicObstructivePulmonaryDiseaseData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
  if (src.HasBronchitisSeverity())
    dst.set_allocated_bronchitisseverity(SEScalar0To1::Unload(*src.m_BronchitisSeverity));
  if (src.HasEmphysemaSeverity())
    dst.set_allocated_emphysemaseverity(SEScalar0To1::Unload(*src.m_EmphysemaSeverity));
}

bool SEChronicObstructivePulmonaryDisease::HasBronchitisSeverity() const
{
  return m_BronchitisSeverity == nullptr ? false : m_BronchitisSeverity->IsValid();
}
SEScalar0To1& SEChronicObstructivePulmonaryDisease::GetBronchitisSeverity()
{
  if (m_BronchitisSeverity == nullptr)
    m_BronchitisSeverity = new SEScalar0To1();
  return *m_BronchitisSeverity;
}

bool SEChronicObstructivePulmonaryDisease::HasEmphysemaSeverity() const
{
  return m_EmphysemaSeverity == nullptr ? false : m_EmphysemaSeverity->IsValid();
}
SEScalar0To1& SEChronicObstructivePulmonaryDisease::GetEmphysemaSeverity()
{
  if (m_EmphysemaSeverity == nullptr)
    m_EmphysemaSeverity = new SEScalar0To1();
  return *m_EmphysemaSeverity;
}

void SEChronicObstructivePulmonaryDisease::ToString(std::ostream &str) const
{
  str << "Patient Condition : COPD";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tBronchitisSeverity: "; HasBronchitisSeverity() ? str << *m_BronchitisSeverity : str << "NaN";
  str << "\n\tEmphysemaSeverity: "; HasEmphysemaSeverity() ? str << *m_EmphysemaSeverity : str << "NaN";
  str << std::flush;
}


