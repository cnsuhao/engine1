/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SESubstance;
class SESubstanceManager;
class SEEnvironmentalConditions;
#include "bind/cdm/Substance.pb.h"

class CDM_DECL SESubstanceConcentration : public Loggable
{
protected:
  friend SEEnvironmentalConditions;// So it can add substances to the manager
public:

  SESubstanceConcentration(SESubstance& substance);
  virtual ~SESubstanceConcentration();

  virtual void Clear();

  static void Load(const cdm::SubstanceData_ConcentrationData& src, SESubstanceConcentration& dst);
  static cdm::SubstanceData_ConcentrationData* Unload(const SESubstanceConcentration& src);
protected:
  static void Serialize(const cdm::SubstanceData_ConcentrationData& src, SESubstanceConcentration& dst);
  static void Serialize(const SESubstanceConcentration& src, cdm::SubstanceData_ConcentrationData& dst);

public:
  virtual bool HasConcentration() const;
  virtual SEScalarMassPerVolume& GetConcentration();  
  virtual double GetConcentration(const MassPerVolumeUnit& unit) const;

  virtual SESubstance& GetSubstance() const;
  
protected: 

  SESubstance&           m_Substance;
  SEScalarMassPerVolume* m_Concentration;
  
};