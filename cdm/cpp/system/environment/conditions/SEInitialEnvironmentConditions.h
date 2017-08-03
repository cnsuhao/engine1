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
#include "system/environment/SEEnvironmentalConditions.h"
#include "SEEnvironmentCondition.h"

class DLL_DECL SEInitialEnvironmentConditions : public SEEnvironmentCondition
{
public:

  SEInitialEnvironmentConditions(SESubstanceManager& substances);
  virtual ~SEInitialEnvironmentConditions();

  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::InitialEnvironmentConditionsData& src, SEInitialEnvironmentConditions& dst);
  static cdm::InitialEnvironmentConditionsData* Unload(const SEInitialEnvironmentConditions& src);
protected:
  static void Serialize(const cdm::InitialEnvironmentConditionsData& src, SEInitialEnvironmentConditions& dst);
  static void Serialize(const SEInitialEnvironmentConditions& src, cdm::InitialEnvironmentConditionsData& dst);

public:
  virtual std::string GetName() const{ return "InitialEnvironment"; }

  virtual bool HasConditions() const;
  virtual SEEnvironmentalConditions& GetConditions();
  virtual const SEEnvironmentalConditions* GetConditions() const;

  virtual std::string GetConditionsFile() const;
  virtual void SetConditionsFile(const std::string& fileName);
  virtual bool HasConditionsFile() const;
  virtual void InvalidateConditionsFile();
  
  virtual void ToString(std::ostream &str) const;

protected:
  SESubstanceManager&  m_Substances;

  std::string                m_ConditionsFile;
  SEEnvironmentalConditions* m_Conditions;
};  
