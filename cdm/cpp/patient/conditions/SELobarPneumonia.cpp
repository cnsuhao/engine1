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
#include "patient/conditions/SELobarPneumonia.h"
#include "properties/SEScalar0To1.h"

SELobarPneumonia::SELobarPneumonia() : SEPatientCondition()
{
  m_Severity = nullptr;
  m_LeftLungAffected = nullptr;
  m_RightLungAffected = nullptr;
}

SELobarPneumonia::~SELobarPneumonia()
{
  Clear();
}

void SELobarPneumonia::Clear()
{
  SEPatientCondition::Clear();
  SAFE_DELETE(m_Severity);
  SAFE_DELETE(m_LeftLungAffected);
  SAFE_DELETE(m_RightLungAffected);
}

bool SELobarPneumonia::IsValid() const
{
  return SEPatientCondition::IsValid() && HasSeverity() && HasLeftLungAffected() && HasRightLungAffected();
}

void SELobarPneumonia::Load(const cdm::LobarPneumoniaData& src, SELobarPneumonia& dst)
{
  SELobarPneumonia::Serialize(src, dst);
}
void SELobarPneumonia::Serialize(const cdm::LobarPneumoniaData& src, SELobarPneumonia& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
  if (src.has_leftlungaffected())
    SEScalar0To1::Load(src.leftlungaffected(), dst.GetLeftLungAffected());
  if (src.has_rightlungaffected())
    SEScalar0To1::Load(src.rightlungaffected(), dst.GetRightLungAffected());
}

cdm::LobarPneumoniaData* SELobarPneumonia::Unload(const SELobarPneumonia& src)
{
  cdm::LobarPneumoniaData* dst = new cdm::LobarPneumoniaData();
  SELobarPneumonia::Serialize(src, *dst);
  return dst;
}
void SELobarPneumonia::Serialize(const SELobarPneumonia& src, cdm::LobarPneumoniaData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
  if (src.HasRightLungAffected())
    dst.set_allocated_rightlungaffected(SEScalar0To1::Unload(*src.m_RightLungAffected));
  if (src.HasLeftLungAffected())
    dst.set_allocated_leftlungaffected(SEScalar0To1::Unload(*src.m_LeftLungAffected));
}

bool SELobarPneumonia::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}
SEScalar0To1& SELobarPneumonia::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

bool SELobarPneumonia::HasLeftLungAffected() const
{
  return m_LeftLungAffected == nullptr ? false : m_LeftLungAffected->IsValid();
}
SEScalar0To1& SELobarPneumonia::GetLeftLungAffected()
{
  if (m_LeftLungAffected == nullptr)
    m_LeftLungAffected = new SEScalar0To1();
  return *m_LeftLungAffected;
}

bool SELobarPneumonia::HasRightLungAffected() const
{
  return m_RightLungAffected == nullptr ? false : m_RightLungAffected->IsValid();
}
SEScalar0To1& SELobarPneumonia::GetRightLungAffected()
{
  if (m_RightLungAffected == nullptr)
    m_RightLungAffected = new SEScalar0To1();
  return *m_RightLungAffected;
}

void SELobarPneumonia::ToString(std::ostream &str) const
{
  str << "Patient Condition : Lobar Pneumonia"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "NaN";
  str << "\n\tLeftLungAffected: "; HasLeftLungAffected() ? str << *m_LeftLungAffected : str << "NaN";
  str << "\n\tRightLungAffected: "; HasRightLungAffected() ? str << *m_RightLungAffected : str << "NaN";
  str << std::flush;
}
