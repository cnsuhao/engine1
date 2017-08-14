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
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineConfiguration.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachine.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachineChamber.h"
#include "system/equipment/anesthesiamachine/SEAnesthesiaMachineOxygenBottle.h"
#include "substance/SESubstance.h"
#include "substance/SESubstanceManager.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"

SEAnesthesiaMachineConfiguration::SEAnesthesiaMachineConfiguration(SESubstanceManager& substances) : SEAnesthesiaMachineAction(), m_Substances(substances)
{
  m_Configuration = nullptr;
  InvalidateConfigurationFile();
}

SEAnesthesiaMachineConfiguration::~SEAnesthesiaMachineConfiguration()
{
  Clear();
}

void SEAnesthesiaMachineConfiguration::Clear()
{
  SEAnesthesiaMachineAction::Clear();
  InvalidateConfigurationFile();
  SAFE_DELETE(m_Configuration);
}

bool SEAnesthesiaMachineConfiguration::IsValid() const
{
  return SEAnesthesiaMachineAction::IsValid() && (HasConfiguration() || HasConfigurationFile());
}

void SEAnesthesiaMachineConfiguration::Load(const cdm::AnesthesiaMachineConfigurationData& src, SEAnesthesiaMachineConfiguration& dst)
{
  SEAnesthesiaMachineConfiguration::Serialize(src, dst);
}
void SEAnesthesiaMachineConfiguration::Serialize(const cdm::AnesthesiaMachineConfigurationData& src, SEAnesthesiaMachineConfiguration& dst)
{
  SEAnesthesiaMachineAction::Serialize(src.anesthesiamachineaction(), dst);
  if (src.has_configuration())
    SEAnesthesiaMachine::Load(src.configuration(), dst.GetConfiguration());
  else
    dst.SetConfigurationFile(src.configurationfile());
}

cdm::AnesthesiaMachineConfigurationData* SEAnesthesiaMachineConfiguration::Unload(const SEAnesthesiaMachineConfiguration& src)
{
  cdm::AnesthesiaMachineConfigurationData* dst = new cdm::AnesthesiaMachineConfigurationData();
  SEAnesthesiaMachineConfiguration::Serialize(src, *dst);
  return dst;
}
void SEAnesthesiaMachineConfiguration::Serialize(const SEAnesthesiaMachineConfiguration& src, cdm::AnesthesiaMachineConfigurationData& dst)
{
  SEAnesthesiaMachineAction::Serialize(src, *dst.mutable_anesthesiamachineaction());
  if (src.HasConfiguration())
    dst.set_allocated_configuration(SEAnesthesiaMachine::Unload(*src.m_Configuration));
  else if (src.HasConfigurationFile())
    dst.set_configurationfile(src.m_ConfigurationFile);
}

bool SEAnesthesiaMachineConfiguration::HasConfiguration() const
{
  return m_Configuration != nullptr;
}
SEAnesthesiaMachine& SEAnesthesiaMachineConfiguration::GetConfiguration()
{
  m_ConfigurationFile = "";
  if (m_Configuration == nullptr)
    m_Configuration = new SEAnesthesiaMachine(m_Substances);
  return *m_Configuration;
}
const SEAnesthesiaMachine* SEAnesthesiaMachineConfiguration::GetConfiguration() const
{
  return m_Configuration;
}

std::string SEAnesthesiaMachineConfiguration::GetConfigurationFile() const
{
  return m_ConfigurationFile;
}
void SEAnesthesiaMachineConfiguration::SetConfigurationFile(const std::string& fileName)
{
  if (m_Configuration != nullptr)
    SAFE_DELETE(m_Configuration);
  m_ConfigurationFile = fileName;
}
bool SEAnesthesiaMachineConfiguration::HasConfigurationFile() const
{
  return m_ConfigurationFile.empty() ? false : true;
}
void SEAnesthesiaMachineConfiguration::InvalidateConfigurationFile()
{
  m_ConfigurationFile = "";
}


void SEAnesthesiaMachineConfiguration::ToString(std::ostream &str) const
{
  str << "Anesthesia Machine Configuration";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  if (HasConfigurationFile())
    str << "\n\tConfiguration File: "; str << m_ConfigurationFile;
  if (HasConfiguration())
  {
    str << "\n\tConnection: " << m_Configuration->GetConnection();
    str << "\n\tInlet Flow Rate: "; m_Configuration->HasInletFlow() ? str << m_Configuration->GetInletFlow() : str << "NaN";
    str << "\n\tInspiratoryExpiratory Ratio: "; m_Configuration->HasInspiratoryExpiratoryRatio() ? str << m_Configuration->GetInspiratoryExpiratoryRatio() : str << "NaN";
    str << "\n\tOxygen Fraction: "; m_Configuration->HasOxygenFraction() ? str << m_Configuration->GetOxygenFraction() : str << "NaN";
    str << "\n\tOxygen Source: " << m_Configuration->GetOxygenSource();
    str << "\n\tPositive End Expired Pressure: "; m_Configuration->HasPositiveEndExpiredPressure() ? str << m_Configuration->GetPositiveEndExpiredPressure() : str << "NaN";
    str << "\n\tPrimary Gas: " << m_Configuration->GetPrimaryGas();
    str << "\n\tRelief Valve Pressure: "; m_Configuration->HasReliefValvePressure() ? str << m_Configuration->GetReliefValvePressure() : str << "NaN";
    str << "\n\tRespiratory Rate: "; m_Configuration->HasRespiratoryRate() ? str << m_Configuration->GetRespiratoryRate() : str << "NaN";
    str << "\n\tVentilator Pressure: "; m_Configuration->HasVentilatorPressure() ? str << m_Configuration->GetVentilatorPressure() : str << "NaN";
    if (m_Configuration->HasLeftChamber())
    {
      str << "\n\tLeftChamberState: " << m_Configuration->GetLeftChamber().GetState();
      str << "\n\tLeftChamberSubstance: "; m_Configuration->GetLeftChamber().HasSubstance() ? str << m_Configuration->GetLeftChamber().GetSubstance()->GetName() : str << "Not Set";
      str << "\n\tLeftChamberSubstanceAmount: "; m_Configuration->GetLeftChamber().HasSubstanceFraction() ? str << m_Configuration->GetLeftChamber().GetSubstanceFraction() : str << "Not Set";
    }
    if (m_Configuration->HasRightChamber())
    {
      str << "\n\tRightChamberState: " << m_Configuration->GetRightChamber().GetState();
      str << "\n\tRightChamberSubstance: "; m_Configuration->GetRightChamber().HasSubstance() ? str << m_Configuration->GetRightChamber().GetSubstance()->GetName() : str << "Not Set";
      str << "\n\tRightChamberSubstanceAmount: "; m_Configuration->GetRightChamber().HasSubstanceFraction() ? str << m_Configuration->GetRightChamber().GetSubstanceFraction() : str << "Not Set";
    }
    if (m_Configuration->HasOxygenBottleOne())
    {
      str << "\n\tOxygenBottleOneVolume: "; m_Configuration->GetOxygenBottleOne().HasVolume() ? str << m_Configuration->GetOxygenBottleOne().GetVolume() : str << "Not Set";
    }
    if (m_Configuration->HasOxygenBottleTwo())
    {
      str << "\n\tOxygenBottleTwoVolume: "; m_Configuration->GetOxygenBottleTwo().HasVolume() ? str << m_Configuration->GetOxygenBottleTwo().GetVolume() : str << "Not Set";
    }
  }
  str << std::flush;
}

