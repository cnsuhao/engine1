/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEMaskLeak : public SEAnesthesiaMachineAction
{
public:

  SEMaskLeak();
  virtual ~SEMaskLeak();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::MaskLeakData& src, SEMaskLeak& dst);
  static cdm::MaskLeakData* Unload(const SEMaskLeak& src);
protected:
  static void Serialize(const cdm::MaskLeakData& src, SEMaskLeak& dst);
  static void Serialize(const SEMaskLeak& src, cdm::MaskLeakData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  