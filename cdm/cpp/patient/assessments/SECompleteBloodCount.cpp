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
#include "patient/assessments/SECompleteBloodCount.h"
#include "system/physiology/SEBloodChemistrySystem.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalarMassPerVolume.h"

SECompleteBloodCount::SECompleteBloodCount(Logger* logger) : SEPatientAssessment(logger)
{
  m_Hematocrit = nullptr;
  m_Hemoglobin = nullptr;
  m_PlateletCount = nullptr;
  m_MeanCorpuscularHemoglobin = nullptr;
  m_MeanCorpuscularHemoglobinConcentration = nullptr;
  m_MeanCorpuscularVolume = nullptr;
  m_RedBloodCellCount = nullptr;
  m_WhiteBloodCellCount = nullptr;
}

SECompleteBloodCount::~SECompleteBloodCount()
{
  Clear();
}

void SECompleteBloodCount::Clear()
{
  SEPatientAssessment::Clear();
  SAFE_DELETE(m_Hematocrit);
  SAFE_DELETE(m_Hemoglobin);
  SAFE_DELETE(m_PlateletCount);
  SAFE_DELETE(m_MeanCorpuscularHemoglobin);
  SAFE_DELETE(m_MeanCorpuscularHemoglobinConcentration);
  SAFE_DELETE(m_MeanCorpuscularVolume);
  SAFE_DELETE(m_RedBloodCellCount);
  SAFE_DELETE(m_WhiteBloodCellCount);
}

void SECompleteBloodCount::Reset()
{
  SEPatientAssessment::Reset();
  INVALIDATE_PROPERTY(m_Hematocrit);
  INVALIDATE_PROPERTY(m_Hemoglobin);
  INVALIDATE_PROPERTY(m_PlateletCount);
  INVALIDATE_PROPERTY(m_MeanCorpuscularHemoglobin);
  INVALIDATE_PROPERTY(m_MeanCorpuscularHemoglobinConcentration);
  INVALIDATE_PROPERTY(m_MeanCorpuscularVolume);
  INVALIDATE_PROPERTY(m_RedBloodCellCount);
  INVALIDATE_PROPERTY(m_WhiteBloodCellCount);

}

void SECompleteBloodCount::Load(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst)
{
  SECompleteBloodCount::Serialize(src, dst);
}
void SECompleteBloodCount::Serialize(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst)
{
  dst.Clear();
  if (src.has_hematocrit())
    SEScalar0To1::Load(src.hematocrit(), dst.GetHematocrit());
  if (src.has_hemoglobin())
    SEScalarMassPerVolume::Load(src.hemoglobin(), dst.GetHemoglobin());
  if (src.has_plateletcount())
    SEScalarAmountPerVolume::Load(src.plateletcount(), dst.GetPlateletCount());
  if (src.has_meancorpuscularhemoglobin())
    SEScalarMassPerAmount::Load(src.meancorpuscularhemoglobin(), dst.GetMeanCorpuscularHemoglobin());
  if (src.has_meancorpuscularhemoglobinconcentration())
    SEScalarMassPerVolume::Load(src.meancorpuscularhemoglobinconcentration(), dst.GetMeanCorpuscularHemoglobinConcentration());
  if (src.has_meancorpuscularvolume())
    SEScalarVolume::Load(src.meancorpuscularvolume(), dst.GetMeanCorpuscularVolume());
  if (src.has_redbloodcellcount())
    SEScalarAmountPerVolume::Load(src.redbloodcellcount(), dst.GetRedBloodCellCount());
  if (src.has_whitebloodcellcount())
    SEScalarAmountPerVolume::Load(src.whitebloodcellcount(), dst.GetWhiteBloodCellCount());
}

cdm::CompleteBloodCountData* SECompleteBloodCount::Unload(const SECompleteBloodCount& src)
{
  cdm::CompleteBloodCountData* dst = new cdm::CompleteBloodCountData();
  SECompleteBloodCount::Serialize(src, *dst);
  return dst;
}
void SECompleteBloodCount::Serialize(const SECompleteBloodCount& src, cdm::CompleteBloodCountData& dst)
{
  if (src.HasHematocrit())
    dst.set_allocated_hematocrit(SEScalar0To1::Unload(*src.m_Hematocrit());
  if (src.HasHemoglobin())
    dst.set_allocated_hemoglobin(SEScalarMassPerVolume::Unload(*src.m_Hemoglobin());
  if (src.HasPlateletCount())
    dst.set_allocated_plateletcount(SEScalarAmountPerVolume::Unload(*src.m_PlateletCount());
  if (src.HasMeanCorpuscularHemoglobin())
    dst.set_allocated_meancorpuscularhemoglobin(SEScalarMassPerAmount::Unload(*src.m_MeanCorpuscularHemoglobin());
  if (src.HasMeanCorpuscularHemoglobinConcentration())
    dst.set_allocated_meancorpuscularhemoglobinconcentration(SEScalarMassPerVolume::Unload(*src.m_MeanCorpuscularHemoglobinConcentration());
  if (src.HasMeanCorpuscularVolume())
    dst.set_allocated_meancorpuscularvolume(SEScalarVolume::Unload(*src.m_MeanCorpuscularVolume());
  if (src.HasRedBloodCellCount())
    dst.set_allocated_redbloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_RedBloodCellCount());
  if (src.HasWhiteBloodCellCount())
    dst.set_allocated_whitebloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_WhiteBloodCellCount());
}

bool SECompleteBloodCount::HasHematocrit()
{
  return m_Hematocrit == nullptr ? false : m_Hematocrit->IsValid();
}
SEScalar0To1& SECompleteBloodCount::GetHematocrit()
{
  if (m_Hematocrit == nullptr)
    m_Hematocrit = new SEScalar0To1();
  return *m_Hematocrit;
}

bool SECompleteBloodCount::HasHemoglobin()
{
  return m_Hemoglobin == nullptr ? false : m_Hemoglobin->IsValid();
}
SEScalarMassPerVolume& SECompleteBloodCount::GetHemoglobin()
{
  if (m_Hemoglobin == nullptr)
    m_Hemoglobin = new SEScalarMassPerVolume();
  return *m_Hemoglobin;
}

bool SECompleteBloodCount::HasPlateletCount()
{
  return m_PlateletCount == nullptr ? false : m_PlateletCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetPlateletCount()
{
  if (m_PlateletCount == nullptr)
    m_PlateletCount = new SEScalarAmountPerVolume();
  return *m_PlateletCount;
}

bool SECompleteBloodCount::HasMeanCorpuscularHemoglobin()
{
  return m_MeanCorpuscularHemoglobin == nullptr ? false : m_MeanCorpuscularHemoglobin->IsValid();
}
SEScalarMassPerAmount& SECompleteBloodCount::GetMeanCorpuscularHemoglobin()
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    m_MeanCorpuscularHemoglobin = new SEScalarMassPerAmount();
  return *m_MeanCorpuscularHemoglobin;
}

bool SECompleteBloodCount::HasMeanCorpuscularHemoglobinConcentration()
{
  return m_MeanCorpuscularHemoglobinConcentration == nullptr ? false : m_MeanCorpuscularHemoglobinConcentration->IsValid();
}
SEScalarMassPerVolume& SECompleteBloodCount::GetMeanCorpuscularHemoglobinConcentration()
{
  if (m_MeanCorpuscularHemoglobinConcentration == nullptr)
    m_MeanCorpuscularHemoglobinConcentration = new SEScalarMassPerVolume();
  return *m_MeanCorpuscularHemoglobinConcentration;
}

bool SECompleteBloodCount::HasMeanCorpuscularVolume()
{
  return m_MeanCorpuscularVolume == nullptr ? false : m_MeanCorpuscularVolume->IsValid();
}
SEScalarVolume& SECompleteBloodCount::GetMeanCorpuscularVolume()
{
  if (m_MeanCorpuscularVolume == nullptr)
    m_MeanCorpuscularVolume = new SEScalarVolume();
  return *m_MeanCorpuscularVolume;
}

bool SECompleteBloodCount::HasRedBloodCellCount()
{
  return m_RedBloodCellCount == nullptr ? false : m_RedBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetRedBloodCellCount()
{
  if (m_RedBloodCellCount == nullptr)
    m_RedBloodCellCount = new SEScalarAmountPerVolume();
  return *m_RedBloodCellCount;
}

bool SECompleteBloodCount::HasWhiteBloodCellCount()
{
  return m_WhiteBloodCellCount == nullptr ? false : m_WhiteBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetWhiteBloodCellCount()
{
  if (m_WhiteBloodCellCount == nullptr)
    m_WhiteBloodCellCount = new SEScalarAmountPerVolume();
  return *m_WhiteBloodCellCount;
}