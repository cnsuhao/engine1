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
#include "patient/actions/SETensionPneumothorax.h"
#include "properties/SEScalar0To1.h"

SETensionPneumothorax::SETensionPneumothorax() : SEPatientAction()
{
  m_Type=(cdm::eGate)-1;
  m_Side=(cdm::eSide)-1;
  m_Severity=nullptr;
}

SETensionPneumothorax::~SETensionPneumothorax()
{
  Clear();
}

void SETensionPneumothorax::Clear()
{
  SEPatientAction::Clear();
  m_Type=(cdm::eGate)-1;
  m_Side=(cdm::eSide)-1;
  SAFE_DELETE(m_Severity);
}

void SETensionPneumothorax::Load(const cdm::TensionPneumothoraxData& src, SETensionPneumothorax& dst)
{
  SETensionPneumothorax::Serialize(src, dst);
}
void SETensionPneumothorax::Serialize(const cdm::TensionPneumothoraxData& src, SETensionPneumothorax& dst)
{
  dst.Clear();
  dst.SetType(src.type());
  dst.SetSide(src.side());
  if (src.has_severity())
    SEScalar0To1::Load(src.severity(), dst.GetSeverity());
}

cdm::TensionPneumothoraxData* SETensionPneumothorax::Unload(const SETensionPneumothorax& src)
{
  cdm::TensionPneumothoraxData* dst = new cdm::TensionPneumothoraxData();
  SETensionPneumothorax::Serialize(src, *dst);
  return dst;
}
void SETensionPneumothorax::Serialize(const SETensionPneumothorax& src, cdm::TensionPneumothoraxData& dst)
{
  if (src.HasType())
    dst.set_type(src.m_Type);
  if (src.HasSide())
    dst.set_side(src.m_Side);
  if (src.HasSeverity())
    dst.set_allocated_severity(SEScalar0To1::Unload(*src.m_Severity));
}

bool SETensionPneumothorax::IsValid() const
{
  return SEPatientAction::IsValid() && HasType() && HasSide() && HasSeverity();
}

bool SETensionPneumothorax::IsActive() const
{
  return IsValid() ? !m_Severity->IsZero() : false;
}

cdm::eGate SETensionPneumothorax::GetType() const
{
  return m_Type;
}
void SETensionPneumothorax::SetType(cdm::eGate Type)
{
  m_Type = Type;
}
bool SETensionPneumothorax::HasType() const
{
  return m_Type==((cdm::eGate)-1)?false:true;
}
void SETensionPneumothorax::InvalidateType()
{
  m_Type = (cdm::eGate)-1;
}

cdm::eSide SETensionPneumothorax::GetSide() const
{
  return m_Side;
}
void SETensionPneumothorax::SetSide(cdm::eSide Side)
{
  m_Side = Side;
}
bool SETensionPneumothorax::HasSide() const
{
  return m_Side==((cdm::eSide)-1)?false:true;
}
void SETensionPneumothorax::InvalidateSide()
{
  m_Side = (cdm::eSide)-1;
}

bool SETensionPneumothorax::HasSeverity() const
{
  return m_Severity==nullptr?false:m_Severity->IsValid();
}
SEScalar0To1& SETensionPneumothorax::GetSeverity()
{
  if(m_Severity==nullptr)
    m_Severity=new SEScalar0To1();
  return *m_Severity;
}

void SETensionPneumothorax::ToString(std::ostream &str) const
{
  str << "Patient Action : Tension Pneumothorax"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tSeverity: "; HasSeverity() ? str << *m_Severity : str << "NaN";
  str  << "\n\tType: "; HasType()? str << GetType() : str << "Not Set";
  str  << "\n\tSide: "; HasSide()? str << GetSide() : str << "Not Set";
  str  << std::flush;
}