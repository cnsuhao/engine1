/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "system/SESystem.h"
#include "system/physiology/SEPupillaryResponse.h"

class CDM_DECL SEDrugSystem : public SESystem
{
public:
  SEDrugSystem(Logger* logger);
  virtual ~SEDrugSystem();

  virtual void Clear();// Deletes all members
  
  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::DrugSystemData& src, SEDrugSystem& dst);
  static cdm::DrugSystemData* Unload(const SEDrugSystem& src);
protected:
  static void Serialize(const cdm::DrugSystemData& src, SEDrugSystem& dst);
  static void Serialize(const SEDrugSystem& src, cdm::DrugSystemData& dst);

public:

  virtual bool HasBronchodilationLevel() const;
  virtual SEScalarNegative1To1& GetBronchodilationLevel();
  virtual double GetBronchodilationLevel() const;

  virtual bool HasHeartRateChange() const;
  virtual SEScalarFrequency& GetHeartRateChange();
  virtual double GetHeartRateChange(const FrequencyUnit& unit) const;

  virtual bool HasMeanBloodPressureChange() const;
  virtual SEScalarPressure& GetMeanBloodPressureChange();
  virtual double GetMeanBloodPressureChange(const PressureUnit& unit) const;

  virtual bool HasNeuromuscularBlockLevel() const;
  virtual SEScalar0To1& GetNeuromuscularBlockLevel();
  virtual double GetNeuromuscularBlockLevel() const;

  virtual bool HasPulsePressureChange() const;
  virtual SEScalarPressure& GetPulsePressureChange();
  virtual double GetPulsePressureChange(const PressureUnit& unit) const;

  virtual bool HasPupillaryResponse() const;
  virtual SEPupillaryResponse& GetPupillaryResponse();
  virtual const SEPupillaryResponse* GetPupillaryResponse() const;
  virtual void RemovePupillaryResponse();

  virtual bool HasRespirationRateChange() const;
  virtual SEScalarFrequency& GetRespirationRateChange();
  virtual double GetRespirationRateChange(const FrequencyUnit& unit) const;

  virtual bool HasSedationLevel() const;
  virtual SEScalar0To1& GetSedationLevel();
  virtual double GetSedationLevel() const;

  virtual bool HasTidalVolumeChange() const;
  virtual SEScalarVolume& GetTidalVolumeChange();
  virtual double GetTidalVolumeChange(const VolumeUnit& unit) const;

  virtual bool HasTubularPermeabilityChange() const;
  virtual SEScalarNegative1To1& GetTubularPermeabilityChange();
  virtual double GetTubularPermeabilityChange() const;

protected:

  SEScalarNegative1To1*  m_BronchodilationLevel;
  SEScalarFrequency*     m_HeartRateChange;
  SEScalarPressure*      m_MeanBloodPressureChange;
  SEScalar0To1*          m_NeuromuscularBlockLevel;
  SEScalarPressure*      m_PulsePressureChange;
  SEPupillaryResponse*   m_PupillaryResponse;
  SEScalarFrequency*     m_RespirationRateChange;
  SEScalar0To1*          m_SedationLevel;
  SEScalarVolume*        m_TidalVolumeChange;
  SEScalarNegative1To1*  m_TubularPermeabilityChange;
};