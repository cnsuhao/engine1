/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEApnea : public SEPatientAction
{
public:

  SEApnea();
  virtual ~SEApnea();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ApneaData& src, SEApnea& dst);
  static cdm::ApneaData* Unload(const SEApnea& src);
protected:
  static void Serialize(const cdm::ApneaData& src, SEApnea& dst);
  static void Serialize(const SEApnea& src, cdm::ApneaData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_Severity;
};