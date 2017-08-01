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

  virtual void Reset(); //reset values
  virtual void Clear(); //clear memory

  static void Load(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst);
  static cdm::CompleteBloodCountData* Unload(const SECompleteBloodCount& src);
protected:
  static void Serialize(const cdm::CompleteBloodCountData& src, SECompleteBloodCount& dst);
  static void Serialize(const SECompleteBloodCount& src, cdm::CompleteBloodCountData& dst);

public:
  
  virtual bool HasHematocrit();
  virtual SEScalar0To1& GetHematocrit(); 

  virtual bool HasHemoglobin();
  virtual SEScalarMassPerVolume& GetHemoglobin();

  virtual bool HasPlateletCount();
  virtual SEScalarAmountPerVolume& GetPlateletCount();

  virtual bool HasMeanCorpuscularHemoglobin();
  virtual SEScalarMassPerAmount& GetMeanCorpuscularHemoglobin();

  virtual bool HasMeanCorpuscularHemoglobinConcentration();
  virtual SEScalarMassPerVolume& GetMeanCorpuscularHemoglobinConcentration();

  virtual bool HasMeanCorpuscularVolume();
  virtual SEScalarVolume& GetMeanCorpuscularVolume();
  
  virtual bool HasRedBloodCellCount();
  virtual SEScalarAmountPerVolume& GetRedBloodCellCount();

  virtual bool HasWhiteBloodCellCount();
  virtual SEScalarAmountPerVolume& GetWhiteBloodCellCount();

protected:

  SEScalar0To1*        m_Hematocrit;
  SEScalarMassPerVolume*        m_Hemoglobin;
  SEScalarAmountPerVolume*      m_PlateletCount;
  SEScalarMassPerAmount*          m_MeanCorpuscularHemoglobin;
  SEScalarMassPerVolume*          m_MeanCorpuscularHemoglobinConcentration;
  SEScalarVolume*                  m_MeanCorpuscularVolume;
  SEScalarAmountPerVolume*    m_RedBloodCellCount;
  SEScalarAmountPerVolume*    m_WhiteBloodCellCount;

};  