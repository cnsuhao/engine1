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
#include "system/equipment/Inhaler/SEInhaler.h"
#include "substance/SESubstance.h"
#include "substance/SESubstanceManager.h"
// State Actions
#include "system/equipment/Inhaler/actions/SEInhalerConfiguration.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"
#include <google/protobuf/text_format.h>

SEInhaler::SEInhaler(SESubstanceManager& substances) : SESystem(substances.GetLogger()), m_Substances(substances)
{
  m_State = cdm::eSwitch(-1);
  m_MeteredDose = nullptr;
  m_NozzleLoss = nullptr;
  m_SpacerVolume = nullptr;
  m_Substance = nullptr;
}

SEInhaler::~SEInhaler()
{
  Clear();
}

void SEInhaler::Clear()
{
  SESystem::Clear();

  m_State = cdm::eSwitch(-1);
  SAFE_DELETE(m_MeteredDose);
  SAFE_DELETE(m_NozzleLoss);
  SAFE_DELETE(m_SpacerVolume);
  m_Substance = nullptr;
}

void SEInhaler::Load(const cdm::InhalerData& src, SEInhaler& dst)
{
  SEInhaler::Serialize(src, dst);
}
void SEInhaler::Serialize(const cdm::InhalerData& src, SEInhaler& dst)
{
  dst.Clear();
  dst.SetState(src.state());
  if (src.has_metereddose())
    SEScalarMass::Load(src.metereddose(), dst.GetMeteredDose());
  if (src.has_nozzleloss())
    SEScalar0To1::Load(src.nozzleloss(), dst.GetNozzleLoss());
  if (src.has_spacervolume())
    SEScalarVolume::Load(src.spacervolume(), dst.GetSpacerVolume());
  dst.SetSubstance(dst.m_Substances.GetSubstance(src.substance()));
  dst.StateChange();
}

cdm::InhalerData* SEInhaler::Unload(const SEInhaler& src)
{
  cdm::InhalerData* dst = new cdm::InhalerData();
  SEInhaler::Serialize(src, *dst);
  return dst;
}
void SEInhaler::Serialize(const SEInhaler& src, cdm::InhalerData& dst)
{
  if (src.HasState())
    dst.set_state(src.m_State);
  if (src.HasMeteredDose())
    dst.set_allocated_metereddose(SEScalarMass::Unload(*src.m_MeteredDose));
  if (src.HasNozzleLoss())
    dst.set_allocated_nozzleloss(SEScalar0To1::Unload(*src.m_NozzleLoss));
  if (src.HasSpacerVolume())
    dst.set_allocated_spacervolume(SEScalarVolume::Unload(*src.m_SpacerVolume));  
  if (src.HasSubstance())
    dst.set_allocated_substance(&src.m_Substance->GetName());
}

const SEScalar* SEInhaler::GetScalar(const std::string& name)
{
  if (name.compare("MeteredDose") == 0)
    return &GetMeteredDose();
  if (name.compare("NozzleLoss") == 0)
    return &GetNozzleLoss();
  if (name.compare("SpacerVolume") == 0)
    return &GetSpacerVolume();
  return nullptr;
}

void SEInhaler::Merge(const SEInhaler& from)
{
  if (from.HasState())
    SetState(from.m_State);
  COPY_PROPERTY(MeteredDose);
  COPY_PROPERTY(NozzleLoss);
  COPY_PROPERTY(SpacerVolume);
  if (from.m_Substance != nullptr)
  {
    if (&m_Substances != &from.m_Substances)
    {
      m_Substance = m_Substances.GetSubstance(from.m_Substance->GetName());
      if (m_Substance == nullptr)
      {
        m_ss << "Do not have substance : " << from.m_Substance->GetName();
        Error(m_ss);
      }
    }
    else
      m_Substance = from.m_Substance;
  }
}

void SEInhaler::ProcessConfiguration(const SEInhalerConfiguration& config)
{
  if (config.HasConfiguration())
    Merge(*config.GetConfiguration());
  else if (config.HasConfigurationFile())
    if (!LoadFile(config.GetConfigurationFile()))// Does NOT merge file in data, Should we?
      Error("Unable to load configuration file", "SEInhaler::ProcessConfiguration");
  StateChange();
}

bool SEInhaler::LoadFile(const std::string& inhalerFile)
{
  cdm::InhalerData src;
  std::ifstream file_stream(inhalerFile, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  google::protobuf::TextFormat::ParseFromString(fmsg, &src);
  SEInhaler::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

cdm::eSwitch SEInhaler::GetState() const
{
  return m_State;
}
void SEInhaler::SetState(cdm::eSwitch state)
{
  m_State = state;
}
bool SEInhaler::HasState() const
{
  return m_State == ((cdm::eSwitch)-1) ? false : true;
}
void SEInhaler::InvalidateState()
{
  m_State = (cdm::eSwitch) - 1;
}

bool SEInhaler::HasMeteredDose() const
{
  return m_MeteredDose == nullptr ? false : m_MeteredDose->IsValid();
}
SEScalarMass& SEInhaler::GetMeteredDose()
{
  if (m_MeteredDose == nullptr)
    m_MeteredDose = new SEScalarMass();
  return *m_MeteredDose;
}
double SEInhaler::GetMeteredDose(const MassUnit& unit) const
{
  if (m_MeteredDose == nullptr)
    return SEScalar::dNaN();
  return m_MeteredDose->GetValue(unit);
}

bool SEInhaler::HasNozzleLoss() const
{
  return m_NozzleLoss == nullptr ? false : m_NozzleLoss->IsValid();
}
SEScalar0To1& SEInhaler::GetNozzleLoss()
{
  if (m_NozzleLoss == nullptr)
    m_NozzleLoss = new SEScalar0To1();
  return *m_NozzleLoss;
}
double SEInhaler::GetNozzleLoss() const
{
  if (m_NozzleLoss == nullptr)
    return SEScalar::dNaN();
  return m_NozzleLoss->GetValue();
}

bool SEInhaler::HasSpacerVolume() const
{
  return m_SpacerVolume == nullptr ? false : m_SpacerVolume->IsValid();
}
SEScalarVolume& SEInhaler::GetSpacerVolume()
{
  if (m_SpacerVolume == nullptr)
    m_SpacerVolume = new SEScalarVolume();
  return *m_SpacerVolume;
}
double SEInhaler::GetSpacerVolume(const VolumeUnit& unit) const
{
  if (m_SpacerVolume == nullptr)
    return SEScalar::dNaN();
  return m_SpacerVolume->GetValue(unit);
}

bool SEInhaler::HasSubstance() const
{
  return m_Substance != nullptr;
}
void SEInhaler::SetSubstance(const SESubstance* sub)
{
  if (!sub->HasAerosolization())
    throw CommonDataModelException("Inhaler substance must have aerosolization data");
  m_Substance = sub;
}
SESubstance* SEInhaler::GetSubstance() const
{
  return (SESubstance*)m_Substance;
}
