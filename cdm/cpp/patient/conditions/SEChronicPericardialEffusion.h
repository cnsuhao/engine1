/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"

class CDM_DECL SEChronicPericardialEffusion : public SEPatientCondition
{
public:

  SEChronicPericardialEffusion();
  virtual ~SEChronicPericardialEffusion();

  virtual void Clear();

  virtual bool IsValid() const;

  static void Load(const cdm::ChronicPericardialEffusionData& src, SEChronicPericardialEffusion& dst);
  static cdm::ChronicPericardialEffusionData* Unload(const SEChronicPericardialEffusion& src);
protected:
  static void Serialize(const cdm::ChronicPericardialEffusionData& src, SEChronicPericardialEffusion& dst);
  static void Serialize(const SEChronicPericardialEffusion& src, cdm::ChronicPericardialEffusionData& dst);

public:
  virtual std::string GetName() const { return "ChronicPericardialEffusion"; }

  virtual bool HasAccumulatedVolume() const;
  virtual SEScalarVolume& GetAccumulatedVolume();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalarVolume* m_AccumulatedVolume;
};