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

#include "../Controller/PulseSystem.h"
#include "system/physiology/SEEnergySystem.h"
#include "utils/RunningAverage.h"
#include "circuit/thermal/SEThermalCircuitCalculator.h"
class SEThermalCircuitCalculator;

/**
 * @brief @copydoc Physiology_EnergySystemData
 */  
class PULSE_API Energy : public SEEnergySystem, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Energy(Pulse& bg);
  Pulse& m_data;

public:
  ~Energy(void);

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::EnergySystemData& src, Energy& dst);
  static pulse::EnergySystemData* Unload(const Energy& src);
protected:
  static void Serialize(const pulse::EnergySystemData& src, Energy& dst);
  static void Serialize(const Energy& src, pulse::EnergySystemData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess();

private:

  // Preprocess Methods
  void CalculateMetabolicHeatGeneration();
  void CalculateSweatRate();
  void UpdateHeatResistance();
  // Actions/Conditions
  void Exercise();
  // These are both part of the consume meal condition.
  //void Dehydration(double time); // Need to revisit
  //void Starvation(double time); // Need to revisit
  // Used in Reset & Starvation
  void CalculateBasalMetabolicRate();

  // Process Methods
  void CalculateVitalSigns();

  // Serializable member variables (Set in Initialize and in schema)
  double m_UsableEnergyStore_J;
  double m_PeakPowerEnergyStore_J;
  double m_MediumPowerEnergyStore_J;
  double m_EnduranceEnergyStore_J;
  RunningAverage m_BloodpH;
  RunningAverage m_BicarbonateMolarity_mmol_Per_L;

  // Stateless member variable (Set in SetUp())
  double                      m_dT_s;
  SEPatient*                  m_Patient;
  SEPatientActionCollection*  m_PatientActions;
  // Cmpts,Substance, and nodes
  SELiquidSubstanceQuantity*  m_AortaHCO3;  
  //Nodes
  SEThermalCircuitNode*       m_coreNode;
  SEThermalCircuitNode*       m_skinNode;
  //Paths
  SEThermalCircuitPath*       m_temperatureGroundToCorePath;
  SEThermalCircuitPath*       m_coreToSkinPath;
  SEFluidCircuitPath*         m_skinExtravascularToSweatingGroundPath;   
  //Circuits
  SEThermalCircuit*           m_InternalTemperatureCircuit;
  SEThermalCircuit*           m_TemperatureCircuit;
  SEThermalCircuitCalculator  m_circuitCalculator;
};

