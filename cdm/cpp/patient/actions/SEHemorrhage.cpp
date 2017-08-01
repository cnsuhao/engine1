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
#include "patient/actions/SEHemorrhage.h"
#include "properties/SEScalarVolumePerTime.h"

SEHemorrhage::SEHemorrhage() : SEPatientAction()
{
  m_Compartment = "";
  m_Rate=nullptr;
}

SEHemorrhage::~SEHemorrhage()
{
  Clear();
}

void SEHemorrhage::Clear()
{
  SEPatientAction::Clear();
  m_Compartment = "";
  SAFE_DELETE(m_Rate);
}

bool SEHemorrhage::IsValid() const
{
  return SEPatientAction::IsValid() && HasCompartment() && HasRate();
}

bool SEHemorrhage::IsActive() const
{
  return IsValid() ? !m_Rate->IsZero() : false;
}

void SEHemorrhage::Load(const cdm::HemorrhageData& src, SEHemorrhage& dst)
{
  SEHemorrhage::Serialize(src, dst);
}
void SEHemorrhage::Serialize(const cdm::HemorrhageData& src, SEHemorrhage& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_rate())
    SEScalarVolumePerTime::Load(src.rate(), dst.GetRate());
  dst.m_Compartment = src.compartment();
}

cdm::HemorrhageData* SEHemorrhage::Unload(const SEHemorrhage& src)
{
  cdm::HemorrhageData* dst = new cdm::HemorrhageData();
  SEHemorrhage::Serialize(src, *dst);
  return dst;
}
void SEHemorrhage::Serialize(const SEHemorrhage& src, cdm::HemorrhageData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasRate())
    dst.set_allocated_rate(SEScalarVolumePerTime::Unload(*src.m_Rate));
  if (src.HasCompartment())
    dst.set_compartment(src.m_Compartment);
}

std::string SEHemorrhage::GetCompartment() const
{
  return m_Compartment;
}

void SEHemorrhage::SetCompartment(const std::string& name)
{
  m_Compartment = name;
}

bool SEHemorrhage::HasCompartment() const
{
  return !m_Compartment.empty();
}

void SEHemorrhage::InvalidateCompartment()
{
  m_Compartment = "";
}

bool SEHemorrhage::HasRate() const
{
  return m_Rate==nullptr?false:m_Rate->IsValid();
}

SEScalarVolumePerTime& SEHemorrhage::GetRate()
{
  if(m_Rate==nullptr)
    m_Rate=new SEScalarVolumePerTime();
  return *m_Rate;
}

void SEHemorrhage::ToString(std::ostream &str) const
{
  str << "Patient Action : Hemorrhage"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tRate: "; HasRate() ? str << *m_Rate : str << "NaN";
  str << "\n\tFor Compartment: "; HasCompartment()? str << GetCompartment() : str << "No Compartment Set"; 
  str << std::flush;
}
