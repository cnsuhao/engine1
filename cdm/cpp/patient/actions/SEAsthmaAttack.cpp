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
#include "patient/actions/SEAsthmaAttack.h"
#include "properties/SEScalar0To1.h"

SEAsthmaAttack::SEAsthmaAttack() : SEPatientAction()
{
  m_Severity=nullptr;
}

SEAsthmaAttack::~SEAsthmaAttack()
{
  Clear();
}

void SEAsthmaAttack::Clear()
{
  SEPatientAction::Clear();
  SAFE_DELETE(m_Severity);
}

bool SEAsthmaAttack::IsValid() const
{
  return SEPatientAction::IsValid() && HasSeverity();
}

bool SEAsthmaAttack::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

void SEAsthmaAttack::Load(const cdm::AsthmaAttackData& src, SEAsthmaAttack& dst)
{
  SEAsthmaAttack::Serialize(src, dst);
}
void SEAsthmaAttack::Serialize(const cdm::AsthmaAttackData& src, SEAsthmaAttack& dst)
{
  dst.Clear();
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::AsthmaAttackData* SEAsthmaAttack::Unload(const SEAsthmaAttack& src)
{
  cdm::AsthmaAttackData* dst = new cdm::AsthmaAttackData();
  SEAsthmaAttack::Serialize(src, *dst);
  return dst;
}
void SEAsthmaAttack::Serialize(const SEAsthmaAttack& src, cdm::AsthmaAttackData& dst)
{
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}


bool SEAsthmaAttack::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}
SEScalar0To1& SEAsthmaAttack::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SEAsthmaAttack::ToString(std::ostream &str) const
{
  str << "Patient Action : AsthmaAttack"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "NaN";
  str <<std::flush;
}
