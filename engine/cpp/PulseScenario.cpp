/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "PulseScenario.h"
#include <google/protobuf/text_format.h>

PulseScenario::PulseScenario(SESubstanceManager& subMgr) : SEScenario(subMgr)
{
  m_Configuration = nullptr;
}

PulseScenario::~PulseScenario()
{
  Clear();
}

void PulseScenario::Clear()
{
  SEScenario::Clear();
  SAFE_DELETE(m_Configuration);
}

void PulseScenario::Load(const pulse::ScenarioData& src, PulseScenario& dst)
{
  PulseScenario::Serialize(src, dst);
}
void PulseScenario::Serialize(const pulse::ScenarioData& src, PulseScenario& dst)
{
  dst.Clear();
  SEScenario::Serialize(src.scenario(), dst);

  if (src.has_configuration())
    PulseConfiguration::Load(src.configuration(), dst.GetConfiguration());
}

pulse::ScenarioData* PulseScenario::Unload(const PulseScenario& src)
{
  pulse::ScenarioData* dst = new pulse::ScenarioData();
  PulseScenario::Serialize(src, *dst);
  return dst;
}
void PulseScenario::Serialize(const PulseScenario& src, pulse::ScenarioData& dst)
{
  SEScenario::Serialize(src, *dst.mutable_scenario());
  if (src.HasConfiguration())
    dst.set_allocated_configuration(PulseConfiguration::Unload(*src.GetConfiguration()));
}

bool PulseScenario::LoadFile(const std::string& scenarioFile)
{
  pulse::ScenarioData src;
  std::ifstream file_stream(scenarioFile, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  if (google::protobuf::TextFormat::ParseFromString(fmsg, &src))
    PulseScenario::Load(src, *this);
  else // Let's see if this is a cdm scenario
  {
    cdm::ScenarioData sce;
    if (!google::protobuf::TextFormat::ParseFromString(fmsg, &sce))
      return false;//nope
    SEScenario::Load(sce, *this);
  }
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}
bool PulseScenario::Load(const std::string& str)
{
  pulse::ScenarioData src;
  if (google::protobuf::TextFormat::ParseFromString(str, &src))
    PulseScenario::Load(src, *this);
  else // Let's see if this is a cdm scenario
  {
    cdm::ScenarioData sce;
    if (!google::protobuf::TextFormat::ParseFromString(str, &sce))
      return false;//nope
    SEScenario::Load(sce, *this);
  }
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(patientFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

bool PulseScenario::HasConfiguration() const
{
  return m_Configuration != nullptr;
}
PulseConfiguration& PulseScenario::GetConfiguration()
{
  if (m_Configuration == nullptr)
    m_Configuration = new PulseConfiguration(m_SubMgr);
  return *m_Configuration;
}
const PulseConfiguration* PulseScenario::GetConfiguration() const
{
  return m_Configuration;
}
void PulseScenario::InvalidateConfiguration()
{
  SAFE_DELETE(m_Configuration);
}
