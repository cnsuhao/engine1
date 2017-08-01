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
#include "patient/actions/SEConsciousRespiration.h"
#include "patient/actions/SEConsciousRespirationCommand.h"
#include "substance/SESubstanceManager.h"

#include "patient/actions/SEBreathHold.h"
#include "patient/actions/SEForcedExhale.h"
#include "patient/actions/SEForcedInhale.h"
#include "patient/actions/SEUseInhaler.h"

SEConsciousRespiration::SEConsciousRespiration() : SEPatientAction()
{
  m_ClearCommands = true;
}

SEConsciousRespiration::~SEConsciousRespiration()
{
  Clear();
}

void SEConsciousRespiration::Clear()
{
  SEPatientAction::Clear();
  if (m_ClearCommands)
    DELETE_VECTOR(m_Commands);
}

bool SEConsciousRespiration::IsValid() const
{
  return SEPatientAction::IsValid() && !m_Commands.empty();
}

bool SEConsciousRespiration::IsActive() const
{
  return SEPatientAction::IsActive();
}

void SEConsciousRespiration::Load(const cdm::ConsciousRespirationData& src, SEConsciousRespiration& dst)
{
  SEConsciousRespiration::Serialize(src, dst);
}
void SEConsciousRespiration::Serialize(const cdm::ConsciousRespirationData& src, SEConsciousRespiration& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.m_ClearCommands = true;
  ;
  for (int i = 0; i < src.command().size(); i++)
  {
    const cdm::ConsciousRespirationData_AnyCommandData& command = src.command()[i];

    switch (command.Command_case())
    {
    case cdm::ConsciousRespirationData_AnyCommandData::CommandCase::kBreathHold:
      SEBreathHold::Load(command.breathhold(), dst.AddBreathHold());
      break;
    case cdm::ConsciousRespirationData_AnyCommandData::CommandCase::kForcedExhale:
      SEForcedExhale::Load(command.forcedexhale(), dst.AddForcedExhale());
      break;
    case cdm::ConsciousRespirationData_AnyCommandData::CommandCase::kForcedInhale:
      SEForcedInhale::Load(command.forcedinhale(), dst.AddForcedInhale());
      break;
    case cdm::ConsciousRespirationData_AnyCommandData::CommandCase::kUseInhaler:
      SEUseInhaler::Load(command.useinhaler(), dst.AddUseInhaler());
      break;
    default:
      dst.Warning("Ignoring unknown Conscious Respiration Command : " + command.Command_case());
      continue;
    }
    dst.m_Commands.back()->SetComment(command.comment());
  }
}

cdm::ConsciousRespirationData* SEConsciousRespiration::Unload(const SEConsciousRespiration& src)
{
  cdm::ConsciousRespirationData* dst = new cdm::ConsciousRespirationData();
  SEConsciousRespiration::Serialize(src, *dst);
  return dst;
}
void SEConsciousRespiration::Serialize(const SEConsciousRespiration& src, cdm::ConsciousRespirationData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.appendtoprevious();
  for (SEConsciousRespirationCommand* cmd : src.m_Commands)
  {
    cdm::ConsciousRespirationData_AnyCommandData* cmdData = dst.add_command();
    cmdData->set_comment(cmd->GetComment());
    SEBreathHold* bh = dynamic_cast<SEBreathHold*>(cmd);
    if (bh != nullptr)
    {
      cmdData->set_allocated_breathhold(SEBreathHold::Unload(*bh));      
      continue;
    }
    SEForcedExhale* fe = dynamic_cast<SEForcedExhale*>(cmd);
    if (fe != nullptr)
    {
      cmdData->set_allocated_forcedexhale(SEForcedExhale::Unload(*fe));
      continue;
    }
    SEForcedInhale* fi = dynamic_cast<SEForcedInhale*>(cmd);
    if (fi != nullptr)
    {
      cmdData->set_allocated_forcedinhale(SEForcedInhale::Unload(*fi));
      continue;
    }
    SEUseInhaler* ui = dynamic_cast<SEUseInhaler*>(cmd);
    if (ui != nullptr)
    {
      cmdData->set_allocated_useinhaler(SEUseInhaler::Unload(*ui));
      continue;
    }
    src.Warning("The unmapped respiration command in SEConsciousRespiration::Serialize");
  }
}

SEConsciousRespirationCommand* SEConsciousRespiration::GetActiveCommand()
{
  if (!m_Commands.empty())
    return m_Commands[0];
  return nullptr;
}
void SEConsciousRespiration::RemoveActiveCommand()
{
  SEConsciousRespirationCommand* c = GetActiveCommand();
  if (c != nullptr)
  {
    m_Commands.erase(m_Commands.begin());
    SAFE_DELETE(c);
  }
}

SEForcedExhale&  SEConsciousRespiration::AddForcedExhale()
{
    SEForcedExhale* myEx = new SEForcedExhale();
    m_Commands.push_back(myEx);
    return *myEx;
}

SEForcedInhale& SEConsciousRespiration::AddForcedInhale()
{
  SEForcedInhale* myIn = new SEForcedInhale();
  m_Commands.push_back(myIn);
  return *myIn;
}

SEBreathHold& SEConsciousRespiration::AddBreathHold()
{
  SEBreathHold* myHold = new SEBreathHold();
  m_Commands.push_back(myHold);
  return *myHold;
}

SEUseInhaler& SEConsciousRespiration::AddUseInhaler()
{
    SEUseInhaler* myUse = new SEUseInhaler();
    m_Commands.push_back(myUse);
    return *myUse;
}

void SEConsciousRespiration::ToString(std::ostream &str) const
{
  str << "Patient Action : Conscious Respiration";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  for (SEConsciousRespirationCommand* c : m_Commands)
  {
    str << "\n\t";
    c->ToString(str);    
  }
  str << std::flush;
}