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
#include "system/environment/SEActiveHeating.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarTemperature.h"

SEActiveHeating::SEActiveHeating(Logger* logger) : Loggable(logger)
{
  m_Power = nullptr;
  m_SurfaceArea = nullptr;
  m_SurfaceAreaFraction = nullptr;
}

SEActiveHeating::~SEActiveHeating()
{
  Clear();
}

void SEActiveHeating::Clear()
{
  SAFE_DELETE(m_Power);
  SAFE_DELETE(m_SurfaceArea);
  SAFE_DELETE(m_SurfaceAreaFraction);
}

void SEActiveHeating::Reset()
{
  Clear();
}

const SEScalar* SEActiveHeating::GetScalar(const std::string& name)
{
  if (name.compare("Power") == 0)
    return &GetPower();
  if (name.compare("SurfaceArea") == 0)
    return &GetSurfaceArea();
  if (name.compare("SurfaceAreaFraction") == 0)
    return &GetSurfaceAreaFraction();
  return nullptr;
}

void SEActiveHeating::Load(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveHeating& dst)
{
  SEActiveHeating::Serialize(src, dst);
}
void SEActiveHeating::Serialize(const cdm::EnvironmentData_ActiveConditioningData& src, SEActiveHeating& dst)
{
  SEActiveHeating::Serialize(src.activeHeating(), dst);
  dst.Clear();
  if (src.has_power())
    SEScalarPower::Load(src.power(), dst.GetPower());
  if (src.has_surfacearea())
    SEScalarArea::Load(src.surfacearea(), dst.GetSurfaceArea());
  if (src.has_surfaceareafraction())
    SEScalar0To1::Load(src.surfaceareafraction(), dst.GetSurfaceAreaFraction());
}

cdm::EnvironmentData_ActiveConditioningData* SEActiveHeating::Unload(const SEActiveHeating& src)
{
  cdm::EnvironmentData_ActiveConditioningData* dst = new cdm::EnvironmentData_ActiveConditioningData();
  SEActiveHeating::Serialize(src, *dst);
  return dst;
}
void SEActiveHeating::Serialize(const SEActiveHeating& src, cdm::EnvironmentData_ActiveConditioningData& dst)
{
  SEActiveHeating::Serialize(src, *dst.mutable_activeHeating());
  if (src.HasPower())
    dst.set_allocated_power(SEScalarPower::Unload(*src.m_Power));
  if (src.HasSurfaceArea())
    dst.set_allocated_surfacearea(SEScalarArea::Unload(*src.m_SurfaceArea));
  if (src.HasSurfaceAreaFraction())
    dst.set_allocated_surfaceareafraction(SEScalar0To1::Unload(*src.m_SurfaceAreaFraction));
}

bool SEActiveHeating::HasPower() const
{
  return m_Power == nullptr ? false : m_Power->IsValid();
}
SEScalarPower& SEActiveHeating::GetPower()
{
  if (m_Power == nullptr)
    m_Power = new SEScalarPower();
  return *m_Power;
}
double SEActiveHeating::GetPower(const PowerUnit& unit) const
{
  if (m_Power == nullptr)
    return SEScalar::dNaN();
  return m_Power->GetValue(unit);
}

bool SEActiveHeating::HasSurfaceArea() const
{
  return m_SurfaceArea == nullptr ? false : m_SurfaceArea->IsValid();
}
SEScalarArea& SEActiveHeating::GetSurfaceArea()
{
  if (m_SurfaceArea == nullptr)
    m_SurfaceArea = new SEScalarArea();
  return *m_SurfaceArea;
}
double SEActiveHeating::GetSurfaceArea(const AreaUnit& unit) const
{
  if (m_SurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceArea->GetValue(unit);
}

bool SEActiveHeating::HasSurfaceAreaFraction() const
{
  return m_SurfaceAreaFraction == nullptr ? false : m_SurfaceAreaFraction->IsValid();
}
SEScalar0To1& SEActiveHeating::GetSurfaceAreaFraction()
{
  if (m_SurfaceAreaFraction == nullptr)
    m_SurfaceAreaFraction = new SEScalar0To1();
  return *m_SurfaceAreaFraction;
}
double SEActiveHeating::GetSurfaceAreaFraction() const
{
  if (m_SurfaceAreaFraction == nullptr)
    return SEScalar::dNaN();
  return m_SurfaceAreaFraction->GetValue();
}

void SEActiveHeating::ToString(std::ostream &str) const
{
  str << "Active Heating :";
  str << "\n\tPower :";                HasPower() ? str << *m_Power : str << "NaN";
  str << "\n\tSurfaceArea :";          HasSurfaceArea() ? str << *m_SurfaceArea : str << "NaN";
  str << "\n\tSurfaceAreaFraction :";  HasSurfaceAreaFraction() ? str << *m_SurfaceAreaFraction : str << "NaN";
  str << std::flush;
}