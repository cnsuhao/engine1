/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "system/SESystem.h"

class CDM_DECL SEEnergySystem : public SESystem
{
public:

  SEEnergySystem(Logger* logger);
  virtual ~SEEnergySystem();

  virtual void Clear();// Deletes all members
  
  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::EnergySystemData& src, SEEnergySystem& dst);
  static cdm::EnergySystemData* Unload(const SEEnergySystem& src);
protected:
  static void Serialize(const cdm::EnergySystemData& src, SEEnergySystem& dst);
  static void Serialize(const SEEnergySystem& src, cdm::EnergySystemData& dst);

public:

  virtual bool HasAchievedExerciseLevel() const;
  virtual SEScalar0To1& GetAchievedExerciseLevel();
  virtual double GetAchievedExerciseLevel() const;
    
  virtual bool HasCoreTemperature() const;
  virtual SEScalarTemperature& GetCoreTemperature();
  virtual double GetCoreTemperature(const TemperatureUnit& unit) const;

  virtual bool HasCreatinineProductionRate() const;
  virtual SEScalarAmountPerTime& GetCreatinineProductionRate();
  virtual double GetCreatinineProductionRate(const AmountPerTimeUnit& unit) const;

  virtual bool HasExerciseMeanArterialPressureDelta() const;
  virtual SEScalarPressure& GetExerciseMeanArterialPressureDelta();
  virtual double GetExerciseMeanArterialPressureDelta(const PressureUnit& unit) const;

  virtual bool HasFatigueLevel() const;
  virtual SEScalar0To1& GetFatigueLevel();
  virtual double GetFatigueLevel() const;
  
  virtual bool HasKetoneProductionRate() const;
  virtual SEScalarAmountPerTime& GetKetoneProductionRate();
  virtual double GetKetoneProductionRate(const AmountPerTimeUnit& unit) const;

  virtual bool HasLactateProductionRate() const;
  virtual SEScalarAmountPerTime& GetLactateProductionRate();
  virtual double GetLactateProductionRate(const AmountPerTimeUnit& unit) const;

  virtual bool HasSkinTemperature() const;
  virtual SEScalarTemperature& GetSkinTemperature();
  virtual double GetSkinTemperature(const TemperatureUnit& unit) const;

  virtual bool HasSweatRate() const;
  virtual SEScalarMassPerTime& GetSweatRate();
  virtual double GetSweatRate(const MassPerTimeUnit& unit) const;
  
  virtual bool HasTotalMetabolicRate() const;
  virtual SEScalarPower& GetTotalMetabolicRate();
  virtual double GetTotalMetabolicRate(const PowerUnit& unit) const;

  virtual bool HasTotalWorkRateLevel() const;
  virtual SEScalar0To1& GetTotalWorkRateLevel();
  virtual double GetTotalWorkRateLevel() const;

protected:

  SEScalar0To1*           m_AchievedExerciseLevel;
  SEScalarTemperature*    m_CoreTemperature;
  SEScalarAmountPerTime*  m_CreatinineProductionRate;
  SEScalarPressure*       m_ExerciseMeanArterialPressureDelta;
  SEScalar0To1*           m_FatigueLevel;
  SEScalarAmountPerTime*  m_KetoneProductionRate;
  SEScalarAmountPerTime*  m_LactateProductionRate;
  SEScalarTemperature*    m_SkinTemperature;
  SEScalarMassPerTime*    m_SweatRate;
  SEScalarPower*          m_TotalMetabolicRate;
  SEScalar0To1*           m_TotalWorkRateLevel;

};
