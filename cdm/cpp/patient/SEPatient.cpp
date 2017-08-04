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

#include "patient/SEPatient.h"
#include "patient/SENutrition.h"
#include "utils/SEEventHandler.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarLength.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarPressurePerVolume.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarArea.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarFlowElastance.h"
#include <google/protobuf/text_format.h>

SEPatient::SEPatient(Logger* logger) : Loggable(logger)
{
  m_EventHandler = nullptr;

  m_Name="";
  m_Sex = cdm::PatientData_eSex_Male;
  m_Age=nullptr;
  m_Weight=nullptr;
  m_Height=nullptr;

  m_AlveoliSurfaceArea = nullptr;
  m_BasalMetabolicRate = nullptr;
  m_BloodVolumeBaseline = nullptr;
  m_BodyDensity = nullptr;
  m_BodyFatFraction = nullptr;
  m_DiastolicArterialPressureBaseline = nullptr;
  m_ExpiratoryReserveVolume = nullptr;
  m_FunctionalResidualCapacity = nullptr;
  m_HeartRateBaseline = nullptr;
  m_HeartRateMaximum = nullptr;
  m_HeartRateMinimum = nullptr;
  m_InspiratoryCapacity = nullptr;
  m_InspiratoryReserveVolume = nullptr;
  m_LeanBodyMass = nullptr;
  m_MeanArterialPressureBaseline = nullptr;
  m_ResidualVolume = nullptr;
  m_RespirationRateBaseline = nullptr;
  m_RightLungRatio = nullptr;
  m_SkinSurfaceArea = nullptr;
  m_SystolicArterialPressureBaseline = nullptr;
  m_TidalVolumeBaseline = nullptr;
  m_TotalLungCapacity = nullptr;
  m_VitalCapacity = nullptr;
}

SEPatient::~SEPatient()
{
  Clear();  
}

bool SEPatient::LoadFile(const std::string& patientFile)
{
  cdm::PatientData src;
  std::ifstream file_stream(patientFile, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  google::protobuf::TextFormat::ParseFromString(fmsg, &src);
  SEPatient::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

void SEPatient::Clear()
{
  m_EventHandler=nullptr;
  m_EventState.clear();
  m_EventDuration_s.clear();
  m_Name="";
  m_Sex = cdm::PatientData_eSex_Male;
  SAFE_DELETE(m_Age);
  SAFE_DELETE(m_Weight);
  SAFE_DELETE(m_Height);

  SAFE_DELETE(m_AlveoliSurfaceArea);
  SAFE_DELETE(m_BasalMetabolicRate);
  SAFE_DELETE(m_BloodVolumeBaseline);
  SAFE_DELETE(m_BodyDensity);
  SAFE_DELETE(m_BodyFatFraction);
  SAFE_DELETE(m_DiastolicArterialPressureBaseline);
  SAFE_DELETE(m_ExpiratoryReserveVolume);
  SAFE_DELETE(m_FunctionalResidualCapacity);
  SAFE_DELETE(m_HeartRateBaseline);
  SAFE_DELETE(m_HeartRateMaximum);
  SAFE_DELETE(m_HeartRateMinimum);
  SAFE_DELETE(m_InspiratoryCapacity);
  SAFE_DELETE(m_InspiratoryReserveVolume);
  SAFE_DELETE(m_LeanBodyMass);
  SAFE_DELETE(m_MeanArterialPressureBaseline);
  SAFE_DELETE(m_ResidualVolume);
  SAFE_DELETE(m_RespirationRateBaseline);
  SAFE_DELETE(m_RightLungRatio);
  SAFE_DELETE(m_SkinSurfaceArea);
  SAFE_DELETE(m_SystolicArterialPressureBaseline);
  SAFE_DELETE(m_TidalVolumeBaseline);
  SAFE_DELETE(m_TotalLungCapacity);
  SAFE_DELETE(m_VitalCapacity);
}

const SEScalar* SEPatient::GetScalar(const std::string& name)
{
  if (name.compare("Age") == 0)
    return &GetAge();
  if (name.compare("Weight") == 0)
    return &GetWeight();
  if (name.compare("Height") == 0)
    return &GetHeight();

  if (name.compare("AlveoliSurfaceArea") == 0)
    return &GetAlveoliSurfaceArea();
  if (name.compare("BasalMetabolicRate") == 0)
    return &GetBasalMetabolicRate();
  if (name.compare("BloodVolumeBaseline") == 0)
    return &GetBloodVolumeBaseline();
  if (name.compare("BodyDensity") == 0)
    return &GetBodyDensity();
  if (name.compare("BodyFatFraction") == 0)
    return &GetBodyFatFraction();
  if (name.compare("DiastolicArterialPressureBaseline") == 0)
    return &GetDiastolicArterialPressureBaseline();
  if (name.compare("ExpiratoryReserveVolume") == 0)
    return &GetExpiratoryReserveVolume();
  if (name.compare("FunctionalResidualCapacity") == 0)
    return &GetFunctionalResidualCapacity();
  if (name.compare("HeartRateBaseline") == 0)
    return &GetHeartRateBaseline();
  if (name.compare("HeartRateMaximum") == 0)
    return &GetHeartRateMaximum();
  if (name.compare("HeartRateMinimum") == 0)
    return &GetHeartRateMinimum();
  if (name.compare("InspiratoryCapacity") == 0)
    return &GetInspiratoryCapacity();
  if (name.compare("InspiratoryReserveVolume") == 0)
    return &GetInspiratoryReserveVolume();
  if (name.compare("LeanBodyMass") == 0)
    return &GetLeanBodyMass();
  if (name.compare("MeanArterialPressureBaseline") == 0)
    return &GetMeanArterialPressureBaseline();
  if (name.compare("ResidualVolume") == 0)
    return &GetResidualVolume();
  if (name.compare("RespirationRateBaseline") == 0)
    return &GetRespirationRateBaseline();
  if (name.compare("RightLungRatio") == 0)
    return &GetRightLungRatio();
  if (name.compare("SkinSurfaceArea") == 0)
    return &GetSkinSurfaceArea();
  if (name.compare("SystolicArterialPressureBaseline") == 0)
    return &GetSystolicArterialPressureBaseline();
  if (name.compare("TidalVolumeBaseline") == 0)
    return &GetTidalVolumeBaseline();
  if (name.compare("TotalLungCapacity") == 0)
    return &GetTotalLungCapacity();
  if (name.compare("VitalCapacity") == 0)
    return &GetVitalCapacity();

  return nullptr;
}

void SEPatient::Load(const cdm::PatientData& src, SEPatient& dst)
{
  SEPatient::Serialize(src, dst);
}
void SEPatient::Serialize(const cdm::PatientData& src, SEPatient& dst)
{
  dst.Clear();
  dst.SetName(src.name());
  dst.SetSex(src.sex());
  if (src.has_age())
    SEScalarTime::Load(src.age(), dst.GetAge());
  if (src.has_weight())
    SEScalarMass::Load(src.weight(), dst.GetWeight());
  if (src.has_height())
    SEScalarLength::Load(src.height(), dst.GetHeight());
  if (src.has_bodydensity())
    SEScalarMassPerVolume::Load(src.bodydensity(), dst.GetBodyDensity());
  if (src.has_bodyfatfraction())
    SEScalar0To1::Load(src.bodyfatfraction(), dst.GetBodyFatFraction());
  if (src.has_leanbodymass())
    SEScalarMass::Load(src.leanbodymass(), dst.GetLeanBodyMass());

  if (src.has_alveolisurfacearea())
    SEScalarArea::Load(src.alveolisurfacearea(), dst.GetAlveoliSurfaceArea());
  if (src.has_rightlungratio())
    SEScalar0To1::Load(src.rightlungratio(), dst.GetRightLungRatio());
  if (src.has_skinsurfacearea())
    SEScalarArea::Load(src.skinsurfacearea(), dst.GetSkinSurfaceArea());

  if (src.has_basalmetabolicrate())
    SEScalarPower::Load(src.basalmetabolicrate(), dst.GetBasalMetabolicRate());
  if (src.has_bloodvolumebaseline())
    SEScalarVolume::Load(src.bloodvolumebaseline(), dst.GetBloodVolumeBaseline());
  if (src.has_diastolicarterialpressurebaseline())
    SEScalarPressure::Load(src.diastolicarterialpressurebaseline(), dst.GetDiastolicArterialPressureBaseline());
  if (src.has_heartratebaseline())
    SEScalarFrequency::Load(src.heartratebaseline(), dst.GetHeartRateBaseline());
  if (src.has_meanarterialpressurebaseline())
    SEScalarPressure::Load(src.meanarterialpressurebaseline(), dst.GetMeanArterialPressureBaseline());
  if (src.has_respirationratebaseline())
    SEScalarFrequency::Load(src.respirationratebaseline(), dst.GetRespirationRateBaseline());
  if (src.has_systolicarterialpressurebaseline())
    SEScalarPressure::Load(src.systolicarterialpressurebaseline(), dst.GetSystolicArterialPressureBaseline());
  if (src.has_tidalvolumebaseline())
    SEScalarVolume::Load(src.tidalvolumebaseline(), dst.GetTidalVolumeBaseline());

  if (src.has_heartratemaximum())
    SEScalarFrequency::Load(src.heartratemaximum(), dst.GetHeartRateMaximum());
  if (src.has_heartrateminimum())
    SEScalarFrequency::Load(src.heartrateminimum(), dst.GetHeartRateMinimum());
  if (src.has_expiratoryreservevolume())
    SEScalarVolume::Load(src.expiratoryreservevolume(), dst.GetExpiratoryReserveVolume());
  if (src.has_functionalresidualcapacity())
    SEScalarVolume::Load(src.functionalresidualcapacity(), dst.GetFunctionalResidualCapacity());
  if (src.has_inspiratorycapacity())
    SEScalarVolume::Load(src.inspiratorycapacity(), dst.GetInspiratoryCapacity());
  if (src.has_inspiratoryreservevolume())
    SEScalarVolume::Load(src.inspiratoryreservevolume(), dst.GetInspiratoryReserveVolume());
  if (src.has_residualvolume())
    SEScalarVolume::Load(src.residualvolume(), dst.GetResidualVolume());
  if (src.has_totallungcapacity())
    SEScalarVolume::Load(src.totallungcapacity(), dst.GetTotalLungCapacity());
  if (src.has_vitalcapacity())
    SEScalarVolume::Load(src.vitalcapacity(), dst.GetVitalCapacity());

  SEScalarTime time;
  for (int i = 0; i < src.activeevent_size(); i++)
  {
    const cdm::PatientData::ActiveEventData& e = src.activeevent(i);
    if(e.has_duration())
      SEScalarTime::Load(e.duration(),time);
    {
      dst.m_ss << "Active Patient event " << e.event() << " does not have time associated with it";
      dst.Warning(dst.m_ss);
      time.SetValue(0, TimeUnit::s);
    }
    dst.m_EventState[e.event()] = true;
    dst.m_EventDuration_s[e.event()] = time.GetValue(TimeUnit::s);
  }
}

cdm::PatientData* SEPatient::Unload(const SEPatient& src)
{
  cdm::PatientData* dst = new cdm::PatientData();
  SEPatient::Serialize(src, *dst);
  return dst;
}
void SEPatient::Serialize(const SEPatient& src, cdm::PatientData& dst)
{
  if (src.HasName())
    dst.set_name(src.m_Name);
  dst.set_sex(src.m_Sex);
  if (src.HasAge())
    dst.set_allocated_age(SEScalarTime::Unload(*src.m_Age));
  if (src.HasWeight())
    dst.set_allocated_weight(SEScalarMass::Unload(*src.m_Weight));
  if (src.HasHeight())
    dst.set_allocated_height(SEScalarLength::Unload(*src.m_Height));
  if (src.HasBodyDensity())
    dst.set_allocated_bodydensity(SEScalarMassPerVolume::Unload(*src.m_BodyDensity));
  if (src.HasBodyFatFraction())
    dst.set_allocated_bodyfatfraction(SEScalar0To1::Unload(*src.m_BodyFatFraction));
  if (src.HasLeanBodyMass())
    dst.set_allocated_leanbodymass(SEScalarMass::Unload(*src.m_LeanBodyMass));

  if (src.HasAlveoliSurfaceArea())
    dst.set_allocated_alveolisurfacearea(SEScalarArea::Unload(*src.m_AlveoliSurfaceArea));
  if (src.HasRightLungRatio())
    dst.set_allocated_rightlungratio(SEScalar0To1::Unload(*src.m_RightLungRatio));
  if (src.HasSkinSurfaceArea())
    dst.set_allocated_skinsurfacearea(SEScalarArea::Unload(*src.m_SkinSurfaceArea));

  if (src.HasBasalMetabolicRate())
    dst.set_allocated_basalmetabolicrate(SEScalarPower::Unload(*src.m_BasalMetabolicRate));
  if (src.HasDiastolicArterialPressureBaseline())
    dst.set_allocated_diastolicarterialpressurebaseline(SEScalarPressure::Unload(*src.m_DiastolicArterialPressureBaseline));
  if (src.HasHeartRateBaseline())
    dst.set_allocated_heartratebaseline(SEScalarFrequency::Unload(*src.m_HeartRateBaseline));
  if (src.HasMeanArterialPressureBaseline())
    dst.set_allocated_meanarterialpressurebaseline(SEScalarPressure::Unload(*src.m_MeanArterialPressureBaseline));
  if (src.HasRespirationRateBaseline())
    dst.set_allocated_respirationratebaseline(SEScalarFrequency::Unload(*src.m_RespirationRateBaseline));
  if (src.HasSystolicArterialPressureBaseline())
    dst.set_allocated_systolicarterialpressurebaseline(SEScalarPressure::Unload(*src.m_SystolicArterialPressureBaseline));
  if (src.HasTidalVolumeBaseline())
    dst.set_allocated_tidalvolumebaseline(SEScalarVolume::Unload(*src.m_TidalVolumeBaseline));

  if (src.HasHeartRateMaximum())
    dst.set_allocated_heartratemaximum(SEScalarFrequency::Unload(*src.m_HeartRateMaximum));
  if (src.HasHeartRateMinimum())
    dst.set_allocated_heartrateminimum(SEScalarFrequency::Unload(*src.m_HeartRateMinimum));
  if (src.HasExpiratoryReserveVolume())
    dst.set_allocated_expiratoryreservevolume(SEScalarVolume::Unload(*src.m_ExpiratoryReserveVolume));
  if (src.HasFunctionalResidualCapacity())
    dst.set_allocated_functionalresidualcapacity(SEScalarVolume::Unload(*src.m_FunctionalResidualCapacity));
  if (src.HasInspiratoryCapacity())
    dst.set_allocated_inspiratorycapacity(SEScalarVolume::Unload(*src.m_InspiratoryCapacity));
  if (src.HasInspiratoryReserveVolume())
    dst.set_allocated_inspiratoryreservevolume(SEScalarVolume::Unload(*src.m_InspiratoryReserveVolume));
  if (src.HasTotalLungCapacity())
    dst.set_allocated_totallungcapacity(SEScalarVolume::Unload(*src.m_TotalLungCapacity));
  if (src.HasBloodVolumeBaseline())
    dst.set_allocated_bloodvolumebaseline(SEScalarVolume::Unload(*src.m_BloodVolumeBaseline));
  if (src.HasVitalCapacity())
    dst.set_allocated_vitalcapacity(SEScalarVolume::Unload(*src.m_VitalCapacity));

  SEScalarTime time;
  for (auto itr : src.m_EventState)
  {
    if (!itr.second)
      continue;

    auto it2 = src.m_EventDuration_s.find(itr.first);
    if (it2 == src.m_EventDuration_s.end())// This should not happen... 
      time.SetValue(0, TimeUnit::s);
    else
      time.SetValue(it2->second, TimeUnit::s);

    cdm::PatientData_ActiveEventData* eData = dst.add_activeevent();

    eData->set_event(itr.first);
    eData->set_allocated_duration(SEScalarTime::Unload(time));
  }
}

void SEPatient::SetEvent(cdm::PatientData::eEvent type, bool active, const SEScalarTime& time)
{
  bool b=false;// Default is off
  if(m_EventState.find(type)!=m_EventState.end())
    b = m_EventState[type];
  if(b==active)
    return;//No Change
  if(active!=b)
  {
    m_ss.str("");
    m_ss<<"[Event] "<<time<<", ";
    if(active)
    {
      switch(type)
      {
      case cdm::PatientData_eEvent_Antidiuresis:
        m_ss << " Patient has Antidiuresis";
        break;
      case cdm::PatientData_eEvent_Asystole:
        m_ss << " Patient has Asystole";
        break;
      case cdm::PatientData_eEvent_Bradycardia:
        m_ss << " Patient has Bradycardia";
        break;
      case cdm::PatientData_eEvent_Bradypnea:
        m_ss << " Patient has Bradypnea";
        break;
      case cdm::PatientData_eEvent_BrainOxygenDeficit:
        m_ss << " Oxygen tension in the brain is dangerously low";
        break;
      case cdm::PatientData_eEvent_CardiacArrest:
        m_ss << " Patient has Cardiac Arrest";
        break;
      case cdm::PatientData_eEvent_CardiogenicShock:
        m_ss << " Patient has Cardiogenic Shock";
        break;
      case cdm::PatientData_eEvent_CriticalBrainOxygenDeficit:
        m_ss << " Oxygen tension in the brain is critically low";
        break;
      case cdm::PatientData_eEvent_Dehydration:
        m_ss << " Patient has entered state of Dehydration";
        break;
      case cdm::PatientData_eEvent_Diuresis:
        m_ss << " Patient has entered Diuresis";
        break;
      case cdm::PatientData_eEvent_Fasciculation:
        m_ss << "Patient has Fasciculation";
        break;
      case cdm::PatientData_eEvent_FunctionalIncontinence:
        m_ss << " Patient has involuntarily emptied their bladder";
        break;
      case cdm::PatientData_eEvent_Hypercapnia:
        m_ss << " Patient has Hypercapnia";
        break;
      case cdm::PatientData_eEvent_Hyperglycemia:
        m_ss << " Patient has Hyperglycemia";
        break;
      case cdm::PatientData_eEvent_Hyperthermia:
        m_ss << " Patient is Hyperthermic";
        break;
      case cdm::PatientData_eEvent_Hypoglycemia:
        m_ss << " Patient has Hypoglycemia";
        break;
      case cdm::PatientData_eEvent_Hypothermia:
        m_ss << " Patient is Hypothermic";
        break;
      case cdm::PatientData_eEvent_Hypoxia:
        m_ss << " Patient has Hypoxia";
        break;
      case cdm::PatientData_eEvent_IntracranialHypertension:
        m_ss << " Patient has Intracranial Hypertension";
        break;
      case cdm::PatientData_eEvent_IntracranialHypotension:
        m_ss << " Patient has Intracranial Hypotension";
        break;
      case cdm::PatientData_eEvent_HypovolemicShock:
        m_ss << " Patient is in Hypovolemic Shock";
        break;
      case cdm::PatientData_eEvent_IrreversibleState:
        m_ss<<" Patient has entered irreversible state";
        break;
      case cdm::PatientData_eEvent_Ketoacidosis:
        m_ss << " Patient has Ketoacidosis";
        break;
      case cdm::PatientData_eEvent_LacticAcidosis:
        m_ss << " Patient has LacticAcidosis";
        break;
      case cdm::PatientData_eEvent_MaximumPulmonaryVentilationRate:
        m_ss << " Patient's Respiratory Driver has exceeded the maximum target pulmonary ventilation rate, setting value to the maximum allowable rate";
        break;
      case cdm::PatientData_eEvent_MetabolicAcidosis:
        m_ss << " The patient is in a state of metabolic acidosis";
        break;
      case cdm::PatientData_eEvent_MetabolicAlkalosis:
        m_ss << " The patient is in a state of metabolic alkalosis";
        break;
      case cdm::PatientData_eEvent_MildAcuteRespiratoryDistress:
        m_ss << " The patient has Mild Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_ModerateAcuteRespiratoryDistress:
        m_ss << " The patient has Moderate Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_MyocardiumOxygenDeficit:
        m_ss << " The patient's heart is not receiving enough oxygen";
        break;
      case cdm::PatientData_eEvent_Natriuresis:
        m_ss << " Patient has Natriuresis";
        break;
      case cdm::PatientData_eEvent_NutritionDepleted:
        m_ss << " Patient has depleted all nutrition in body";
        break;
      case cdm::PatientData_eEvent_PulselessRhythm:
        m_ss << " Patient has a Pulseless Rhythm";
        break;
      case cdm::PatientData_eEvent_RenalHypoperfusion:
        m_ss << " Patient has Renal Hypoperfusion";
        break;
      case cdm::PatientData_eEvent_SevereAcuteRespiratoryDistress:
        m_ss << " The patient has Severe Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_Tachycardia:
        m_ss<<" Patient has Tachycardia";
        break;
      case cdm::PatientData_eEvent_Tachypnea:
        m_ss << " Patient has Tachypnea";
        break;
      case cdm::PatientData_eEvent_Fatigue:
        m_ss << "Patient has fatigue";
        break;
      case cdm::PatientData_eEvent_StartOfCardiacCycle:
      case cdm::PatientData_eEvent_StartOfExhale:
      case cdm::PatientData_eEvent_StartOfInhale:
        m_ss.str("");// make m_ss empty and nothing will be logged, this event does not need to get logged each activation
        break;
      default:
        m_ss<<" Patient has entered state : "<<type;// TODO cdm::PatientData_eEvent__xsd_enumPatientEvent_literals_[type];
      }
    }
    else
    {
      switch(type)
      {
      case cdm::PatientData_eEvent_Antidiuresis:
        m_ss << " Patient no longer is in Antidiuresis";
        break;
      case cdm::PatientData_eEvent_Asystole:
        m_ss << " Patient no longer is in Asystole";
        break; 
      case cdm::PatientData_eEvent_Bradycardia:
        m_ss << " Patient no longer has Bradycardia";
        break;
      case cdm::PatientData_eEvent_Bradypnea:
        m_ss << " Patient no longer has Bradypnea";
        break;
      case cdm::PatientData_eEvent_BrainOxygenDeficit:
        m_ss << " Oxygen tension in the brain has increased above the danger threshold";
        break;
      case cdm::PatientData_eEvent_CardiacArrest:
        m_ss << " Patient no longer has Cardiac Arrest";
        break;
      case cdm::PatientData_eEvent_CardiogenicShock:
        m_ss << " Patient no longer has Cardiogenic Shock";
        break;
      case cdm::PatientData_eEvent_CriticalBrainOxygenDeficit:
        m_ss << " Oxygen tension in the brain has increased above the critical threshold";
        break;
      case cdm::PatientData_eEvent_Dehydration:
        m_ss << " Patient no longer is in Dehydration state";
        break;
      case cdm::PatientData_eEvent_Diuresis:
        m_ss << " Patient no longer has Diuresis";
        break;
      case cdm::PatientData_eEvent_Fasciculation:
        m_ss << "Patient no longer has fasciculations";
        break;
      case cdm::PatientData_eEvent_FunctionalIncontinence:
        m_ss << " Patient has an empty bladder";
        break;
      case cdm::PatientData_eEvent_Hypercapnia:
        m_ss << " Patient no longer has Hypercapnia";
        break;
      case cdm::PatientData_eEvent_Hyperglycemia:
        m_ss << " Patient no longer has Hyperglycemia";
        break;
      case cdm::PatientData_eEvent_Hyperthermia:
        m_ss << " Patient is no longer has Hyperthermic";
        break;
      case cdm::PatientData_eEvent_Hypoglycemia:
        m_ss << " Patient no longer has Hypoglycemia";
        break;
      case cdm::PatientData_eEvent_Hypothermia:
        m_ss << " Patient is no longer has Hypothermic";
        break;
      case cdm::PatientData_eEvent_Hypoxia:
        m_ss << " Patient no longer has Hypoxia";
        break;
      case cdm::PatientData_eEvent_HypovolemicShock:
        m_ss << " Patient is no longer in Hypovolemic Shock";
        break;
      case cdm::PatientData_eEvent_IntracranialHypertension:
        m_ss << " Patient no longer has Intracranial Hypertension";
        break;
      case cdm::PatientData_eEvent_IntracranialHypotension:
        m_ss << " Patient no longer has Intracranial Hypotension";
        break;
      case cdm::PatientData_eEvent_IrreversibleState:
        m_ss<<" Patient no longer is in irreversible state?!";
        break;
      case cdm::PatientData_eEvent_Ketoacidosis:
        m_ss << " Patient no longer has Ketoacidosis";
        break;
      case cdm::PatientData_eEvent_LacticAcidosis:
        m_ss << " Patient no longer has LacticAcidosis";
        break;
      case cdm::PatientData_eEvent_MaximumPulmonaryVentilationRate:
        m_ss << " Patient's Respiratory Driver is no longer exceeding the maximum target pulmonary ventilation rate";
        break;
      case cdm::PatientData_eEvent_MetabolicAcidosis:
        m_ss << " The patient is no longer in a state of metabolic acidosis";
        break;
      case cdm::PatientData_eEvent_MetabolicAlkalosis:
        m_ss << " The patient is no longer in a state of metabolic alkalosis";
        break;
      case cdm::PatientData_eEvent_MildAcuteRespiratoryDistress:
        m_ss << " Patient no longer has a Mild Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_ModerateAcuteRespiratoryDistress:
        m_ss << " Patient no longer has a Moderate Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_MyocardiumOxygenDeficit:
        m_ss << " Patient no longer has a Myocardium Oxygen Deficit";
        break;
      case cdm::PatientData_eEvent_Natriuresis:
        m_ss << " Patient no longer has Natriuresis";
        break;
      case cdm::PatientData_eEvent_NutritionDepleted:
        m_ss << " Patient has nutrition in body";
        break;
      case cdm::PatientData_eEvent_PulselessRhythm:
        m_ss << " Patient no longer has a Pulseless Rhythm";
        break;
      case cdm::PatientData_eEvent_RenalHypoperfusion:
        m_ss << " Patient no longer has Renal Hypoperfusion";
        break;
      case cdm::PatientData_eEvent_SevereAcuteRespiratoryDistress:
        m_ss << " Patient no longer has a Severe Acute Respiratory Distress";
        break;
      case cdm::PatientData_eEvent_Tachycardia:
        m_ss<<" Patient no longer has Tachycardia";
        break;
      case cdm::PatientData_eEvent_Tachypnea:
        m_ss << " Patient no longer has Tachypnea";
        break;
      case cdm::PatientData_eEvent_Fatigue:
        m_ss << "Patient is no longer fatigued";
        break;
      case cdm::PatientData_eEvent_StartOfCardiacCycle:
      case cdm::PatientData_eEvent_StartOfExhale:
      case cdm::PatientData_eEvent_StartOfInhale:
        m_ss.str("");// make m_ss empty and nothing will be logged, this event does not need to get logged each activation
        break;
      default:
        m_ss<<" Patient has exited state : "<<type;//TODO cdm::PatientData_eEvent__xsd_enumPatientEvent_literals_[type];
      }
    }
    if (!m_ss.str().empty())
      Info(m_ss);
  }
  m_EventState[type] = active;
  m_EventDuration_s[type] = 0;
  if(m_EventHandler!=nullptr)
    m_EventHandler->HandlePatientEvent(type,active,&time);
}

bool SEPatient::IsEventActive(cdm::PatientData::eEvent type) const
{
  auto i = m_EventState.find(type);
  if(i==m_EventState.end())
    return false;
  return i->second;
}

double SEPatient::GetEventDuration(cdm::PatientData::eEvent type, const TimeUnit& unit) const
{
  auto i = m_EventDuration_s.find(type);
  if (i == m_EventDuration_s.end())
    return 0;
  return Convert(i->second, TimeUnit::s, unit);
}

void SEPatient::UpdateEvents(const SEScalarTime& timeStep)
{
  for(auto& itr : m_EventDuration_s)
    itr.second += timeStep.GetValue(TimeUnit::s);
}

void SEPatient::ForwardEvents(SEEventHandler* handler) const
{
  m_EventHandler=handler;
}

std::string SEPatient::GetName() const
{
  return m_Name;
}
void SEPatient::SetName(const std::string& name)
{
  m_Name = name;
}
bool SEPatient::HasName() const
{
  return m_Name.empty()?false:true;
}
void SEPatient::InvalidateName()
{
  m_Name = "";
}

cdm::PatientData::eSex SEPatient::GetSex() const
{
  return m_Sex;
}
void SEPatient::SetSex(cdm::PatientData::eSex sex)
{
  m_Sex = sex;
}

bool SEPatient::HasAge() const
{
  return m_Age==nullptr?false:m_Age->IsValid();
}
SEScalarTime& SEPatient::GetAge()
{
  if(m_Age==nullptr)
    m_Age=new SEScalarTime();
  return *m_Age;
}
double SEPatient::GetAge(const TimeUnit& unit) const
{
  if (m_Age == nullptr)
    return SEScalar::dNaN();
  return m_Age->GetValue(unit);
}

bool SEPatient::HasWeight() const
{
  return m_Weight==nullptr?false:m_Weight->IsValid();
}
SEScalarMass& SEPatient::GetWeight()
{
  if(m_Weight==nullptr)
    m_Weight=new SEScalarMass();
  return *m_Weight;
}
double SEPatient::GetWeight(const MassUnit& unit) const
{
  if (m_Weight == nullptr)
    return SEScalar::dNaN();
  return m_Weight->GetValue(unit);
}

bool SEPatient::HasHeight() const
{
  return m_Height==nullptr?false:m_Height->IsValid();
}
SEScalarLength& SEPatient::GetHeight()
{
  if(m_Height==nullptr)
    m_Height=new SEScalarLength();
  return *m_Height;
}
double SEPatient::GetHeight(const LengthUnit& unit) const
{
  if (m_Height == nullptr)
    return SEScalar::dNaN();
  return m_Height->GetValue(unit);
}

bool SEPatient::HasAlveoliSurfaceArea() const
{
  return m_AlveoliSurfaceArea == nullptr ? false : m_AlveoliSurfaceArea->IsValid();
}
SEScalarArea& SEPatient::GetAlveoliSurfaceArea()
{
  if (m_AlveoliSurfaceArea == nullptr)
    m_AlveoliSurfaceArea = new SEScalarArea();
  return *m_AlveoliSurfaceArea;
}
double SEPatient::GetAlveoliSurfaceArea(const AreaUnit& unit) const
{
  if (m_AlveoliSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_AlveoliSurfaceArea->GetValue(unit);
}

bool SEPatient::HasBasalMetabolicRate() const
{
  return m_BasalMetabolicRate == nullptr ? false : m_BasalMetabolicRate->IsValid();
}
SEScalarPower& SEPatient::GetBasalMetabolicRate()
{
  if (m_BasalMetabolicRate == nullptr)
    m_BasalMetabolicRate = new SEScalarPower();
  return *m_BasalMetabolicRate;
}
double SEPatient::GetBasalMetabolicRate(const PowerUnit& unit) const
{
  if (m_BasalMetabolicRate == nullptr)
    return SEScalar::dNaN();
  return m_BasalMetabolicRate->GetValue(unit);
}

bool SEPatient::HasBloodVolumeBaseline() const
{
  return m_BloodVolumeBaseline == nullptr ? false : m_BloodVolumeBaseline->IsValid();
}
SEScalarVolume& SEPatient::GetBloodVolumeBaseline()
{
  if (m_BloodVolumeBaseline == nullptr)
    m_BloodVolumeBaseline = new SEScalarVolume();
  return *m_BloodVolumeBaseline;
}
double SEPatient::GetBloodVolumeBaseline(const VolumeUnit& unit) const
{
  if (m_BloodVolumeBaseline == nullptr)
    return SEScalar::dNaN();
  return m_BloodVolumeBaseline->GetValue(unit);
}

bool SEPatient::HasBodyDensity() const
{
  return m_BodyDensity == nullptr ? false : m_BodyDensity->IsValid();
}
SEScalarMassPerVolume& SEPatient::GetBodyDensity()
{
  if (m_BodyDensity == nullptr)
    m_BodyDensity = new SEScalarMassPerVolume();
  return *m_BodyDensity;
}
double SEPatient::GetBodyDensity(const MassPerVolumeUnit& unit) const
{
  if (m_BodyDensity == nullptr)
    return SEScalar::dNaN();
  return m_BodyDensity->GetValue(unit);
}

bool SEPatient::HasBodyFatFraction() const
{
  return m_BodyFatFraction == nullptr ? false : m_BodyFatFraction->IsValid();
}
SEScalar0To1& SEPatient::GetBodyFatFraction()
{
  if (m_BodyFatFraction == nullptr)
    m_BodyFatFraction = new SEScalar0To1();
  return *m_BodyFatFraction;
}
double SEPatient::GetBodyFatFraction() const
{
  if (m_BodyFatFraction == nullptr)
    return SEScalar::dNaN();
  return m_BodyFatFraction->GetValue();
}

bool SEPatient::HasDiastolicArterialPressureBaseline() const
{
  return m_DiastolicArterialPressureBaseline == nullptr ? false : m_DiastolicArterialPressureBaseline->IsValid();
}
SEScalarPressure& SEPatient::GetDiastolicArterialPressureBaseline()
{
  if (m_DiastolicArterialPressureBaseline == nullptr)
    m_DiastolicArterialPressureBaseline = new SEScalarPressure();
  return *m_DiastolicArterialPressureBaseline;
}
double SEPatient::GetDiastolicArterialPressureBaseline(const PressureUnit& unit) const
{
  if (m_DiastolicArterialPressureBaseline == nullptr)
    return SEScalar::dNaN();
  return m_DiastolicArterialPressureBaseline->GetValue(unit);
}

bool SEPatient::HasExpiratoryReserveVolume() const
{
  return m_ExpiratoryReserveVolume==nullptr?false:m_ExpiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPatient::GetExpiratoryReserveVolume()
{
  if(m_ExpiratoryReserveVolume==nullptr)
    m_ExpiratoryReserveVolume=new SEScalarVolume();
  return *m_ExpiratoryReserveVolume;
}
double SEPatient::GetExpiratoryReserveVolume(const VolumeUnit& unit) const
{
  if (m_ExpiratoryReserveVolume == nullptr)
    return SEScalar::dNaN();
  return m_ExpiratoryReserveVolume->GetValue(unit);
}

bool SEPatient::HasFunctionalResidualCapacity() const
{
  return m_FunctionalResidualCapacity==nullptr?false:m_FunctionalResidualCapacity->IsValid();
}
SEScalarVolume& SEPatient::GetFunctionalResidualCapacity()
{
  if(m_FunctionalResidualCapacity==nullptr)
    m_FunctionalResidualCapacity=new SEScalarVolume();
  return *m_FunctionalResidualCapacity;
}
double SEPatient::GetFunctionalResidualCapacity(const VolumeUnit& unit) const
{
  if (m_FunctionalResidualCapacity == nullptr)
    return SEScalar::dNaN();
  return m_FunctionalResidualCapacity->GetValue(unit);
}

bool SEPatient::HasHeartRateBaseline() const
{
  return m_HeartRateBaseline==nullptr?false:m_HeartRateBaseline->IsValid();
}
SEScalarFrequency& SEPatient::GetHeartRateBaseline()
{
  if(m_HeartRateBaseline==nullptr)
    m_HeartRateBaseline=new SEScalarFrequency();
  return *m_HeartRateBaseline;
}
double SEPatient::GetHeartRateBaseline(const FrequencyUnit& unit) const
{
  if (m_HeartRateBaseline == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateBaseline->GetValue(unit);
}

bool SEPatient::HasHeartRateMaximum() const
{
  return m_HeartRateMaximum==nullptr?false:m_HeartRateMaximum->IsValid();
}
SEScalarFrequency& SEPatient::GetHeartRateMaximum()
{
  if(m_HeartRateMaximum==nullptr)
    m_HeartRateMaximum=new SEScalarFrequency();
  return *m_HeartRateMaximum;
}
double SEPatient::GetHeartRateMaximum(const FrequencyUnit& unit) const
{
  if (m_HeartRateMaximum == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateMaximum->GetValue(unit);
}

bool SEPatient::HasHeartRateMinimum() const
{
  return m_HeartRateMinimum==nullptr?false:m_HeartRateMinimum->IsValid();
}
SEScalarFrequency& SEPatient::GetHeartRateMinimum()
{
  if(m_HeartRateMinimum==nullptr)
    m_HeartRateMinimum=new SEScalarFrequency();
  return *m_HeartRateMinimum;
}
double SEPatient::GetHeartRateMinimum(const FrequencyUnit& unit) const
{
  if (m_HeartRateMinimum == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateMinimum->GetValue(unit);
}

bool SEPatient::HasInspiratoryCapacity() const
{
  return m_InspiratoryCapacity == nullptr ? false : m_InspiratoryCapacity->IsValid();
}
SEScalarVolume& SEPatient::GetInspiratoryCapacity()
{
  if (m_InspiratoryCapacity == nullptr)
    m_InspiratoryCapacity = new SEScalarVolume();
  return *m_InspiratoryCapacity;
}
double SEPatient::GetInspiratoryCapacity(const VolumeUnit& unit) const
{
  if (m_InspiratoryCapacity == nullptr)
    return SEScalar::dNaN();
  return m_InspiratoryCapacity->GetValue(unit);
}

bool SEPatient::HasInspiratoryReserveVolume() const
{
  return m_InspiratoryReserveVolume == nullptr ? false : m_InspiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPatient::GetInspiratoryReserveVolume()
{
  if (m_InspiratoryReserveVolume == nullptr)
    m_InspiratoryReserveVolume = new SEScalarVolume();
  return *m_InspiratoryReserveVolume;
}
double SEPatient::GetInspiratoryReserveVolume(const VolumeUnit& unit) const
{
  if (m_InspiratoryReserveVolume == nullptr)
    return SEScalar::dNaN();
  return m_InspiratoryReserveVolume->GetValue(unit);
}

bool SEPatient::HasLeanBodyMass() const
{
  return m_LeanBodyMass == nullptr ? false : m_LeanBodyMass->IsValid();
}
SEScalarMass& SEPatient::GetLeanBodyMass()
{
  if (m_LeanBodyMass == nullptr)
    m_LeanBodyMass = new SEScalarMass();
  return *m_LeanBodyMass;
}
double SEPatient::GetLeanBodyMass(const MassUnit& unit) const
{
  if (m_LeanBodyMass == nullptr)
    return SEScalar::dNaN();
  return m_LeanBodyMass->GetValue(unit);
}

bool SEPatient::HasMeanArterialPressureBaseline() const
{
  return m_MeanArterialPressureBaseline==nullptr?false:m_MeanArterialPressureBaseline->IsValid();
}
SEScalarPressure& SEPatient::GetMeanArterialPressureBaseline()
{
  if(m_MeanArterialPressureBaseline==nullptr)
    m_MeanArterialPressureBaseline=new SEScalarPressure();
  return *m_MeanArterialPressureBaseline;
}
double SEPatient::GetMeanArterialPressureBaseline(const PressureUnit& unit) const
{
  if (m_MeanArterialPressureBaseline == nullptr)
    return SEScalar::dNaN();
  return m_MeanArterialPressureBaseline->GetValue(unit);
}

bool SEPatient::HasResidualVolume() const
{
  return m_ResidualVolume == nullptr ? false : m_ResidualVolume->IsValid();
}
SEScalarVolume& SEPatient::GetResidualVolume()
{
  if (m_ResidualVolume == nullptr)
    m_ResidualVolume = new SEScalarVolume();
  return *m_ResidualVolume;
}
double SEPatient::GetResidualVolume(const VolumeUnit& unit) const
{
  if (m_ResidualVolume == nullptr)
    return SEScalar::dNaN();
  return m_ResidualVolume->GetValue(unit);
}

bool SEPatient::HasRespirationRateBaseline() const
{
  return m_RespirationRateBaseline==nullptr?false:m_RespirationRateBaseline->IsValid();
}
SEScalarFrequency& SEPatient::GetRespirationRateBaseline()
{
  if(m_RespirationRateBaseline==nullptr)
    m_RespirationRateBaseline=new SEScalarFrequency();
  return *m_RespirationRateBaseline;
}
double SEPatient::GetRespirationRateBaseline(const FrequencyUnit& unit) const
{
  if (m_RespirationRateBaseline == nullptr)
    return SEScalar::dNaN();
  return m_RespirationRateBaseline->GetValue(unit);
}

bool SEPatient::HasRightLungRatio() const
{
  return m_RightLungRatio==nullptr?false:m_RightLungRatio->IsValid();
}
SEScalar0To1& SEPatient::GetRightLungRatio()
{
  if(m_RightLungRatio==nullptr)
    m_RightLungRatio=new SEScalar0To1();
  return *m_RightLungRatio;
}
double SEPatient::GetRightLungRatio() const
{
  if (m_RightLungRatio == nullptr)
    return SEScalar::dNaN();
  return m_RightLungRatio->GetValue();
}

bool SEPatient::HasSkinSurfaceArea() const
{
  return m_SkinSurfaceArea == nullptr ? false : m_SkinSurfaceArea->IsValid();
}
SEScalarArea& SEPatient::GetSkinSurfaceArea()
{
  if (m_SkinSurfaceArea == nullptr)
    m_SkinSurfaceArea = new SEScalarArea();
  return *m_SkinSurfaceArea;
}
double SEPatient::GetSkinSurfaceArea(const AreaUnit& unit) const
{
  if (m_SkinSurfaceArea == nullptr)
    return SEScalar::dNaN();
  return m_SkinSurfaceArea->GetValue(unit);
}

bool SEPatient::HasSystolicArterialPressureBaseline() const
{
  return m_SystolicArterialPressureBaseline == nullptr ? false : m_SystolicArterialPressureBaseline->IsValid();
}
SEScalarPressure& SEPatient::GetSystolicArterialPressureBaseline()
{
  if (m_SystolicArterialPressureBaseline == nullptr)
    m_SystolicArterialPressureBaseline = new SEScalarPressure();
  return *m_SystolicArterialPressureBaseline;
}
double SEPatient::GetSystolicArterialPressureBaseline(const PressureUnit& unit) const
{
  if (m_SystolicArterialPressureBaseline == nullptr)
    return SEScalar::dNaN();
  return m_SystolicArterialPressureBaseline->GetValue(unit);
}

bool SEPatient::HasTidalVolumeBaseline() const
{
  return m_TidalVolumeBaseline == nullptr ? false : m_TidalVolumeBaseline->IsValid();
}
SEScalarVolume& SEPatient::GetTidalVolumeBaseline()
{
  if (m_TidalVolumeBaseline == nullptr)
    m_TidalVolumeBaseline = new SEScalarVolume();
  return *m_TidalVolumeBaseline;
}
double SEPatient::GetTidalVolumeBaseline(const VolumeUnit& unit) const
{
  if (m_TidalVolumeBaseline == nullptr)
    return SEScalar::dNaN();
  return m_TidalVolumeBaseline->GetValue(unit);
}

bool SEPatient::HasTotalLungCapacity() const
{
  return m_TotalLungCapacity==nullptr?false:m_TotalLungCapacity->IsValid();
}
SEScalarVolume& SEPatient::GetTotalLungCapacity()
{
  if(m_TotalLungCapacity==nullptr)
    m_TotalLungCapacity=new SEScalarVolume();
  return *m_TotalLungCapacity;
}
double SEPatient::GetTotalLungCapacity(const VolumeUnit& unit) const
{
  if (m_TotalLungCapacity == nullptr)
    return SEScalar::dNaN();
  return m_TotalLungCapacity->GetValue(unit);
}

bool SEPatient::HasVitalCapacity() const
{
  return m_VitalCapacity == nullptr ? false : m_VitalCapacity->IsValid();
}
SEScalarVolume& SEPatient::GetVitalCapacity()
{
  if (m_VitalCapacity == nullptr)
    m_VitalCapacity = new SEScalarVolume();
  return *m_VitalCapacity;
}
double SEPatient::GetVitalCapacity(const VolumeUnit& unit) const
{
  if (m_VitalCapacity == nullptr)
    return SEScalar::dNaN();
  return m_VitalCapacity->GetValue(unit);
}