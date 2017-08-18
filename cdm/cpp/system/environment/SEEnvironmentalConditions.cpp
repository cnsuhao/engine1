/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/environment/SEEnvironmentalConditions.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarHeatConductancePerArea.h"
#include "properties/SEScalarHeatResistanceArea.h"
#include "properties/SEScalarLengthPerTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarTemperature.h"

#include <google/protobuf/text_format.h>


SEEnvironmentalConditions::SEEnvironmentalConditions(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
  m_SurroundingType = cdm::EnvironmentData_eSurroundingType_Air;

  m_AirDensity=nullptr;
  m_AirVelocity = nullptr;
  m_AmbientTemperature = nullptr;
  m_AtmosphericPressure = nullptr;
  m_ClothingResistance = nullptr;
  m_Emissivity = nullptr;
  m_MeanRadiantTemperature = nullptr;
  m_RelativeHumidity = nullptr;
  m_RespirationAmbientTemperature = nullptr;
}

SEEnvironmentalConditions::~SEEnvironmentalConditions()
{
  Clear();
}

void SEEnvironmentalConditions::Clear()
{
  m_SurroundingType = cdm::EnvironmentData_eSurroundingType_Air;
  SAFE_DELETE(m_AirDensity);
  SAFE_DELETE(m_AirVelocity);
  SAFE_DELETE(m_AmbientTemperature);
  SAFE_DELETE(m_AtmosphericPressure);
  SAFE_DELETE(m_ClothingResistance);
  SAFE_DELETE(m_Emissivity); 
  SAFE_DELETE(m_MeanRadiantTemperature);
  SAFE_DELETE(m_RelativeHumidity);
  SAFE_DELETE(m_RespirationAmbientTemperature);

  DELETE_VECTOR(m_AmbientGases);
  m_cAmbientGases.clear();

  DELETE_VECTOR(m_AmbientAerosols);
  m_cAmbientAerosols.clear();
}

const SEScalar* SEEnvironmentalConditions::GetScalar(const std::string& name)
{
  if (name.compare("AirDensity") == 0)
    return &GetAirDensity();
  if (name.compare("AirVelocity") == 0)
    return &GetAirVelocity();
  if (name.compare("AmbientTemperature") == 0)
    return &GetAmbientTemperature();
  if (name.compare("AtmosphericPressure") == 0)
    return &GetAtmosphericPressure();
  if (name.compare("ClothingResistance") == 0)
    return &GetClothingResistance();
  if (name.compare("Emissivity") == 0)
    return &GetEmissivity();
  if (name.compare("MeanRadiantTemperature") == 0)
    return &GetMeanRadiantTemperature();
  if (name.compare("RelativeHumidity") == 0)
    return &GetRelativeHumidity();
  if (name.compare("RespirationAmbientTemperature") == 0)
    return &GetRespirationAmbientTemperature();
  // I did not support for getting a specific gas/aerosol scalars due to lack of coffee
  return nullptr;
}

void SEEnvironmentalConditions::Load(const cdm::EnvironmentData_ConditionsData& src, SEEnvironmentalConditions& dst)
{
  SEEnvironmentalConditions::Serialize(src, dst);
}
void SEEnvironmentalConditions::Serialize(const cdm::EnvironmentData_ConditionsData& src, SEEnvironmentalConditions& dst)
{
  dst.Clear();
  dst.SetSurroundingType(src.surroundingtype());
  if (src.has_airdensity())
    SEScalarMassPerVolume::Load(src.airdensity(), dst.GetAirDensity());
  if (src.has_airvelocity())
    SEScalarLengthPerTime::Load(src.airvelocity(), dst.GetAirVelocity());
  if (src.has_ambienttemperature())
    SEScalarTemperature::Load(src.ambienttemperature(), dst.GetAmbientTemperature());
  if (src.has_atmosphericpressure())
    SEScalarPressure::Load(src.atmosphericpressure(), dst.GetAtmosphericPressure());
  if (src.has_clothingresistance())
    SEScalarHeatResistanceArea::Load(src.clothingresistance(), dst.GetClothingResistance());
  if (src.has_emissivity())
    SEScalar0To1::Load(src.emissivity(), dst.GetEmissivity());
  if (src.has_meanradianttemperature())
    SEScalarTemperature::Load(src.meanradianttemperature(), dst.GetMeanRadiantTemperature());
  if (src.has_relativehumidity())
    SEScalar0To1::Load(src.relativehumidity(), dst.GetRelativeHumidity());
  if (src.has_respirationambienttemperature())
    SEScalarTemperature::Load(src.respirationambienttemperature(), dst.GetRespirationAmbientTemperature());

  SESubstance* sub;
  for (int i = 0; i < src.ambientgas_size(); i++)
  {
    const cdm::SubstanceData_FractionAmountData& sfData = src.ambientgas()[i];
    sub = dst.m_Substances.GetSubstance(sfData.name());
    if (sub == nullptr)
    {
      dst.Error("Ignoring an environmental conditions ambient gas that was not found : " + sfData.name());
      continue;
    }
    if (sub->GetState() != cdm::SubstanceData_eState_Gas)
    {
      dst.Error("Ignoring an environmental conditions ambient gas that is not a gas : " + sfData.name());
      continue;
    }
    SESubstanceFraction::Load(sfData, dst.GetAmbientGas(*sub));
  }

  for (int i = 0; i < src.ambientaerosol_size(); i++)
  {
    const cdm::SubstanceData_ConcentrationData& scData = src.ambientaerosol()[i];
    sub = dst.m_Substances.GetSubstance(scData.name());
    if (sub == nullptr)
    {
      dst.Error("Ignoring an environmental conditions ambient aerosol that was not found : " + scData.name());
      continue;
    }
    if (sub->GetState() != cdm::SubstanceData_eState_Liquid && sub->GetState() != cdm::SubstanceData_eState_Solid)
    {
      dst.Error("Ignoring an environmental conditions ambient aerosol that is not a gas : " + scData.name());
      continue;
    }
    SESubstanceConcentration::Load(scData, dst.GetAmbientAerosol(*sub));
  }
}

cdm::EnvironmentData_ConditionsData* SEEnvironmentalConditions::Unload(const SEEnvironmentalConditions& src)
{
  cdm::EnvironmentData_ConditionsData* dst = new cdm::EnvironmentData_ConditionsData();
  SEEnvironmentalConditions::Serialize(src, *dst);
  return dst;
}

void SEEnvironmentalConditions::Serialize(const SEEnvironmentalConditions& src, cdm::EnvironmentData_ConditionsData& dst)
{
  dst.set_surroundingtype(src.m_SurroundingType);
  if (src.HasAirDensity())
    dst.set_allocated_airdensity(SEScalarMassPerVolume::Unload(*src.m_AirDensity));
  if (src.HasAirVelocity())
    dst.set_allocated_airvelocity(SEScalarLengthPerTime::Unload(*src.m_AirVelocity));
  if (src.HasAmbientTemperature())
    dst.set_allocated_ambienttemperature(SEScalarTemperature::Unload(*src.m_AmbientTemperature));
  if (src.HasAtmosphericPressure())
    dst.set_allocated_atmosphericpressure(SEScalarPressure::Unload(*src.m_AtmosphericPressure));
  if (src.HasClothingResistance())
    dst.set_allocated_clothingresistance(SEScalarHeatResistanceArea::Unload(*src.m_ClothingResistance));
  if (src.HasEmissivity())
    dst.set_allocated_emissivity(SEScalar0To1::Unload(*src.m_Emissivity));
  if (src.HasMeanRadiantTemperature())
    dst.set_allocated_meanradianttemperature(SEScalarTemperature::Unload(*src.m_MeanRadiantTemperature));
  if (src.HasRelativeHumidity())
    dst.set_allocated_relativehumidity(SEScalar0To1::Unload(*src.m_RelativeHumidity));
  if (src.HasRespirationAmbientTemperature())
    dst.set_allocated_respirationambienttemperature(SEScalarTemperature::Unload(*src.m_RespirationAmbientTemperature));

  for (SESubstanceFraction *sf : src.m_AmbientGases)
    dst.mutable_ambientgas()->AddAllocated(SESubstanceFraction::Unload(*sf));

  for (SESubstanceConcentration *sc : src.m_AmbientAerosols)
    dst.mutable_ambientaerosol()->AddAllocated(SESubstanceConcentration::Unload(*sc));
}

void SEEnvironmentalConditions::Merge(const SEEnvironmentalConditions& from)
{
  SetSurroundingType(from.m_SurroundingType);
  COPY_PROPERTY(AirDensity);
  COPY_PROPERTY(AirVelocity);
  COPY_PROPERTY(AmbientTemperature);
  COPY_PROPERTY(AtmosphericPressure);
  COPY_PROPERTY(ClothingResistance);
  COPY_PROPERTY(Emissivity);
  COPY_PROPERTY(MeanRadiantTemperature);
  COPY_PROPERTY(RelativeHumidity);
  COPY_PROPERTY(RespirationAmbientTemperature);

  // Always need to provide a full (fractions sum to 1) substance list that replaces current
  if (from.HasAmbientGas())
  {
    double amt;
    double total = 0;
    RemoveAmbientGases();
    SESubstance* sub;
    SESubstanceFraction* sf;
    for (SESubstanceFraction* osf : from.m_AmbientGases)
    {
      if (&m_Substances != &from.m_Substances)
      {
        sub = m_Substances.GetSubstance(osf->GetSubstance().GetName());
        if (sub==nullptr)
        {
          std::stringstream ss;
          ss << "Do not have substance : " << osf->GetSubstance().GetName();
          Error(ss);
        }
      }
      else
        sub = &osf->GetSubstance();

      sf = new SESubstanceFraction(*sub); 
      sf->GetFractionAmount().Set(osf->GetFractionAmount());
      amt = sf->GetFractionAmount().GetValue();
      total += amt;
      m_AmbientGases.push_back(sf);
      m_cAmbientGases.push_back(sf);
      m_Substances.AddActiveSubstance((SESubstance&)sf->m_Substance);
    }
    if (!SEScalar::IsValue(1, total))
      Error("Environment Ambient Substance fractions do not sum to 1");
  }

  if (from.HasAmbientAerosol())
  {
    for (SESubstanceConcentration* sc : from.m_AmbientAerosols)
    {
      SESubstanceConcentration& mine = GetAmbientAerosol(sc->GetSubstance());
      mine.GetConcentration().Set(sc->GetConcentration());
    }
  }
}

bool SEEnvironmentalConditions::LoadFile(const std::string& filename)
{
  cdm::EnvironmentData_ConditionsData src;
  std::ifstream file_stream(filename, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  SEEnvironmentalConditions::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

cdm::EnvironmentData_eSurroundingType SEEnvironmentalConditions::GetSurroundingType() const
{
  return m_SurroundingType;
}
void SEEnvironmentalConditions::SetSurroundingType(cdm::EnvironmentData_eSurroundingType state)
{
  m_SurroundingType = state;
}

bool SEEnvironmentalConditions::HasAirDensity() const
{
  return m_AirDensity == nullptr ? false : m_AirDensity->IsValid();
}
SEScalarMassPerVolume& SEEnvironmentalConditions::GetAirDensity()
{
  if (m_AirDensity == nullptr)
    m_AirDensity = new SEScalarMassPerVolume();
  return *m_AirDensity;
}
double SEEnvironmentalConditions::GetAirDensity(const MassPerVolumeUnit& unit) const
{
  if (m_AirDensity == nullptr)
    return SEScalar::dNaN();
  return m_AirDensity->GetValue(unit);
}

bool SEEnvironmentalConditions::HasAirVelocity() const
{
  return m_AirVelocity == nullptr ? false : m_AirVelocity->IsValid();
}
SEScalarLengthPerTime& SEEnvironmentalConditions::GetAirVelocity()
{
  if (m_AirVelocity == nullptr)
    m_AirVelocity = new SEScalarLengthPerTime();
  return *m_AirVelocity;
}
double SEEnvironmentalConditions::GetAirVelocity(const LengthPerTimeUnit& unit) const
{
  if (m_AirVelocity == nullptr)
    return SEScalar::dNaN();
  return m_AirVelocity->GetValue(unit);
}


bool SEEnvironmentalConditions::HasAmbientTemperature() const
{
  return m_AmbientTemperature==nullptr?false:m_AmbientTemperature->IsValid();
}
SEScalarTemperature& SEEnvironmentalConditions::GetAmbientTemperature()
{
  if(m_AmbientTemperature==nullptr)
    m_AmbientTemperature=new SEScalarTemperature();
  return *m_AmbientTemperature;
}
double SEEnvironmentalConditions::GetAmbientTemperature(const TemperatureUnit& unit) const
{
  if (m_AmbientTemperature == nullptr)
    return SEScalar::dNaN();
  return m_AmbientTemperature->GetValue(unit);
}

bool SEEnvironmentalConditions::HasAtmosphericPressure() const
{
  return m_AtmosphericPressure==nullptr?false:m_AtmosphericPressure->IsValid();
}
SEScalarPressure& SEEnvironmentalConditions::GetAtmosphericPressure()
{
  if(m_AtmosphericPressure==nullptr)
    m_AtmosphericPressure=new SEScalarPressure();
  return *m_AtmosphericPressure;
}
double SEEnvironmentalConditions::GetAtmosphericPressure(const PressureUnit& unit) const
{
  if (m_AtmosphericPressure == nullptr)
    return SEScalar::dNaN();
  return m_AtmosphericPressure->GetValue(unit);
}

bool SEEnvironmentalConditions::HasClothingResistance() const
{
  return m_ClothingResistance == nullptr ? false : m_ClothingResistance->IsValid();
}
SEScalarHeatResistanceArea& SEEnvironmentalConditions::GetClothingResistance()
{
  if (m_ClothingResistance == nullptr)
    m_ClothingResistance = new SEScalarHeatResistanceArea();
  return *m_ClothingResistance;
}
double SEEnvironmentalConditions::GetClothingResistance(const HeatResistanceAreaUnit& unit) const
{
  if (m_ClothingResistance == nullptr)
    return SEScalar::dNaN();
  return m_ClothingResistance->GetValue(unit);
}

bool SEEnvironmentalConditions::HasEmissivity() const
{
  return m_Emissivity == nullptr ? false : m_Emissivity->IsValid();
}
SEScalar0To1& SEEnvironmentalConditions::GetEmissivity()
{
  if (m_Emissivity == nullptr)
    m_Emissivity = new SEScalar0To1();
  return *m_Emissivity;
}
double SEEnvironmentalConditions::GetEmissivity() const
{
  if (m_Emissivity == nullptr)
    return SEScalar::dNaN();
  return m_Emissivity->GetValue();
}

bool SEEnvironmentalConditions::HasMeanRadiantTemperature() const
{
  return m_MeanRadiantTemperature == nullptr ? false : m_MeanRadiantTemperature->IsValid();
}
SEScalarTemperature& SEEnvironmentalConditions::GetMeanRadiantTemperature()
{
  if (m_MeanRadiantTemperature == nullptr)
    m_MeanRadiantTemperature = new SEScalarTemperature();
  return *m_MeanRadiantTemperature;
}
double SEEnvironmentalConditions::GetMeanRadiantTemperature(const TemperatureUnit& unit) const
{
  if (m_MeanRadiantTemperature == nullptr)
    return SEScalar::dNaN();
  return m_MeanRadiantTemperature->GetValue(unit);
}

bool SEEnvironmentalConditions::HasRelativeHumidity() const
{
  return m_RelativeHumidity == nullptr ? false : m_RelativeHumidity->IsValid();
}
SEScalar0To1& SEEnvironmentalConditions::GetRelativeHumidity()
{
  if (m_RelativeHumidity == nullptr)
    m_RelativeHumidity = new SEScalar0To1();
  return *m_RelativeHumidity;
}
double SEEnvironmentalConditions::GetRelativeHumidity() const
{
  if (m_RelativeHumidity == nullptr)
    return SEScalar::dNaN();
  return m_RelativeHumidity->GetValue();
}

bool SEEnvironmentalConditions::HasRespirationAmbientTemperature() const
{
  return m_RespirationAmbientTemperature == nullptr ? false : m_RespirationAmbientTemperature->IsValid();
}
SEScalarTemperature& SEEnvironmentalConditions::GetRespirationAmbientTemperature()
{
  if (m_RespirationAmbientTemperature == nullptr)
    m_RespirationAmbientTemperature = new SEScalarTemperature();
  return *m_RespirationAmbientTemperature;
}
double SEEnvironmentalConditions::GetRespirationAmbientTemperature(const TemperatureUnit& unit) const
{
  if (m_RespirationAmbientTemperature == nullptr)
    return SEScalar::dNaN();
  return m_RespirationAmbientTemperature->GetValue(unit);
}

bool SEEnvironmentalConditions::HasAmbientGas() const
{
  return m_AmbientGases.size() == 0 ? false : true;
}
bool SEEnvironmentalConditions::HasAmbientGas(const SESubstance& s) const
{
  for (const SESubstanceFraction* sf : m_AmbientGases)
  {
    if (&s == &sf->GetSubstance())
      return true;
  }
  return false;
}
const std::vector<SESubstanceFraction*>& SEEnvironmentalConditions::GetAmbientGases() 
{
  return m_AmbientGases;
}
const std::vector<const SESubstanceFraction*>& SEEnvironmentalConditions::GetAmbientGases() const
{
  return m_cAmbientGases;
}
SESubstanceFraction& SEEnvironmentalConditions::GetAmbientGas(SESubstance& s)
{
  for (SESubstanceFraction* sf : m_AmbientGases)
  {
    if (&s == &sf->GetSubstance())
      return *sf;
  }
  SESubstanceFraction* sf = new SESubstanceFraction(s);
  sf->GetFractionAmount().SetValue(0);
  m_AmbientGases.push_back(sf);
  m_cAmbientGases.push_back(sf);
  return *sf;
}
const SESubstanceFraction* SEEnvironmentalConditions::GetAmbientGas(const SESubstance& s) const
{
  const SESubstanceFraction* sf = nullptr;
  for (unsigned int i = 0; i<m_AmbientGases.size(); i++)
  {
    sf = m_AmbientGases[i];
    if (&s == &sf->GetSubstance())
      return sf;
  }
  return sf;
}
void SEEnvironmentalConditions::RemoveAmbientGas(const SESubstance& s)
{
  const SESubstanceFraction* sf;
  for (unsigned int i = 0; i<m_AmbientGases.size(); i++)
  {
    sf = m_AmbientGases[i];
    if (&s == &sf->GetSubstance())
    {
      m_AmbientGases.erase(m_AmbientGases.begin() + i);
      m_cAmbientGases.erase(m_cAmbientGases.begin() + i);
      delete sf;
    }
  }
}
void SEEnvironmentalConditions::RemoveAmbientGases()
{  
  DELETE_VECTOR(m_AmbientGases);
  m_cAmbientGases.clear();
}


bool SEEnvironmentalConditions::HasAmbientAerosol() const
{
  return m_AmbientAerosols.size() == 0 ? false : true;
}
bool SEEnvironmentalConditions::HasAmbientAerosol(const SESubstance& substance) const
{
  for (const SESubstanceConcentration* sc : m_AmbientAerosols)
  {
    if (&substance == &sc->GetSubstance())
      return true;
  }
  return false;
}
const std::vector<SESubstanceConcentration*>& SEEnvironmentalConditions::GetAmbientAerosols()
{
  return m_AmbientAerosols;
}
const std::vector<const SESubstanceConcentration*>& SEEnvironmentalConditions::GetAmbientAerosols() const
{
  return m_cAmbientAerosols;
}
SESubstanceConcentration& SEEnvironmentalConditions::GetAmbientAerosol(SESubstance& substance)
{
  for (SESubstanceConcentration* sc : m_AmbientAerosols)
  {
    if (&substance == &sc->GetSubstance())
      return *sc;
  }
  SESubstanceConcentration* sc = new SESubstanceConcentration(substance);
  sc->GetConcentration().SetValue(0,MassPerVolumeUnit::ug_Per_L);
  m_AmbientAerosols.push_back(sc);
  m_cAmbientAerosols.push_back(sc);
  return *sc;
}
const SESubstanceConcentration* SEEnvironmentalConditions::GetAmbientAerosol(const SESubstance& substance) const
{
  const SESubstanceConcentration* sc = nullptr;
  for (unsigned int i = 0; i<m_AmbientAerosols.size(); i++)
  {
    sc = m_AmbientAerosols[i];
    if (&substance == &sc->GetSubstance())
      return sc;
  }
  return sc;
}
void SEEnvironmentalConditions::RemoveAmbientAerosol(const SESubstance& substance)
{
  const SESubstanceConcentration* sc;
  for (unsigned int i = 0; i<m_AmbientAerosols.size(); i++)
  {
    sc = m_AmbientAerosols[i];
    if (&substance == &sc->GetSubstance())
    {
      m_AmbientAerosols.erase(m_AmbientAerosols.begin() + i);
      m_cAmbientAerosols.erase(m_cAmbientAerosols.begin() + i);
      delete sc;
    }
  }
}
void SEEnvironmentalConditions::RemoveAmbientAerosols()
{
  DELETE_VECTOR(m_AmbientAerosols);
  m_cAmbientAerosols.clear();
}