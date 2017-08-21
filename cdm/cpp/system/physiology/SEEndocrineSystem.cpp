/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

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


