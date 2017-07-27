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
#include "patient/actions/SEUseInhaler.h"
#include "substance/SESubstance.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarVolume.h"

SEUseInhaler::SEUseInhaler() : SEConsciousRespirationCommand()
{
  
}

SEUseInhaler::~SEUseInhaler()
{
  Clear();
}

void SEUseInhaler::Clear()
{
  SEConsciousRespirationCommand::Clear();
}

bool SEUseInhaler::IsValid() const
{
  return SEConsciousRespirationCommand::IsValid();
}

bool SEUseInhaler::IsActive() const
{
  return SEConsciousRespirationCommand::IsActive();
}

void SEUseInhaler::Load(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst)
{
  SEUseInhaler::Serialize(src, dst);
}
void SEUseInhaler::Serialize(const cdm::ConsciousRespirationData_UseInhalerData& src, SEUseInhaler& dst)
{
  dst.Clear();
}

cdm::ConsciousRespirationData_UseInhalerData* SEUseInhaler::Unload(const SEUseInhaler& src)
{
  cdm::ConsciousRespirationData_UseInhalerData* dst = new cdm::ConsciousRespirationData_UseInhalerData();
  SEUseInhaler::Serialize(src, *dst);
  return dst;
}
void SEUseInhaler::Serialize(const SEUseInhaler& src, cdm::ConsciousRespirationData_UseInhalerData& dst)
{

}

void SEUseInhaler::ToString(std::ostream &str) const
{
  str << "Use Inhaler";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;  
  str << std::flush;
}