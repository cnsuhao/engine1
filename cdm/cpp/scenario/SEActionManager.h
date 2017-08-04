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
class SESubstanceManager;
class SEAction;
#include "scenario/SEPatientActionCollection.h"
#include "scenario/SEAnesthesiaMachineActionCollection.h"
#include "scenario/SEEnvironmentActionCollection.h"
#include "scenario/SEInhalerActionCollection.h"
#include "bind/cdm/Scenario.pb.h"

class DLL_DECL SEActionManager : public Loggable
{
public:

  SEActionManager(SESubstanceManager&);
  ~SEActionManager();

  void Clear();

  bool ProcessAction(const SEAction& action);// Will make a copy

  SEPatientActionCollection&           GetPatientActions()           { return m_PatientActions; }
  SEEnvironmentActionCollection&       GetEnvironmentActions()       { return m_EnvironmentActions; }
  SEAnesthesiaMachineActionCollection& GetAnesthesiaMachineActions() { return m_AnesthesiaMachineActions; }
  SEInhalerActionCollection&           GetInhalerActions()           { return m_InhalerActions; }

  // This is here in case you want to take all the actions from an engine and write them out so you can reproduce the same engine state later
  const cdm::ActionListData& GetActionList() { return m_ProcessedActions; }// I don't really have anything that does that yet...

protected:

  SESubstanceManager&                 m_Substances;
  SEPatientActionCollection           m_PatientActions;
  SEEnvironmentActionCollection       m_EnvironmentActions;
  SEAnesthesiaMachineActionCollection m_AnesthesiaMachineActions;
  SEInhalerActionCollection           m_InhalerActions;

  cdm::ActionListData                 m_ProcessedActions;
  
  std::stringstream m_ss;
};