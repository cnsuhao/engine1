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
#include "system/physiology/SEGastrointestinalSystem.h"
#include "properties/SEScalarMassPerTime.h"
#include "properties/SEScalarVolumePerTime.h"

/**
* @brief @copydoc Physiology_GastrointestinalSystemData
*/
class PULSE_API Gastrointestinal : public SEGastrointestinalSystem, public PulseSystem
{
  friend Pulse;
  friend class PulseEngineTest;
protected:
  Gastrointestinal(Pulse& bg);
  Pulse& m_data;

public:
  virtual ~Gastrointestinal();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::GastrointestinalSystemData& src, Gastrointestinal& dst);
  static pulse::GastrointestinalSystemData* Unload(const Gastrointestinal& src);
protected:
  static void Serialize(const pulse::GastrointestinalSystemData& src, Gastrointestinal& dst);
  static void Serialize(const Gastrointestinal& src, pulse::GastrointestinalSystemData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess();

protected:

  void   GastricSecretion(double duration_s);
  void   DefaultNutritionRates(SENutrition& n);
  void   DigestStomachNutrients(double duration_s);
  double DigestNutrient(SEUnitScalar& totalAmt, SEUnitScalar& rate, bool mass, double duration_s);
  void   AbsorbMeal(double duration_s);
  void   AbsorbNutrients(double duration_s);

  // Serializable member variables (Set in Initialize and in schema)  

  // Stateless member variable (Set in SetUp())
  SELiquidCompartment*         m_SmallIntestineChyme;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeAlbumin;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeGlucose;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeTristearin;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeCalcium;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeSodium;
  SELiquidSubstanceQuantity*   m_SmallIntestineChymeUrea;

  SEFluidCircuitPath*          m_GItoCVPath;
  SEFluidCircuitPath*          m_GutT1ToGroundPath;
  SEScalarMassPerTime          m_CalciumDigestionRate;
  SEScalarVolumePerTime        m_WaterDigestionRate;

  // We want to start simulation time 0 (after stabilization) with the initial gut mass from the meal specified in the config file
  std::map<SELiquidSubstanceQuantity*, double> m_InitialSubstanceMasses_ug;// Used only during the final AtSteadyState

  bool   m_ConsumeRate; // Some substance digestion rates are specified by the user, some by configuration,
  //if the stomach runs out of a substance with a user provided rate, we invalidate the rate (true)
  //if the rate is a configuration rate, we don't want to invalidate it if we run out of the substance (false)
  bool   m_DecrementNutrients; // True  Signals that we decrement stomach nutrients when we digest them
  // We do not decriment stomach contents during stabilization
  double m_secretionRate_mL_Per_s;
  double m_dT_s;

};
