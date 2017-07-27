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
  dst.Clear();

  dst.m_ClearCommands = true;
  cdm::ConsciousRespirationData_AnyCommandData* command;
  for (unsigned int i = 0; i < src.command().size(); i++)
  {
    command = (cdm::ConsciousRespirationData_AnyCommandData*)&src.command()[i];

    cdm::ConsciousRespirationData_BreathHoldData* bh = dynamic_cast<cdm::ConsciousRespirationData_BreathHoldData*>(command);
    if (bh != nullptr)
    {
      SEBreathHold::Load(*bh, dst.AddBreathHold());
      continue;
    }

    cdm::ConsciousRespirationData_ForcedInhaleData* fi = dynamic_cast<cdm::ConsciousRespirationData_ForcedInhaleData*>(command);
    if (fi != nullptr)
    {
      SEForcedInhale::Load(*fi, dst.AddForcedInhale());
      continue;
    }

    cdm::ConsciousRespirationData_ForcedExhaleData* fe = dynamic_cast<cdm::ConsciousRespirationData_ForcedExhaleData*>(command);
    if (fe != nullptr)
    {
      SEForcedExhale::Load(*fe, dst.AddForcedExhale());
      continue;
    }

    cdm::ConsciousRespirationData_UseInhalerData* si = dynamic_cast<cdm::ConsciousRespirationData_UseInhalerData*>(command);
    if (si != nullptr)
    {
      SEUseInhaler::Load(*si, dst.AddUseInhaler());
      continue;
    }
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
  dst.appendtoprevious();
  for (SEConsciousRespirationCommand* cmd : src.m_Commands)
  {
    //jbw - How do you do this crap?
    //dst.command().push_back(std::unique_ptr<cdm::ConsciousRespirationData_AnyCommandData>(cmd->Unload()));
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