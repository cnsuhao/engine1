/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "compartment/SECompartment.h"
class SESubstance;
class SESubstanceManager;
class SELiquidCompartment;

class CDM_DECL SETissueCompartment : public SECompartment
{
  friend class SECompartmentManager;
protected:
  SETissueCompartment(const std::string& name, Logger* logger);
public:
  virtual ~SETissueCompartment();

  virtual void Clear();

  static void Load(const cdm::TissueCompartmentData& src, SETissueCompartment& dst);
  static cdm::TissueCompartmentData* Unload(const SETissueCompartment& src);
protected:
  static void Serialize(const cdm::TissueCompartmentData& src, SETissueCompartment& dst);
  static void Serialize(const SETissueCompartment& src, cdm::TissueCompartmentData& dst);

public:
  virtual const SEScalar* GetScalar(const std::string& name);

  virtual bool HasChildren() const { return !m_Children.empty(); }// Children on tissue is not supported at this time
  virtual const std::vector<SETissueCompartment*>& GetChildren() { return m_Children; }// Children on tissue is not supported at this time
  virtual const std::vector<SETissueCompartment*>& GetLeaves() { return m_Leaves; }// Children on tissue is not supported at this time

  virtual void StateChange();

  virtual bool HasAcidicPhospohlipidConcentration() const;
  virtual SEScalarMassPerMass& GetAcidicPhospohlipidConcentration();
  virtual double GetAcidicPhospohlipidConcentration(const MassPerMassUnit& unit) const;

  virtual bool HasMatrixVolume() const;
  virtual SEScalarVolume& GetMatrixVolume();
  virtual double GetMatrixVolume(const VolumeUnit& unit) const;

  virtual bool HasNeutralLipidsVolumeFraction() const;
  virtual SEScalar0To1& GetNeutralLipidsVolumeFraction();
  virtual double GetNeutralLipidsVolumeFraction() const;

  virtual bool HasNeutralPhospholipidsVolumeFraction() const;
  virtual SEScalar0To1& GetNeutralPhospholipidsVolumeFraction();
  virtual double GetNeutralPhospholipidsVolumeFraction() const;

  virtual bool HasTissueToPlasmaAlbuminRatio() const;
  virtual SEScalar& GetTissueToPlasmaAlbuminRatio();
  virtual double GetTissueToPlasmaAlbuminRatio() const;

  virtual bool HasTissueToPlasmaAlphaAcidGlycoproteinRatio() const;
  virtual SEScalar& GetTissueToPlasmaAlphaAcidGlycoproteinRatio();
  virtual double GetTissueToPlasmaAlphaAcidGlycoproteinRatio() const;

  virtual bool HasTissueToPlasmaLipoproteinRatio() const;
  virtual SEScalar& GetTissueToPlasmaLipoproteinRatio();
  virtual double GetTissueToPlasmaLipoproteinRatio() const;

  virtual bool HasTotalMass() const;
  virtual SEScalarMass& GetTotalMass();
  virtual double GetTotalMass(const MassUnit& unit) const;

protected:
  
  SEScalarMassPerMass*   m_AcidicPhospohlipidConcentration;
  SEScalarVolume*        m_MatrixVolume;
  SEScalar0To1*      m_NeutralLipidsVolumeFraction;
  SEScalar0To1*      m_NeutralPhospholipidsVolumeFraction;
  SEScalar*              m_TissueToPlasmaAlbuminRatio;
  SEScalar*              m_TissueToPlasmaAlphaAcidGlycoproteinRatio;
  SEScalar*              m_TissueToPlasmaLipoproteinRatio;
  SEScalarMass*          m_TotalMass;

  std::vector<SETissueCompartment*> m_Children;
  std::vector<SETissueCompartment*> m_Leaves;
};