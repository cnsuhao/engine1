/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SESubstanceAdministration.h"
CDM_BIND_DECL(SubstanceInfusionData)
class SESubstance;

class CDM_DECL SESubstanceInfusion : public SESubstanceAdministration
{
public:

  SESubstanceInfusion(const SESubstance& substance);
  virtual ~SESubstanceInfusion();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::SubstanceInfusionData& src, SESubstanceInfusion& dst);
  static cdm::SubstanceInfusionData* Unload(const SESubstanceInfusion& src);
protected:
  static void Serialize(const cdm::SubstanceInfusionData& src, SESubstanceInfusion& dst);
  static void Serialize(const SESubstanceInfusion& src, cdm::SubstanceInfusionData& dst);

public:

  virtual bool HasConcentration() const;
  virtual SEScalarMassPerVolume& GetConcentration();

  virtual bool HasRate() const;
  virtual SEScalarVolumePerTime& GetRate();  

  virtual SESubstance& GetSubstance() const;

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarMassPerVolume*                  m_Concentration;
  SEScalarVolumePerTime*                  m_Rate;
  const SESubstance&                      m_Substance;
};