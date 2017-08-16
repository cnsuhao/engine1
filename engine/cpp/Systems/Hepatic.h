/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/System.h"
#include "system/physiology/SEHepaticSystem.h"
#include "bind/engine/EnginePhysiology.pb.h"

/**
 * @copydoc Physiology_HepaticystemData
 */  
class PULSE_DECL Hepatic : public SEHepaticSystem, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  Hepatic(PulseController& data);
  PulseController& m_data;

public:
  virtual ~Hepatic();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::HepaticSystemData& src, Hepatic& dst);
  static pulse::HepaticSystemData* Unload(const Hepatic& src);
protected:
  static void Serialize(const pulse::HepaticSystemData& src, Hepatic& dst);
  static void Serialize(const Hepatic& src, pulse::HepaticSystemData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void AtSteadyState();
  void PreProcess();
  void Process();
  void PostProcess();

protected:

};