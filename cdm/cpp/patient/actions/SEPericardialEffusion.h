/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEPericardialEffusion : public SEPatientAction
{
public:

  SEPericardialEffusion();
  virtual ~SEPericardialEffusion();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::PericardialEffusionData& src, SEPericardialEffusion& dst);
  static cdm::PericardialEffusionData* Unload(const SEPericardialEffusion& src);
protected:
  static void Serialize(const cdm::PericardialEffusionData& src, SEPericardialEffusion& dst);
  static void Serialize(const SEPericardialEffusion& src, cdm::PericardialEffusionData& dst);

public:

  virtual bool HasEffusionRate() const;
  virtual SEScalarVolumePerTime& GetEffusionRate();
  
  virtual void ToString(std::ostream &str) const;

protected:
  SEScalarVolumePerTime* m_EffusionRate;
};      