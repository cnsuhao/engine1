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
#include "SEDataRequestManager.h"
#include "substance/SESubstanceManager.h"

SEDataRequestManager::SEDataRequestManager(Logger* logger) : Loggable(logger)
{
  m_DefaultDecimalFormatting = nullptr;
  m_OverrideDecimalFormatting = nullptr;
  Clear();
}

SEDataRequestManager::~SEDataRequestManager()
{
  Clear();
}

void SEDataRequestManager::Clear()
{
  m_SamplesPerSecond = 0; // Sample every time step
  DELETE_VECTOR(m_Requests);
  SAFE_DELETE(m_DefaultDecimalFormatting);
  SAFE_DELETE(m_OverrideDecimalFormatting);
}

void SEDataRequestManager::Load(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr)
{

}
void SEDataRequestManager::Serialize(const cdm::DataRequestManagerData& src, SEDataRequestManager& dst, SESubstanceManager& subMgr)
{
  dst.Clear();
  dst.m_ResultsFilename = src.resultsfilename();
  dst.m_SamplesPerSecond = src.samplespersecond();
  if (src.has_defaultdecimalformatting())
    SEDecimalFormat::Load(src.defaultdecimalformatting(),dst.GetDefaultDecimalFormatting());
  if (src.has_overridedecimalformatting())
    SEDecimalFormat::Load(src.overridedecimalformatting(), dst.GetOverrideDecimalFormatting());

  for (int i=0; i<src.datarequest_size(); i++)
  {
    const cdm::DataRequestData& drData = src.datarequest(i);
    SEDataRequest* dr = new SEDataRequest(drData.category(), dst.HasOverrideDecimalFormatting() ? dst.m_OverrideDecimalFormatting : dst.m_DefaultDecimalFormatting);
    SEDataRequest::Load(drData, *dr);
    if (!dr->IsValid())
      dst.Error("Ignoring invalid DataRequest for property " + dr->m_PropertyName);
    else
      dst.m_Requests.push_back(dr);
  }
}

cdm::DataRequestManagerData* SEDataRequestManager::Unload(const SEDataRequestManager& src)
{
  cdm::DataRequestManagerData* dst = new cdm::DataRequestManagerData();
  SEDataRequestManager::Serialize(src,*dst);
  return dst;
}
void SEDataRequestManager::Serialize(const SEDataRequestManager& src, cdm::DataRequestManagerData& dst)
{
  dst.set_resultsfilename(src.m_ResultsFilename);
  dst.set_samplespersecond(src.m_SamplesPerSecond);
  if (src.HasDefaultDecimalFormatting())
    dst.set_allocated_defaultdecimalformatting(SEDecimalFormat::Unload(*src.m_DefaultDecimalFormatting));
  if (src.HasOverrideDecimalFormatting())
    dst.set_allocated_overridedecimalformatting(SEDecimalFormat::Unload(*src.m_OverrideDecimalFormatting));
  for (SEDataRequest* dr : src.m_Requests)
    dst.mutable_datarequest()->AddAllocated(SEDataRequest::Unload(*dr));
}

bool SEDataRequestManager::HasDefaultDecimalFormatting() const
{
  return m_DefaultDecimalFormatting != nullptr;
}
SEDecimalFormat& SEDataRequestManager::GetDefaultDecimalFormatting()
{
  if (m_DefaultDecimalFormatting == nullptr)
    m_DefaultDecimalFormatting = new SEDecimalFormat();
  return *m_DefaultDecimalFormatting;
}
void SEDataRequestManager::RemoveDefaultDecimalFormatting()
{
  SAFE_DELETE(m_DefaultDecimalFormatting);
}

bool SEDataRequestManager::HasOverrideDecimalFormatting() const
{
  return m_OverrideDecimalFormatting != nullptr;
}
SEDecimalFormat& SEDataRequestManager::GetOverrideDecimalFormatting()
{
  if (m_OverrideDecimalFormatting == nullptr)
    m_OverrideDecimalFormatting = new SEDecimalFormat();
  return *m_OverrideDecimalFormatting;
}
void SEDataRequestManager::RemoveOverrideDecimalFormatting()
{
  SAFE_DELETE(m_OverrideDecimalFormatting);
}
