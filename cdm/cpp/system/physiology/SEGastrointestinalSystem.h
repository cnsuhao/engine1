/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "system/SESystem.h"
#include "patient/SENutrition.h"

class CDM_DECL SEGastrointestinalSystem : public SESystem
{
public:

  SEGastrointestinalSystem(Logger* logger);
  virtual ~SEGastrointestinalSystem();

  virtual void Clear();// Deletes all members

  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst);
  static cdm::GastrointestinalSystemData* Unload(const SEGastrointestinalSystem& src);
protected:
  static void Serialize(const cdm::GastrointestinalSystemData& src, SEGastrointestinalSystem& dst);
  static void Serialize(const SEGastrointestinalSystem& src, cdm::GastrointestinalSystemData& dst);
  
public:
  virtual bool HasChymeAbsorbtionRate() const;
  virtual SEScalarVolumePerTime& GetChymeAbsorbtionRate();
  virtual double GetChymeAbsorbtionRate(const VolumePerTimeUnit& unit) const;

  virtual bool HasStomachContents() const;
  virtual SENutrition& GetStomachContents();
  virtual const SENutrition* GetStomachContents() const;
  virtual void RemoveStomachContents();

protected:

  SEScalarVolumePerTime* m_ChymeAbsorbtionRate;
  SENutrition* m_StomachContents;
};
