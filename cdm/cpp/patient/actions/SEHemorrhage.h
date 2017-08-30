/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"
CDM_BIND_DECL(HemorrhageData)

class CDM_DECL SEHemorrhage : public SEPatientAction
{
public:

  SEHemorrhage();
  virtual ~SEHemorrhage();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::HemorrhageData& src, SEHemorrhage& dst);
  static cdm::HemorrhageData* Unload(const SEHemorrhage& src);
protected:
  static void Serialize(const cdm::HemorrhageData& src, SEHemorrhage& dst);
  static void Serialize(const SEHemorrhage& src, cdm::HemorrhageData& dst);

public:

  virtual std::string GetCompartment() const;
  virtual void SetCompartment(const std::string& name);
  virtual bool HasCompartment() const;
  virtual void InvalidateCompartment();

  virtual bool HasRate() const;
  virtual SEScalarVolumePerTime& GetRate();  

  virtual void ToString(std::ostream &str) const;

protected:
  std::string             m_Compartment;
  SEScalarVolumePerTime*  m_Rate;
  
};    