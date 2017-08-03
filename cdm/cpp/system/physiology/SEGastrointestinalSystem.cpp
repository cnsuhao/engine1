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
#include "system/physiology/SEGastrointestinalSystem.h"
#include "substance/SESubstanceManager.h"

#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarMassPerTime.h"

SEGastrointestinalSystem::SEGastrointestinalSystem(Logger* logger) : SESystem(logger)
{
  m_ChymeAbsorbtionRate = nullptr;
  m_StomachContents = nullptr;
}

SEGastrointestinalSystem::~SEGastrointestinalSystem()
{
  Clear();
}

void SEGastrointestinalSystem::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_ChymeAbsorbtionRate);
  SAFE_DELETE(m_StomachContents);
}


const SEScalar* SEGastrointestinalSystem::GetScalar(const std::string& name)
{
  if(name.compare("ChymeAbsorbtionRate") == 0)
    return &GetChymeAbsorbtionRate();

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
  if (src.has_chymeabsorbtionrate())
    SEScalarVolumePerTime::Load(src.chymeabsorbtionrate(), dst.GetChymeAbsorbtionRate());
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
  if (src.HasChymeAbsorbtionRate())
    dst.set_allocated_chymeabsorbtionrate(SEScalarVolumePerTime::Unload(*src.m_ChymeAbsorbtionRate));
  if (src.HasStomachContents())
    dst.set_allocated_stomachcontents(SENutrition::Unload(*src.m_StomachContents));
}

bool SEGastrointestinalSystem::HasChymeAbsorbtionRate() const
{
  return m_ChymeAbsorbtionRate == nullptr ? false : m_ChymeAbsorbtionRate->IsValid();
}
SEScalarVolumePerTime& SEGastrointestinalSystem::GetChymeAbsorbtionRate()
{
  if (m_ChymeAbsorbtionRate == nullptr)
    m_ChymeAbsorbtionRate = new SEScalarVolumePerTime();
  return *m_ChymeAbsorbtionRate;
}
double SEGastrointestinalSystem::GetChymeAbsorbtionRate(const VolumePerTimeUnit& unit) const
{
  if (m_ChymeAbsorbtionRate == nullptr)
    return SEScalar::dNaN();
  return m_ChymeAbsorbtionRate->GetValue(unit);
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
