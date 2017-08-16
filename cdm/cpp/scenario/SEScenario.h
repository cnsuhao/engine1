/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEAction.h"
#include "scenario/SECondition.h"
#include "scenario/SEDataRequestManager.h"
#include "scenario/SEScenarioInitialParameters.h"
#include "substance/SESubstanceManager.h"

class CDM_DECL SEScenario : public Loggable
{
public:

  SEScenario(SESubstanceManager& subMgr);
  virtual ~SEScenario();
  
  virtual void Clear(); //clear memory

  bool LoadFile(const std::string& scenarioFile);

  static void Load(const cdm::ScenarioData& src, SEScenario& dst);
  static cdm::ScenarioData* Unload(const SEScenario& src);
protected:
  static void Serialize(const cdm::ScenarioData& src, SEScenario& dst);
  static void Serialize(const SEScenario& src, cdm::ScenarioData& dst);

public:
  bool IsValid() const;

  virtual std::string GetName() const;
  virtual void SetName(const std::string& name);
  virtual bool HasName() const;
  virtual void InvalidateName();

  virtual std::string GetDescription() const;
  virtual void SetDescription(const std::string& desc);
  virtual bool HasDescription() const;
  virtual void InvalidateDescription();

  virtual std::string GetEngineStateFile() const;
  virtual void SetEngineStateFile(const std::string& file);
  virtual bool HasEngineStateFile() const;
  virtual void InvalidateEngineStateFile();
  
  virtual SEScenarioInitialParameters& GetInitialParameters();
  virtual const SEScenarioInitialParameters* GetInitialParameters() const;
  virtual bool HasInitialParameters() const;
  virtual void InvalidateInitialParameters();

  virtual void AddAction(const SEAction& action);
  virtual const std::vector<SEAction*>& GetActions() const;

  virtual SEDataRequestManager& GetDataRequestManager() { return m_DataRequestMgr; }
  virtual const SEDataRequestManager& GetDataRequestManager() const { return m_DataRequestMgr; }

protected:
  SESubstanceManager&                         m_SubMgr;
  std::string                                 m_Name;
  std::string                                 m_Description;
  std::string                                 m_EngineStateFile;
  SEScenarioInitialParameters*                m_InitialParameters;
  SEDataRequestManager                        m_DataRequestMgr;
  std::vector<SEAction*>                      m_Actions;

};