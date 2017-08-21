/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEBronchoconstriction : public SEPatientAction
{
public:

  SEBronchoconstriction();
  virtual ~SEBronchoconstriction();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::BronchoconstrictionData& src, SEBronchoconstriction& dst);
  static cdm::BronchoconstrictionData* Unload(const SEBronchoconstriction& src);
protected:
  static void Serialize(const cdm::BronchoconstrictionData& src, SEBronchoconstriction& dst);
  static void Serialize(const SEBronchoconstriction& src, cdm::BronchoconstrictionData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_Severity;
};      