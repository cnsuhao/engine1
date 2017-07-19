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
#include "system/environment/actions/SEEnvironmentAction.h"

SEEnvironmentAction::SEEnvironmentAction() : SEAction()
{

}

SEEnvironmentAction::~SEEnvironmentAction()
{
  Clear();
}

void SEEnvironmentAction::Clear()
{
  SEAction::Clear();
}

bool SEEnvironmentAction::IsValid() const
{
  return SEAction::IsValid();
}

void SEEnvironmentAction::Load(const cdm::EnvironmentData& src, SEEnvironmentAction& dst)
{
	SEEnvironmentAction::Serialize(src, dst);
}
void SEEnvironmentAction::Serialize(const cdm::EnvironmentData& src, SEEnvironmentAction& dst)
{
	dst.Clear();
}

cdm::EnvironmentData* SEEnvironmentAction::Unload(const SEEnvironmentAction& src)
{
	cdm::EnvironmentData* dst = new cdm::EnvironmentData();
	SEEnvironmentAction::Serialize(src, *dst);
	return dst;
}
void SEEnvironmentAction::Serialize(const SEEnvironmentAction& src, cdm::EnvironmentActionData& dst)
{

}