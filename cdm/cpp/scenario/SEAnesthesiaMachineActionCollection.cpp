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

#include "stdafx.h"
#include "scenario/SEAnesthesiaMachineActionCollection.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachineChamber.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolumePerTime.h"

SEAnesthesiaMachineActionCollection::SEAnesthesiaMachineActionCollection(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
  m_Configuration = nullptr;

  m_OxygenTankPressureLoss = nullptr;
  m_OxygenWallPortPressureLoss = nullptr;

  m_ExpiratoryValveLeak = nullptr;
  m_ExpiratoryValveObstruction = nullptr;
  m_InspiratoryValveLeak = nullptr;
  m_InspiratoryValveObstruction = nullptr;
  m_MaskLeak = nullptr;
  m_SodaLimeFailure = nullptr;
  m_TubeCuffLeak = nullptr;
  m_VaporizerFailure = nullptr;
  m_VentilatorPressureLoss = nullptr;
  m_YPieceDisconnect = nullptr;
}

SEAnesthesiaMachineActionCollection::~SEAnesthesiaMachineActionCollection()
{
  Clear();
}

void SEAnesthesiaMachineActionCollection::Clear()
{
  // State
  RemoveConfiguration();
  // Incidents
  RemoveOxygenTankPressureLoss();
  RemoveOxygenWallPortPressureLoss();
  // Failures
  RemoveExpiratoryValveLeak();
  RemoveExpiratoryValveObstruction();
  RemoveInspiratoryValveLeak();
  RemoveInspiratoryValveObstruction();
  RemoveMaskLeak();
  RemoveSodaLimeFailure();
  RemoveTubeCuffLeak();
  RemoveVaporizerFailure();
  RemoveVentilatorPressureLoss();
  RemoveYPieceDisconnect();
}

bool SEAnesthesiaMachineActionCollection::ProcessAction(const SEAnesthesiaMachineAction& action, cdm::AnyAnesthesiaMachineActionData& any)
{
  const SEAnesthesiaMachineConfiguration* config = dynamic_cast<const SEAnesthesiaMachineConfiguration*>(&action);
  if (config != nullptr)
  {
    if (m_Configuration == nullptr)
      m_Configuration = new SEAnesthesiaMachineConfiguration(m_Substances);
    any.set_allocated_configuration(SEAnesthesiaMachineConfiguration::Unload(*config));
    SEAnesthesiaMachineConfiguration::Load(any.configuration(), *m_Configuration);
    if (!m_Configuration->IsActive())
      RemoveConfiguration();
    return true;
  }

  const SEOxygenTankPressureLoss* O2Tank = dynamic_cast<const SEOxygenTankPressureLoss*>(&action);
  if (O2Tank != nullptr)
  {
    if (m_OxygenTankPressureLoss == nullptr)
      m_OxygenTankPressureLoss = new SEOxygenTankPressureLoss();
    any.set_allocated_oxygentankpressureloss(SEOxygenTankPressureLoss::Unload(*O2Tank));
    SEOxygenTankPressureLoss::Load(any.oxygentankpressureloss(), *m_OxygenTankPressureLoss);
    if (!m_OxygenTankPressureLoss->IsActive())
      RemoveOxygenTankPressureLoss();
    return true;
  }

  const SEOxygenWallPortPressureLoss* O2Wall = dynamic_cast<const SEOxygenWallPortPressureLoss*>(&action);
  if (O2Wall != nullptr)
  {
    if (m_OxygenWallPortPressureLoss == nullptr)
      m_OxygenWallPortPressureLoss = new SEOxygenWallPortPressureLoss();
    any.set_allocated_oxygenwallportpressureloss(SEOxygenWallPortPressureLoss::Unload(*O2Wall));
    SEOxygenWallPortPressureLoss::Load(any.oxygenwallportpressureloss(), *m_OxygenWallPortPressureLoss);
    if (!m_OxygenWallPortPressureLoss->IsActive())
      RemoveOxygenWallPortPressureLoss();
    return true;
  }

  const SEExpiratoryValveLeak* eLeak = dynamic_cast<const SEExpiratoryValveLeak*>(&action);
  if (eLeak != nullptr)
  {
    if (m_ExpiratoryValveLeak == nullptr)
      m_ExpiratoryValveLeak = new SEExpiratoryValveLeak();
    any.set_allocated_expiratoryvalveleak(SEExpiratoryValveLeak::Unload(*eLeak));
    SEExpiratoryValveLeak::Load(any.expiratoryvalveleak(), *m_ExpiratoryValveLeak);
    if (!m_ExpiratoryValveLeak->IsActive())
      RemoveExpiratoryValveLeak();
    return true;
  }

  const SEExpiratoryValveObstruction* eOb = dynamic_cast<const SEExpiratoryValveObstruction*>(&action);
  if (eOb != nullptr)
  {
    if (m_ExpiratoryValveObstruction == nullptr)
      m_ExpiratoryValveObstruction = new SEExpiratoryValveObstruction();
    any.set_allocated_expiratoryvalveobstruction(SEExpiratoryValveObstruction::Unload(*eOb));
    SEExpiratoryValveObstruction::Load(any.expiratoryvalveobstruction(), *m_ExpiratoryValveObstruction);
    if (!m_ExpiratoryValveObstruction->IsActive())
      RemoveExpiratoryValveObstruction();
    return true;
  }

  const SEInspiratoryValveLeak* iLeak = dynamic_cast<const SEInspiratoryValveLeak*>(&action);
  if (iLeak != nullptr)
  {
    if (m_InspiratoryValveLeak == nullptr)
      m_InspiratoryValveLeak = new SEInspiratoryValveLeak();
    any.set_allocated_inspiratoryvalveleak(SEInspiratoryValveLeak::Unload(*iLeak));
    SEInspiratoryValveLeak::Load(any.inspiratoryvalveleak(), *m_InspiratoryValveLeak);
    if (!m_InspiratoryValveLeak->IsActive())
      RemoveInspiratoryValveLeak();
    return true;
  }

  const SEInspiratoryValveObstruction* iOb = dynamic_cast<const SEInspiratoryValveObstruction*>(&action);
  if (iOb != nullptr)
  {
    if (m_InspiratoryValveObstruction == nullptr)
      m_InspiratoryValveObstruction = new SEInspiratoryValveObstruction();
    any.set_allocated_inspiratoryvalveobstruction(SEInspiratoryValveObstruction::Unload(*iOb));
    SEInspiratoryValveObstruction::Load(any.inspiratoryvalveobstruction(), *m_InspiratoryValveObstruction);
    if (!m_InspiratoryValveObstruction->IsActive())
      RemoveInspiratoryValveObstruction();
    return true;
  }

  const SEMaskLeak* mask = dynamic_cast<const SEMaskLeak*>(&action);
  if (mask != nullptr)
  {
    if (m_MaskLeak == nullptr)
      m_MaskLeak = new SEMaskLeak();
    any.set_allocated_maskleak(SEMaskLeak::Unload(*mask));
    SEMaskLeak::Load(any.maskleak(), *m_MaskLeak);
    if (!m_MaskLeak->IsActive())
      RemoveMaskLeak();
    return true;
  }

  const SESodaLimeFailure* soda = dynamic_cast<const SESodaLimeFailure*>(&action);
  if (soda != nullptr)
  {
    if (m_SodaLimeFailure == nullptr)
      m_SodaLimeFailure = new SESodaLimeFailure();
    any.set_allocated_sodalimefailure(SESodaLimeFailure::Unload(*soda));
    SESodaLimeFailure::Load(any.sodalimefailure(), *m_SodaLimeFailure);
    if (!m_SodaLimeFailure->IsActive())
      RemoveSodaLimeFailure();
    return true;
  }

  const SETubeCuffLeak* tube = dynamic_cast<const SETubeCuffLeak*>(&action);
  if (tube != nullptr)
  {
    if (m_TubeCuffLeak == nullptr)
      m_TubeCuffLeak = new SETubeCuffLeak();
    any.set_allocated_tubecuffleak(SETubeCuffLeak::Unload(*tube));
    SETubeCuffLeak::Load(any.tubecuffleak(), *m_TubeCuffLeak);
    if (!m_TubeCuffLeak->IsActive())
      RemoveTubeCuffLeak();
    return true;
  }

  const SEVaporizerFailure* vFail = dynamic_cast<const SEVaporizerFailure*>(&action);
  if (vFail != nullptr)
  {
    if (m_VaporizerFailure == nullptr)
      m_VaporizerFailure = new SEVaporizerFailure();
    any.set_allocated_vaporizerfailure(SEVaporizerFailure::Unload(*vFail));
    SEVaporizerFailure::Load(any.vaporizerfailure(), *m_VaporizerFailure);
    if (!m_VaporizerFailure->IsActive())
      RemoveVaporizerFailure();
    return true;
  }

  const SEVentilatorPressureLoss* vLoss = dynamic_cast<const SEVentilatorPressureLoss*>(&action);
  if (vLoss != nullptr)
  {
    if (m_VentilatorPressureLoss == nullptr)
      m_VentilatorPressureLoss = new SEVentilatorPressureLoss();
    any.set_allocated_ventilatorpressureloss(SEVentilatorPressureLoss::Unload(*vLoss));
    SEVentilatorPressureLoss::Load(any.ventilatorpressureloss(), *m_VentilatorPressureLoss);
    if (!m_VentilatorPressureLoss->IsActive())
      RemoveVentilatorPressureLoss();
    return true;
  }

  const SEYPieceDisconnect* Y = dynamic_cast<const SEYPieceDisconnect*>(&action);
  if (Y != nullptr)
  {
    if (m_YPieceDisconnect == nullptr)
      m_YPieceDisconnect = new SEYPieceDisconnect();
    any.set_allocated_ypiecedisconnect(SEYPieceDisconnect::Unload(*Y));
    SEYPieceDisconnect::Load(any.ypiecedisconnect(), *m_YPieceDisconnect);
    if (!m_YPieceDisconnect->IsActive())
      RemoveYPieceDisconnect();
    return true;
  }
  /// \error Unsupported Action
  Error("Unsupported Action");
  return false;
}

bool SEAnesthesiaMachineActionCollection::HasConfiguration() const
{
  return m_Configuration == nullptr ? false : true;
}
SEAnesthesiaMachineConfiguration* SEAnesthesiaMachineActionCollection::GetConfiguration() const
{
  return m_Configuration;
}
void SEAnesthesiaMachineActionCollection::RemoveConfiguration()
{
  SAFE_DELETE(m_Configuration);
}

bool SEAnesthesiaMachineActionCollection::HasOxygenTankPressureLoss() const
{
  return m_OxygenTankPressureLoss == nullptr ? false : true;
}
SEOxygenTankPressureLoss* SEAnesthesiaMachineActionCollection::GetOxygenTankPressureLoss() const
{
  return m_OxygenTankPressureLoss;
}
void SEAnesthesiaMachineActionCollection::RemoveOxygenTankPressureLoss()
{
  SAFE_DELETE(m_OxygenTankPressureLoss);
}

bool SEAnesthesiaMachineActionCollection::HasOxygenWallPortPressureLoss()
{
  return m_OxygenWallPortPressureLoss == nullptr ? false : true;
}
SEOxygenWallPortPressureLoss* SEAnesthesiaMachineActionCollection::GetOxygenWallPortPressureLoss()
{
  return m_OxygenWallPortPressureLoss;
}
void SEAnesthesiaMachineActionCollection::RemoveOxygenWallPortPressureLoss()
{
  SAFE_DELETE(m_OxygenWallPortPressureLoss);
}

bool SEAnesthesiaMachineActionCollection::HasExpiratoryValveLeak() const
{
  return m_ExpiratoryValveLeak == nullptr ? false : true;
}
SEExpiratoryValveLeak* SEAnesthesiaMachineActionCollection::GetExpiratoryValveLeak() const
{
  return m_ExpiratoryValveLeak;
}
void SEAnesthesiaMachineActionCollection::RemoveExpiratoryValveLeak()
{
  SAFE_DELETE(m_ExpiratoryValveLeak);
}

bool SEAnesthesiaMachineActionCollection::HasExpiratoryValveObstruction() const
{
  return m_ExpiratoryValveObstruction == nullptr ? false : true;
}
SEExpiratoryValveObstruction* SEAnesthesiaMachineActionCollection::GetExpiratoryValveObstruction() const
{
  return m_ExpiratoryValveObstruction;
}
void SEAnesthesiaMachineActionCollection::RemoveExpiratoryValveObstruction()
{
  SAFE_DELETE(m_ExpiratoryValveObstruction);
}

bool SEAnesthesiaMachineActionCollection::HasInspiratoryValveLeak() const
{
  return m_InspiratoryValveLeak == nullptr ? false : true;
}
SEInspiratoryValveLeak* SEAnesthesiaMachineActionCollection::GetInspiratoryValveLeak() const
{
  return m_InspiratoryValveLeak;
}
void SEAnesthesiaMachineActionCollection::RemoveInspiratoryValveLeak()
{
  SAFE_DELETE(m_InspiratoryValveLeak);
}

bool SEAnesthesiaMachineActionCollection::HasInspiratoryValveObstruction() const
{
  return m_InspiratoryValveObstruction == nullptr ? false : true;
}
SEInspiratoryValveObstruction* SEAnesthesiaMachineActionCollection::GetInspiratoryValveObstruction() const
{
  return m_InspiratoryValveObstruction;
}
void SEAnesthesiaMachineActionCollection::RemoveInspiratoryValveObstruction()
{
  SAFE_DELETE(m_InspiratoryValveObstruction);
}

bool SEAnesthesiaMachineActionCollection::HasMaskLeak() const
{
  return m_MaskLeak == nullptr ? false : true;
}
SEMaskLeak* SEAnesthesiaMachineActionCollection::GetMaskLeak() const
{
  return m_MaskLeak;
}
void SEAnesthesiaMachineActionCollection::RemoveMaskLeak()
{
  SAFE_DELETE(m_MaskLeak);
}

bool SEAnesthesiaMachineActionCollection::HasSodaLimeFailure() const
{
  return m_SodaLimeFailure == nullptr ? false : true;
}
SESodaLimeFailure* SEAnesthesiaMachineActionCollection::GetSodaLimeFailure() const
{
  return m_SodaLimeFailure;
}
void SEAnesthesiaMachineActionCollection::RemoveSodaLimeFailure()
{
  SAFE_DELETE(m_SodaLimeFailure);
}

bool SEAnesthesiaMachineActionCollection::HasTubeCuffLeak() const
{
  return m_TubeCuffLeak == nullptr ? false : true;
}
SETubeCuffLeak* SEAnesthesiaMachineActionCollection::GetTubeCuffLeak() const
{
  return m_TubeCuffLeak;
}
void SEAnesthesiaMachineActionCollection::RemoveTubeCuffLeak()
{
  SAFE_DELETE(m_TubeCuffLeak);
}

bool SEAnesthesiaMachineActionCollection::HasVaporizerFailure() const
{
  return m_VaporizerFailure == nullptr ? false : true;
}
SEVaporizerFailure* SEAnesthesiaMachineActionCollection::GetVaporizerFailure() const
{
  return m_VaporizerFailure;
}
void SEAnesthesiaMachineActionCollection::RemoveVaporizerFailure()
{
  SAFE_DELETE(m_VaporizerFailure);
}

bool SEAnesthesiaMachineActionCollection::HasVentilatorPressureLoss() const
{
  return m_VentilatorPressureLoss == nullptr ? false : true;
}
SEVentilatorPressureLoss* SEAnesthesiaMachineActionCollection::GetVentilatorPressureLoss() const
{
  return m_VentilatorPressureLoss;
}
void SEAnesthesiaMachineActionCollection::RemoveVentilatorPressureLoss()
{
  SAFE_DELETE(m_VentilatorPressureLoss);
}

bool SEAnesthesiaMachineActionCollection::HasYPieceDisconnect() const
{
  return m_YPieceDisconnect == nullptr ? false : true;
}
SEYPieceDisconnect* SEAnesthesiaMachineActionCollection::GetYPieceDisconnect() const
{
  return m_YPieceDisconnect;
}
void SEAnesthesiaMachineActionCollection::RemoveYPieceDisconnect()
{
  SAFE_DELETE(m_YPieceDisconnect);
}