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
#include "system/physiology/SEEndocrineSystem.h"
#include "properties/SEScalarAmountPerTime.h"

SEEndocrineSystem::SEEndocrineSystem(Logger* logger) : SESystem(logger)
{
  m_InsulinSynthesisRate = nullptr;
}

SEEndocrineSystem::~SEEndocrineSystem()
{
  Clear();
}

void SEEndocrineSystem::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_InsulinSynthesisRate);
}

const SEScalar* SEEndocrineSystem::GetScalar(const std::string& name)
{
  if (name.compare("InsulinSynthesisRate") == 0)
    return &GetInsulinSynthesisRate();
  return nullptr;
}

void SEEndocrineSystem::Load(const cdm::EndocrineSystemData& src, SEEndocrineSystem& dst)
{
  SEEndocrineSystem::Serialize(src, dst);
}
void SEEndocrineSystem::Serialize(const cdm::EndocrineSystemData& src, SEEndocrineSystem& dst)
{
  dst.Clear();
  if (src.has_insulinsynthesisrate())
    SEScalarAmountPerTime::Load(src.insulinsynthesisrate(), dst.GetInsulinSynthesisRate());
}

cdm::EndocrineSystemData* SEEndocrineSystem::Unload(const SEEndocrineSystem& src)
{
  cdm::EndocrineSystemData* dst = new cdm::EndocrineSystemData();
  SEEndocrineSystem::Serialize(src, *dst);
  return dst;
}
void SEEndocrineSystem::Serialize(const SEEndocrineSystem& src, cdm::EndocrineSystemData& dst)
{
  if (src.HasInsulinSynthesisRate())
    dst.set_allocated_insulinsynthesisrate(SEScalarAmountPerTime::Unload(*src.m_InsulinSynthesisRate));
}

bool SEEndocrineSystem::HasInsulinSynthesisRate() const
{
  return m_InsulinSynthesisRate == nullptr ? false : m_InsulinSynthesisRate->IsValid();
}
SEScalarAmountPerTime& SEEndocrineSystem::GetInsulinSynthesisRate()
{
  if (m_InsulinSynthesisRate == nullptr)
    m_InsulinSynthesisRate = new SEScalarAmountPerTime();
  return *m_InsulinSynthesisRate;
}
double SEEndocrineSystem::GetInsulinSynthesisRate(const AmountPerTimeUnit& unit) const
{
  if (m_InsulinSynthesisRate == nullptr)
    return SEScalar::dNaN();
  return m_InsulinSynthesisRate->GetValue(unit);
}


