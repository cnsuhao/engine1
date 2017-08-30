/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"
CDM_BIND_DECL(ChronicAnemiaData)

class CDM_DECL SEChronicAnemia : public SEPatientCondition
{
public:

  SEChronicAnemia();
  virtual ~SEChronicAnemia();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicAnemiaData& src, SEChronicAnemia& dst);
  static cdm::ChronicAnemiaData* Unload(const SEChronicAnemia& src);
protected:
  static void Serialize(const cdm::ChronicAnemiaData& src, SEChronicAnemia& dst);
  static void Serialize(const SEChronicAnemia& src, cdm::ChronicAnemiaData& dst);

public:
  virtual std::string GetName() const{ return "ChronicAnemia"; }

  virtual bool HasReductionFactor() const;
  virtual SEScalar0To1& GetReductionFactor();

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalar0To1*           m_ReductionFactor;
};      