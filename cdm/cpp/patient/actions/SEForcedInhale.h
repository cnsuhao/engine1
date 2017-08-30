/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEConsciousRespirationCommand.h"
CDM_BIND_DECL(ConsciousRespirationData_ForcedInhaleData)

class CDM_DECL SEForcedInhale : public SEConsciousRespirationCommand
{
  friend class SEConsciousRespiration;
  SEForcedInhale();
public:

  virtual ~SEForcedInhale();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData_ForcedInhaleData& src, SEForcedInhale& dst);
  static cdm::ConsciousRespirationData_ForcedInhaleData* Unload(const SEForcedInhale& src);
protected:
  static void Serialize(const cdm::ConsciousRespirationData_ForcedInhaleData& src, SEForcedInhale& dst);
  static void Serialize(const SEForcedInhale& src, cdm::ConsciousRespirationData_ForcedInhaleData& dst);

public:

  virtual bool HasInspiratoryCapacityFraction() const;
  virtual SEScalar0To1& GetInspiratoryCapacityFraction();

  virtual bool HasPeriod() const;
  virtual SEScalarTime& GetPeriod();

  virtual void ToString(std::ostream &str) const;
protected:
  SEScalar0To1* m_InspiratoryCapacityFraction;
  SEScalarTime*     m_Period;
};