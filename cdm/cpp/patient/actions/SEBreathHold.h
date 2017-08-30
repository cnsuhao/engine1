/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEConsciousRespirationCommand.h"
CDM_BIND_DECL(ConsciousRespirationData_BreathHoldData)

class CDM_DECL SEBreathHold : public SEConsciousRespirationCommand
{
  friend class SEConsciousRespiration;
  SEBreathHold();
public:

  virtual ~SEBreathHold();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst);
  static cdm::ConsciousRespirationData_BreathHoldData* Unload(const SEBreathHold& src);
protected:
  static void Serialize(const cdm::ConsciousRespirationData_BreathHoldData& src, SEBreathHold& dst);
  static void Serialize(const SEBreathHold& src, cdm::ConsciousRespirationData_BreathHoldData& dst);

public:

  virtual bool HasPeriod() const;
  virtual SEScalarTime& GetPeriod();

  virtual void ToString(std::ostream &str) const;
protected:
  SEScalarTime*     m_Period;
};  