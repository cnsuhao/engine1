/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/System.h"
#include "system/physiology/SEDrugSystem.h"

/**
 * @brief
 * The drug system contains the physiologically based pharmacokinetic (PBPK) model and the pharmacodynamic (PD) model.
 * @details 
 * Drug transvascular transport is modeled with a physiologically-based pharmacokinetic (PBPK) model,
 * and the physiologic effects on the body are modeled with a low-fidelity pharmacodynamic (PD) model.
 */  
class PULSE_DECL Drugs : public SEDrugSystem, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  Drugs(PulseController& data);
  PulseController& m_data;

public:
  virtual ~Drugs();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::DrugSystemData& src, Drugs& dst);
  static pulse::DrugSystemData* Unload(const Drugs& src);
protected:
  static void Serialize(const pulse::DrugSystemData& src, Drugs& dst);
  static void Serialize(const Drugs& src, pulse::DrugSystemData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess(){}

protected:

  void AdministerSubstanceBolus();
  void AdministerSubstanceInfusion();
  void AdministerSubstanceCompoundInfusion();

  void CalculatePartitionCoefficients();
  void CalculateSubstanceClearance();
  void CalculatePlasmaSubstanceConcentration();
  void CalculateDrugEffects();

  // Stateless member variable (Set in SetUp())
  double m_dt_s;
  SELiquidCompartment*  m_aortaVascular;
  SELiquidCompartment*  m_venaCavaVascular;
  SELiquidCompartment*  m_muscleIntracellular;
  SELiquidCompartment*  m_liverVascular;
  SETissueCompartment*  m_liverTissue;
  SEFluidCircuitPath*   m_IVToVenaCava;
  SETissueCompartment*  m_fatTissue;
};