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


