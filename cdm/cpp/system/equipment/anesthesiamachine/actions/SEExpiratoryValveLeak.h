/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEExpiratoryValveLeak : public SEAnesthesiaMachineAction
{
public:

  SEExpiratoryValveLeak();
  virtual ~SEExpiratoryValveLeak();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ExpiratoryValveLeakData& src, SEExpiratoryValveLeak& dst);
  static cdm::ExpiratoryValveLeakData* Unload(const SEExpiratoryValveLeak& src);
protected:
  static void Serialize(const cdm::ExpiratoryValveLeakData& src, SEExpiratoryValveLeak& dst);
  static void Serialize(const SEExpiratoryValveLeak& src, cdm::ExpiratoryValveLeakData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  