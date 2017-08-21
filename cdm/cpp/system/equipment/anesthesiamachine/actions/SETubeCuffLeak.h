/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SETubeCuffLeak : public SEAnesthesiaMachineAction
{
public:

  SETubeCuffLeak();
  virtual ~SETubeCuffLeak();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::TubeCuffLeakData& src, SETubeCuffLeak& dst);
  static cdm::TubeCuffLeakData* Unload(const SETubeCuffLeak& src);
protected:
  static void Serialize(const cdm::TubeCuffLeakData& src, SETubeCuffLeak& dst);
  static void Serialize(const SETubeCuffLeak& src, cdm::TubeCuffLeakData& dst);

public:
  
  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  