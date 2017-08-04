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
#include "system/environment/SEAppliedTemperature.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarTemperature.h"

SEAppliedTemperature::SEAppliedTemperature(Logger* logger) : Loggable(logger)
{
  m_Temperature = nullptr;
  m_SurfaceArea = nullptr;
  m_SurfaceAreaFraction = nullptr;
  m_State = cdm::eSwitch::Off;
}

SEAppliedTemperature::~SEAppliedTemperature()
{
  Clear();
}

void SEAppliedTemperature::Clear()
{
  SAFE_DELETE(m_Temperature);
  SAFE_DELETE(m_SurfaceArea);
  SAFE_DELETE(m_SurfaceAreaFraction);
  m_State = cdm::eSwitch::Off;
}

const SEScalar* SEAppliedTemperature::GetScalar(const std::string& name)
{
  if (name.compare("Temperature") == 0)
    return &GetTemperature();
  if (name.compare("SurfaceArea") == 0)
    return &GetSurfaceArea();
  if (name.compare("SurfaceAreaFraction") == 0)
    return &GetSurfaceAreaFraction();
  return nullptr;
}

void SEAppliedTemperature::Load(const cdm::EnvironmentData_AppliedTemperatureData& src, SEAppliedTemperature& dst)
{
  SEAppliedTemperature::Serialize(src, dst);
}
void SEAppliedTemperature::Serialize(const cdm::EnvironmentData_AppliedTemperatureData& src, SEAppliedTemperature& dst)
{
  dst.Clear();
  if (src.has_temperature())
    SEScalarTemperature::Load(src.temperature(), dst.GetTemperature());
  if (src.has_surfacearea())
    SEScalarArea::Load(src.surfacearea(), dst.GetSurfaceArea());
  if (src.has_surfaceareafraction())
    SEScalar0To1::Load(src.surfaceareafraction(), dst.GetSurfaceAreaFraction());
}

cdm::EnvironmentData_AppliedTemperatureData* SEAppliedTemperature::Unload(const SEAppliedTemperature& src)
{
  cdm::EnvironmentData_AppliedTemperatureData* dst = new cdm::EnvironmentData_AppliedTemperatureData();
  SEAppliedTemperature::Serialize(src, *dst);
  return dst;
}
void SEAppliedTemperature::Serialize(const SEAppliedTemperature& src, cdm::EnvironmentData_AppliedTemperatureData& dst)
{
  if (src.HasTemperature())
    dst.set_allocated_temperature(SEScalarTemperature::Unload(*src.m_Temperature));
  if (src.HasSurfaceArea())
    dst.set_allocated_surfacearea(SEScalarArea::Unload(*src.m_SurfaceArea));
  if (src.HasSurfaceAreaFraction())
    dst.set_allocated_surfaceareafraction(SEScalar0To1::Unload(*src.m_SurfaceAreaFraction));
}

bool SEAppliedTemperature::HasTemperature() const
{
  return m_Temperature == nullptr ? false : m_Temperature->IsValid();
}
SEScalarTemperature& SEAppliedTemperature::GetTemperature()
{
  if (m_Temperature == nullptr)
    m_Temperature = new SEScalarTemperature();
  return *m_Temperature;
}
double SEAppliedTemperature::GetTemperature(const TemperatureUnit& unit) const
{
  if (m_Temperature == nullptr)
    return SEScalar::dNaN();
  return m_Temperature->GetValue(unit);
}

bool SEAppliedTemperature::HasSurfaceArea() const
{
  return m_SurfaceArea == nullptr ? false : m_SurfaceArea->IsValid();
}
SEScalarArea& SEAppliedTemperature::GetSurfaceArea()
{
  if (m_SurfaceArea == nullptr)
    m_SurfaceArea = new SEScalarArea();
  return *m_SurfaceArea;
}
double SEAppliedTemperature::GetSurfaceArea(const AreaUnit& unit) const
{
  if (m_SurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceArea->GetValue(unit);
}

bool SEAppliedTemperature::HasSurfaceAreaFraction() const
{
  return m_SurfaceAreaFraction == nullptr ? false : m_SurfaceAreaFraction->IsValid();
}
SEScalar0To1& SEAppliedTemperature::GetSurfaceAreaFraction()
{
  if (m_SurfaceAreaFraction == nullptr)
    m_SurfaceAreaFraction = new SEScalar0To1();
  return *m_SurfaceAreaFraction;
}
double SEAppliedTemperature::GetSurfaceAreaFraction() const
{
  if (m_SurfaceAreaFraction == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceAreaFraction->GetValue();
}

cdm::eSwitch SEAppliedTemperature::GetState() const
{
  return m_State;
}
void SEAppliedTemperature::SetState(cdm::eSwitch onOff)
{
  m_State = onOff;
}



void SEAppliedTemperature::ToString(std::ostream &str) const
{
  str << "Applied Temperature :";  
  str << "\n\tTemperature :";         HasTemperature() ? str << *m_Temperature : str << "NaN";
  str << "\n\tSurfaceArea :";         HasSurfaceArea() ? str << *m_SurfaceArea : str << "NaN";
  str << "\n\tSurfaceAreaFraction :"; HasSurfaceAreaFraction() ? str << *m_SurfaceAreaFraction : str << "NaN";
  str << "\n\tState :" <<  m_State;
  str << std::flush;
}