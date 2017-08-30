/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"
CDM_BIND_DECL(ChronicObstructivePulmonaryDiseaseData)

class CDM_DECL SEChronicObstructivePulmonaryDisease : public SEPatientCondition
{
public:

  SEChronicObstructivePulmonaryDisease();
  virtual ~SEChronicObstructivePulmonaryDisease();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst);
  static cdm::ChronicObstructivePulmonaryDiseaseData* Unload(const SEChronicObstructivePulmonaryDisease& src);
protected:
  static void Serialize(const cdm::ChronicObstructivePulmonaryDiseaseData& src, SEChronicObstructivePulmonaryDisease& dst);
  static void Serialize(const SEChronicObstructivePulmonaryDisease& src, cdm::ChronicObstructivePulmonaryDiseaseData& dst);

public:
  virtual std::string GetName() const { return "ChronicObstructivePulmonaryDisease"; }

  virtual bool HasBronchitisSeverity() const;
  virtual SEScalar0To1& GetBronchitisSeverity();

  virtual bool HasEmphysemaSeverity() const;
  virtual SEScalar0To1& GetEmphysemaSeverity();

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*     m_BronchitisSeverity;
  SEScalar0To1*     m_EmphysemaSeverity;
};
