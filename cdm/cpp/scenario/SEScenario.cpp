/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "scenario/SEScenario.h"
#include <google/protobuf/text_format.h>

SEScenario::SEScenario(SESubstanceManager& subMgr) : Loggable(subMgr.GetLogger()), m_SubMgr(subMgr), m_DataRequestMgr(subMgr.GetLogger())
{
  m_InitialParameters = nullptr;
  Clear();
}

SEScenario::~SEScenario()
{
  Clear();
}

void SEScenario::Clear()
{
  m_Name = "";
  m_Description = "";
  m_EngineStateFile = "";
  SAFE_DELETE(m_InitialParameters);
  DELETE_VECTOR(m_Actions);
  m_DataRequestMgr.Clear();
}

void SEScenario::Load(const cdm::ScenarioData& src, SEScenario& dst)
{
  SEScenario::Serialize(src, dst);
}
void SEScenario::Serialize(const cdm::ScenarioData& src, SEScenario& dst)
{
  dst.Clear();
  dst.SetName(src.name());
  dst.SetDescription(src.description());

  if (src.has_initialparameters())
    SEScenarioInitialParameters::Load(src.initialparameters(), dst.GetInitialParameters());
  else
  {
    dst.SetEngineStateFile(src.enginestatefile());
  }
  
  if (src.has_datarequestmanager())
    SEDataRequestManager::Load(src.datarequestmanager(), dst.GetDataRequestManager(), dst.m_SubMgr);

  for (int i = 0; i<src.anyaction_size(); i++)
      dst.m_Actions.push_back(SEAction::Load(src.anyaction()[i], dst.m_SubMgr));
}

cdm::ScenarioData* SEScenario::Unload(const SEScenario& src)
{
  cdm::ScenarioData* dst = new cdm::ScenarioData();
  SEScenario::Serialize(src,*dst);
  return dst;
}
void SEScenario::Serialize(const SEScenario& src, cdm::ScenarioData& dst)
{
  dst.set_name(src.m_Name);
  dst.set_description(src.m_Description);

  if (src.HasEngineStateFile())
    dst.set_enginestatefile(src.m_EngineStateFile);
  else if (src.HasInitialParameters())
    dst.set_allocated_initialparameters(SEScenarioInitialParameters::Unload(*src.m_InitialParameters));

  dst.set_allocated_datarequestmanager(SEDataRequestManager::Unload(src.m_DataRequestMgr));

  for (SEAction* a :src.m_Actions)
    dst.mutable_anyaction()->AddAllocated(SEAction::Unload(*a));
}

bool SEScenario::LoadFile(const std::string& scenarioFile)
{
  cdm::ScenarioData src;
  std::ifstream file_stream(scenarioFile, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (!google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    return false;
  SEScenario::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

bool SEScenario::IsValid() const
{
  if (HasInitialParameters())
  {
    if (!m_InitialParameters->IsValid())
      return false;
  }
  if(m_Actions.size()==0)
    return false;
  return true;
}

std::string SEScenario::GetName() const
{
  return m_Name;
}
void SEScenario::SetName(const std::string& name)
{
  m_Name = name;
}
bool SEScenario::HasName() const
{
  return m_Name.empty()?false:true;
}
void SEScenario::InvalidateName()
{
  m_Name = "";
}

std::string SEScenario::GetDescription() const
{
  return m_Description;
}
void SEScenario::SetDescription(const std::string& desc)
{
  m_Description = desc;
}
bool SEScenario::HasDescription() const
{
  return m_Description.empty()?false:true;
}
void SEScenario::InvalidateDescription()
{
  m_Description = "";
}

std::string SEScenario::GetEngineStateFile() const
{
  return m_EngineStateFile;
}
void SEScenario::SetEngineStateFile(const std::string& file)
{
  InvalidateInitialParameters();
  m_EngineStateFile = file;
}
bool SEScenario::HasEngineStateFile() const
{
  return m_EngineStateFile.empty() ? false : true;
}
void SEScenario::InvalidateEngineStateFile()
{
  m_EngineStateFile = "";
}

SEScenarioInitialParameters& SEScenario::GetInitialParameters()
{
  InvalidateEngineStateFile();
  if (m_InitialParameters == nullptr)
    m_InitialParameters = new SEScenarioInitialParameters(m_SubMgr);
  return *m_InitialParameters;
}
const SEScenarioInitialParameters* SEScenario::GetInitialParameters() const
{
  return m_InitialParameters;
}
bool SEScenario::HasInitialParameters() const
{
  return m_InitialParameters != nullptr;
}
void SEScenario::InvalidateInitialParameters()
{
  SAFE_DELETE(m_InitialParameters);
}

void SEScenario::AddAction(const SEAction& a)
{
  cdm::AnyActionData* any = SEAction::Unload(a);
  m_Actions.push_back(SEAction::Load(*any, m_SubMgr));
  delete any;
}
const std::vector<SEAction*>& SEScenario::GetActions() const
{
  return m_Actions;
}

