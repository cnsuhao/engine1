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
#include "patient/actions/SEUrinate.h"

SEUrinate::SEUrinate() : SEPatientAction()
{

}

SEUrinate::~SEUrinate()
{
  Clear();
}

void SEUrinate::Clear()
{
  SEPatientAction::Clear();
}

bool SEUrinate::IsValid() const
{
  return SEPatientAction::IsValid();
}

bool SEUrinate::IsActive() const
{
  return IsValid();
}

void SEUrinate::Load(const cdm::UrinateData& src, SEUrinate& dst)
{
  SEUrinate::Serialize(src, dst);
}
void SEUrinate::Serialize(const cdm::UrinateData& src, SEUrinate& dst)
{
  dst.Clear();
}

cdm::UrinateData* SEUrinate::Unload(const SEUrinate& src)
{
  cdm::UrinateData* dst = new cdm::UrinateData();
  SEUrinate::Serialize(src, *dst);
  return dst;
}
void SEUrinate::Serialize(const SEUrinate& src, cdm::UrinateData& dst)
{

}

void SEUrinate::ToString(std::ostream &str) const
{
  str << "Patient Action : Urinate"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << std::flush;
}
