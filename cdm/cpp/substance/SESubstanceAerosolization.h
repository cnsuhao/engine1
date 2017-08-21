/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
PROTO_PUSH
#include "bind/cdm/Substance.pb.h"
PROTO_POP

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