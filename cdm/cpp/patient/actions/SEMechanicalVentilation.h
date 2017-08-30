/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"
CDM_BIND_DECL(MechanicalVentilationData)
class Serializer;
class SESubstance;
class SESubstanceFraction;
class SEMechanicalVentilationConfiguration;

class CDM_DECL SEMechanicalVentilation : public SEPatientAction
{
protected:

public:

  SEMechanicalVentilation();
  virtual ~SEMechanicalVentilation();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::MechanicalVentilationData& src, SEMechanicalVentilation& dst, const SESubstanceManager& subMgr);
  static cdm::MechanicalVentilationData* Unload(const SEMechanicalVentilation& src);
protected:
  static void Serialize(const cdm::MechanicalVentilationData& src, SEMechanicalVentilation& dst, const SESubstanceManager& subMgr);
  static void Serialize(const SEMechanicalVentilation& src, cdm::MechanicalVentilationData& dst);

public:

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch name);

  virtual bool HasFlow() const;
  virtual SEScalarVolumePerTime& GetFlow();
  virtual double GetFlow(const VolumePerTimeUnit& unit) const;

  virtual bool HasPressure() const;
  virtual SEScalarPressure& GetPressure();
  virtual double GetPressure(const PressureUnit& unit) const;

  bool HasGasFraction() const;
  bool HasGasFraction(const SESubstance& substance) const;
  const std::vector<SESubstanceFraction*>& GetGasFractions();
  const std::vector<const SESubstanceFraction*>& GetGasFractions() const;
  SESubstanceFraction& GetGasFraction(SESubstance& substance);
  const SESubstanceFraction* GetGasFraction(const SESubstance& substance) const;
  void RemoveGasFraction(const SESubstance& substance);
  void RemoveGasFractions();

  virtual void ToString(std::ostream &str) const;
protected:

  std::stringstream    m_ss;

  cdm::eSwitch            m_State;
  SEScalarVolumePerTime*  m_Flow;
  SEScalarPressure*       m_Pressure;

  std::vector<SESubstanceFraction*>       m_GasFractions;
  std::vector<const SESubstanceFraction*> m_cGasFractions;
};
