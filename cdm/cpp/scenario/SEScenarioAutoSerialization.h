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
#include "properties/SEScalarTime.h"

class DLL_DECL SEScenarioAutoSerialization : public Loggable
{
public:
  SEScenarioAutoSerialization(Logger* logger);
  virtual ~SEScenarioAutoSerialization();

  virtual void Clear();
  virtual bool IsValid() const;

  static void Load(const cdm::ScenarioData_AutoSerializationData& src, SEScenarioAutoSerialization& dst);
  static cdm::ScenarioData_AutoSerializationData* Unload(const SEScenarioAutoSerialization& src);
protected:
  static void Serialize(const cdm::ScenarioData_AutoSerializationData& src, SEScenarioAutoSerialization& dst);
  static void Serialize(const SEScenarioAutoSerialization& src, cdm::ScenarioData_AutoSerializationData& dst);

public:

  virtual bool HasPeriod() const;
  virtual SEScalarTime& GetPeriod();
  virtual double GetPeriod(const TimeUnit& unit) const;

  virtual cdm::eSwitch GetPeriodTimeStamps() const;
  virtual void SetPeriodTimeStamps(cdm::eSwitch v);

  virtual cdm::eSwitch GetAfterActions() const;
  virtual void SetAfterActions(cdm::eSwitch v);

  virtual cdm::eSwitch GetReloadState() const;
  virtual void SetReloadState(cdm::eSwitch v);

  virtual bool HasDirectory() const;
  virtual std::string GetDirectory() const;
  virtual void SetDirectory(const std::string& dir);
  virtual void InvalidateDirectory();

  virtual bool HasFileName() const;
  virtual std::string GetFileName() const;
  virtual void SetFileName(const std::string& dir);
  virtual void InvalidateFileName();


protected:

  SEScalarTime*         m_Period;
  cdm::eSwitch          m_PeriodTimeStamps;
  cdm::eSwitch          m_AfterActions;
  cdm::eSwitch          m_ReloadState;
  std::string           m_Directory;
  std::string           m_FileName;
};
