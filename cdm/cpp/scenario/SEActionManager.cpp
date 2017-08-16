/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "scenario/SEActionManager.h"

SEActionManager::SEActionManager(SESubstanceManager& substances) : Loggable(substances.GetLogger()), 
                                                                   m_PatientActions(substances),
                                                                   m_AnesthesiaMachineActions(substances),
                                                                   m_EnvironmentActions(substances),
                                                                   m_InhalerActions(substances),
                                                                   m_Substances(substances)
{
  
}

SEActionManager::~SEActionManager()
{
  Clear();
}

void SEActionManager::Clear()
{
  m_PatientActions.Clear();
  m_AnesthesiaMachineActions.Clear();
  m_EnvironmentActions.Clear();
  m_InhalerActions.Clear();
  m_ProcessedActions.Clear();// amb Does this delete?
}

void SEActionManager::Load(const cdm::ActionListData& src, SEActionManager& dst)
{
  SEActionManager::Serialize(src, dst);
}
void SEActionManager::Serialize(const cdm::ActionListData& src, SEActionManager& dst)
{
  for (int i = 0; i < src.anyaction_size(); i++)
  {
    SEAction* a = SEAction::Load(src.anyaction()[i], dst.m_Substances);
    dst.ProcessAction(*a);
    delete a;
  }
}

cdm::ActionListData* SEActionManager::Unload(const SEActionManager& src)
{
  cdm::ActionListData* dst = new cdm::ActionListData();
  SEActionManager::Serialize(src, *dst);
  return dst;
}
void SEActionManager::Serialize(const SEActionManager& src, cdm::ActionListData& dst)
{
  SEPatientActionCollection::Serialize(src.m_PatientActions, dst);
  SEEnvironmentActionCollection::Serialize(src.m_EnvironmentActions, dst);
  SEAnesthesiaMachineActionCollection::Serialize(src.m_AnesthesiaMachineActions, dst);
  SEInhalerActionCollection::Serialize(src.m_InhalerActions, dst);
}

bool SEActionManager::ProcessAction(const SEAction& action)
{
  if (!action.IsValid())
  { 
    m_ss << "Ignoring invalid action : " << action;
    Error(m_ss);
    return false;
  }
  bool bRet;
  cdm::AnyActionData* aData = m_ProcessedActions.add_anyaction();
  
  const SEPatientAction* pa = dynamic_cast<const SEPatientAction*>(&action);
  if (pa != nullptr)
    bRet = m_PatientActions.ProcessAction(*pa,*aData->mutable_patientaction());

  const SEEnvironmentAction* ea = dynamic_cast<const SEEnvironmentAction*>(&action);
  if (ea != nullptr)
    bRet = m_EnvironmentActions.ProcessAction(*ea, *aData->mutable_environmentaction());

  const SEAnesthesiaMachineAction* aa = dynamic_cast<const SEAnesthesiaMachineAction*>(&action);
  if (aa != nullptr)
    bRet = m_AnesthesiaMachineActions.ProcessAction(*aa, *aData->mutable_anesthesiamachineaction());

  const SEInhalerAction* ia = dynamic_cast<const SEInhalerAction*>(&action);
  if (ia != nullptr)
    bRet = m_InhalerActions.ProcessAction(*ia, *aData->mutable_inhaleraction());

  if (!bRet)
  {
    m_ss << "Not including action due to processing error : " << action;
    Error(m_ss);
    m_ProcessedActions.mutable_anyaction()->RemoveLast();// amb does this delete?
  }
  return bRet;
}


