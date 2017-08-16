/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"

class CDM_DECL SEChronicRenalStenosis : public SEPatientCondition
{
public:

  SEChronicRenalStenosis();
  virtual ~SEChronicRenalStenosis();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicRenalStenosisData& src, SEChronicRenalStenosis& dst);
  static cdm::ChronicRenalStenosisData* Unload(const SEChronicRenalStenosis& src);
protected:
  static void Serialize(const cdm::ChronicRenalStenosisData& src, SEChronicRenalStenosis& dst);
  static void Serialize(const SEChronicRenalStenosis& src, cdm::ChronicRenalStenosisData& dst);

public:
  virtual std::string GetName() const { return "ChronicRenalStenosis"; }

  virtual bool HasLeftKidneySeverity() const;
  virtual SEScalar0To1& GetLeftKidneySeverity();

  virtual bool HasRightKidneySeverity() const;
  virtual SEScalar0To1& GetRightKidneySeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*           m_LeftKidneySeverity;
  SEScalar0To1*           m_RightKidneySeverity;
};