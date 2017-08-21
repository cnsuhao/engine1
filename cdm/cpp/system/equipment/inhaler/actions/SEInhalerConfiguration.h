/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once

#include "SEInhalerAction.h"
class SEInhaler;
class SESubstanceManager;

class CDM_DECL SEInhalerConfiguration : public SEInhalerAction
{
public:

  SEInhalerConfiguration(SESubstanceManager& substances);
  virtual ~SEInhalerConfiguration();

  virtual void Clear();
  
  virtual bool IsValid() const;

  static void Load(const cdm::InhalerConfigurationData& src, SEInhalerConfiguration& dst);
  static cdm::InhalerConfigurationData* Unload(const SEInhalerConfiguration& src);
protected:
  static void Serialize(const cdm::InhalerConfigurationData& src, SEInhalerConfiguration& dst);
  static void Serialize(const SEInhalerConfiguration& src, cdm::InhalerConfigurationData& dst);

public:

  bool HasConfiguration() const;
  SEInhaler& GetConfiguration();
  const SEInhaler* GetConfiguration() const;

  virtual std::string GetConfigurationFile() const;
  virtual void SetConfigurationFile(const std::string& fileName);
  virtual bool HasConfigurationFile() const;
  virtual void InvalidateConfigurationFile();

  virtual void ToString(std::ostream &str) const;

protected:
  SESubstanceManager&  m_Substances;

  std::string m_ConfigurationFile;
  SEInhaler*  m_Configuration;
};
