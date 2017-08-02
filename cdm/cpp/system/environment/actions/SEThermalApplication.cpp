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
#include "system/environment/actions/SEThermalApplication.h"
#include "system/environment/SEActiveHeating.h"
#include "system/environment/SEActiveCooling.h"
#include "system/environment/SEAppliedTemperature.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarTemperature.h"

SEThermalApplication::SEThermalApplication() : SEEnvironmentAction()
{
  m_ClearContents = true;
  m_ActiveHeating = nullptr;
  m_ActiveCooling = nullptr;
  m_AppliedTemperature = nullptr;
}

SEThermalApplication::~SEThermalApplication()
{
  Clear();
}

void SEThermalApplication::Clear()
{
  SEEnvironmentAction::Clear();
  if (m_ClearContents)
  {
    SAFE_DELETE(m_ActiveHeating);
    SAFE_DELETE(m_ActiveCooling);
    SAFE_DELETE(m_AppliedTemperature);
  }
}

bool SEThermalApplication::IsValid() const
{
  return SEEnvironmentAction::IsValid();
}

bool SEThermalApplication::IsActive() const
{
  if (HasActiveHeating() && m_ActiveHeating->GetPower().IsPositive())
    return true;
  if (HasActiveCooling() && m_ActiveCooling->GetPower().IsPositive())
    return true;
  if (HasAppliedTemperature() && m_AppliedTemperature->GetState() == cdm::eSwitch::On)
    return true;
  return false;
}

void SEThermalApplication::Load(const cdm::ThermalApplicationData& src, SEThermalApplication& dst)
{
  SEThermalApplication::Serialize(src, dst);
}
void SEThermalApplication::Serialize(const cdm::ThermalApplicationData& src, SEThermalApplication& dst)
{
  SEEnvironmentAction::Serialize(src.environmentaction(), dst);
  if (src.has_activeheating())
    SEActiveHeating::Load(src.activeheating(), dst.GetActiveHeating());
  if (src.has_activecooling())
    SEActiveCooling::Load(src.activecooling(), dst.GetActiveCooling());
  if (src.has_appliedtemperature())
    SEAppliedTemperature::Load(src.appliedtemperature(), dst.GetAppliedTemperature());
}

cdm::ThermalApplicationData* SEThermalApplication::Unload(const SEThermalApplication& src)
{
  cdm::ThermalApplicationData* dst = new cdm::ThermalApplicationData();
  SEThermalApplication::Serialize(src, *dst);
  return dst;
}
void SEThermalApplication::Serialize(const SEThermalApplication& src, cdm::ThermalApplicationData& dst)
{
  SEEnvironmentAction::Serialize(src, *dst.mutable_environmentaction());
  if (src.HasActiveHeating())
    dst.set_allocated_activeheating(SEActiveHeating::Unload(*src.m_ActiveHeating));
  if (src.HasActiveCooling())
    dst.set_allocated_activecooling(SEActiveCooling::Unload(*src.m_ActiveCooling));
  if (src.HasAppliedTemperature())
    dst.set_allocated_appliedtemperature(SEAppliedTemperature::Unload(*src.m_AppliedTemperature));
}

bool SEThermalApplication::HasActiveHeating() const
{
  return m_ActiveHeating != nullptr;
}
SEActiveHeating& SEThermalApplication::GetActiveHeating()
{
  if (m_ActiveHeating == nullptr)
    m_ActiveHeating = new SEActiveHeating(GetLogger());
  return *m_ActiveHeating;
}
void SEThermalApplication::RemoveActiveHeating()
{
  SAFE_DELETE(m_ActiveHeating);
}

bool SEThermalApplication::HasActiveCooling() const
{
  return m_ActiveCooling != nullptr;
}
SEActiveCooling& SEThermalApplication::GetActiveCooling()
{
  if (m_ActiveCooling == nullptr)
    m_ActiveCooling = new SEActiveCooling(GetLogger());
  return *m_ActiveCooling;
}
void SEThermalApplication::RemoveActiveCooling()
{
  SAFE_DELETE(m_ActiveCooling);
}

bool SEThermalApplication::HasAppliedTemperature() const
{
  return m_AppliedTemperature != nullptr;
}
SEAppliedTemperature& SEThermalApplication::GetAppliedTemperature()
{
  if (m_AppliedTemperature == nullptr)
    m_AppliedTemperature = new SEAppliedTemperature(GetLogger());
  return *m_AppliedTemperature;
}
void SEThermalApplication::RemoveAppliedTemperature()
{
  SAFE_DELETE(m_AppliedTemperature);
}


void SEThermalApplication::ToString(std::ostream &str) const
{
  str << "Environment Action : Thermal Application";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  if (HasActiveHeating())
  {
    str << "\n\t";
    m_ActiveHeating->ToString(str);
  }
  else
    str << "\n\tNo Active Heating";

  if (HasActiveCooling())
  {
    str << "\n\t";
    m_ActiveCooling->ToString(str);
  }
  else
    str << "\n\tNo Active Cooling";

  if (HasAppliedTemperature())
  {
    str << "\n\t";
    m_AppliedTemperature->ToString(str);
  }
  else
    str << "\n\tNo Applied Temperature";
  
  str << std::flush;
}