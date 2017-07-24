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
#include "patient/actions/SEConsciousRespirationCommand.h"

SEConsciousRespirationCommand::SEConsciousRespirationCommand()
{
  m_Comment = "";
}

SEConsciousRespirationCommand::~SEConsciousRespirationCommand()
{
  Clear();
}

void SEConsciousRespirationCommand::Clear()
{
  m_Comment = "";
}

void SEConsciousRespirationCommand::Load(const cdm::ConsciousRespirationData_AnyCommandData& src, SEConsciousRespirationCommand& dst)
{
  SEConsciousRespirationCommand::Serialize(src, dst);
}
void SEConsciousRespirationCommand::Serialize(const cdm::ConsciousRespirationData_AnyCommandData& src, SEConsciousRespirationCommand& dst)
{
  dst.Clear();
  //jbw - do I need to do something about comment?
}

cdm::ConsciousRespirationData_AnyCommandData* SEConsciousRespirationCommand::Unload(const SEConsciousRespirationCommand& src)
{
  cdm::ConsciousRespirationData_AnyCommandData* dst = new cdm::ConsciousRespirationData_AnyCommandData();
  SEConsciousRespirationCommand::Serialize(src, *dst);
  return dst;
}
void SEConsciousRespirationCommand::Serialize(const SEConsciousRespirationCommand& src, cdm::ConsciousRespirationData_AnyCommandData& dst)
{
  //jbw - do I need to do something about comment?
}

bool SEConsciousRespirationCommand::IsValid() const
{
  return true;
}

bool SEConsciousRespirationCommand::IsActive() const
{
  return true;
}

std::string SEConsciousRespirationCommand::GetComment() const
{
  return m_Comment;
}
void SEConsciousRespirationCommand::SetComment(const std::string& comment)
{
  m_Comment = comment;
}
bool SEConsciousRespirationCommand::HasComment() const
{
  return m_Comment.empty() ? false : true;
}
void SEConsciousRespirationCommand::InvalidateComment()
{
  m_Comment = "";
}


