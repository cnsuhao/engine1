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
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

SEAnesthesiaMachineAction::SEAnesthesiaMachineAction() : SEAction()
{

}

SEAnesthesiaMachineAction::~SEAnesthesiaMachineAction()
{
  Clear();
}

void SEAnesthesiaMachineAction::Clear()
{
  SEAction::Clear();
}

bool SEAnesthesiaMachineAction::IsValid() const
{
  return SEAction::IsValid();
}

void SEAnesthesiaMachineAction::Serialize(const cdm::AnesthesiaMachineActionData& src, SEAnesthesiaMachineAction& dst)
{
  dst.Clear();
}

void SEAnesthesiaMachineAction::Serialize(const SEAnesthesiaMachineAction& src, cdm::AnesthesiaMachineActionData& dst)
{

}

#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineConfiguration.h"
#include "system/equipment/anesthesiamachine/actions/SEOxygenWallPortPressureLoss.h"
#include "system/equipment/anesthesiamachine/actions/SEOxygenTankPressureLoss.h"
#include "system/equipment/anesthesiamachine/actions/SEExpiratoryValveLeak.h"
#include "system/equipment/anesthesiamachine/actions/SEExpiratoryValveObstruction.h"
#include "system/equipment/anesthesiamachine/actions/SEInspiratoryValveLeak.h"
#include "system/equipment/anesthesiamachine/actions/SEInspiratoryValveObstruction.h"
#include "system/equipment/anesthesiamachine/actions/SEMaskLeak.h"
#include "system/equipment/anesthesiamachine/actions/SESodaLimeFailure.h"
#include "system/equipment/anesthesiamachine/actions/SETubeCuffLeak.h"
#include "system/equipment/anesthesiamachine/actions/SEVaporizerFailure.h"
#include "system/equipment/anesthesiamachine/actions/SEVentilatorPressureLoss.h"
#include "system/equipment/anesthesiamachine/actions/SEYPieceDisconnect.h"
SEAnesthesiaMachineAction* SEAnesthesiaMachineAction::Load(const cdm::AnyAnesthesiaMachineActionData& any, SESubstanceManager& subMgr)
{
  switch (any.Action_case())
  {
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kConfiguration:
    {
      SEAnesthesiaMachineConfiguration* a = new SEAnesthesiaMachineConfiguration(subMgr);
      SEAnesthesiaMachineConfiguration::Load(any.configuration(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kOxygenTankPressureLoss:
    {
      SEOxygenTankPressureLoss* a = new SEOxygenTankPressureLoss();
      SEOxygenTankPressureLoss::Load(any.oxygentankpressureloss(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kOxygenWallPortPressureLoss:
    {
      SEOxygenWallPortPressureLoss* a = new SEOxygenWallPortPressureLoss();
      SEOxygenWallPortPressureLoss::Load(any.oxygenwallportpressureloss(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kExpiratoryValveLeak:
    {
      SEExpiratoryValveLeak* a = new SEExpiratoryValveLeak();
      SEExpiratoryValveLeak::Load(any.expiratoryvalveleak(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kExpiratoryValveObstruction:
    {
      SEExpiratoryValveObstruction* a = new SEExpiratoryValveObstruction();
      SEExpiratoryValveObstruction::Load(any.expiratoryvalveobstruction(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kInspiratoryValveLeak:
    {
      SEInspiratoryValveLeak* a = new SEInspiratoryValveLeak();
      SEInspiratoryValveLeak::Load(any.inspiratoryvalveleak(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kInspiratoryValveObstruction:
    {
      SEInspiratoryValveObstruction* a = new SEInspiratoryValveObstruction();
      SEInspiratoryValveObstruction::Load(any.inspiratoryvalveobstruction(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kMaskLeak:
    {
      SEMaskLeak* a = new SEMaskLeak();
      SEMaskLeak::Load(any.maskleak(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kSodaLimeFailure:
    {
      SESodaLimeFailure* a = new SESodaLimeFailure();
      SESodaLimeFailure::Load(any.sodalimefailure(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kTubeCuffLeak:
    {
      SETubeCuffLeak* a = new SETubeCuffLeak();
      SETubeCuffLeak::Load(any.tubecuffleak(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kVaporizerFailure:
    {
      SEVaporizerFailure* a = new SEVaporizerFailure();
      SEVaporizerFailure::Load(any.vaporizerfailure(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kVentilatorPressureLoss:
    {
      SEVentilatorPressureLoss* a = new SEVentilatorPressureLoss();
      SEVentilatorPressureLoss::Load(any.ventilatorpressureloss(), *a);
      return a;
    }
    case cdm::AnyAnesthesiaMachineActionData::ActionCase::kYPieceDisconnect:
    {
      SEYPieceDisconnect* a = new SEYPieceDisconnect();
      SEYPieceDisconnect::Load(any.ypiecedisconnect(), *a);
      return a;
    }
  }
  subMgr.Error("Unknown action type : " + any.Action_case());
  return nullptr;
}
cdm::AnyAnesthesiaMachineActionData* SEAnesthesiaMachineAction::Unload(const SEAnesthesiaMachineAction& action)
{
  cdm::AnyAnesthesiaMachineActionData* any = new cdm::AnyAnesthesiaMachineActionData();
  const SEAnesthesiaMachineConfiguration* amc = dynamic_cast<const SEAnesthesiaMachineConfiguration*>(&action);
  if (amc != nullptr)
  {
    any->set_allocated_configuration(SEAnesthesiaMachineConfiguration::Unload(*amc));
    return any;
  }

  const SEOxygenWallPortPressureLoss* owppl = dynamic_cast<const SEOxygenWallPortPressureLoss*>(&action);
  if (owppl != nullptr)
  {
    any->set_allocated_oxygenwallportpressureloss(SEOxygenWallPortPressureLoss::Unload(*owppl));
    return any;
  }

  const SEOxygenTankPressureLoss* otpl = dynamic_cast<const SEOxygenTankPressureLoss*>(&action);
  if (otpl != nullptr)
  {
    any->set_allocated_oxygentankpressureloss(SEOxygenTankPressureLoss::Unload(*otpl));
    return any;
  }

  const SEExpiratoryValveLeak* evl = dynamic_cast<const SEExpiratoryValveLeak*>(&action);
  if (evl != nullptr)
  {
    any->set_allocated_expiratoryvalveleak(SEExpiratoryValveLeak::Unload(*evl));
    return any;
  }

  const SEExpiratoryValveObstruction* evo = dynamic_cast<const SEExpiratoryValveObstruction*>(&action);
  if (evo != nullptr)
  {
    any->set_allocated_expiratoryvalveobstruction(SEExpiratoryValveObstruction::Unload(*evo));
    return any;
  }

  const SEInspiratoryValveLeak* ivl = dynamic_cast<const SEInspiratoryValveLeak*>(&action);
  if (ivl != nullptr)
  {
    any->set_allocated_inspiratoryvalveleak(SEInspiratoryValveLeak::Unload(*ivl));
    return any;
  }

  const SEInspiratoryValveObstruction* ivo = dynamic_cast<const SEInspiratoryValveObstruction*>(&action);
  if (ivo != nullptr)
  {
    any->set_allocated_inspiratoryvalveobstruction(SEInspiratoryValveObstruction::Unload(*ivo));
    return any;
  }

  const SEMaskLeak* ml = dynamic_cast<const SEMaskLeak*>(&action);
  if (ml != nullptr)
  {
    any->set_allocated_maskleak(SEMaskLeak::Unload(*ml));
    return any;
  }

  const SESodaLimeFailure* slf = dynamic_cast<const SESodaLimeFailure*>(&action);
  if (slf != nullptr)
  {
    any->set_allocated_sodalimefailure(SESodaLimeFailure::Unload(*slf));
    return any;
  }

  const SETubeCuffLeak* tcl = dynamic_cast<const SETubeCuffLeak*>(&action);
  if (tcl != nullptr)
  {
    any->set_allocated_tubecuffleak(SETubeCuffLeak::Unload(*tcl));
    return any;
  }

  const SEVaporizerFailure* vf = dynamic_cast<const SEVaporizerFailure*>(&action);
  if (vf != nullptr)
  {
    any->set_allocated_vaporizerfailure(SEVaporizerFailure::Unload(*vf));
    return any;
  }

  const SEVentilatorPressureLoss* vpl = dynamic_cast<const SEVentilatorPressureLoss*>(&action);
  if (vpl != nullptr)
  {
    any->set_allocated_ventilatorpressureloss(SEVentilatorPressureLoss::Unload(*vpl));
    return any;
  }

  const SEYPieceDisconnect* ypd = dynamic_cast<const SEYPieceDisconnect*>(&action);
  if (ypd != nullptr)
  {
    any->set_allocated_ypiecedisconnect(SEYPieceDisconnect::Unload(*ypd));
    return any;
  }
  delete any;
  return nullptr;
}