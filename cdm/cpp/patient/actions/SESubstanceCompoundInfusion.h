/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SESubstanceAdministration.h"
class SESubstanceCompound;

class CDM_DECL SESubstanceCompoundInfusion : public SESubstanceAdministration
{
public:

  SESubstanceCompoundInfusion(const SESubstanceCompound& compound);
  virtual ~SESubstanceCompoundInfusion();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::SubstanceCompoundInfusionData& src, SESubstanceCompoundInfusion& dst);
  static cdm::SubstanceCompoundInfusionData* Unload(const SESubstanceCompoundInfusion& src);
protected:
  static void Serialize(const cdm::SubstanceCompoundInfusionData& src, SESubstanceCompoundInfusion& dst);
  static void Serialize(const SESubstanceCompoundInfusion& src, cdm::SubstanceCompoundInfusionData& dst);

public:

  virtual bool HasBagVolume() const;
  virtual SEScalarVolume& GetBagVolume();

  virtual bool HasRate() const;
  virtual SEScalarVolumePerTime& GetRate();  

  virtual SESubstanceCompound& GetSubstanceCompound() const;

  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarVolume*                  m_BagVolume;
  SEScalarVolumePerTime*           m_Rate;
  const SESubstanceCompound&       m_Compound;
};