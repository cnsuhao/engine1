/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "scenario/SEScenario.h"
#include "PulseConfiguration.h"

/**
* @brief A Pulse specific scenario (i.e. holds a %Pulse configuration object)
*/
class PULSE_DECL PulseScenario : public SEScenario
{
public:

  PulseScenario(SESubstanceManager& subMgr);
  virtual ~PulseScenario();

  virtual void Clear();


  bool LoadFile(const std::string& scenarioFile);
  bool Load(const std::string& str);

  static void Load(const pulse::ScenarioData& src, PulseScenario& dst);
  static pulse::ScenarioData* Unload(const PulseScenario& src);
protected:
  static void Serialize(const pulse::ScenarioData& src, PulseScenario& dst);
  static void Serialize(const PulseScenario& src, pulse::ScenarioData& dst);
  
public:
  virtual PulseConfiguration& GetConfiguration();
  virtual const PulseConfiguration* GetConfiguration() const;
  virtual bool HasConfiguration() const;
  virtual void InvalidateConfiguration();

protected:
  PulseConfiguration*         m_Configuration;
};