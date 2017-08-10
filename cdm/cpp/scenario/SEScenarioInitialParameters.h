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
#include "engine/SEEngineConfiguration.h"
#include "patient/SEPatient.h"
#include "scenario/SECondition.h"
#include "substance/SESubstanceManager.h"

class CDM_DECL SEScenarioInitialParameters : public Loggable
{
  friend class SEScenario;
protected:
  SEScenarioInitialParameters(SESubstanceManager& subMgr);
public:
  virtual ~SEScenarioInitialParameters();
  virtual void Clear(); //clear memory

  static void Load(const cdm::ScenarioData_InitialParametersData& src, SEScenarioInitialParameters& dst);
  static cdm::ScenarioData_InitialParametersData* Unload(const SEScenarioInitialParameters& src);
protected:
  static void Serialize(const cdm::ScenarioData_InitialParametersData& src, SEScenarioInitialParameters& dst);
  static void Serialize(const SEScenarioInitialParameters& src, cdm::ScenarioData_InitialParametersData& dst);

public:

  virtual bool IsValid()const;

  virtual std::string GetPatientFile() const;
  virtual void SetPatientFile(const std::string& patientFile);
  virtual bool HasPatientFile() const;
  virtual void InvalidatePatientFile();

  virtual SEPatient& GetPatient();
  virtual const SEPatient* GetPatient() const;
  virtual void CopyPatient(const SEPatient& patient);
  virtual bool HasPatient() const;
  virtual void InvalidatePatient();

  virtual void CopyCondition(const SECondition& c);
  virtual const std::vector<SECondition*>& GetConditions() const;

protected:
  SESubstanceManager&            m_SubMgr;
  SEPatient*                     m_Patient;
  std::string                    m_PatientFile;
  std::vector<SECondition*>      m_Conditions;
};