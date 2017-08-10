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
#include "system/physiology/SEPupillaryResponse.h"
#include "bind/cdm/Substance.pb.h"

class CDM_DECL SESubstancePharmacodynamics : Loggable
{
public:

  SESubstancePharmacodynamics(Logger* logger);
  virtual ~SESubstancePharmacodynamics();

  virtual void Clear();
  virtual bool IsValid() const;

  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::SubstanceData_PharmacodynamicsData& src, SESubstancePharmacodynamics& dst);
  static cdm::SubstanceData_PharmacodynamicsData* Unload(const SESubstancePharmacodynamics& src);
protected:
  static void Serialize(const cdm::SubstanceData_PharmacodynamicsData& src, SESubstancePharmacodynamics& dst);
  static void Serialize(const SESubstancePharmacodynamics& src, cdm::SubstanceData_PharmacodynamicsData& dst);

public:
  virtual bool HasBronchodilation() const;
  virtual SEScalar0To1& GetBronchodilation();
  virtual double GetBronchodilation() const;

  virtual bool HasDiastolicPressureModifier() const;
  virtual SEScalar0To1& GetDiastolicPressureModifier();
  virtual double GetDiastolicPressureModifier() const;

  virtual bool HasEC50() const;
  virtual SEScalarMassPerVolume& GetEC50();
  virtual double GetEC50(const MassPerVolumeUnit& unit) const;

  virtual bool HasEMaxShapeParameter() const;
  virtual SEScalar& GetEMaxShapeParameter();
  virtual double GetEMaxShapeParameter() const;

  virtual bool HasHeartRateModifier() const;
  virtual SEScalar0To1& GetHeartRateModifier();
  virtual double GetHeartRateModifier() const;

  virtual bool HasNeuromuscularBlock() const;
  virtual SEScalar0To1& GetNeuromuscularBlock();
  virtual double GetNeuromuscularBlock() const;

  virtual bool HasPupillaryResponse() const;
  virtual SEPupillaryResponse& GetPupillaryResponse();
  virtual const SEPupillaryResponse* GetPupillaryResponse() const;
  virtual void RemovePupillaryResponse();

  virtual bool HasRespirationRateModifier() const;
  virtual SEScalar0To1& GetRespirationRateModifier();
  virtual double GetRespirationRateModifier() const;

  virtual bool HasSedation() const;
  virtual SEScalar0To1& GetSedation();
  virtual double GetSedation() const;

  virtual bool HasSystolicPressureModifier() const;
  virtual SEScalar0To1& GetSystolicPressureModifier();
  virtual double GetSystolicPressureModifier() const;

  virtual bool HasTidalVolumeModifier() const;
  virtual SEScalar0To1& GetTidalVolumeModifier();
  virtual double GetTidalVolumeModifier() const;

  virtual bool HasTubularPermeabilityModifier() const;
  virtual SEScalar0To1& GetTubularPermeabilityModifier();
  virtual double GetTubularPermeabilityModifier() const;

protected:
  virtual void CalculateDerived();

  SEScalar0To1*          m_Bronchodilation;
  SEScalar0To1*          m_DiastolicPressureModifier;
  SEScalarMassPerVolume*     m_EC50;
  SEScalar*                  m_EMaxShapeParameter;
  SEScalar0To1*          m_HeartRateModifier;
  SEScalar0To1*          m_NeuromuscularBlock;
  SEPupillaryResponse*       m_PupillaryResponse;
  SEScalar0To1*          m_RespirationRateModifier;
  SEScalar0To1*          m_Sedation;
  SEScalar0To1*          m_SystolicPressureModifier;
  SEScalar0To1*          m_TidalVolumeModifier;
  SEScalar0To1*          m_TubularPermeabilityModifier;
};