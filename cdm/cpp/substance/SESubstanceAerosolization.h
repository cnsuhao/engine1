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
#include "bind/cdm/Substance.pb.h"

class CDM_DECL SESubstanceAerosolization : public Loggable
{
public:

  SESubstanceAerosolization(Logger* logger);
  virtual ~SESubstanceAerosolization();

  virtual void Clear();
  virtual bool IsValid() const;

  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::SubstanceData_AerosolizationData& src, SESubstanceAerosolization& dst);
  static cdm::SubstanceData_AerosolizationData* Unload(const SESubstanceAerosolization& src);
protected:
  static void Serialize(const cdm::SubstanceData_AerosolizationData& src, SESubstanceAerosolization& dst);
  static void Serialize(const SESubstanceAerosolization& src, cdm::SubstanceData_AerosolizationData& dst);

public:

  virtual bool HasBronchioleModifier() const;
  virtual SEScalarNegative1To1& GetBronchioleModifier();
  virtual double GetBronchioleModifier() const;

  virtual bool HasInflammationCoefficient() const;
  virtual SEScalar0To1& GetInflammationCoefficient();
  virtual double GetInflammationCoefficient() const;

  virtual bool HasParticulateSizeDistribution() const;
  virtual SEHistogramFractionVsLength& GetParticulateSizeDistribution();
  virtual const SEHistogramFractionVsLength* GetParticulateSizeDistribution() const;
  
protected: 

  SEScalarNegative1To1*          m_BronchioleModifier;
  SEScalar0To1*                  m_InflammationCoefficient;
  SEHistogramFractionVsLength*   m_ParticulateSizeDistribution;
};