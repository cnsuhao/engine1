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
#include "system/environment/SEEnvironment.h"
#include "system/environment/SEActiveHeating.h"
#include "system/environment/SEActiveCooling.h"
#include "system/environment/SEAppliedTemperature.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarHeatConductancePerArea.h"
#include "properties/SEScalarHeatResistanceArea.h"
#include "properties/SEScalarLengthPerTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPower.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarTemperature.h"

#include "substance/SESubstance.h"
#include "substance/SESubstanceFraction.h"
#include "substance/SESubstanceManager.h"

#include "system/environment/actions/SEEnvironmentChange.h"
#include "system/environment/conditions/SEInitialEnvironment.h"

SEEnvironment::SEEnvironment(SESubstanceManager& substances) : SESystem(substances.GetLogger()), m_Substances(substances)
{
  m_ActiveHeating = nullptr;
  m_ActiveCooling = nullptr;
  m_AppliedTemperature = nullptr; 
  m_Conditions = nullptr;
  m_ConvectiveHeatLoss = nullptr;
  m_ConvectiveHeatTranferCoefficient = nullptr;
  m_EvaporativeHeatLoss = nullptr;
  m_EvaporativeHeatTranferCoefficient = nullptr;
  m_RadiativeHeatLoss = nullptr;
  m_RadiativeHeatTranferCoefficient = nullptr;
  m_RespirationHeatLoss = nullptr;
  m_SkinHeatLoss = nullptr;
}

SEEnvironment::~SEEnvironment()
{
  Clear();
}

void SEEnvironment::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_ActiveHeating);
  SAFE_DELETE(m_ActiveCooling);
  SAFE_DELETE(m_AppliedTemperature);
  SAFE_DELETE(m_Conditions);
  SAFE_DELETE(m_ConvectiveHeatLoss);
  SAFE_DELETE(m_ConvectiveHeatTranferCoefficient);
  SAFE_DELETE(m_EvaporativeHeatLoss);
  SAFE_DELETE(m_EvaporativeHeatTranferCoefficient);
  SAFE_DELETE(m_RadiativeHeatLoss);
  SAFE_DELETE(m_RadiativeHeatTranferCoefficient);
  SAFE_DELETE(m_RespirationHeatLoss);
  SAFE_DELETE(m_SkinHeatLoss);
}

const SEScalar* SEEnvironment::GetScalar(const std::string& name)
{
  if (name.compare("ConvectiveHeatLoss") == 0)
    return &GetConvectiveHeatLoss();
  if (name.compare("ConvectiveHeatTranferCoefficient") == 0)
    return &GetConvectiveHeatTranferCoefficient();
  if (name.compare("EvaporativeHeatLoss") == 0)
    return &GetEvaporativeHeatLoss();
  if (name.compare("EvaporativeHeatTranferCoefficient") == 0)
    return &GetEvaporativeHeatTranferCoefficient();
  if (name.compare("RadiativeHeatLoss") == 0)
    return &GetRadiativeHeatLoss();
  if (name.compare("RadiativeHeatTranferCoefficient") == 0)
    return &GetRadiativeHeatTranferCoefficient();
  if (name.compare("RespirationHeatLoss") == 0)
    return &GetRespirationHeatLoss();
  if (name.compare("SkinHeatLoss") == 0)
    return &GetSkinHeatLoss();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == "Conditions")
      return GetConditions().GetScalar(prop);
    if (child == "ActiveHeating")
      return GetActiveHeating().GetScalar(prop);
    if (child == "ActiveCooling")
      return GetActiveCooling().GetScalar(prop);
    if (child == "AppliedTemperature")
      return GetAppliedTemperature().GetScalar(prop);
  }  
  return nullptr;
}

void SEEnvironment::Load(const cdm::EnvironmentData& src, SEEnvironment& dst)
{
  SEEnvironment::Serialize(src, dst);
}
void SEEnvironment::Serialize(const cdm::EnvironmentData& src, SEEnvironment& dst)
{
  dst.Clear();
  if (src.has_activeheating())
    SEActiveHeating::Load(src.activeheating(), dst.GetActiveHeating());
  if (src.has_activecooling())
    SEActiveCooling::Load(src.activecooling(), dst.GetActiveCooling());
  if (src.has_appliedtemperature())
    SEAppliedTemperature::Load(src.appliedtemperature(), dst.GetAppliedTemperature());
  if (src.has_conditions())
    SEEnvironmentalConditions::Load(src.conditions(), dst.GetConditions());

  if (src.has_convectiveheatloss())
    SEScalarPower::Load(src.convectiveheatloss(), dst.GetConvectiveHeatLoss());
  if (src.has_convectiveheattranfercoefficient())
    SEScalarHeatConductancePerArea::Load(src.convectiveheattranfercoefficient(), dst.GetConvectiveHeatTranferCoefficient());
  if (src.has_evaporativeheatloss())
    SEScalarPower::Load(src.evaporativeheatloss(), dst.GetEvaporativeHeatLoss());
  if (src.has_evaporativeheattranfercoefficient())
    SEScalarHeatConductancePerArea::Load(src.evaporativeheattranfercoefficient(), dst.GetEvaporativeHeatTranferCoefficient());
  if (src.has_radiativeheatloss())
    SEScalarPower::Load(src.radiativeheatloss(), dst.GetRadiativeHeatLoss());
  if (src.has_radiativeheattranfercoefficient())
    SEScalarHeatConductancePerArea::Load(src.radiativeheattranfercoefficient(), dst.GetRadiativeHeatTranferCoefficient());
  if (src.has_respirationheatloss())
    SEScalarPower::Load(src.respirationheatloss(), dst.GetRespirationHeatLoss());
  if (src.has_skinheatloss())
    SEScalarPower::Load(src.skinheatloss(), dst.GetSkinHeatLoss());

  StateChange();
}

cdm::EnvironmentData* SEEnvironment::Unload(const SEEnvironment& src)
{
  cdm::EnvironmentData* dst = new cdm::EnvironmentData();
  SEEnvironment::Serialize(src, *dst);
  return dst;
}
void SEEnvironment::Serialize(const SEEnvironment& src, cdm::EnvironmentData& dst)
{
  if (src.HasActiveHeating() && src.m_ActiveHeating->GetPower().IsPositive())
    dst.set_allocated_activeheating(SEActiveHeating::Unload(*src.m_ActiveHeating));  
  if (src.HasActiveCooling() && src.m_ActiveCooling->GetPower().IsPositive())
    dst.set_allocated_activecooling(SEActiveCooling::Unload(*src.m_ActiveCooling));
  if (src.HasAppliedTemperature())
    dst.set_allocated_appliedtemperature(SEAppliedTemperature::Unload(*src.m_AppliedTemperature);
  if (src.HasConditions())
    dst.set_allocated_conditions(SEEnvironmentalConditions::Unload(*src.m_Conditions));

  if (src.HasConvectiveHeatLoss())
    dst.set_allocated_convectiveheatloss(SEScalarPower::Unload(*src.m_ConvectiveHeatLoss));
  if (src.HasConvectiveHeatTranferCoefficient())
    dst.set_allocated_convectiveheattranfercoefficient(SEScalarHeatConductancePerArea::Unload(*src.m_ConvectiveHeatTranferCoefficient));
  if (src.HasEvaporativeHeatLoss())
    dst.set_allocated_evaporativeheatloss(SEScalarPower::Unload(*src.m_EvaporativeHeatLoss));
  if (src.HasEvaporativeHeatTranferCoefficient())
    dst.set_allocated_evaporativeheattranfercoefficient(SEScalarHeatConductancePerArea::Unload(*src.m_EvaporativeHeatTranferCoefficient));
  if (src.HasRadiativeHeatLoss())
    dst.set_allocated_radiativeheatloss(SEScalarPower::Unload(*src.m_RadiativeHeatLoss));
  if (src.HasRadiativeHeatTranferCoefficient())
    dst.set_allocated_radiativeheattranfercoefficient(SEScalarHeatConductancePerArea::Unload(*src.m_RadiativeHeatTranferCoefficient));
  if (src.HasRespirationHeatLoss())
    dst.set_allocated_respirationheatloss(SEScalarPower::Unload(*src.m_RespirationHeatLoss));
  if (src.HasSkinHeatLoss())
    dst.set_allocated_skinheatloss(SEScalarPower::Unload(*src.m_SkinHeatLoss));
}

bool SEEnvironment::ProcessChange(const SEInitialEnvironment& change)
{
  // If we have data then we merge it, if a file was provided
  // we reset and set the environment to the file, so we only have the file data
  if (change.HasConditions())
    GetConditions().Merge(*change.GetConditions());
  else if (change.HasConditionsFile())
  {
    if (!GetConditions().LoadFile(change.GetConditionsFile()))// Does NOT merge file in data, Should we?
    {
      /// \error Unable to read Configuration Action file
      Error("Could not read provided SEInitialEnvironment file", "SEEnvironment::ProcessChange");
      return false;
    }
  }
  StateChange();
  return true;
}

bool SEEnvironment::ProcessChange(const SEEnvironmentChange& change)
{
  // If we have data then we merge it, if a file was provided
  // we reset and set the environment to the file, so we only have the file data
  if (change.HasConditions())
    GetConditions().Merge(*change.GetConditions());
  else if (change.HasConditionsFile())
  {
    if (!GetConditions().LoadFile(change.GetConditionsFile()))// Does NOT merge file in data, Should we?
    {
      /// \error Unable to read Configuration Action file
      Error("Could not read provided SEEnvironmentChange file", "SEEnvironment::ProcessChange");
      return false;
    }
  }
  StateChange();
  return true;
}

bool SEEnvironment::HasActiveHeating() const
{
  return m_ActiveHeating != nullptr;
}
SEActiveHeating& SEEnvironment::GetActiveHeating()
{
  if (m_ActiveHeating == nullptr)
    m_ActiveHeating = new SEActiveHeating(GetLogger());
  return *m_ActiveHeating;
}
const SEActiveHeating* SEEnvironment::GetActiveHeating() const
{
  return m_ActiveHeating;
}
void SEEnvironment::RemoveActiveHeating()
{
  SAFE_DELETE(m_ActiveHeating);
}

bool SEEnvironment::HasActiveCooling() const
{
  return m_ActiveCooling != nullptr;
}
SEActiveCooling& SEEnvironment::GetActiveCooling()
{
  if (m_ActiveCooling == nullptr)
    m_ActiveCooling = new SEActiveCooling(GetLogger());
  return *m_ActiveCooling;
}
const SEActiveCooling* SEEnvironment::GetActiveCooling() const
{
  return m_ActiveCooling;
}
void SEEnvironment::RemoveActiveCooling()
{
  SAFE_DELETE(m_ActiveCooling);
}

bool SEEnvironment::HasAppliedTemperature() const
{
  return m_AppliedTemperature != nullptr;
}
SEAppliedTemperature& SEEnvironment::GetAppliedTemperature()
{
  if (m_AppliedTemperature == nullptr)
    m_AppliedTemperature = new SEAppliedTemperature(GetLogger());
  return *m_AppliedTemperature;
}
const SEAppliedTemperature* SEEnvironment::GetAppliedTemperature() const
{
  return m_AppliedTemperature;
}
void SEEnvironment::RemoveAppliedTemperature()
{
  SAFE_DELETE(m_AppliedTemperature);
}

bool SEEnvironment::HasConditions() const
{
  return m_Conditions != nullptr;
}
SEEnvironmentalConditions& SEEnvironment::GetConditions()
{
  if (m_Conditions == nullptr)
    m_Conditions = new SEEnvironmentalConditions(m_Substances);
  return *m_Conditions;
}
const SEEnvironmentalConditions* SEEnvironment::GetConditions() const
{
  return m_Conditions;
}
void SEEnvironment::RemoveConditions()
{
  SAFE_DELETE(m_Conditions);
}

bool SEEnvironment::HasConvectiveHeatLoss() const
{
  return m_ConvectiveHeatLoss == nullptr ? false : m_ConvectiveHeatLoss->IsValid();
}
SEScalarPower& SEEnvironment::GetConvectiveHeatLoss()
{
  if (m_ConvectiveHeatLoss == nullptr)
    m_ConvectiveHeatLoss = new SEScalarPower();
  return *m_ConvectiveHeatLoss;
}
double SEEnvironment::GetConvectiveHeatLoss(const PowerUnit& unit) const
{
  if (m_ConvectiveHeatLoss == nullptr)
    return SEScalar::dNaN();
  return m_ConvectiveHeatLoss->GetValue(unit);
}

bool SEEnvironment::HasConvectiveHeatTranferCoefficient() const
{
  return m_ConvectiveHeatTranferCoefficient == nullptr ? false : m_ConvectiveHeatTranferCoefficient->IsValid();
}
SEScalarHeatConductancePerArea& SEEnvironment::GetConvectiveHeatTranferCoefficient()
{
  if (m_ConvectiveHeatTranferCoefficient == nullptr)
    m_ConvectiveHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
  return *m_ConvectiveHeatTranferCoefficient;
}
double SEEnvironment::GetConvectiveHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const
{
  if (m_ConvectiveHeatTranferCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_ConvectiveHeatTranferCoefficient->GetValue(unit);
}

bool SEEnvironment::HasEvaporativeHeatLoss() const
{
  return m_EvaporativeHeatLoss == nullptr ? false : m_EvaporativeHeatLoss->IsValid();
}
SEScalarPower& SEEnvironment::GetEvaporativeHeatLoss()
{
  if (m_EvaporativeHeatLoss == nullptr)
    m_EvaporativeHeatLoss = new SEScalarPower();
  return *m_EvaporativeHeatLoss;
}
double SEEnvironment::GetEvaporativeHeatLoss(const PowerUnit& unit) const
{
  if (m_EvaporativeHeatLoss == nullptr)
    return SEScalar::dNaN();
  return m_EvaporativeHeatLoss->GetValue(unit);
}

bool SEEnvironment::HasEvaporativeHeatTranferCoefficient() const
{
  return m_EvaporativeHeatTranferCoefficient == nullptr ? false : m_EvaporativeHeatTranferCoefficient->IsValid();
}
SEScalarHeatConductancePerArea& SEEnvironment::GetEvaporativeHeatTranferCoefficient()
{
  if (m_EvaporativeHeatTranferCoefficient == nullptr)
    m_EvaporativeHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
  return *m_EvaporativeHeatTranferCoefficient;
}
double SEEnvironment::GetEvaporativeHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const
{
  if (m_EvaporativeHeatTranferCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_EvaporativeHeatTranferCoefficient->GetValue(unit);
}

bool SEEnvironment::HasRadiativeHeatLoss() const
{
  return m_RadiativeHeatLoss == nullptr ? false : m_RadiativeHeatLoss->IsValid();
}
SEScalarPower& SEEnvironment::GetRadiativeHeatLoss()
{
  if (m_RadiativeHeatLoss == nullptr)
    m_RadiativeHeatLoss = new SEScalarPower();
  return *m_RadiativeHeatLoss;
}
double SEEnvironment::GetRadiativeHeatLoss(const PowerUnit& unit) const
{
  if (m_RadiativeHeatLoss == nullptr)
    return SEScalar::dNaN();
  return m_RadiativeHeatLoss->GetValue(unit);
}

bool SEEnvironment::HasRadiativeHeatTranferCoefficient() const
{
  return m_RadiativeHeatTranferCoefficient == nullptr ? false : m_RadiativeHeatTranferCoefficient->IsValid();
}
SEScalarHeatConductancePerArea& SEEnvironment::GetRadiativeHeatTranferCoefficient()
{
  if (m_RadiativeHeatTranferCoefficient == nullptr)
    m_RadiativeHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
  return *m_RadiativeHeatTranferCoefficient;
}
double SEEnvironment::GetRadiativeHeatTranferCoefficient(const HeatConductancePerAreaUnit& unit) const
{
  if (m_RadiativeHeatTranferCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_RadiativeHeatTranferCoefficient->GetValue(unit);
}

bool SEEnvironment::HasRespirationHeatLoss() const
{
  return m_RespirationHeatLoss == nullptr ? false : m_RespirationHeatLoss->IsValid();
}
SEScalarPower& SEEnvironment::GetRespirationHeatLoss()
{
  if (m_RespirationHeatLoss == nullptr)
    m_RespirationHeatLoss = new SEScalarPower();
  return *m_RespirationHeatLoss;
}
double SEEnvironment::GetRespirationHeatLoss(const PowerUnit& unit) const
{
  if (m_RespirationHeatLoss == nullptr)
    return SEScalar::dNaN();
  return m_RespirationHeatLoss->GetValue(unit);
}

bool SEEnvironment::HasSkinHeatLoss() const
{
  return m_SkinHeatLoss == nullptr ? false : m_SkinHeatLoss->IsValid();
}
SEScalarPower& SEEnvironment::GetSkinHeatLoss()
{
  if (m_SkinHeatLoss == nullptr)
    m_SkinHeatLoss = new SEScalarPower();
  return *m_SkinHeatLoss;
}
double SEEnvironment::GetSkinHeatLoss(const PowerUnit& unit) const
{
  if (m_SkinHeatLoss == nullptr)
    return SEScalar::dNaN();
  return m_SkinHeatLoss->GetValue(unit);
}
