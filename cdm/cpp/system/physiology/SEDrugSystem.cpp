/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/physiology/SEDrugSystem.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalar.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarNegative1To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarLength.h"

SEDrugSystem::SEDrugSystem(Logger* logger) : SESystem(logger)
{
  m_BronchodilationLevel = nullptr;
  m_HeartRateChange = nullptr;
  m_MeanBloodPressureChange = nullptr;
  m_NeuromuscularBlockLevel = nullptr;
  m_PulsePressureChange = nullptr;
  m_PupillaryResponse = nullptr;
  m_RespirationRateChange = nullptr;
  m_SedationLevel = nullptr;
  m_TidalVolumeChange = nullptr;
  m_TubularPermeabilityChange = nullptr;
}

SEDrugSystem::~SEDrugSystem()
{
  Clear();
}

void SEDrugSystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_BronchodilationLevel);
  SAFE_DELETE(m_HeartRateChange);
  SAFE_DELETE(m_MeanBloodPressureChange);
  SAFE_DELETE(m_NeuromuscularBlockLevel);
  SAFE_DELETE(m_PulsePressureChange);
  SAFE_DELETE(m_PupillaryResponse);
  SAFE_DELETE(m_RespirationRateChange);
  SAFE_DELETE(m_SedationLevel);
  SAFE_DELETE(m_TidalVolumeChange);
  SAFE_DELETE(m_TubularPermeabilityChange);
}

void SEDrugSystem::Load(const cdm::DrugSystemData& src, SEDrugSystem& dst)
{
  SEDrugSystem::Serialize(src, dst);
}
void SEDrugSystem::Serialize(const cdm::DrugSystemData& src, SEDrugSystem& dst)
{
  dst.Clear();
  if (src.has_bronchodilationlevel())
    SEScalarNegative1To1::Load(src.bronchodilationlevel(), dst.GetBronchodilationLevel());
  if (src.has_heartratechange())
    SEScalarFrequency::Load(src.heartratechange(), dst.GetHeartRateChange());
  if (src.has_meanbloodpressurechange())
    SEScalarPressure::Load(src.meanbloodpressurechange(), dst.GetMeanBloodPressureChange());
  if (src.has_neuromuscularblocklevel())
    SEScalar0To1::Load(src.neuromuscularblocklevel(), dst.GetNeuromuscularBlockLevel());
  if (src.has_pulsepressurechange())
    SEScalarPressure::Load(src.pulsepressurechange(), dst.GetPulsePressureChange());
  if (src.has_pupillaryresponse())
    SEPupillaryResponse::Load(src.pupillaryresponse(), dst.GetPupillaryResponse());
  if (src.has_respirationratechange())
    SEScalarFrequency::Load(src.respirationratechange(), dst.GetRespirationRateChange());
  if (src.has_sedationlevel())
    SEScalar0To1::Load(src.sedationlevel(), dst.GetSedationLevel());
  if (src.has_tidalvolumechange())
    SEScalarVolume::Load(src.tidalvolumechange(), dst.GetTidalVolumeChange());
  if (src.has_tubularpermeabilitychange())
    SEScalarNegative1To1::Load(src.tubularpermeabilitychange(), dst.GetTubularPermeabilityChange());
}

cdm::DrugSystemData* SEDrugSystem::Unload(const SEDrugSystem& src)
{
  cdm::DrugSystemData* dst = new cdm::DrugSystemData();
  SEDrugSystem::Serialize(src, *dst);
  return dst;
}
void SEDrugSystem::Serialize(const SEDrugSystem& src, cdm::DrugSystemData& dst)
{
  if (src.HasBronchodilationLevel())
    dst.set_allocated_bronchodilationlevel(SEScalarNegative1To1::Unload(*src.m_BronchodilationLevel));
  if (src.HasHeartRateChange())
    dst.set_allocated_heartratechange(SEScalarFrequency::Unload(*src.m_HeartRateChange));
  if (src.HasMeanBloodPressureChange())
    dst.set_allocated_meanbloodpressurechange(SEScalarPressure::Unload(*src.m_MeanBloodPressureChange));
  if (src.HasNeuromuscularBlockLevel())
    dst.set_allocated_neuromuscularblocklevel(SEScalar0To1::Unload(*src.m_NeuromuscularBlockLevel));
  if (src.HasPulsePressureChange())
    dst.set_allocated_pulsepressurechange(SEScalarPressure::Unload(*src.m_PulsePressureChange));
  if (src.HasPupillaryResponse())
    dst.set_allocated_pupillaryresponse(SEPupillaryResponse::Unload(*src.m_PupillaryResponse));
  if (src.HasRespirationRateChange())
    dst.set_allocated_respirationratechange(SEScalarFrequency::Unload(*src.m_RespirationRateChange));
  if (src.HasSedationLevel())
    dst.set_allocated_sedationlevel(SEScalar0To1::Unload(*src.m_SedationLevel));
  if (src.HasTidalVolumeChange())
    dst.set_allocated_tidalvolumechange(SEScalarVolume::Unload(*src.m_TidalVolumeChange));
  if (src.HasTubularPermeabilityChange())
    dst.set_allocated_tubularpermeabilitychange(SEScalarNegative1To1::Unload(*src.m_TubularPermeabilityChange));
}

const SEScalar* SEDrugSystem::GetScalar(const std::string& name)
{
  if (name.compare("BronchodilationLevel") == 0)
    return &GetBronchodilationLevel();
  if (name.compare("HeartRateChange") == 0)
    return &GetHeartRateChange();
  if (name.compare("MeanBloodPressureChange") == 0)
    return &GetMeanBloodPressureChange();
  if (name.compare("NeuromuscularBlockLevel") == 0)
    return &GetNeuromuscularBlockLevel();
  if (name.compare("PulsePressureChange") == 0)
    return &GetPulsePressureChange();
  if (name.compare("RespirationRateChange") == 0)
    return &GetRespirationRateChange();
  if (name.compare("SedationLevel") == 0)
    return &GetSedationLevel();
  if (name.compare("TidalVolumeChange") == 0)
    return &GetTidalVolumeChange();
  if (name.compare("TubularPermeabilityChange") == 0)
    return &GetTubularPermeabilityChange();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == "PupillaryResponse")
      return GetPupillaryResponse().GetScalar(prop);    
  }

  return nullptr;
}

bool SEDrugSystem::HasBronchodilationLevel() const
{
  return m_BronchodilationLevel == nullptr ? false : m_BronchodilationLevel->IsValid();
}
SEScalarNegative1To1& SEDrugSystem::GetBronchodilationLevel()
{
  if (m_BronchodilationLevel == nullptr)
    m_BronchodilationLevel = new SEScalarNegative1To1();
  return *m_BronchodilationLevel;
}
double SEDrugSystem::GetBronchodilationLevel() const
{
  if (m_BronchodilationLevel == nullptr)
    return SEScalar::dNaN();
  return m_BronchodilationLevel->GetValue();
}

bool SEDrugSystem::HasHeartRateChange() const
{
  return m_HeartRateChange == nullptr ? false : m_HeartRateChange->IsValid();
}
SEScalarFrequency& SEDrugSystem::GetHeartRateChange()
{
  if (m_HeartRateChange == nullptr)
    m_HeartRateChange = new SEScalarFrequency();
  return *m_HeartRateChange;
}
double SEDrugSystem::GetHeartRateChange(const FrequencyUnit& unit) const
{
  if (m_HeartRateChange == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateChange->GetValue(unit);
}

bool SEDrugSystem::HasMeanBloodPressureChange() const
{
  return m_MeanBloodPressureChange == nullptr ? false : m_MeanBloodPressureChange->IsValid();
}
SEScalarPressure& SEDrugSystem::GetMeanBloodPressureChange()
{
  if (m_MeanBloodPressureChange == nullptr)
    m_MeanBloodPressureChange = new SEScalarPressure();
  return *m_MeanBloodPressureChange;
}
double SEDrugSystem::GetMeanBloodPressureChange(const PressureUnit& unit) const
{
  if (m_MeanBloodPressureChange == nullptr)
    return SEScalar::dNaN();
  return m_MeanBloodPressureChange->GetValue(unit);
}

bool SEDrugSystem::HasNeuromuscularBlockLevel() const
{
  return m_NeuromuscularBlockLevel == nullptr ? false : m_NeuromuscularBlockLevel->IsValid();
}
SEScalar0To1& SEDrugSystem::GetNeuromuscularBlockLevel()
{
  if (m_NeuromuscularBlockLevel == nullptr)
    m_NeuromuscularBlockLevel = new SEScalar0To1();
  return *m_NeuromuscularBlockLevel;
}
double SEDrugSystem::GetNeuromuscularBlockLevel() const
{
  if (m_NeuromuscularBlockLevel == nullptr)
    return SEScalar::dNaN();
  return m_NeuromuscularBlockLevel->GetValue();
}

bool SEDrugSystem::HasPulsePressureChange() const
{
  return m_PulsePressureChange == nullptr ? false : m_PulsePressureChange->IsValid();
}
SEScalarPressure& SEDrugSystem::GetPulsePressureChange()
{
  if (m_PulsePressureChange == nullptr)
    m_PulsePressureChange = new SEScalarPressure();
  return *m_PulsePressureChange;
}
double SEDrugSystem::GetPulsePressureChange(const PressureUnit& unit) const
{
  if (m_PulsePressureChange == nullptr)
    return SEScalar::dNaN();
  return m_PulsePressureChange->GetValue(unit);
}

bool SEDrugSystem::HasPupillaryResponse() const
{
  return (m_PupillaryResponse != nullptr);
}
SEPupillaryResponse& SEDrugSystem::GetPupillaryResponse()
{
  if (m_PupillaryResponse == nullptr)
    m_PupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_PupillaryResponse;
}
const SEPupillaryResponse* SEDrugSystem::GetPupillaryResponse() const
{
  return m_PupillaryResponse;
}
void SEDrugSystem::RemovePupillaryResponse()
{
  SAFE_DELETE(m_PupillaryResponse);
}

bool SEDrugSystem::HasRespirationRateChange() const
{
  return m_RespirationRateChange == nullptr ? false : m_RespirationRateChange->IsValid();
}
SEScalarFrequency& SEDrugSystem::GetRespirationRateChange()
{
  if (m_RespirationRateChange == nullptr)
    m_RespirationRateChange = new SEScalarFrequency();
  return *m_RespirationRateChange;
}
double SEDrugSystem::GetRespirationRateChange(const FrequencyUnit& unit) const
{
  if (m_RespirationRateChange == nullptr)
    return SEScalar::dNaN();
  return m_RespirationRateChange->GetValue(unit);
}

bool SEDrugSystem::HasSedationLevel() const
{
  return m_SedationLevel == nullptr ? false : m_SedationLevel->IsValid();
}
SEScalar0To1& SEDrugSystem::GetSedationLevel()
{
  if (m_SedationLevel == nullptr)
    m_SedationLevel = new SEScalar0To1();
  return *m_SedationLevel;
}
double SEDrugSystem::GetSedationLevel() const
{
  if (m_SedationLevel == nullptr)
    return SEScalar::dNaN();
  return m_SedationLevel->GetValue();
}

bool SEDrugSystem::HasTidalVolumeChange() const
{
  return m_TidalVolumeChange == nullptr ? false : m_TidalVolumeChange->IsValid();
}
SEScalarVolume& SEDrugSystem::GetTidalVolumeChange()
{
  if (m_TidalVolumeChange == nullptr)
    m_TidalVolumeChange = new SEScalarVolume();
  return *m_TidalVolumeChange;
}

double SEDrugSystem::GetTidalVolumeChange(const VolumeUnit& unit) const
{
  if (m_TidalVolumeChange == nullptr)
    return SEScalar::dNaN();
  return m_TidalVolumeChange->GetValue(unit);
}

bool SEDrugSystem::HasTubularPermeabilityChange() const
{
  return m_TubularPermeabilityChange == nullptr ? false : m_TubularPermeabilityChange->IsValid();
}
SEScalarNegative1To1& SEDrugSystem::GetTubularPermeabilityChange()
{
  if (m_TubularPermeabilityChange == nullptr)
    m_TubularPermeabilityChange = new SEScalarNegative1To1();
  return *m_TubularPermeabilityChange;
}
double SEDrugSystem::GetTubularPermeabilityChange() const
{
  if (m_TubularPermeabilityChange == nullptr)
    return SEScalar::dNaN();
  return m_TubularPermeabilityChange->GetValue();
}
