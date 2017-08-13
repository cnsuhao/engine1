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

#include "substance/SESubstanceManager.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachine.h"
#include "system/equipment/Anesthesia/actions/SEOxygenTankPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEOxygenWallPortPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEExpiratoryValveLeak.h"
#include "system/equipment/Anesthesia/actions/SEExpiratoryValveObstruction.h"
#include "system/equipment/Anesthesia/actions/SEInspiratoryValveLeak.h"
#include "system/equipment/Anesthesia/actions/SEInspiratoryValveObstruction.h"
#include "system/equipment/Anesthesia/actions/SEMaskLeak.h"
#include "system/equipment/Anesthesia/actions/SESodaLimeFailure.h"
#include "system/equipment/Anesthesia/actions/SETubeCuffLeak.h"
#include "system/equipment/Anesthesia/actions/SEVaporizerFailure.h"
#include "system/equipment/Anesthesia/actions/SEVentilatorPressureLoss.h"
#include "system/equipment/Anesthesia/actions/SEYPieceDisconnect.h"
#include "system/equipment/Anesthesia/actions/SEAnesthesiaMachineConfiguration.h"

class CDM_DECL SEAnesthesiaMachineActionCollection : public Loggable
{
  friend class SEActionManager;
protected:
  SEAnesthesiaMachineActionCollection(SESubstanceManager&);
public:
  ~SEAnesthesiaMachineActionCollection();

  // STATE ACTION
  bool HasConfiguration() const;
  SEAnesthesiaMachineConfiguration* GetConfiguration() const;
  void RemoveConfiguration();
  
  // INCIDENT ACTIONS

  bool HasOxygenTankPressureLoss() const;
  SEOxygenTankPressureLoss* GetOxygenTankPressureLoss() const;
  void RemoveOxygenTankPressureLoss();

  bool HasOxygenWallPortPressureLoss() const;
  SEOxygenWallPortPressureLoss* GetOxygenWallPortPressureLoss();
  void RemoveOxygenWallPortPressureLoss();

  // FAILURE ACTIONS

  bool HasExpiratoryValveLeak() const;
  SEExpiratoryValveLeak* GetExpiratoryValveLeak() const;
  void RemoveExpiratoryValveLeak();  

  bool HasExpiratoryValveObstruction() const;
  SEExpiratoryValveObstruction* GetExpiratoryValveObstruction() const;
  void RemoveExpiratoryValveObstruction();

  bool HasInspiratoryValveLeak() const;
  SEInspiratoryValveLeak* GetInspiratoryValveLeak() const;
  void RemoveInspiratoryValveLeak();

  bool HasInspiratoryValveObstruction() const;
  SEInspiratoryValveObstruction* GetInspiratoryValveObstruction() const;
  void RemoveInspiratoryValveObstruction();

  bool HasMaskLeak() const;
  SEMaskLeak* GetMaskLeak() const;
  void RemoveMaskLeak();

  bool HasSodaLimeFailure() const;
  SESodaLimeFailure* GetSodaLimeFailure() const;
  void RemoveSodaLimeFailure();

  bool HasTubeCuffLeak() const;
  SETubeCuffLeak* GetTubeCuffLeak() const;
  void RemoveTubeCuffLeak();

  bool HasVaporizerFailure() const;
  SEVaporizerFailure* GetVaporizerFailure() const;
  void RemoveVaporizerFailure();

  bool HasVentilatorPressureLoss() const;
  SEVentilatorPressureLoss* GetVentilatorPressureLoss() const;
  void RemoveVentilatorPressureLoss();

  bool HasYPieceDisconnect() const;
  SEYPieceDisconnect* GetYPieceDisconnect() const;
  void RemoveYPieceDisconnect();
  
protected:
  void Clear();
  static void Serialize(const SEAnesthesiaMachineActionCollection& src, cdm::ActionListData& dst);
  bool ProcessAction(const SEAnesthesiaMachineAction& action, cdm::AnyAnesthesiaMachineActionData& any);

  SEAnesthesiaMachineConfiguration*           m_Configuration;
  //Anesthesia Machine Incidents
  SEOxygenTankPressureLoss*                   m_OxygenTankPressureLoss;
  SEOxygenWallPortPressureLoss*               m_OxygenWallPortPressureLoss;
  //Anesthesia Machine Failures
  SEExpiratoryValveLeak*                      m_ExpiratoryValveLeak;
  SEExpiratoryValveObstruction*               m_ExpiratoryValveObstruction;
  SEInspiratoryValveLeak*                     m_InspiratoryValveLeak;
  SEInspiratoryValveObstruction*              m_InspiratoryValveObstruction;
  SEMaskLeak*                                 m_MaskLeak;
  SESodaLimeFailure*                          m_SodaLimeFailure;
  SETubeCuffLeak*                             m_TubeCuffLeak;
  SEVaporizerFailure*                         m_VaporizerFailure;
  SEVentilatorPressureLoss*                   m_VentilatorPressureLoss;
  SEYPieceDisconnect*                         m_YPieceDisconnect;
  // General
  SESubstanceManager& m_Substances;
};
