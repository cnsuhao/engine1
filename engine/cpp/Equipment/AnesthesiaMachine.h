/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "Controller/System.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachine.h"
PROTO_PUSH
#include "bind/engine/EngineEquipment.pb.h"
PROTO_POP
class SEAnesthesiaMachineActionCollection;

/**
 * @brief 
 * Generic anesthesia machine for positive pressure ventilation.
 */    
class PULSE_DECL AnesthesiaMachine : public SEAnesthesiaMachine, public PulseSystem
{
  friend PulseController;
  friend class PulseEngineTest;
protected:
  AnesthesiaMachine(PulseController& pc);
  PulseController& m_data;

public:
  virtual ~AnesthesiaMachine();

  void Clear();

  // Set members to a stable homeostatic state
  void Initialize();

  static void Load(const pulse::AnesthesiaMachineData& src, AnesthesiaMachine& dst);
  static pulse::AnesthesiaMachineData* Unload(const AnesthesiaMachine& src);
protected:
  static void Serialize(const pulse::AnesthesiaMachineData& src, AnesthesiaMachine& dst);
  static void Serialize(const AnesthesiaMachine& src, pulse::AnesthesiaMachineData& dst);

  // Set pointers and other member varialbes common to both homeostatic initialization and loading a state
  void SetUp();

public:
  void StateChange();

  void PreProcess();
  void Process();
  void PostProcess();

  void CalculateScrubber();

  // Extending some functionality to these base class methods
  // We will update the Pulse Airway mode when these are called
  virtual void SetConnection(cdm::AnesthesiaMachineData_eConnection c);
  virtual void InvalidateConnection();

private:
  void CalculateSourceStatus();
  void CalculateEquipmentLeak();
  void SetConnection();
  void CalculateValveResistances();
  void CalculateVentilator();
  void CalculateGasSource();
  void CalculateCyclePhase();
  void CheckReliefValve();

  // Serializable member variables (Set in Initialize and in schema)
  bool         m_inhaling; 
  SEScalarTime m_inspirationTime;
  SEScalar     m_O2InletVolumeFraction;
  SEScalarTime m_currentbreathingCycleTime;
  SEScalarTime m_totalBreathingCycleTime;

  // Stateless member variable (Set in SetUp())
  double m_dt_s;
  double m_dValveOpenResistance_cmH2O_s_Per_L;
  double m_dValveClosedResistance_cmH2O_s_Per_L;
  double m_dSwitchOpenResistance_cmH2O_s_Per_L;
  double m_dSwitchClosedResistance_cmH2O_s_Per_L;
  SEAnesthesiaMachineActionCollection* m_actions;
  SEGasCompartment*                    m_ambient;
  SEGasSubstanceQuantity*              m_ambientCO2;
  SEGasSubstanceQuantity*              m_ambientN2;
  SEGasSubstanceQuantity*              m_ambientO2;
  SEGasCompartment*                    m_gasSource;
  SEGasSubstanceQuantity*              m_gasSourceCO2;
  SEGasSubstanceQuantity*              m_gasSourceN2;
  SEGasSubstanceQuantity*              m_gasSourceO2;
  SEGasCompartment*                    m_scrubber;
  SEGasSubstanceQuantity*              m_scubberCO2;
  SEGasSubstanceQuantity*              m_scrubberN2;
  SEFluidCircuitNode*                  m_nVentilator;
  SEFluidCircuitPath*                  m_pAnesthesiaConnectionToEnvironment;
  SEFluidCircuitPath*                  m_pYPieceToExpiratoryLimb;
  SEFluidCircuitPath*                  m_pGasSourceToGasInlet;
  SEFluidCircuitPath*                  m_pInspiratoryLimbToYPiece;
  SEFluidCircuitPath*                  m_pSelectorToReliefValve;
  SEFluidCircuitPath*                  m_pEnvironmentToReliefValve;
  SEFluidCircuitPath*                  m_pSelectorToEnvironment;
  SEFluidCircuitPath*                  m_pEnvironmentToVentilator;
  SEFluidCircuitPath*                  m_pExpiratoryLimbToSelector;
  SEFluidCircuitPath*                  m_pSelectorToScrubber;
};





