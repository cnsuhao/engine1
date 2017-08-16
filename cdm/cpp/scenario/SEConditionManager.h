/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

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

class CDM_DECL SEConditionManager : public Loggable
{
public:

  SEConditionManager(SESubstanceManager&);
  ~SEConditionManager();

  void Clear();

  static void Load(const cdm::ConditionListData& src, SEConditionManager& dst);
  static cdm::ConditionListData* Unload(const SEConditionManager& src);
protected:
  static void Serialize(const cdm::ConditionListData& src, SEConditionManager& dst);
  static void Serialize(const SEConditionManager& src, cdm::ConditionListData& dst);

public:

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
  const cdm::ConditionListData& GetConditionList() { return m_Conditions; }// I don't really have anything that does that yet...

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