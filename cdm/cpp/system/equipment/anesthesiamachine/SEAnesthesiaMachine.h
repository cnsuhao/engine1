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
#include "system/SESystem.h"
#include "bind/cdm/AnesthesiaMachine.pb.h"
class SEEventHandler;
class SESubstanceManager;
class SEAnesthesiaMachineChamber;
class SEAnesthesiaMachineOxygenBottle;
class SEAnesthesiaMachineConfiguration;
class Serializer;

class CDM_DECL SEAnesthesiaMachine : public SESystem
{
protected:
  friend SEAnesthesiaMachineConfiguration;
public:

  SEAnesthesiaMachine(SESubstanceManager& substances);
  virtual ~SEAnesthesiaMachine();

  virtual void Clear();

  static void Load(const cdm::AnesthesiaMachineData& src, SEAnesthesiaMachine& dst);
  static cdm::AnesthesiaMachineData* Unload(const SEAnesthesiaMachine& src);
protected:
  static void Serialize(const cdm::AnesthesiaMachineData& src, SEAnesthesiaMachine& dst);
  static void Serialize(const SEAnesthesiaMachine& src, cdm::AnesthesiaMachineData& dst);

  /** @name StateChange
  *   @brief - This method is called when ever there is a state change
  *            Specically a new file has been loaded, configuration action, or the system reset
  *            Engine specific methodology can then update their logic.
  */
  virtual void StateChange(){};
  virtual void Merge(const SEAnesthesiaMachine& from);
  virtual void ProcessConfiguration(const SEAnesthesiaMachineConfiguration& config);
public:

  bool LoadFile(const std::string& anesthesiaMachineFile);

  virtual const SEScalar* GetScalar(const std::string& name);

  virtual const std::map<cdm::AnesthesiaMachineData_eEvent, bool>& GetEventStates() const { return m_EventState; }
  virtual void SetEvent(cdm::AnesthesiaMachineData_eEvent state, bool active, const SEScalarTime& time);
  virtual bool IsEventActive(cdm::AnesthesiaMachineData_eEvent state) const;
  virtual double GetEventDuration(cdm::AnesthesiaMachineData_eEvent type, const TimeUnit& unit) const;
  virtual void UpdateEvents(const SEScalarTime& timeStep);
  /** @name ForwardEvents
  *  @brief - Set a callback class to invoke when any event changes
  *  @details - Note that the handler callback can and will be called in the middle of a time step
  *             So system and compartment objects may not be completely up to date when called.
  *             Use the PhysiologyEngineInterface::SetEventHandler to ensure that all engine
  *             data is up to date at the time the callback is invoked
  */
  virtual void ForwardEvents(SEEventHandler* handler);

  virtual cdm::AnesthesiaMachineData_eConnection GetConnection() const;
  virtual void SetConnection(cdm::AnesthesiaMachineData_eConnection c);

  virtual bool HasInletFlow() const;
  virtual SEScalarVolumePerTime& GetInletFlow();
  virtual double GetInletFlow(const VolumePerTimeUnit& unit) const;
  
  virtual bool HasInspiratoryExpiratoryRatio() const;
  virtual SEScalar& GetInspiratoryExpiratoryRatio();
  virtual double GetInspiratoryExpiratoryRatio() const;
    
  virtual bool HasOxygenFraction() const;
  virtual SEScalar0To1& GetOxygenFraction();
  virtual double GetOxygenFraction() const;

  virtual cdm::AnesthesiaMachineData_eOxygenSource GetOxygenSource() const;
  virtual void SetOxygenSource(cdm::AnesthesiaMachineData_eOxygenSource name);

  virtual bool HasPositiveEndExpiredPressure() const;
  virtual SEScalarPressure& GetPositiveEndExpiredPressure();
  virtual double GetPositiveEndExpiredPressure(const PressureUnit& unit) const;
  
  virtual cdm::AnesthesiaMachineData_ePrimaryGas GetPrimaryGas() const;
  virtual void SetPrimaryGas(cdm::AnesthesiaMachineData_ePrimaryGas name);
  
  virtual bool HasRespiratoryRate() const;
  virtual SEScalarFrequency& GetRespiratoryRate();
  virtual double GetRespiratoryRate(const FrequencyUnit& unit) const;

  virtual bool HasReliefValvePressure() const;
  virtual SEScalarPressure& GetReliefValvePressure();
  virtual double GetReliefValvePressure(const PressureUnit& unit) const;

  virtual bool HasVentilatorPressure() const;
  virtual SEScalarPressure& GetVentilatorPressure();
  virtual double GetVentilatorPressure(const PressureUnit& unit) const;

  virtual bool HasLeftChamber() const;
  virtual SEAnesthesiaMachineChamber& GetLeftChamber();
  virtual const SEAnesthesiaMachineChamber* GetLeftChamber() const;
  virtual void RemoveLeftChamber();

  virtual bool HasRightChamber() const;
  virtual SEAnesthesiaMachineChamber& GetRightChamber();
  virtual const SEAnesthesiaMachineChamber* GetRightChamber() const;
  virtual void RemoveRightChamber();

  virtual bool HasOxygenBottleOne() const;
  virtual SEAnesthesiaMachineOxygenBottle& GetOxygenBottleOne();
  virtual const SEAnesthesiaMachineOxygenBottle* GetOxygenBottleOne() const;
  virtual void RemoveOxygenBottleOne();

  virtual bool HasOxygenBottleTwo() const;
  virtual SEAnesthesiaMachineOxygenBottle& GetOxygenBottleTwo();
  virtual const SEAnesthesiaMachineOxygenBottle* GetOxygenBottleTwo() const;
  virtual void RemoveOxygenBottleTwo();

protected:

  SEEventHandler*                                        m_EventHandler;
  std::map<cdm::AnesthesiaMachineData_eEvent, bool>      m_EventState;
  std::map<cdm::AnesthesiaMachineData_eEvent, double>    m_EventDuration_s;

  cdm::AnesthesiaMachineData_eConnection                 m_Connection;
  SEScalarVolumePerTime*                                 m_InletFlow;
  SEScalar*                                              m_InspiratoryExpiratoryRatio;
  SEScalar0To1*                                          m_OxygenFraction;  
  cdm::AnesthesiaMachineData_eOxygenSource               m_OxygenSource;
  SEScalarPressure*                                      m_PositiveEndExpiredPressure;  
  cdm::AnesthesiaMachineData_ePrimaryGas                 m_PrimaryGas;
  SEScalarFrequency*                                     m_RespiratoryRate;
  SEScalarPressure*                                      m_ReliefValvePressure;

  SEScalarPressure*                                      m_VentilatorPressure;

  SEAnesthesiaMachineChamber*                            m_LeftChamber;
  SEAnesthesiaMachineChamber*                            m_RightChamber;

  SEAnesthesiaMachineOxygenBottle*                       m_OxygenBottleOne;
  SEAnesthesiaMachineOxygenBottle*                       m_OxygenBottleTwo;

  SESubstanceManager&                                    m_Substances;
};
