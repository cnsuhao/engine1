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
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"
class SEAnesthesiaMachine;
class SESubstanceManager;

class CDM_DECL SEAnesthesiaMachineConfiguration : public SEAnesthesiaMachineAction
{
public:

  SEAnesthesiaMachineConfiguration(SESubstanceManager& substances);
  virtual ~SEAnesthesiaMachineConfiguration();

  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::AnesthesiaMachineConfigurationData& src, SEAnesthesiaMachineConfiguration& dst);
  static cdm::AnesthesiaMachineConfigurationData* Unload(const SEAnesthesiaMachineConfiguration& src);
protected:
  static void Serialize(const cdm::AnesthesiaMachineConfigurationData& src, SEAnesthesiaMachineConfiguration& dst);
  static void Serialize(const SEAnesthesiaMachineConfiguration& src, cdm::AnesthesiaMachineConfigurationData& dst);

public:

  bool HasConfiguration() const;
  SEAnesthesiaMachine& GetConfiguration();
  const SEAnesthesiaMachine* GetConfiguration() const;

  virtual std::string GetConfigurationFile() const;
  virtual void SetConfigurationFile(const std::string& fileName);
  virtual bool HasConfigurationFile() const;
  virtual void InvalidateConfigurationFile();

  virtual void ToString(std::ostream &str) const;

protected:
  SESubstanceManager&  m_Substances;

  std::string          m_ConfigurationFile;
  SEAnesthesiaMachine* m_Configuration;
};