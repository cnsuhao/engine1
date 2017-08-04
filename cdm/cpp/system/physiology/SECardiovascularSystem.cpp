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
#include "system/physiology/SECardiovascularSystem.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarFlowResistance.h"
#include "properties/SEScalarPressurePerVolume.h"
#include "properties/SEScalarPressureTimePerArea.h"
#include "properties/SEScalarPressureTimePerVolumeArea.h"
#include "properties/SEScalarVolumePerTimeArea.h"

SECardiovascularSystem::SECardiovascularSystem(Logger* logger) : SESystem(logger)
{
  m_ArterialPressure = nullptr;
  m_BloodVolume = nullptr;
  m_CardiacIndex = nullptr;
  m_CardiacOutput = nullptr;
  m_CentralVenousPressure = nullptr;
  m_CerebralBloodFlow = nullptr;
  m_CerebralPerfusionPressure = nullptr;
  m_DiastolicArterialPressure = nullptr;
  m_HeartEjectionFraction = nullptr;
  m_HeartRate = nullptr;
  m_HeartRhythm = cdm::eHeartRhythm::NormalSinus;
  m_HeartStrokeVolume = nullptr; 
  m_IntracranialPressure = nullptr;
  m_MeanArterialPressure = nullptr;
  m_MeanArterialCarbonDioxidePartialPressure = nullptr;
  m_MeanArterialCarbonDioxidePartialPressureDelta = nullptr;
  m_MeanCentralVenousPressure = nullptr;
  m_MeanSkinFlow = nullptr;
  m_PulmonaryArterialPressure = nullptr;
  m_PulmonaryCapillariesWedgePressure = nullptr;
  m_PulmonaryDiastolicArterialPressure = nullptr;
  m_PulmonaryMeanArterialPressure = nullptr;
  m_PulmonaryMeanCapillaryFlow = nullptr;
  m_PulmonaryMeanShuntFlow = nullptr;
  m_PulmonarySystolicArterialPressure = nullptr;
  m_PulmonaryVascularResistance = nullptr;
  m_PulmonaryVascularResistanceIndex = nullptr;
  m_PulsePressure = nullptr;
  m_SystemicVascularResistance = nullptr;
  m_SystolicArterialPressure = nullptr;
}

SECardiovascularSystem::~SECardiovascularSystem()
{
  Clear();
}

void SECardiovascularSystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_ArterialPressure);
  SAFE_DELETE(m_BloodVolume);
  SAFE_DELETE(m_CardiacIndex);
  SAFE_DELETE(m_CardiacOutput);
  SAFE_DELETE(m_CentralVenousPressure);
  SAFE_DELETE(m_CerebralBloodFlow);
  SAFE_DELETE(m_CerebralPerfusionPressure);
  SAFE_DELETE(m_DiastolicArterialPressure);
  SAFE_DELETE(m_HeartEjectionFraction);
  SAFE_DELETE(m_HeartRate);
  m_HeartRhythm = cdm::eHeartRhythm::NormalSinus;
  SAFE_DELETE(m_HeartStrokeVolume);
  SAFE_DELETE(m_IntracranialPressure);
  SAFE_DELETE(m_MeanArterialPressure);
  SAFE_DELETE(m_MeanArterialCarbonDioxidePartialPressure);
  SAFE_DELETE(m_MeanArterialCarbonDioxidePartialPressureDelta);
  SAFE_DELETE(m_MeanCentralVenousPressure);
  SAFE_DELETE(m_MeanSkinFlow);
  SAFE_DELETE(m_PulmonaryArterialPressure);
  SAFE_DELETE(m_PulmonaryCapillariesWedgePressure);
  SAFE_DELETE(m_PulmonaryDiastolicArterialPressure);
  SAFE_DELETE(m_PulmonaryMeanArterialPressure);
  SAFE_DELETE(m_PulmonaryMeanCapillaryFlow);
  SAFE_DELETE(m_PulmonaryMeanShuntFlow);
  SAFE_DELETE(m_PulmonarySystolicArterialPressure);
  SAFE_DELETE(m_PulmonaryVascularResistance);
  SAFE_DELETE(m_PulmonaryVascularResistanceIndex);
  SAFE_DELETE(m_PulsePressure);
  SAFE_DELETE(m_SystemicVascularResistance);
  SAFE_DELETE(m_SystolicArterialPressure);
}

const SEScalar* SECardiovascularSystem::GetScalar(const std::string& name)
{
  if (name.compare("ArterialPressure") == 0)
    return &GetArterialPressure();
  if (name.compare("BloodVolume") == 0)
    return &GetBloodVolume();
  if (name.compare("CardiacIndex") == 0)
    return &GetCardiacIndex();
  if (name.compare("CardiacOutput") == 0)
    return &GetCardiacOutput();
  if (name.compare("CentralVenousPressure") == 0)
    return &GetCentralVenousPressure();
  if (name.compare("CerebralBloodFlow") == 0)
    return &GetCerebralBloodFlow();
  if (name.compare("CerebralPerfusionPressure") == 0)
    return &GetCerebralPerfusionPressure();
  if (name.compare("DiastolicArterialPressure") == 0)
    return &GetDiastolicArterialPressure();
  if (name.compare("HeartEjectionFraction") == 0)
    return &GetHeartEjectionFraction();
  if (name.compare("HeartRate") == 0)
    return &GetHeartRate();
  if (name.compare("HeartStrokeVolume") == 0)
    return &GetHeartStrokeVolume();
  if (name.compare("IntracranialPressure") == 0)
    return &GetIntracranialPressure();
  if (name.compare("MeanArterialPressure") == 0)
    return &GetMeanArterialPressure();
  if (name.compare("MeanArterialCarbonDioxidePartialPressure") == 0)
    return &GetMeanArterialCarbonDioxidePartialPressure();
  if (name.compare("MeanArterialCarbonDioxidePartialPressureDelta") == 0)
    return &GetMeanArterialCarbonDioxidePartialPressureDelta();
  if (name.compare("MeanCentralVenousPressure") == 0)
    return &GetMeanCentralVenousPressure();
  if (name.compare("MeanSkinFlow") == 0)
    return &GetMeanSkinFlow();
  if (name.compare("PulmonaryArterialPressure") == 0)
    return &GetPulmonaryArterialPressure();
  if (name.compare("PulmonaryCapillariesWedgePressure") == 0)
    return &GetPulmonaryCapillariesWedgePressure();
  if (name.compare("PulmonaryDiastolicArterialPressure") == 0)
    return &GetPulmonaryDiastolicArterialPressure();
  if (name.compare("PulmonaryMeanArterialPressure") == 0)
    return &GetPulmonaryMeanArterialPressure();
  if (name.compare("PulmonaryMeanCapillaryFlow") == 0)
    return &GetPulmonaryMeanCapillaryFlow();
  if (name.compare("PulmonaryMeanShuntFlow") == 0)
    return &GetPulmonaryMeanShuntFlow();
  if (name.compare("PulmonarySystolicArterialPressure") == 0)
    return &GetPulmonarySystolicArterialPressure();
  if (name.compare("PulmonaryVascularResistance") == 0)
    return &GetPulmonaryVascularResistance();
  if (name.compare("PulmonaryVascularResistanceIndex") == 0)
    return &GetPulmonaryVascularResistanceIndex();
  if (name.compare("PulsePressure") == 0)
    return &GetPulsePressure();
  if (name.compare("SystemicVascularResistance") == 0)
    return &GetSystemicVascularResistance();
  if (name.compare("SystolicArterialPressure") == 0)
    return &GetSystolicArterialPressure();
  return nullptr;
}

void SECardiovascularSystem::Load(const cdm::CardiovascularSystemData& src, SECardiovascularSystem& dst)
{
  SECardiovascularSystem::Serialize(src, dst);
}
void SECardiovascularSystem::Serialize(const cdm::CardiovascularSystemData& src, SECardiovascularSystem& dst)
{
  dst.Clear();
  if (src.has_arterialpressure())
    SEScalarPressure::Load(src.arterialpressure(), dst.GetArterialPressure());
  if (src.has_bloodvolume())
    SEScalarVolume::Load(src.bloodvolume(), dst.GetBloodVolume());
  if (src.has_cardiacindex())
    SEScalarVolumePerTimeArea::Load(src.cardiacindex(), dst.GetCardiacIndex());
  if (src.has_cardiacoutput())
    SEScalarVolumePerTime::Load(src.cardiacoutput(), dst.GetCardiacOutput());
  if (src.has_centralvenouspressure())
    SEScalarPressure::Load(src.centralvenouspressure(), dst.GetCentralVenousPressure());
  if (src.has_cerebralbloodflow())
    SEScalarVolumePerTime::Load(src.cerebralbloodflow(), dst.GetCerebralBloodFlow());
  if (src.has_cerebralperfusionpressure())
    SEScalarPressure::Load(src.cerebralperfusionpressure(), dst.GetCerebralPerfusionPressure());
  if (src.has_diastolicarterialpressure())
    SEScalarPressure::Load(src.diastolicarterialpressure(), dst.GetDiastolicArterialPressure());
  if (src.has_heartejectionfraction())
    SEScalar0To1::Load(src.heartejectionfraction(), dst.GetHeartEjectionFraction());
  if (src.has_heartrate())
    SEScalarFrequency::Load(src.heartrate(), dst.GetHeartRate());
  dst.SetHeartRhythm(src.heartrhythm());
  if (src.has_heartstrokevolume())
    SEScalarVolume::Load(src.heartstrokevolume(), dst.GetHeartStrokeVolume());
  if (src.has_intracranialpressure())
    SEScalarPressure::Load(src.intracranialpressure(), dst.GetIntracranialPressure());
  if (src.has_meanarterialpressure())
    SEScalarPressure::Load(src.meanarterialpressure(), dst.GetMeanArterialPressure());
  if (src.has_meanarterialcarbondioxidepartialpressure())
    SEScalarPressure::Load(src.meanarterialcarbondioxidepartialpressure(), dst.GetMeanArterialCarbonDioxidePartialPressure());
  if (src.has_meanarterialcarbondioxidepartialpressuredelta())
    SEScalarPressure::Load(src.meanarterialcarbondioxidepartialpressuredelta(), dst.GetMeanArterialCarbonDioxidePartialPressureDelta());
  if (src.has_meancentralvenouspressure())
    SEScalarPressure::Load(src.meancentralvenouspressure(), dst.GetMeanCentralVenousPressure());
  if (src.has_meanskinflow())
    SEScalarVolumePerTime::Load(src.meanskinflow(), dst.GetMeanSkinFlow());
  if (src.has_pulmonaryarterialpressure())
    SEScalarPressure::Load(src.pulmonaryarterialpressure(), dst.GetPulmonaryArterialPressure());
  if (src.has_pulmonarycapillarieswedgepressure())
    SEScalarPressure::Load(src.pulmonarycapillarieswedgepressure(), dst.GetPulmonaryCapillariesWedgePressure());
  if (src.has_pulmonarydiastolicarterialpressure())
    SEScalarPressure::Load(src.pulmonarydiastolicarterialpressure(), dst.GetPulmonaryDiastolicArterialPressure());
  if (src.has_pulmonarymeanarterialpressure())
    SEScalarPressure::Load(src.pulmonarymeanarterialpressure(), dst.GetPulmonaryMeanArterialPressure());
  if (src.has_pulmonarymeancapillaryflow())
    SEScalarVolumePerTime::Load(src.pulmonarymeancapillaryflow(), dst.GetPulmonaryMeanCapillaryFlow());
  if (src.has_pulmonarymeanshuntflow())
    SEScalarVolumePerTime::Load(src.pulmonarymeanshuntflow(), dst.GetPulmonaryMeanShuntFlow());
  if (src.has_pulmonarysystolicarterialpressure())
    SEScalarPressure::Load(src.pulmonarysystolicarterialpressure(), dst.GetPulmonarySystolicArterialPressure());
  if (src.has_pulmonaryvascularresistance())
    SEScalarFlowResistance::Load(src.pulmonaryvascularresistance(), dst.GetPulmonaryVascularResistance());
  if (src.has_pulmonaryvascularresistanceindex())
    SEScalarPressureTimePerVolumeArea::Load(src.pulmonaryvascularresistanceindex(), dst.GetPulmonaryVascularResistanceIndex());
  if (src.has_pulsepressure())
    SEScalarPressure::Load(src.pulsepressure(), dst.GetPulsePressure());
  if (src.has_systemicvascularresistance())
    SEScalarFlowResistance::Load(src.systemicvascularresistance(), dst.GetSystemicVascularResistance());
  if (src.has_systolicarterialpressure())
    SEScalarPressure::Load(src.systolicarterialpressure(), dst.GetSystolicArterialPressure());
}

cdm::CardiovascularSystemData* SECardiovascularSystem::Unload(const SECardiovascularSystem& src)
{
  cdm::CardiovascularSystemData* dst = new cdm::CardiovascularSystemData();
  SECardiovascularSystem::Serialize(src, *dst);
  return dst;
}
void SECardiovascularSystem::Serialize(const SECardiovascularSystem& src, cdm::CardiovascularSystemData& dst)
{
  if (src.HasArterialPressure())
    dst.set_allocated_arterialpressure(SEScalarPressure::Unload(*src.m_ArterialPressure));
  if (src.HasBloodVolume())
    dst.set_allocated_bloodvolume(SEScalarVolume::Unload(*src.m_BloodVolume));
  if (src.HasCardiacIndex())
    dst.set_allocated_cardiacindex(SEScalarVolumePerTimeArea::Unload(*src.m_CardiacIndex));
  if (src.HasCardiacOutput())
    dst.set_allocated_cardiacoutput(SEScalarVolumePerTime::Unload(*src.m_CardiacOutput));
  if (src.HasCentralVenousPressure())
    dst.set_allocated_centralvenouspressure(SEScalarPressure::Unload(*src.m_CentralVenousPressure));
  if (src.HasCerebralBloodFlow())
    dst.set_allocated_cerebralbloodflow(SEScalarVolumePerTime::Unload(*src.m_CerebralBloodFlow));
  if (src.HasCerebralPerfusionPressure())
    dst.set_allocated_cerebralperfusionpressure(SEScalarPressure::Unload(*src.m_CerebralPerfusionPressure));
  if (src.HasDiastolicArterialPressure())
    dst.set_allocated_diastolicarterialpressure(SEScalarPressure::Unload(*src.m_DiastolicArterialPressure));
  if (src.HasHeartEjectionFraction())
    dst.set_allocated_heartejectionfraction(SEScalar0To1::Unload(*src.m_HeartEjectionFraction));
  if (src.HasHeartRate())
    dst.set_allocated_heartrate(SEScalarFrequency::Unload(*src.m_HeartRate));
  dst.set_heartrhythm(src.m_HeartRhythm);
  if (src.HasHeartStrokeVolume())
    dst.set_allocated_heartstrokevolume(SEScalarVolume::Unload(*src.m_HeartStrokeVolume));
  if (src.HasIntracranialPressure())
    dst.set_allocated_intracranialpressure(SEScalarPressure::Unload(*src.m_IntracranialPressure));
  if (src.HasMeanArterialPressure())
    dst.set_allocated_meanarterialpressure(SEScalarPressure::Unload(*src.m_MeanArterialPressure));
  if (src.HasMeanArterialCarbonDioxidePartialPressure())
    dst.set_allocated_meanarterialcarbondioxidepartialpressure(SEScalarPressure::Unload(*src.m_MeanArterialCarbonDioxidePartialPressure));
  if (src.HasMeanArterialCarbonDioxidePartialPressureDelta())
    dst.set_allocated_meanarterialcarbondioxidepartialpressuredelta(SEScalarPressure::Unload(*src.m_MeanArterialCarbonDioxidePartialPressureDelta));
  if (src.HasMeanCentralVenousPressure())
    dst.set_allocated_meancentralvenouspressure(SEScalarPressure::Unload(*src.m_MeanCentralVenousPressure));
  if (src.HasMeanSkinFlow())
    dst.set_allocated_meanskinflow(SEScalarVolumePerTime::Unload(*src.m_MeanSkinFlow));
  if (src.HasPulmonaryArterialPressure())
    dst.set_allocated_pulmonaryarterialpressure(SEScalarPressure::Unload(*src.m_PulmonaryArterialPressure));
  if (src.HasPulmonaryCapillariesWedgePressure())
    dst.set_allocated_pulmonarycapillarieswedgepressure(SEScalarPressure::Unload(*src.m_PulmonaryCapillariesWedgePressure));
  if (src.HasPulmonaryDiastolicArterialPressure())
    dst.set_allocated_pulmonarydiastolicarterialpressure(SEScalarPressure::Unload(*src.m_PulmonaryDiastolicArterialPressure));
  if (src.HasPulmonaryMeanArterialPressure())
    dst.set_allocated_pulmonarymeanarterialpressure(SEScalarPressure::Unload(*src.m_PulmonaryMeanArterialPressure));
  if (src.HasPulmonaryMeanCapillaryFlow())
    dst.set_allocated_pulmonarymeancapillaryflow(SEScalarVolumePerTime::Unload(*src.m_PulmonaryMeanCapillaryFlow));
  if (src.HasPulmonaryMeanShuntFlow())
    dst.set_allocated_pulmonarymeanshuntflow(SEScalarVolumePerTime::Unload(*src.m_PulmonaryMeanShuntFlow));
  if (src.HasPulmonarySystolicArterialPressure())
    dst.set_allocated_pulmonarysystolicarterialpressure(SEScalarPressure::Unload(*src.m_PulmonarySystolicArterialPressure));
  if (src.HasPulmonaryVascularResistance())
    dst.set_allocated_pulmonaryvascularresistance(SEScalarFlowResistance::Unload(*src.m_PulmonaryVascularResistance));
  if (src.HasPulmonaryVascularResistanceIndex())
    dst.set_allocated_pulmonaryvascularresistanceindex(SEScalarPressureTimePerVolumeArea::Unload(*src.m_PulmonaryVascularResistanceIndex));
  if (src.HasPulsePressure())
    dst.set_allocated_pulsepressure(SEScalarPressure::Unload(*src.m_PulsePressure));
  if (src.HasSystemicVascularResistance())
    dst.set_allocated_systemicvascularresistance(SEScalarFlowResistance::Unload(*src.m_SystemicVascularResistance));
  if (src.HasSystolicArterialPressure())
    dst.set_allocated_systolicarterialpressure(SEScalarPressure::Unload(*src.m_SystolicArterialPressure));
}

bool SECardiovascularSystem::HasArterialPressure() const
{
  return m_ArterialPressure==nullptr?false:m_ArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetArterialPressure()
{
  if(m_ArterialPressure==nullptr)
    m_ArterialPressure=new SEScalarPressure();
  return *m_ArterialPressure;
}
double SECardiovascularSystem::GetArterialPressure(const PressureUnit& unit) const
{
  if (m_ArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_ArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasBloodVolume() const
{
  return m_BloodVolume==nullptr?false:m_BloodVolume->IsValid();
}
SEScalarVolume& SECardiovascularSystem::GetBloodVolume()
{
  if(m_BloodVolume==nullptr)
    m_BloodVolume=new SEScalarVolume();
  return *m_BloodVolume;
}
double SECardiovascularSystem::GetBloodVolume(const VolumeUnit& unit) const
{
  if (m_BloodVolume == nullptr)
    return SEScalar::dNaN();
  return m_BloodVolume->GetValue(unit);
}

bool SECardiovascularSystem::HasCardiacOutput() const
{
  return m_CardiacOutput==nullptr?false:m_CardiacOutput->IsValid();
}
SEScalarVolumePerTime& SECardiovascularSystem::GetCardiacOutput()
{
  if(m_CardiacOutput==nullptr)
    m_CardiacOutput=new SEScalarVolumePerTime();
  return *m_CardiacOutput;
}
double SECardiovascularSystem::GetCardiacOutput(const VolumePerTimeUnit& unit) const
{
  if (m_CardiacOutput == nullptr)
    return SEScalar::dNaN();
  return m_CardiacOutput->GetValue(unit);
}

bool SECardiovascularSystem::HasCardiacIndex() const
{
  return m_CardiacIndex == nullptr ? false : m_CardiacIndex->IsValid();
}
SEScalarVolumePerTimeArea& SECardiovascularSystem::GetCardiacIndex()
{
  if (m_CardiacIndex == nullptr)
    m_CardiacIndex = new SEScalarVolumePerTimeArea();
  return *m_CardiacIndex;
}
double SECardiovascularSystem::GetCardiacIndex(const VolumePerTimeAreaUnit& unit) const
{
  if (m_CardiacIndex == nullptr)
    return SEScalar::dNaN();
  return m_CardiacIndex->GetValue(unit);
}

bool SECardiovascularSystem::HasCentralVenousPressure() const
{
  return m_CentralVenousPressure==nullptr?false:m_CentralVenousPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetCentralVenousPressure()
{
  if(m_CentralVenousPressure==nullptr)
    m_CentralVenousPressure=new SEScalarPressure();
  return *m_CentralVenousPressure;
}
double SECardiovascularSystem::GetCentralVenousPressure(const PressureUnit& unit) const
{
  if (m_CentralVenousPressure == nullptr)
    return SEScalar::dNaN();
  return m_CentralVenousPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasCerebralBloodFlow() const
{
  return m_CerebralBloodFlow == nullptr ? false : m_CerebralBloodFlow->IsValid();
}
SEScalarVolumePerTime& SECardiovascularSystem::GetCerebralBloodFlow()
{
  if (m_CerebralBloodFlow == nullptr)
    m_CerebralBloodFlow = new SEScalarVolumePerTime();
  return *m_CerebralBloodFlow;
}
double SECardiovascularSystem::GetCerebralBloodFlow(const VolumePerTimeUnit& unit) const
{
  if (m_CerebralBloodFlow == nullptr)
    return SEScalar::dNaN();
  return m_CerebralBloodFlow->GetValue(unit);
}

bool SECardiovascularSystem::HasCerebralPerfusionPressure() const
{
  return m_CerebralPerfusionPressure == nullptr ? false : m_CerebralPerfusionPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetCerebralPerfusionPressure()
{
  if (m_CerebralPerfusionPressure == nullptr)
    m_CerebralPerfusionPressure = new SEScalarPressure();
  return *m_CerebralPerfusionPressure;
}
double SECardiovascularSystem::GetCerebralPerfusionPressure(const PressureUnit& unit) const
{
  if (m_CerebralPerfusionPressure == nullptr)
    return SEScalar::dNaN();
  return m_CerebralPerfusionPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasDiastolicArterialPressure() const
{
  return m_DiastolicArterialPressure==nullptr?false:m_DiastolicArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetDiastolicArterialPressure()
{
  if(m_DiastolicArterialPressure==nullptr)
    m_DiastolicArterialPressure=new SEScalarPressure();
  return *m_DiastolicArterialPressure;
}
double SECardiovascularSystem::GetDiastolicArterialPressure(const PressureUnit& unit) const
{
  if (m_DiastolicArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_DiastolicArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasHeartEjectionFraction() const
{
  return m_HeartEjectionFraction==nullptr?false:m_HeartEjectionFraction->IsValid();
}
SEScalar0To1& SECardiovascularSystem::GetHeartEjectionFraction()
{
  if(m_HeartEjectionFraction==nullptr)
    m_HeartEjectionFraction=new SEScalar0To1();
  return *m_HeartEjectionFraction;
}
double SECardiovascularSystem::GetHeartEjectionFraction() const
{
  if (m_HeartEjectionFraction == nullptr)
    return SEScalar::dNaN();
  return m_HeartEjectionFraction->GetValue();
}

bool SECardiovascularSystem::HasHeartRate() const
{
  return m_HeartRate==nullptr?false:m_HeartRate->IsValid();
}
SEScalarFrequency& SECardiovascularSystem::GetHeartRate()
{
  if(m_HeartRate==nullptr)
    m_HeartRate=new SEScalarFrequency();
  return *m_HeartRate;
}
double SECardiovascularSystem::GetHeartRate(const FrequencyUnit& unit) const
{
  if (m_HeartRate == nullptr)
    return SEScalar::dNaN();
  return m_HeartRate->GetValue(unit);
}

cdm::eHeartRhythm SECardiovascularSystem::GetHeartRhythm() const
{
  return m_HeartRhythm;
}
void SECardiovascularSystem::SetHeartRhythm(cdm::eHeartRhythm rhythm)
{
  m_HeartRhythm = rhythm;
}

bool SECardiovascularSystem::HasHeartStrokeVolume() const
{
  return m_HeartStrokeVolume==nullptr?false:m_HeartStrokeVolume->IsValid();
}
SEScalarVolume& SECardiovascularSystem::GetHeartStrokeVolume()
{
  if(m_HeartStrokeVolume==nullptr)
    m_HeartStrokeVolume=new SEScalarVolume();
  return *m_HeartStrokeVolume;
}
double SECardiovascularSystem::GetHeartStrokeVolume(const VolumeUnit& unit) const
{
  if (m_HeartStrokeVolume == nullptr)
    return SEScalar::dNaN();
  return m_HeartStrokeVolume->GetValue(unit);
}

bool SECardiovascularSystem::HasIntracranialPressure() const
{
  return m_IntracranialPressure == nullptr ? false : m_IntracranialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetIntracranialPressure()
{
  if (m_IntracranialPressure == nullptr)
    m_IntracranialPressure = new SEScalarPressure();
  return *m_IntracranialPressure;
}
double SECardiovascularSystem::GetIntracranialPressure(const PressureUnit& unit) const
{
  if (m_IntracranialPressure == nullptr)
    return SEScalar::dNaN();
  return m_IntracranialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasMeanArterialPressure() const
{
  return m_MeanArterialPressure == nullptr ? false : m_MeanArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetMeanArterialPressure()
{
  if (m_MeanArterialPressure == nullptr)
    m_MeanArterialPressure = new SEScalarPressure();
  return *m_MeanArterialPressure;
}
double SECardiovascularSystem::GetMeanArterialPressure(const PressureUnit& unit) const
{
  if (m_MeanArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_MeanArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasMeanArterialCarbonDioxidePartialPressure() const
{
  return m_MeanArterialCarbonDioxidePartialPressure == nullptr ? false : m_MeanArterialCarbonDioxidePartialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressure()
{
  if (m_MeanArterialCarbonDioxidePartialPressure == nullptr)
    m_MeanArterialCarbonDioxidePartialPressure = new SEScalarPressure();
  return *m_MeanArterialCarbonDioxidePartialPressure;
}
double SECardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressure(const PressureUnit& unit) const
{
  if (m_MeanArterialCarbonDioxidePartialPressure == nullptr)
    return SEScalar::dNaN();
  return m_MeanArterialCarbonDioxidePartialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasMeanArterialCarbonDioxidePartialPressureDelta() const
{
  return m_MeanArterialCarbonDioxidePartialPressureDelta == nullptr ? false : m_MeanArterialCarbonDioxidePartialPressureDelta->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressureDelta()
{
  if (m_MeanArterialCarbonDioxidePartialPressureDelta == nullptr)
    m_MeanArterialCarbonDioxidePartialPressureDelta = new SEScalarPressure();
  return *m_MeanArterialCarbonDioxidePartialPressureDelta;
}
double SECardiovascularSystem::GetMeanArterialCarbonDioxidePartialPressureDelta(const PressureUnit& unit) const
{
  if (m_MeanArterialCarbonDioxidePartialPressureDelta == nullptr)
    return SEScalar::dNaN();
  return m_MeanArterialCarbonDioxidePartialPressureDelta->GetValue(unit);
}

bool SECardiovascularSystem::HasMeanCentralVenousPressure() const
{
  return m_MeanCentralVenousPressure == nullptr ? false : m_MeanCentralVenousPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetMeanCentralVenousPressure()
{
  if (m_MeanCentralVenousPressure == nullptr)
    m_MeanCentralVenousPressure = new SEScalarPressure();
  return *m_MeanCentralVenousPressure;
}
double SECardiovascularSystem::GetMeanCentralVenousPressure(const PressureUnit& unit) const
{
  if (m_MeanCentralVenousPressure == nullptr)
    return SEScalar::dNaN();
  return m_MeanCentralVenousPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasMeanSkinFlow() const
{
  return m_MeanSkinFlow == nullptr ? false : m_MeanSkinFlow->IsValid();
}
SEScalarVolumePerTime& SECardiovascularSystem::GetMeanSkinFlow()
{
  if (m_MeanSkinFlow == nullptr)
    m_MeanSkinFlow = new SEScalarVolumePerTime();
  return *m_MeanSkinFlow;
}
double SECardiovascularSystem::GetMeanSkinFlow(const VolumePerTimeUnit& unit) const
{
  if (m_MeanSkinFlow == nullptr)
    return SEScalar::dNaN();
  return m_MeanSkinFlow->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryArterialPressure() const
{
  return m_PulmonaryArterialPressure == nullptr ? false : m_PulmonaryArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulmonaryArterialPressure()
{
  if (m_PulmonaryArterialPressure == nullptr)
    m_PulmonaryArterialPressure = new SEScalarPressure();
  return *m_PulmonaryArterialPressure;
}
double SECardiovascularSystem::GetPulmonaryArterialPressure(const PressureUnit& unit) const
{
  if (m_PulmonaryArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryCapillariesWedgePressure() const
{
  return m_PulmonaryCapillariesWedgePressure==nullptr?false:m_PulmonaryCapillariesWedgePressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulmonaryCapillariesWedgePressure()
{
  if(m_PulmonaryCapillariesWedgePressure==nullptr)
    m_PulmonaryCapillariesWedgePressure=new SEScalarPressure();
  return *m_PulmonaryCapillariesWedgePressure;
}
double SECardiovascularSystem::GetPulmonaryCapillariesWedgePressure(const PressureUnit& unit) const
{
  if (m_PulmonaryCapillariesWedgePressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryCapillariesWedgePressure->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryDiastolicArterialPressure() const
{
  return m_PulmonaryDiastolicArterialPressure==nullptr?false:m_PulmonaryDiastolicArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulmonaryDiastolicArterialPressure()
{
  if(m_PulmonaryDiastolicArterialPressure==nullptr)
    m_PulmonaryDiastolicArterialPressure=new SEScalarPressure();
  return *m_PulmonaryDiastolicArterialPressure;
}
double SECardiovascularSystem::GetPulmonaryDiastolicArterialPressure(const PressureUnit& unit) const
{
  if (m_PulmonaryDiastolicArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryDiastolicArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryMeanArterialPressure() const
{
  return m_PulmonaryMeanArterialPressure==nullptr?false:m_PulmonaryMeanArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulmonaryMeanArterialPressure()
{
  if(m_PulmonaryMeanArterialPressure==nullptr)
    m_PulmonaryMeanArterialPressure=new SEScalarPressure();
  return *m_PulmonaryMeanArterialPressure;
}
double SECardiovascularSystem::GetPulmonaryMeanArterialPressure(const PressureUnit& unit) const
{
  if (m_PulmonaryMeanArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryMeanArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryMeanCapillaryFlow() const
{
  return m_PulmonaryMeanCapillaryFlow==nullptr?false:m_PulmonaryMeanCapillaryFlow->IsValid();
}
SEScalarVolumePerTime& SECardiovascularSystem::GetPulmonaryMeanCapillaryFlow()
{
  if(m_PulmonaryMeanCapillaryFlow==nullptr)
    m_PulmonaryMeanCapillaryFlow=new SEScalarVolumePerTime();
  return *m_PulmonaryMeanCapillaryFlow;
}
double SECardiovascularSystem::GetPulmonaryMeanCapillaryFlow(const VolumePerTimeUnit& unit) const
{
  if (m_PulmonaryMeanCapillaryFlow == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryMeanCapillaryFlow->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryMeanShuntFlow() const
{
  return m_PulmonaryMeanShuntFlow==nullptr?false:m_PulmonaryMeanShuntFlow->IsValid();
}
SEScalarVolumePerTime& SECardiovascularSystem::GetPulmonaryMeanShuntFlow()
{
  if(m_PulmonaryMeanShuntFlow==nullptr)
    m_PulmonaryMeanShuntFlow=new SEScalarVolumePerTime();
  return *m_PulmonaryMeanShuntFlow;
}
double SECardiovascularSystem::GetPulmonaryMeanShuntFlow(const VolumePerTimeUnit& unit) const
{
  if (m_PulmonaryMeanShuntFlow == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryMeanShuntFlow->GetValue(unit);
}

bool SECardiovascularSystem::HasSystemicVascularResistance() const
{
  return m_SystemicVascularResistance == nullptr ? false : m_SystemicVascularResistance->IsValid();
}
SEScalarFlowResistance& SECardiovascularSystem::GetSystemicVascularResistance()
{
  if (m_SystemicVascularResistance == nullptr)
    m_SystemicVascularResistance = new SEScalarFlowResistance();
  return *m_SystemicVascularResistance;
}
double SECardiovascularSystem::GetSystemicVascularResistance(const FlowResistanceUnit& unit) const
{
  if (m_SystemicVascularResistance == nullptr)
    return SEScalar::dNaN();
  return m_SystemicVascularResistance->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonarySystolicArterialPressure() const
{
  return m_PulmonarySystolicArterialPressure==nullptr?false:m_PulmonarySystolicArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulmonarySystolicArterialPressure()
{
  if(m_PulmonarySystolicArterialPressure==nullptr)
    m_PulmonarySystolicArterialPressure=new SEScalarPressure();
  return *m_PulmonarySystolicArterialPressure;
}
double SECardiovascularSystem::GetPulmonarySystolicArterialPressure(const PressureUnit& unit) const
{
  if (m_PulmonarySystolicArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonarySystolicArterialPressure->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryVascularResistance() const
{
  return m_PulmonaryVascularResistance == nullptr ? false : m_PulmonaryVascularResistance->IsValid();
}
SEScalarFlowResistance& SECardiovascularSystem::GetPulmonaryVascularResistance()
{
  if (m_PulmonaryVascularResistance == nullptr)
    m_PulmonaryVascularResistance = new SEScalarFlowResistance();
  return *m_PulmonaryVascularResistance;
}
double SECardiovascularSystem::GetPulmonaryVascularResistance(const FlowResistanceUnit& unit) const
{
  if (m_PulmonaryVascularResistance == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVascularResistance->GetValue(unit);
}

bool SECardiovascularSystem::HasPulmonaryVascularResistanceIndex() const
{
  return m_PulmonaryVascularResistanceIndex == nullptr ? false : m_PulmonaryVascularResistanceIndex->IsValid();
}
SEScalarPressureTimePerVolumeArea& SECardiovascularSystem::GetPulmonaryVascularResistanceIndex()
{
  if (m_PulmonaryVascularResistanceIndex == nullptr)
    m_PulmonaryVascularResistanceIndex = new SEScalarPressureTimePerVolumeArea();
  return *m_PulmonaryVascularResistanceIndex;
}
double SECardiovascularSystem::GetPulmonaryVascularResistanceIndex(const PressureTimePerVolumeAreaUnit& unit) const
{
  if (m_PulmonaryVascularResistanceIndex == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVascularResistanceIndex->GetValue(unit);
}

bool SECardiovascularSystem::HasPulsePressure() const
{
  return m_PulsePressure==nullptr?false:m_PulsePressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetPulsePressure()
{
  if(m_PulsePressure==nullptr)
    m_PulsePressure=new SEScalarPressure();
  return *m_PulsePressure;
}
double SECardiovascularSystem::GetPulsePressure(const PressureUnit& unit) const
{
  if (m_PulsePressure == nullptr)
    return SEScalar::dNaN();
  return m_PulsePressure->GetValue(unit);
}

bool SECardiovascularSystem::HasSystolicArterialPressure() const
{
  return m_SystolicArterialPressure==nullptr?false:m_SystolicArterialPressure->IsValid();
}
SEScalarPressure& SECardiovascularSystem::GetSystolicArterialPressure()
{
  if(m_SystolicArterialPressure==nullptr)
    m_SystolicArterialPressure=new SEScalarPressure();
  return *m_SystolicArterialPressure;
}
double SECardiovascularSystem::GetSystolicArterialPressure(const PressureUnit& unit) const
{
  if (m_SystolicArterialPressure == nullptr)
    return SEScalar::dNaN();
  return m_SystolicArterialPressure->GetValue(unit);
}
