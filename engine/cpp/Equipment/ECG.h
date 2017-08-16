/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/


#pragma once
#include "Controller/System.h"
#include "bind/engine/EngineEquipment.pb.h"
#include "system/equipment/electrocardiogram/SEElectroCardioGram.h"
#include "system/equipment/electrocardiogram/SEElectroCardioGramWaveformInterpolator.h"

/**
* @brief 
* Generic ECG machine to assess the heart rhythm.
*/
class PULSE_DECL ECG : public SEElectroCardioGram, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  ECG(PulseController& pc);
  PulseController& m_data;

public:
  virtual ~ECG();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::ElectroCardioGramData& src, ECG& dst);
  static pulse::ElectroCardioGramData* Unload(const ECG& src);
protected:
  static void Serialize(const pulse::ElectroCardioGramData& src, ECG& dst);
  static void Serialize(const ECG& src, pulse::ElectroCardioGramData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:

  // main driver function responsible for calling the various ECG functions:
  void PreProcess();
  void Process();
  void PostProcess();

protected:
  // Serializable member variables (Set in Initialize and in schema)
  SEScalarTime m_heartRhythmTime;
  SEScalarTime m_heartRhythmPeriod;
  SEElectroCardioGramWaveformInterpolator m_interpolator;

  // Stateless member variable (Set in SetUp())
  double m_dt_s;
};
