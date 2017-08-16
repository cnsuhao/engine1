/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEConsciousRespirationCommand.h"

class CDM_DECL SEForcedExhale : public SEConsciousRespirationCommand
{
  friend class SEConsciousRespiration;
  SEForcedExhale();
public:

  virtual ~SEForcedExhale();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData_ForcedExhaleData& src, SEForcedExhale& dst);
  static cdm::ConsciousRespirationData_ForcedExhaleData* Unload(const SEForcedExhale& src);
protected:
  static void Serialize(const cdm::ConsciousRespirationData_ForcedExhaleData& src, SEForcedExhale& dst);
  static void Serialize(const SEForcedExhale& src, cdm::ConsciousRespirationData_ForcedExhaleData& dst);

public:

  virtual void ToString(std::ostream &str) const;

  virtual bool HasExpiratoryReserveVolumeFraction() const;
  virtual SEScalar0To1& GetExpiratoryReserveVolumeFraction();

  virtual bool HasPeriod() const;
  virtual SEScalarTime& GetPeriod();
protected:
  SEScalar0To1* m_ExpiratoryReserveVolumeFraction;
  SEScalarTime* m_Period;
};  