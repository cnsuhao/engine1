/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/environment/SEEnvironmentalConditions.h"
#include "system/environment/actions/SEEnvironmentAction.h"

class CDM_DECL SEChangeEnvironmentConditions : public SEEnvironmentAction
{
public:

  SEChangeEnvironmentConditions(SESubstanceManager& substances);
  virtual ~SEChangeEnvironmentConditions();

  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::ChangeEnvironmentConditionsData& src, SEChangeEnvironmentConditions& dst);
  static cdm::ChangeEnvironmentConditionsData* Unload(const SEChangeEnvironmentConditions& src);
protected:
  static void Serialize(const cdm::ChangeEnvironmentConditionsData& src, SEChangeEnvironmentConditions& dst);
  static void Serialize(const SEChangeEnvironmentConditions& src, cdm::ChangeEnvironmentConditionsData& dst);

public:
  
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
