/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/environment/SEEnvironmentalConditions.h"
#include "SEEnvironmentCondition.h"

class CDM_DECL SEInitialEnvironmentConditions : public SEEnvironmentCondition
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
