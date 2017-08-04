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

#pragma once
#include "bind/cdm/Scenario.pb.h"
#include "substance/SESubstanceManager.h"
//Patient Conditions
#include "patient/conditions/SEChronicAnemia.h"
#include "patient/conditions/SEChronicObstructivePulmonaryDisease.h"
#include "patient/conditions/SEChronicHeartFailure.h"
#include "patient/conditions/SEChronicRenalStenosis.h"
#include "patient/conditions/SEChronicVentricularSystolicDysfunction.h"
#include "patient/conditions/SEConsumeMeal.h"
#include "patient/conditions/SELobarPneumonia.h"
#include "patient/conditions/SEChronicPericardialEffusion.h"
#include "patient/conditions/SEImpairedAlveolarExchange.h"
// Environment Conditions
#include "system/environment/conditions/SEInitialEnvironmentConditions.h"

class DLL_DECL SEConditionManager : public Loggable
{
public:

  SEConditionManager(SESubstanceManager&);
  ~SEConditionManager();

  void Clear();

  bool ProcessCondition(const SECondition& condition);// Will make a copy

  // Not too many conditions, so just have one manager
  // If we start getting alot, I will make patient/environment/equipment condition managers, like the action managers

  // Patient Conditions

  bool HasChronicAnemia() const;
  SEChronicAnemia* GetChronicAnemia() const;

  bool HasChronicObstructivePulmonaryDisease() const;
  SEChronicObstructivePulmonaryDisease* GetChronicObstructivePulmonaryDisease() const;

  bool HasChronicHeartFailure() const;
  bool HasChronicVentricularSystolicDysfunction() const;
  SEChronicVentricularSystolicDysfunction* GetChronicVentricularSystolicDysfunction() const;

  bool HasChronicPericardialEffusion() const;
  SEChronicPericardialEffusion* GetChronicPericardialEffusion() const;

  bool HasChronicRenalStenosis() const;
  SEChronicRenalStenosis* GetChronicRenalStenosis() const;

  bool HasConsumeMeal() const;
  SEConsumeMeal* GetConsumeMeal() const;

  bool HasImpairedAlveolarExchange() const;
  SEImpairedAlveolarExchange* GetImpairedAlveolarExchange() const;

  bool HasLobarPneumonia() const;
  SELobarPneumonia* GetLobarPneumonia() const;

  // Environment Conditions

  bool HasInitialEnvironmentConditions() const;
  SEInitialEnvironmentConditions* GetInitialEnvironmentConditions() const;
  
  // This is here in case you want to take all the conditions from an engine and write them out so you can reproduce the same engine state later
  const cdm::ConditionListData& GetActionList() { return m_Conditions; }// I don't really have anything that does that yet...

protected:

  SESubstanceManager&                      m_Substances;
  SEChronicAnemia*                         m_Anemia;
  SEConsumeMeal*                           m_ConsumeMeal;
  SEChronicObstructivePulmonaryDisease*    m_COPD;
  SEChronicVentricularSystolicDysfunction* m_ChronicVentricularSystolicDysfunction;
  SEImpairedAlveolarExchange*              m_ImpairedAlveolarExchange;
  SEChronicPericardialEffusion*            m_PericardialEffusion;
  SELobarPneumonia*                        m_LobarPneumonia;
  SEChronicRenalStenosis*                  m_RenalStenosis;

  SEInitialEnvironmentConditions*          m_InitialEnvironmentConditions;

  cdm::ConditionListData                   m_Conditions;
  std::stringstream m_ss;
};