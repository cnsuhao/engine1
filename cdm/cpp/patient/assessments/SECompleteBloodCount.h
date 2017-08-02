/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once
#include "patient/assessments/SEPatientAssessment.h"
class SEBloodChemistrySystem;

class DLL_DECL SECompleteBloodCount : public SEPatientAssessment
{
public:

  SECompleteBloodCount(Logger* logger);
  virtual ~SECompleteBloodCount();

  virtual void Clear(); //clear memory

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