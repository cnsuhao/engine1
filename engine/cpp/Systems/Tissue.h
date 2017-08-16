/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/System.h"
#include "system/physiology/SETissueSystem.h"
#include "bind/engine/EnginePhysiology.pb.h"

/**
 * @brief This class encapsulates logic necessary to connect independent systems together.
 * @details Each system calculates the behavior that occurs within its individual physiology function; 
 * however, several processes extend between two systems, i.e., alveoli transfer links the %Respiratory and %Anesthesia Machine Systems. 
 * To capture this behavior, the System Interactions methodology was introduced. 
 * The primary function of this system is to capture the substance transport that occurs between systems.
 */  
class PULSE_DECL Tissue : public SETissueSystem, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  Tissue(PulseController& data);
  PulseController& m_data;

public:
  virtual ~Tissue();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::TissueSystemData& src, Tissue& dst);
  static pulse::TissueSystemData* Unload(const Tissue& src);
protected:
  static void Serialize(const pulse::TissueSystemData& src, Tissue& dst);
  static void Serialize(const Tissue& src, pulse::TissueSystemData& dst);

  // Set pointers and other member variables common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();  
  void PreProcess();
  void Process();
  void PostProcess();

protected:

  // Preprocess Methods
  void ProduceAlbumin(double duration_s);

    /*Tissue System*/
  void CalculateMetabolicConsumptionAndProduction(double time);
  void GlucoseLipidControl(double time);

  /*Process Methods*/
  void CalculateDiffusion();
  void CalculatePulmonaryCapillarySubstanceTransfer();
  void CalculateVitals();
  

  /*Postprocess Methods*/  

  /*Diffusion Utilities*/
  void DistributeMassbyVolumeWeighted(SELiquidCompartment& cmpt, const SESubstance& sub, double mass, const MassUnit& unit);
  void DistributeMassbyMassWeighted(SELiquidCompartment& cmpt, const SESubstance& sub, double mass, const MassUnit& unit);

  double PerfusionLimitedDiffusion(SETissueCompartment& tissue, SELiquidCompartment& vascular, const SESubstance& sub, double partitionCoeff, double timestep_s);
  void AlveolarPartialPressureGradientDiffusion(SEGasCompartment& pulmonary, SELiquidCompartment& vascular, SESubstance& sub, double DiffusingCapacityO2_mL_Per_s_mmHg, double timestep_s);

  double MoveMassByInstantDiffusion(SELiquidCompartment& source, SELiquidCompartment& target, const SESubstance& sub, double timestep_s);
  double MoveMassBySimpleDiffusion(SELiquidCompartment& source, SELiquidCompartment& target, const SESubstance& sub, double permeabilityCofficient_mL_Per_s, double timestep_s);  
  double MoveMassByFacilitatedDiffusion(SELiquidCompartment& source, SELiquidCompartment& target, const SESubstance& sub, double combinedCoefficient_g_Per_s, double timestep_s);
  double MoveMassByActiveTransport(SELiquidCompartment& source, SELiquidCompartment& target, const SESubstance& sub, double DiffusingCapacityO2_mL_Per_s_mmHg, double timestep_s);

  // Serializable member variables (Set in Initialize and in schema
  double m_RestingTissueGlucose_g;
  double m_RestingBloodGlucose_g_Per_L;
  double m_RestingBloodLipid_g_Per_L;
  double m_RestingBloodInsulin_g_Per_L;
  double m_RestingPatientMass_kg;
  double m_RestingFluidMass_kg;

  // Stateless member variable (Set in SetUp())
  double m_Dt_s;
  double m_AlbuminProdutionRate_g_Per_s;
  SESubstance*                m_Albumin;
  SESubstance*                m_Glucose;
  SESubstance*                m_Tristearin;
  SESubstance*                m_O2;
  SESubstance*                m_CO2;
  SESubstance*                m_CO; 
  SESubstance*                m_Lactate;
  SESubstance*                m_Acetoacetate;
  SESubstance*                m_Creatinine;
  SESubstance*                m_Sodium;
  SESubstance*                m_Calcium;
  SESubstance*                m_Insulin;

  SEFluidCircuitNode*         m_GutT1;
  SEFluidCircuitPath*         m_GutT1ToGutT3;

  SELiquidSubstanceQuantity*  m_LiverTissueAlbumin;
  SETissueCompartment*        m_LeftLungTissue;
  SETissueCompartment*        m_RightLungTissue;
  SETissueCompartment*        m_MuscleTissue;
  SELiquidCompartment*        m_MuscleIntracellular;
  SETissueCompartment*        m_LiverTissue;
  SELiquidCompartment*        m_LiverIntracellular;
  SETissueCompartment*        m_FatTissue;
  SELiquidCompartment*        m_FatIntracellular;

  SELiquidCompartment*        m_FatVascular;
  SELiquidSubstanceQuantity*  m_FatVascularLipid;
  SELiquidSubstanceQuantity*  m_LiverVascularGlucose;
  SELiquidCompartment*        m_MuscleVascular;
  SELiquidSubstanceQuantity*  m_MuscleVascularGlucose;

  SEGasCompartment*           m_LeftAlveoli;
  SEGasCompartment*           m_RightAlveoli;
  SELiquidCompartment*        m_LeftPulmonaryCapillaries;
  SELiquidCompartment*        m_RightPulmonaryCapillaries;
  
  SEPatientActionCollection*  m_PatientActions;  

  std::map<SETissueCompartment*, SELiquidCompartment*> m_TissueToVascular;
  std::vector<SETissueCompartment*>                    m_ConsumptionProdutionTissues;
};



