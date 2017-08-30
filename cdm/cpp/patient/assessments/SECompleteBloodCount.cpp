/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/assessments/SECompleteBloodCount.h"
#include "system/physiology/SEBloodChemistrySystem.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalarMassPerVolume.h"
PROTO_PUSH
#include "bind/cdm/PatientAssessments.pb.h"
PROTO_POP
#include <google/protobuf/text_format.h>

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


std::string SECompleteBloodCount::Save() const
{
  std::string content;
  cdm::CompleteBloodCountData* src = SECompleteBloodCount::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  return content;
}
void SECompleteBloodCount::SaveFile(const std::string& filename) const
{
  std::string content;
  cdm::CompleteBloodCountData* src = SECompleteBloodCount::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  delete src;
}

void SECompleteBloodCount::Load(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst)
{
  SECompleteBloodCount::Serialize(src, dst);
}
void SECompleteBloodCount::Serialize(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst)
{
  SEPatientAssessment::Serialize(src.patientassessment(), dst);
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
  SEPatientAssessment::Serialize(src, *dst.mutable_patientassessment());
  if (src.HasHematocrit())
    dst.set_allocated_hematocrit(SEScalar0To1::Unload(*src.m_Hematocrit));
  if (src.HasHemoglobin())
    dst.set_allocated_hemoglobin(SEScalarMassPerVolume::Unload(*src.m_Hemoglobin));
  if (src.HasPlateletCount())
    dst.set_allocated_plateletcount(SEScalarAmountPerVolume::Unload(*src.m_PlateletCount));
  if (src.HasMeanCorpuscularHemoglobin())
    dst.set_allocated_meancorpuscularhemoglobin(SEScalarMassPerAmount::Unload(*src.m_MeanCorpuscularHemoglobin));
  if (src.HasMeanCorpuscularHemoglobinConcentration())
    dst.set_allocated_meancorpuscularhemoglobinconcentration(SEScalarMassPerVolume::Unload(*src.m_MeanCorpuscularHemoglobinConcentration));
  if (src.HasMeanCorpuscularVolume())
    dst.set_allocated_meancorpuscularvolume(SEScalarVolume::Unload(*src.m_MeanCorpuscularVolume));
  if (src.HasRedBloodCellCount())
    dst.set_allocated_redbloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_RedBloodCellCount));
  if (src.HasWhiteBloodCellCount())
    dst.set_allocated_whitebloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_WhiteBloodCellCount));
}

bool SECompleteBloodCount::HasHematocrit() const
{
  return m_Hematocrit == nullptr ? false : m_Hematocrit->IsValid();
}
SEScalar0To1& SECompleteBloodCount::GetHematocrit()
{
  if (m_Hematocrit == nullptr)
    m_Hematocrit = new SEScalar0To1();
  return *m_Hematocrit;
}
double SECompleteBloodCount::GetHematocrit() const
{
  if (!HasHematocrit())
    return SEScalar::dNaN();
  return m_Hematocrit->GetValue();
}

bool SECompleteBloodCount::HasHemoglobin() const
{
  return m_Hemoglobin == nullptr ? false : m_Hemoglobin->IsValid();
}
SEScalarMassPerVolume& SECompleteBloodCount::GetHemoglobin()
{
  if (m_Hemoglobin == nullptr)
    m_Hemoglobin = new SEScalarMassPerVolume();
  return *m_Hemoglobin;
}
double SECompleteBloodCount::GetHemoglobin(const MassPerVolumeUnit& unit) const
{
  if (!HasHemoglobin())
    return SEScalar::dNaN();
  return m_Hemoglobin->GetValue(unit);
}

bool SECompleteBloodCount::HasPlateletCount() const
{
  return m_PlateletCount == nullptr ? false : m_PlateletCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetPlateletCount()
{
  if (m_PlateletCount == nullptr)
    m_PlateletCount = new SEScalarAmountPerVolume();
  return *m_PlateletCount;
}
double SECompleteBloodCount::GetPlateletCount(const AmountPerVolumeUnit& unit) const
{
  if (!HasPlateletCount())
    return SEScalar::dNaN();
  return m_PlateletCount->GetValue(unit);
}

bool SECompleteBloodCount::HasMeanCorpuscularHemoglobin() const
{
  return m_MeanCorpuscularHemoglobin == nullptr ? false : m_MeanCorpuscularHemoglobin->IsValid();
}
SEScalarMassPerAmount& SECompleteBloodCount::GetMeanCorpuscularHemoglobin()
{
  if (m_MeanCorpuscularHemoglobin == nullptr)
    m_MeanCorpuscularHemoglobin = new SEScalarMassPerAmount();
  return *m_MeanCorpuscularHemoglobin;
}
double SECompleteBloodCount::GetMeanCorpuscularHemoglobin(const MassPerAmountUnit& unit) const
{
  if (!HasMeanCorpuscularHemoglobin())
    return SEScalar::dNaN();
  return m_MeanCorpuscularHemoglobin->GetValue(unit);
}

bool SECompleteBloodCount::HasMeanCorpuscularHemoglobinConcentration() const
{
  return m_MeanCorpuscularHemoglobinConcentration == nullptr ? false : m_MeanCorpuscularHemoglobinConcentration->IsValid();
}
SEScalarMassPerVolume& SECompleteBloodCount::GetMeanCorpuscularHemoglobinConcentration()
{
  if (m_MeanCorpuscularHemoglobinConcentration == nullptr)
    m_MeanCorpuscularHemoglobinConcentration = new SEScalarMassPerVolume();
  return *m_MeanCorpuscularHemoglobinConcentration;
}
double SECompleteBloodCount::GetMeanCorpuscularHemoglobinConcentration(const MassPerVolumeUnit& unit) const
{
  if (!HasMeanCorpuscularHemoglobinConcentration())
    return SEScalar::dNaN();
  return m_MeanCorpuscularHemoglobinConcentration->GetValue(unit);
}

bool SECompleteBloodCount::HasMeanCorpuscularVolume() const
{
  return m_MeanCorpuscularVolume == nullptr ? false : m_MeanCorpuscularVolume->IsValid();
}
SEScalarVolume& SECompleteBloodCount::GetMeanCorpuscularVolume()
{
  if (m_MeanCorpuscularVolume == nullptr)
    m_MeanCorpuscularVolume = new SEScalarVolume();
  return *m_MeanCorpuscularVolume;
}
double SECompleteBloodCount::GetMeanCorpuscularVolume(const VolumeUnit& unit) const
{
  if (!HasMeanCorpuscularVolume())
    return SEScalar::dNaN();
  return m_MeanCorpuscularVolume->GetValue(unit);
}

bool SECompleteBloodCount::HasRedBloodCellCount() const
{
  return m_RedBloodCellCount == nullptr ? false : m_RedBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetRedBloodCellCount()
{
  if (m_RedBloodCellCount == nullptr)
    m_RedBloodCellCount = new SEScalarAmountPerVolume();
  return *m_RedBloodCellCount;
}
double SECompleteBloodCount::GetRedBloodCellCount(const AmountPerVolumeUnit& unit) const
{
  if (!HasRedBloodCellCount())
    return SEScalar::dNaN();
  return m_RedBloodCellCount->GetValue(unit);
}

bool SECompleteBloodCount::HasWhiteBloodCellCount() const
{
  return m_WhiteBloodCellCount == nullptr ? false : m_WhiteBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SECompleteBloodCount::GetWhiteBloodCellCount()
{
  if (m_WhiteBloodCellCount == nullptr)
    m_WhiteBloodCellCount = new SEScalarAmountPerVolume();
  return *m_WhiteBloodCellCount;
}
double SECompleteBloodCount::GetWhiteBloodCellCount(const AmountPerVolumeUnit& unit) const
{
  if (!HasWhiteBloodCellCount())
    return SEScalar::dNaN();
  return m_WhiteBloodCellCount->GetValue(unit);
}