/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEAcuteStress : public SEPatientAction
{
public:

  SEAcuteStress();
  virtual ~SEAcuteStress();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::AcuteStressData& src, SEAcuteStress& dst);
  static cdm::AcuteStressData* Unload(const SEAcuteStress& src);
protected:
  static void Serialize(const cdm::AcuteStressData& src, SEAcuteStress& dst);
  static void Serialize(const SEAcuteStress& src, cdm::AcuteStressData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_Severity;
};      