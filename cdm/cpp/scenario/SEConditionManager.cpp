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
#include "scenario/SEConditionManager.h"

SEConditionManager::SEConditionManager(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
  m_Anemia = nullptr;
  m_COPD = nullptr;
  m_ChronicVentricularSystolicDysfunction = nullptr;
  m_RenalStenosis = nullptr;
  m_ConsumeMeal = nullptr;
  m_LobarPneumonia = nullptr;
  m_PericardialEffusion = nullptr;
  m_ImpairedAlveolarExchange = nullptr;
  m_InitialEnvironmentConditions = nullptr;
}

SEConditionManager::~SEConditionManager()
{
  Clear();
}

void SEConditionManager::Clear()
{
  SAFE_DELETE(m_Anemia);
  SAFE_DELETE(m_COPD);
  SAFE_DELETE(m_ChronicVentricularSystolicDysfunction);
  SAFE_DELETE(m_RenalStenosis);
  SAFE_DELETE(m_ConsumeMeal);
  SAFE_DELETE(m_LobarPneumonia);
  SAFE_DELETE(m_PericardialEffusion);
  SAFE_DELETE(m_ImpairedAlveolarExchange);
  SAFE_DELETE(m_InitialEnvironmentConditions);
  m_Conditions.Clear(); // amd does this delete?
}

bool SEConditionManager::ProcessCondition(const SECondition& condition)
{
  if (!condition.IsValid())
  {
    m_ss << "Ignoring invalid condition : " << condition;
    Error(m_ss);
    return false;
  }

  cdm::AnyConditionData* cData = m_Conditions.add_anycondition();

  if (dynamic_cast<const SEPatientCondition*>(&condition) != nullptr)
  {

    const SEChronicAnemia* a = dynamic_cast<const SEChronicAnemia*>(&condition);
    if (a != nullptr)
    {
      if (HasChronicAnemia())
      {
        Error("Cannot have multiple Anemia conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_Anemia = new SEChronicAnemia();
      cData->mutable_patientcondition()->set_allocated_chronicanemia(SEChronicAnemia::Unload(*m_Anemia));
      SEChronicAnemia::Load(cData->mutable_patientcondition()->chronicanemia(), *m_Anemia);
      return true;
    }

    const SEChronicObstructivePulmonaryDisease* copd = dynamic_cast<const SEChronicObstructivePulmonaryDisease*>(&condition);
    if (copd != nullptr)
    {
      if (HasChronicObstructivePulmonaryDisease())
      {
        Error("Cannot have multiple COPD conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_COPD = new SEChronicObstructivePulmonaryDisease();
      cData->mutable_patientcondition()->set_allocated_chronicobstructivepulmonarydisease(SEChronicObstructivePulmonaryDisease::Unload(*m_COPD));
      SEChronicObstructivePulmonaryDisease::Load(cData->mutable_patientcondition()->chronicobstructivepulmonarydisease(), *m_COPD);
      return true;
    }

    const SEChronicHeartFailure* h = dynamic_cast<const SEChronicHeartFailure*>(&condition);
    if (h != nullptr)
    {
      if (HasChronicHeartFailure())
      {
        Error("Cannot have multiple Heart Failure conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      const SEChronicVentricularSystolicDysfunction* vsd = dynamic_cast<const SEChronicVentricularSystolicDysfunction*>(&condition);
      if (vsd != nullptr)
      {
        m_ChronicVentricularSystolicDysfunction = new SEChronicVentricularSystolicDysfunction();
        cData->mutable_patientcondition()->set_allocated_chronicventricularsystolicdysfunction(SEChronicVentricularSystolicDysfunction::Unload(*m_ChronicVentricularSystolicDysfunction));
        SEChronicVentricularSystolicDysfunction::Load(cData->mutable_patientcondition()->chronicventricularsystolicdysfunction(), *m_ChronicVentricularSystolicDysfunction);
        return true;
      }
      Error("Unknown Heart Failure condition");
      m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
      return false;
    }

    const SEChronicPericardialEffusion* pe = dynamic_cast<const SEChronicPericardialEffusion*>(&condition);
    if (pe != nullptr)
    {
      if (HasChronicPericardialEffusion())
      {
        Error("Cannot have multiple Pericardial Effusion conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_PericardialEffusion = new SEChronicPericardialEffusion();
      cData->mutable_patientcondition()->set_allocated_chronicpericardialeffusion(SEChronicPericardialEffusion::Unload(*m_PericardialEffusion));
      SEChronicPericardialEffusion::Load(cData->mutable_patientcondition()->chronicpericardialeffusion(), *m_PericardialEffusion);
      return true;
    }

    const SEChronicRenalStenosis* r = dynamic_cast<const SEChronicRenalStenosis*>(&condition);
    if (r != nullptr)
    {
      if (HasChronicRenalStenosis())
      {
        Error("Cannot have multiple Renal Stenosis conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_RenalStenosis = new SEChronicRenalStenosis();
      cData->mutable_patientcondition()->set_allocated_chronicrenalstenosis(SEChronicRenalStenosis::Unload(*m_RenalStenosis));
      SEChronicRenalStenosis::Load(cData->mutable_patientcondition()->chronicrenalstenosis(), *m_RenalStenosis);
      return true;
    }

    const SEConsumeMeal* g = dynamic_cast<const SEConsumeMeal*>(&condition);
    if (g != nullptr)
    {
      if (HasConsumeMeal())
      {
        Error("Cannot have multiple Gut Nutrient conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_ConsumeMeal = new SEConsumeMeal();
      cData->mutable_patientcondition()->set_allocated_consumemeal(SEConsumeMeal::Unload(*m_ConsumeMeal));
      SEConsumeMeal::Load(cData->mutable_patientcondition()->consumemeal(), *m_ConsumeMeal);
      return true;
    }

    const SEImpairedAlveolarExchange* iae = dynamic_cast<const SEImpairedAlveolarExchange*>(&condition);
    if (iae != nullptr)
    {
      if (HasImpairedAlveolarExchange())
      {
        Error("Cannot have multiple Impaired Alveolar Exchange conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_ImpairedAlveolarExchange = new SEImpairedAlveolarExchange();
      cData->mutable_patientcondition()->set_allocated_impairedalveolarexchange(SEImpairedAlveolarExchange::Unload(*m_ImpairedAlveolarExchange));
      SEImpairedAlveolarExchange::Load(cData->mutable_patientcondition()->impairedalveolarexchange(), *m_ImpairedAlveolarExchange);
      return true;
    }

    const SELobarPneumonia* lp = dynamic_cast<const SELobarPneumonia*>(&condition);
    if (lp != nullptr)
    {
      if (HasLobarPneumonia())
      {
        Error("Cannot have multiple Lobar Pneumonia conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_LobarPneumonia = new SELobarPneumonia();
      cData->mutable_patientcondition()->set_allocated_lobarpneumonia(SELobarPneumonia::Unload(*m_LobarPneumonia));
      SELobarPneumonia::Load(cData->mutable_patientcondition()->lobarpneumonia(), *m_LobarPneumonia);
      return true;
    }
  }

  if (dynamic_cast<const SEEnvironmentCondition*>(&condition) != nullptr)
  {
    const SEInitialEnvironmentConditions* ie = dynamic_cast<const SEInitialEnvironmentConditions*>(&condition);
    if (ie != nullptr)
    {
      if (HasInitialEnvironmentConditions())
      {
        Error("Cannot have multiple Initial Environment conditions");
        m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
        return false;
      }
      m_InitialEnvironmentConditions = new SEInitialEnvironmentConditions(m_Substances);
      cData->mutable_environmentcondition()->set_allocated_initialenvironmentconditions(SEInitialEnvironmentConditions::Unload(*m_InitialEnvironmentConditions));
      SEInitialEnvironmentConditions::Load(cData->mutable_environmentcondition()->initialenvironmentconditions(), *m_InitialEnvironmentConditions);
      return true;
    }
  }
  
  /// \error Unsupported Condition
  Error("Unsupported Condition");
  m_Conditions.mutable_anycondition()->RemoveLast();// amb does this delete?
  return false;
}

bool SEConditionManager::HasChronicAnemia() const
{
  return m_Anemia == nullptr ? false : m_Anemia->IsValid();
}
SEChronicAnemia* SEConditionManager::GetChronicAnemia() const
{
  return m_Anemia;
}

bool SEConditionManager::HasChronicObstructivePulmonaryDisease() const
{
  return m_COPD == nullptr ? false : m_COPD->IsValid();
}
SEChronicObstructivePulmonaryDisease* SEConditionManager::GetChronicObstructivePulmonaryDisease() const
{
  return m_COPD;
}

bool SEConditionManager::HasChronicHeartFailure() const
{
  return m_ChronicVentricularSystolicDysfunction != nullptr;
}
bool SEConditionManager::HasChronicVentricularSystolicDysfunction() const
{
  return m_ChronicVentricularSystolicDysfunction == nullptr ? false : m_ChronicVentricularSystolicDysfunction->IsValid();
}
SEChronicVentricularSystolicDysfunction* SEConditionManager::GetChronicVentricularSystolicDysfunction() const
{
  return m_ChronicVentricularSystolicDysfunction;
}

bool SEConditionManager::HasChronicPericardialEffusion() const
{
  return m_PericardialEffusion == nullptr ? false : m_PericardialEffusion->IsValid();
}
SEChronicPericardialEffusion* SEConditionManager::GetChronicPericardialEffusion() const
{
  return m_PericardialEffusion;
}

bool SEConditionManager::HasChronicRenalStenosis() const
{
  return m_RenalStenosis == nullptr ? false : m_RenalStenosis->IsValid();
}
SEChronicRenalStenosis* SEConditionManager::GetChronicRenalStenosis() const
{
  return m_RenalStenosis;
}

bool SEConditionManager::HasConsumeMeal() const
{
  return m_ConsumeMeal == nullptr ? false : m_ConsumeMeal->IsValid();
}
SEConsumeMeal* SEConditionManager::GetConsumeMeal() const
{
  return m_ConsumeMeal;
}

bool SEConditionManager::HasImpairedAlveolarExchange() const
{
  return m_ImpairedAlveolarExchange == nullptr ? false : m_ImpairedAlveolarExchange->IsValid();
}
SEImpairedAlveolarExchange* SEConditionManager::GetImpairedAlveolarExchange() const
{
  return m_ImpairedAlveolarExchange;
}

bool SEConditionManager::HasLobarPneumonia() const
{
  return m_LobarPneumonia == nullptr ? false : m_LobarPneumonia->IsValid();
}
SELobarPneumonia* SEConditionManager::GetLobarPneumonia() const
{
  return m_LobarPneumonia;
}

bool SEConditionManager::HasInitialEnvironmentConditions() const
{
  return m_InitialEnvironmentConditions == nullptr ? false : m_InitialEnvironmentConditions->IsValid();
}
SEInitialEnvironmentConditions* SEConditionManager::GetInitialEnvironmentConditions() const
{
  return m_InitialEnvironmentConditions;
}