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
#include "scenario/SEInhalerActionCollection.h"
#include "system/equipment/Inhaler/SEInhaler.h"

SEInhalerActionCollection::SEInhalerActionCollection(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
   m_Configuration = nullptr;
}

SEInhalerActionCollection::~SEInhalerActionCollection()
{
  Clear();
}

void SEInhalerActionCollection::Clear()
{
  // State
  RemoveConfiguration();
}

void SEInhalerActionCollection::Serialize(const SEInhalerActionCollection& src, cdm::ActionListData& dst)
{
  if (src.HasConfiguration())
    dst.mutable_anyaction()->AddAllocated(SEAction::Unload(*src.m_Configuration));
}

bool SEInhalerActionCollection::ProcessAction(const SEInhalerAction& action, cdm::AnyInhalerActionData& any)
{
  const SEInhalerConfiguration* config = dynamic_cast<const SEInhalerConfiguration*>(&action);
  if (config != nullptr)
  {
    if (m_Configuration == nullptr)
      m_Configuration = new SEInhalerConfiguration(m_Substances);
    any.set_allocated_configuration(SEInhalerConfiguration::Unload(*config));
    SEInhalerConfiguration::Load(any.configuration(), *m_Configuration);
    if (!m_Configuration->IsActive())
      RemoveConfiguration();
    return true;
  }

  /// \error Unsupported Action
  Error("Unsupported Inhaler Action");
  return false;
}

bool SEInhalerActionCollection::HasConfiguration() const
{
  return m_Configuration == nullptr ? false : true;
}
SEInhalerConfiguration* SEInhalerActionCollection::GetConfiguration() const
{
  return m_Configuration;
}
void SEInhalerActionCollection::RemoveConfiguration()
{
  SAFE_DELETE(m_Configuration);
}
