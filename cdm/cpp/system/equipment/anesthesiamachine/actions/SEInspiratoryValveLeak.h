/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEInspiratoryValveLeak : public SEAnesthesiaMachineAction
{
public:

  SEInspiratoryValveLeak();
  virtual ~SEInspiratoryValveLeak();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::InspiratoryValveLeakData& src, SEInspiratoryValveLeak& dst);
  static cdm::InspiratoryValveLeakData* Unload(const SEInspiratoryValveLeak& src);
protected:
  static void Serialize(const cdm::InspiratoryValveLeakData& src, SEInspiratoryValveLeak& dst);
  static void Serialize(const SEInspiratoryValveLeak& src, cdm::InspiratoryValveLeakData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  