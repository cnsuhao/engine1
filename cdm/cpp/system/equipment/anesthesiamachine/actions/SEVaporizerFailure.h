/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEVaporizerFailure : public SEAnesthesiaMachineAction
{
public:

  SEVaporizerFailure();
  virtual ~SEVaporizerFailure();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::VaporizerFailureData& src, SEVaporizerFailure& dst);
  static cdm::VaporizerFailureData* Unload(const SEVaporizerFailure& src);
protected:
  static void Serialize(const cdm::VaporizerFailureData& src, SEVaporizerFailure& dst);
  static void Serialize(const SEVaporizerFailure& src, cdm::VaporizerFailureData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  