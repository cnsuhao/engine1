/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SESodaLimeFailure : public SEAnesthesiaMachineAction
{
public:

  SESodaLimeFailure();
  virtual ~SESodaLimeFailure();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::SodaLimeFailureData& src, SESodaLimeFailure& dst);
  static cdm::SodaLimeFailureData* Unload(const SESodaLimeFailure& src);
protected:
  static void Serialize(const cdm::SodaLimeFailureData& src, SESodaLimeFailure& dst);
  static void Serialize(const SESodaLimeFailure& src, cdm::SodaLimeFailureData& dst);

public:
  
  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  