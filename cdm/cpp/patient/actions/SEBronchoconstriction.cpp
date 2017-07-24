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
  dst.Clear();
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