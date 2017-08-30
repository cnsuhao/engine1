/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/assessments/SEPatientAssessment.h"
CDM_BIND_DECL(CompleteBloodCountData)
class SEBloodChemistrySystem;

class CDM_DECL SECompleteBloodCount : public SEPatientAssessment
{
public:

  SECompleteBloodCount(Logger* logger);
  virtual ~SECompleteBloodCount();

  virtual void Clear(); //clear memory

  virtual std::string Save() const;
  virtual void SaveFile(const std::string& filename) const;

  static void Load(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst);
  static cdm::CompleteBloodCountData* Unload(const SECompleteBloodCount& src);
protected:
  static void Serialize(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst);
  static void Serialize(const SECompleteBloodCount& src, cdm::CompleteBloodCountData& dst);

public:
  
  virtual bool HasHematocrit() const;
  virtual SEScalar0To1& GetHematocrit(); 
  virtual double GetHematocrit() const;

  virtual bool HasHemoglobin() const;
  virtual SEScalarMassPerVolume& GetHemoglobin();
  virtual double GetHemoglobin(const MassPerVolumeUnit& unit) const;

  virtual bool HasPlateletCount() const;
  virtual SEScalarAmountPerVolume& GetPlateletCount();
  virtual double GetPlateletCount(const AmountPerVolumeUnit& unit) const;

  virtual bool HasMeanCorpuscularHemoglobin() const;
  virtual SEScalarMassPerAmount& GetMeanCorpuscularHemoglobin();
  virtual double GetMeanCorpuscularHemoglobin(const MassPerAmountUnit& unit) const;

  virtual bool HasMeanCorpuscularHemoglobinConcentration() const;
  virtual SEScalarMassPerVolume& GetMeanCorpuscularHemoglobinConcentration();
  virtual double GetMeanCorpuscularHemoglobinConcentration(const MassPerVolumeUnit& unit) const;

  virtual bool HasMeanCorpuscularVolume() const;
  virtual SEScalarVolume& GetMeanCorpuscularVolume();
  virtual double GetMeanCorpuscularVolume(const VolumeUnit& unit) const;
  
  virtual bool HasRedBloodCellCount() const;
  virtual SEScalarAmountPerVolume& GetRedBloodCellCount();
  virtual double GetRedBloodCellCount(const AmountPerVolumeUnit& unit) const;

  virtual bool HasWhiteBloodCellCount() const;
  virtual SEScalarAmountPerVolume& GetWhiteBloodCellCount();
  virtual double GetWhiteBloodCellCount(const AmountPerVolumeUnit& unit) const;

protected:

  SEScalar0To1*               m_Hematocrit;
  SEScalarMassPerVolume*      m_Hemoglobin;
  SEScalarAmountPerVolume*    m_PlateletCount;
  SEScalarMassPerAmount*      m_MeanCorpuscularHemoglobin;
  SEScalarMassPerVolume*      m_MeanCorpuscularHemoglobinConcentration;
  SEScalarVolume*             m_MeanCorpuscularVolume;
  SEScalarAmountPerVolume*    m_RedBloodCellCount;
  SEScalarAmountPerVolume*    m_WhiteBloodCellCount;

};  