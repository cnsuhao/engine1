/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/physiology/SEGastrointestinalSystem.h"
#include "substance/SESubstanceManager.h"

#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarMassPerTime.h"

SEGastrointestinalSystem::SEGastrointestinalSystem(Logger* logger) : SESystem(logger)
{
  m_ChymeAbsorptionRate = nullptr;
  m_StomachContents     = nullptr;
}

SEGastrointestinalSystem::~SEGastrointestinalSystem()
{
  Clear();
}

void SEGastrointestinalSystem::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_ChymeAbsorptionRate);
  SAFE_DELETE(m_StomachContents);
}


const SEScalar* SEGastrointestinalSystem::GetScalar(const std::string& name)
{
  if(name.compare("ChymeAbsorptionRate") == 0)
    return &GetChymeAbsorptionRate();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == "StomachContents")
      return GetStomachContents().GetScalar(prop);
  }
  return nullptr;
}

void SEGastrointestinalSystem::Load(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst)
{
  SEGastrointestinalSystem::Serialize(src, dst);
}
void SEGastrointestinalSystem::Serialize(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst)
{
  dst.Clear();
  if (src.has_chymeabsorptionrate())
    SEScalarVolumePerTime::Load(src.chymeabsorptionrate(), dst.GetChymeAbsorptionRate());
  if (src.has_stomachcontents())
    SENutrition::Load(src.stomachcontents(), dst.GetStomachContents());
}

cdm::GastrointestinalSystemData* SEGastrointestinalSystem::Unload(const SEGastrointestinalSystem& src)
{
  cdm::GastrointestinalSystemData* dst = new cdm::GastrointestinalSystemData();
  SEGastrointestinalSystem::Serialize(src, *dst);
  return dst;
}
void SEGastrointestinalSystem::Serialize(const SEGastrointestinalSystem& src, cdm::GastrointestinalSystemData& dst)
{
  if (src.HasChymeAbsorptionRate())
    dst.set_allocated_chymeabsorptionrate(SEScalarVolumePerTime::Unload(*src.m_ChymeAbsorptionRate));
  if (src.HasStomachContents())
    dst.set_allocated_stomachcontents(SENutrition::Unload(*src.m_StomachContents));
}

bool SEGastrointestinalSystem::HasChymeAbsorptionRate() const
{
  return m_ChymeAbsorptionRate == nullptr ? false : m_ChymeAbsorptionRate->IsValid();
}
SEScalarVolumePerTime& SEGastrointestinalSystem::GetChymeAbsorptionRate()
{
  if (m_ChymeAbsorptionRate == nullptr)
    m_ChymeAbsorptionRate = new SEScalarVolumePerTime();
  return *m_ChymeAbsorptionRate;
}
double SEGastrointestinalSystem::GetChymeAbsorptionRate(const VolumePerTimeUnit& unit) const
{
  if (m_ChymeAbsorptionRate == nullptr)
    return SEScalar::dNaN();
  return m_ChymeAbsorptionRate->GetValue(unit);
}

bool SEGastrointestinalSystem::HasStomachContents() const
{
  return m_StomachContents == nullptr ? false : true;
}
SENutrition& SEGastrointestinalSystem::GetStomachContents()
{
  if (m_StomachContents == nullptr)
    m_StomachContents = new SENutrition(GetLogger());
  return *m_StomachContents;
}
const SENutrition* SEGastrointestinalSystem::GetStomachContents() const
{
  return m_StomachContents;
}
void SEGastrointestinalSystem::RemoveStomachContents()
{
  SAFE_DELETE(m_StomachContents);
}
