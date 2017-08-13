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
#include "system/equipment/ElectroCardioGram/SEElectroCardioGram.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarElectricPotential.h"

SEElectroCardioGram::SEElectroCardioGram(Logger* logger) : SESystem(logger)
{
  m_Lead1ElectricPotential = nullptr;
  m_Lead2ElectricPotential = nullptr;
  m_Lead3ElectricPotential = nullptr;
  m_Lead4ElectricPotential = nullptr;
  m_Lead5ElectricPotential = nullptr;
  m_Lead6ElectricPotential = nullptr;
  m_Lead7ElectricPotential = nullptr;
  m_Lead8ElectricPotential = nullptr;
  m_Lead9ElectricPotential = nullptr;
  m_Lead10ElectricPotential = nullptr;
  m_Lead11ElectricPotential = nullptr;
  m_Lead12ElectricPotential = nullptr;
}

SEElectroCardioGram::~SEElectroCardioGram()
{
  Clear();
}

void SEElectroCardioGram::Clear()
{
  SAFE_DELETE(m_Lead1ElectricPotential);
  SAFE_DELETE(m_Lead2ElectricPotential);
  SAFE_DELETE(m_Lead3ElectricPotential);
  SAFE_DELETE(m_Lead4ElectricPotential);
  SAFE_DELETE(m_Lead5ElectricPotential);
  SAFE_DELETE(m_Lead6ElectricPotential);
  SAFE_DELETE(m_Lead7ElectricPotential);
  SAFE_DELETE(m_Lead8ElectricPotential);
  SAFE_DELETE(m_Lead9ElectricPotential);
  SAFE_DELETE(m_Lead10ElectricPotential);
  SAFE_DELETE(m_Lead11ElectricPotential);
  SAFE_DELETE(m_Lead12ElectricPotential);
}

void SEElectroCardioGram::Load(const cdm::ElectroCardioGramData& src, SEElectroCardioGram& dst)
{
  SEElectroCardioGram::Serialize(src, dst);
}
void SEElectroCardioGram::Serialize(const cdm::ElectroCardioGramData& src, SEElectroCardioGram& dst)
{
  if (src.has_lead1electricpotential())
    SEScalarElectricPotential::Load(src.lead1electricpotential(), dst.GetLead1ElectricPotential());
  if (src.has_lead2electricpotential())
    SEScalarElectricPotential::Load(src.lead2electricpotential(), dst.GetLead2ElectricPotential());
  if (src.has_lead3electricpotential())
    SEScalarElectricPotential::Load(src.lead3electricpotential(), dst.GetLead3ElectricPotential());
  if (src.has_lead4electricpotential())
    SEScalarElectricPotential::Load(src.lead4electricpotential(), dst.GetLead4ElectricPotential());
  if (src.has_lead5electricpotential())
    SEScalarElectricPotential::Load(src.lead5electricpotential(), dst.GetLead5ElectricPotential());
  if (src.has_lead6electricpotential())
    SEScalarElectricPotential::Load(src.lead6electricpotential(), dst.GetLead6ElectricPotential());
  if (src.has_lead7electricpotential())
    SEScalarElectricPotential::Load(src.lead7electricpotential(), dst.GetLead7ElectricPotential());
  if (src.has_lead8electricpotential())
    SEScalarElectricPotential::Load(src.lead8electricpotential(), dst.GetLead8ElectricPotential());
  if (src.has_lead9electricpotential())
    SEScalarElectricPotential::Load(src.lead9electricpotential(), dst.GetLead9ElectricPotential());
  if (src.has_lead10electricpotential())
    SEScalarElectricPotential::Load(src.lead10electricpotential(), dst.GetLead10ElectricPotential());
  if (src.has_lead11electricpotential())
    SEScalarElectricPotential::Load(src.lead11electricpotential(), dst.GetLead11ElectricPotential());
  if (src.has_lead12electricpotential())
    SEScalarElectricPotential::Load(src.lead12electricpotential(), dst.GetLead12ElectricPotential());
}

cdm::ElectroCardioGramData* SEElectroCardioGram::Unload(const SEElectroCardioGram& src)
{
  cdm::ElectroCardioGramData* dst = new cdm::ElectroCardioGramData();
  SEElectroCardioGram::Serialize(src,*dst);
  return dst;
}
void SEElectroCardioGram::Serialize(const SEElectroCardioGram& src, cdm::ElectroCardioGramData& dst)
{
  if (src.HasLead1ElectricPotential())
    dst.set_allocated_lead1electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead1ElectricPotential));
  if (src.HasLead2ElectricPotential())
    dst.set_allocated_lead2electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead2ElectricPotential));
  if (src.HasLead3ElectricPotential())
    dst.set_allocated_lead3electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead3ElectricPotential));
  if (src.HasLead4ElectricPotential())
    dst.set_allocated_lead4electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead4ElectricPotential));
  if (src.HasLead5ElectricPotential())
    dst.set_allocated_lead5electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead5ElectricPotential));
  if (src.HasLead6ElectricPotential())
    dst.set_allocated_lead6electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead6ElectricPotential));
  if (src.HasLead7ElectricPotential())
    dst.set_allocated_lead7electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead7ElectricPotential));
  if (src.HasLead8ElectricPotential())
    dst.set_allocated_lead8electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead8ElectricPotential));
  if (src.HasLead9ElectricPotential())
    dst.set_allocated_lead9electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead9ElectricPotential));
  if (src.HasLead10ElectricPotential())
    dst.set_allocated_lead10electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead10ElectricPotential));
  if (src.HasLead11ElectricPotential())
    dst.set_allocated_lead11electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead11ElectricPotential));
  if (src.HasLead12ElectricPotential())
    dst.set_allocated_lead12electricpotential(SEScalarElectricPotential::Unload(*src.m_Lead12ElectricPotential));
}

const SEScalar* SEElectroCardioGram::GetScalar(const std::string& name)
{
  if (name.compare("Lead1ElectricPotential") == 0)
    return &GetLead1ElectricPotential();
  if (name.compare("Lead2ElectricPotential") == 0)
    return &GetLead2ElectricPotential();
  if (name.compare("Lead3ElectricPotential") == 0)
    return &GetLead3ElectricPotential();
  if (name.compare("Lead4ElectricPotential") == 0)
    return &GetLead4ElectricPotential();
  if (name.compare("Lead5ElectricPotential") == 0)
    return &GetLead5ElectricPotential();
  if (name.compare("Lead6ElectricPotential") == 0)
    return &GetLead6ElectricPotential();
  if (name.compare("Lead7ElectricPotential") == 0)
    return &GetLead7ElectricPotential();
  if (name.compare("Lead8ElectricPotential") == 0)
    return &GetLead8ElectricPotential();
  if (name.compare("Lead9ElectricPotential") == 0)
    return &GetLead9ElectricPotential();
  if (name.compare("Lead10ElectricPotential") == 0)
    return &GetLead10ElectricPotential();
  if (name.compare("Lead11ElectricPotential") == 0)
    return &GetLead11ElectricPotential();
  if (name.compare("Lead12ElectricPotential") == 0)
    return &GetLead12ElectricPotential();
  return nullptr;
}

bool SEElectroCardioGram::HasLead1ElectricPotential() const
{
  return m_Lead1ElectricPotential == nullptr ? false : m_Lead1ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead1ElectricPotential()
{
  if (m_Lead1ElectricPotential == nullptr)
    m_Lead1ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead1ElectricPotential;
}
double SEElectroCardioGram::GetLead1ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead1ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead1ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead2ElectricPotential() const
{
  return m_Lead2ElectricPotential == nullptr ? false : m_Lead2ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead2ElectricPotential()
{
  if (m_Lead2ElectricPotential == nullptr)
    m_Lead2ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead2ElectricPotential;
}
double SEElectroCardioGram::GetLead2ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead2ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead2ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead3ElectricPotential() const
{
  return m_Lead3ElectricPotential == nullptr ? false : m_Lead3ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead3ElectricPotential()
{
  if (m_Lead3ElectricPotential == nullptr)
    m_Lead3ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead3ElectricPotential;
}
double SEElectroCardioGram::GetLead3ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead3ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead3ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead4ElectricPotential() const
{
  return m_Lead4ElectricPotential == nullptr ? false : m_Lead4ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead4ElectricPotential()
{
  if (m_Lead4ElectricPotential == nullptr)
    m_Lead4ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead4ElectricPotential;
}
double SEElectroCardioGram::GetLead4ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead4ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead4ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead5ElectricPotential() const
{
  return m_Lead5ElectricPotential == nullptr ? false : m_Lead5ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead5ElectricPotential()
{
  if (m_Lead5ElectricPotential == nullptr)
    m_Lead5ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead5ElectricPotential;
}
double SEElectroCardioGram::GetLead5ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead5ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead5ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead6ElectricPotential() const
{
  return m_Lead6ElectricPotential == nullptr ? false : m_Lead6ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead6ElectricPotential()
{
  if (m_Lead6ElectricPotential == nullptr)
    m_Lead6ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead6ElectricPotential;
}
double SEElectroCardioGram::GetLead6ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead6ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead6ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead7ElectricPotential() const
{
  return m_Lead7ElectricPotential == nullptr ? false : m_Lead7ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead7ElectricPotential()
{
  if (m_Lead7ElectricPotential == nullptr)
    m_Lead7ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead7ElectricPotential;
}
double SEElectroCardioGram::GetLead7ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead7ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead7ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead8ElectricPotential() const
{
  return m_Lead8ElectricPotential == nullptr ? false : m_Lead8ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead8ElectricPotential()
{
  if (m_Lead8ElectricPotential == nullptr)
    m_Lead8ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead8ElectricPotential;
}
double SEElectroCardioGram::GetLead8ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead8ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead8ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead9ElectricPotential() const
{
  return m_Lead9ElectricPotential == nullptr ? false : m_Lead9ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead9ElectricPotential()
{
  if (m_Lead9ElectricPotential == nullptr)
    m_Lead9ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead9ElectricPotential;
}
double SEElectroCardioGram::GetLead9ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead9ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead9ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead10ElectricPotential() const
{
  return m_Lead10ElectricPotential == nullptr ? false : m_Lead10ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead10ElectricPotential()
{
  if (m_Lead10ElectricPotential == nullptr)
    m_Lead10ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead10ElectricPotential;
}
double SEElectroCardioGram::GetLead10ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead10ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead10ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead11ElectricPotential() const
{
  return m_Lead11ElectricPotential == nullptr ? false : m_Lead11ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead11ElectricPotential()
{
  if (m_Lead11ElectricPotential == nullptr)
    m_Lead11ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead11ElectricPotential;
}
double SEElectroCardioGram::GetLead11ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead11ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead11ElectricPotential->GetValue(unit);
}

bool SEElectroCardioGram::HasLead12ElectricPotential() const
{
  return m_Lead12ElectricPotential == nullptr ? false : m_Lead12ElectricPotential->IsValid();
}
SEScalarElectricPotential& SEElectroCardioGram::GetLead12ElectricPotential()
{
  if (m_Lead12ElectricPotential == nullptr)
    m_Lead12ElectricPotential = new SEScalarElectricPotential();
  return *m_Lead12ElectricPotential;
}
double SEElectroCardioGram::GetLead12ElectricPotential(const ElectricPotentialUnit& unit) const
{
  if (m_Lead12ElectricPotential == nullptr)
    return SEScalar::dNaN();
  return m_Lead12ElectricPotential->GetValue(unit);
}