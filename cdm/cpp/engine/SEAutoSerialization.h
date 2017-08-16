/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

CDM_BIND_DECL(AutoSerializationData)
#include "properties/SEScalarTime.h"

class CDM_DECL SEAutoSerialization : public Loggable
{
public:
  SEAutoSerialization(Logger* logger);
  virtual ~SEAutoSerialization();

  virtual void Clear();
  virtual bool IsValid() const;

  static void Load(const cdm::AutoSerializationData& src, SEAutoSerialization& dst);
  static cdm::AutoSerializationData* Unload(const SEAutoSerialization& src);
protected:
  static void Serialize(const cdm::AutoSerializationData& src, SEAutoSerialization& dst);
  static void Serialize(const SEAutoSerialization& src, cdm::AutoSerializationData& dst);

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
