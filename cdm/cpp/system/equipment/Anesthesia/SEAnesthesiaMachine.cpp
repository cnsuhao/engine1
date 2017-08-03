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
#include "system/equipment/Anesthesia/SEAnesthesiaMachine.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachineChamber.h"
#include "system/equipment/Anesthesia/SEAnesthesiaMachineOxygenBottle.h"
#include "substance/SESubstanceManager.h"

// State Actions
#include "system/equipment/Anesthesia/actions/SEAnesthesiaMachineConfiguration.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarTime.h"
#include "utils/SEEventHandler.h"
#include <google/protobuf/text_format.h>

SEAnesthesiaMachine::SEAnesthesiaMachine(SESubstanceManager& substances) : SESystem(substances.GetLogger()), m_Substances(substances)
{
  m_Connection = (cdm::AnesthesiaMachineData_eConnection) - 1;
  m_InletFlow = nullptr;
  m_InspiratoryExpiratoryRatio = nullptr;
  m_OxygenFraction = nullptr;
  m_OxygenSource = (cdm::AnesthesiaMachineData_eOxygenSource) - 1;
  m_PositiveEndExpiredPressure = nullptr;
  m_PrimaryGas = (cdm::AnesthesiaMachineData_ePrimaryGas) - 1;  
  m_RespiratoryRate = nullptr;
  m_ReliefValvePressure = nullptr;
  m_VentilatorPressure = nullptr;
  m_LeftChamber = nullptr;
  m_RightChamber = nullptr;
  m_OxygenBottleOne = nullptr;
  m_OxygenBottleTwo = nullptr;
  m_EventHandler = nullptr;
}

SEAnesthesiaMachine::~SEAnesthesiaMachine()
{
  Clear();
}

void SEAnesthesiaMachine::Clear()
{
  SESystem::Clear();

  m_EventHandler = nullptr;
  m_EventState.clear();
  m_EventDuration_s.clear();
  m_Connection = (cdm::AnesthesiaMachineData_eConnection) - 1;
  SAFE_DELETE(m_InletFlow);
  SAFE_DELETE(m_InspiratoryExpiratoryRatio);
  SAFE_DELETE(m_OxygenFraction);
  m_OxygenSource = (cdm::AnesthesiaMachineData_eOxygenSource) - 1;
  SAFE_DELETE(m_PositiveEndExpiredPressure);
  m_PrimaryGas = (cdm::AnesthesiaMachineData_ePrimaryGas) - 1;
  SAFE_DELETE(m_RespiratoryRate);
  SAFE_DELETE(m_ReliefValvePressure);
  SAFE_DELETE(m_VentilatorPressure);
  SAFE_DELETE(m_LeftChamber);
  SAFE_DELETE(m_RightChamber);
  SAFE_DELETE(m_OxygenBottleOne);
  SAFE_DELETE(m_OxygenBottleTwo);
}

void SEAnesthesiaMachine::Merge(const SEAnesthesiaMachine& from)
{
  if (from.HasConnection())
    SetConnection(from.m_Connection);
  // Copy EventHandler? I don't think so...
  for (auto e : from.m_EventState)
      m_EventState[e.first] = e.second;
  for (auto e : from.m_EventDuration_s)
      m_EventDuration_s[e.first] = e.second;
  COPY_PROPERTY(InletFlow);
  COPY_PROPERTY(InspiratoryExpiratoryRatio);
  COPY_PROPERTY(OxygenFraction);
  if(from.HasOxygenSource())
    SetOxygenSource(from.m_OxygenSource);
  COPY_PROPERTY(PositiveEndExpiredPressure);
  if(from.HasPrimaryGas())
    SetPrimaryGas(from.m_PrimaryGas);
  COPY_PROPERTY(RespiratoryRate);
  COPY_PROPERTY(ReliefValvePressure);
  COPY_PROPERTY(VentilatorPressure);

  MERGE_CHILD(LeftChamber);
  MERGE_CHILD(RightChamber);
 
  MERGE_CHILD(OxygenBottleOne);
  MERGE_CHILD(OxygenBottleTwo);
}

void SEAnesthesiaMachine::ProcessConfiguration(const SEAnesthesiaMachineConfiguration& config)
{
  if (config.HasConfiguration())
    Merge(*config.GetConfiguration());
  else if (config.HasConfigurationFile())
    if (!LoadFile(config.GetConfigurationFile())) // Does NOT merge file in data, Should we ?
      Error("Unable to load configuration file", "SEAnesthesiaMachine::ProcessConfiguration");
  StateChange();
}

bool SEAnesthesiaMachine::LoadFile(const std::string& anesthesiaMachineFile)
{
  cdm::AnesthesiaMachineData src;
  std::ifstream file_stream(anesthesiaMachineFile, std::ios::in);
  std::string fmsg((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
  google::protobuf::TextFormat::ParseFromString(fmsg, &src);
  SEAnesthesiaMachine::Load(src, *this);
  return true;

  // If its a binary string in the file...
  //std::ifstream binary_istream(AnesthesiaMachineFile, std::ios::in | std::ios::binary);
  //src.ParseFromIstream(&binary_istream);
}

void SEAnesthesiaMachine::Load(const cdm::AnesthesiaMachineData& src, SEAnesthesiaMachine& dst)
{
  SEAnesthesiaMachine::Serialize(src, dst);
}
void SEAnesthesiaMachine::Serialize(const cdm::AnesthesiaMachineData& src, SEAnesthesiaMachine& dst)
{
  dst.Clear();
  dst.SetConnection(src.connection());
  if(src.has_inlet_flow())
    SEScalarVolumePerTime::Load(src.inlet_flow(), dst.GetInletFlow());
  if (src.has_inspiratoryexpiratoryratio())
    SEScalar::Load(src.inspiratoryexpiratoryratio(), dst.GetInspiratoryExpiratoryRatio());
  if (src.has_oxygenfraction())
    SEScalar0To1::Load(src.oxygenfraction(), dst.GetOxygenFraction());

  dst.SetOxygenSource(src.oxygensource());
  if (src.has_positiveendexpiredpressure())
    SEScalarPressure::Load(src.positiveendexpiredpressure(), dst.GetPositiveEndExpiredPressure());
  dst.SetPrimaryGas(src.primarygas());

  if (src.has_respiratoryrate())
    SEScalarFrequency::Load(src.respiratoryrate(), dst.GetRespiratoryRate());
  if (src.has_reliefvalvepressure())
    SEScalarPressure::Load(src.reliefvalvepressure(), dst.GetReliefValvePressure());
  if (src.has_ventilatorpressure())
    SEScalarPressure::Load(src.ventilatorpressure(), dst.GetVentilatorPressure());
  if (src.has_leftchamber())
    SEAnesthesiaMachineChamber::Load(src.leftchamber(), dst.GetLeftChamber());
  if (src.has_rightchamber())
    SEAnesthesiaMachineChamber::Load(src.rightchamber(), dst.GetRightChamber());
  if (src.has_oxygenbottleone())
    SEAnesthesiaMachineOxygenBottle::Load(src.oxygenbottleone(), dst.GetOxygenBottleOne());
  if (src.has_oxygenbottletwo())
    SEAnesthesiaMachineOxygenBottle::Load(src.oxygenbottletwo(), dst.GetOxygenBottleTwo());

  SEScalarTime time;
  for (int i = 0; i < src.activeevent_size(); i++)
  {
    const cdm::AnesthesiaMachineData::ActiveEventData& e = src.activeevent(i);
    if (e.has_duration())
      SEScalarTime::Load(e.duration(), time);
    {
      dst.m_ss << "Active AnesthesiaMachine event " << e.event() << " does not have time associated with it";
      dst.Warning(dst.m_ss);
      time.SetValue(0, TimeUnit::s);
    }
    dst.m_EventState[e.event()] = true;
    dst.m_EventDuration_s[e.event()] = time.GetValue(TimeUnit::s);
  }

  dst.StateChange();
}

cdm::AnesthesiaMachineData* SEAnesthesiaMachine::Unload(const SEAnesthesiaMachine& src)
{
  cdm::AnesthesiaMachineData* dst = new cdm::AnesthesiaMachineData();
  SEAnesthesiaMachine::Serialize(src, *dst);
  return dst;
}
void SEAnesthesiaMachine::Serialize(const SEAnesthesiaMachine& src, cdm::AnesthesiaMachineData& dst)
{
  if (src.HasConnection())
    dst.set_connection(src.m_Connection);
  if (src.HasInletFlow())
    dst.set_allocated_inlet_flow(SEScalarVolumePerTime::Unload(*src.m_InletFlow));
  if (src.HasInspiratoryExpiratoryRatio())
    dst.set_allocated_inspiratoryexpiratoryratio(SEScalar::Unload(*src.m_InspiratoryExpiratoryRatio));
  if (src.HasOxygenFraction())
    dst.set_allocated_oxygenfraction(SEScalar0To1::Unload(*src.m_OxygenFraction));

  if (src.HasOxygenSource())
    dst.set_oxygensource(src.m_OxygenSource);
  if (src.HasPositiveEndExpiredPressure())
    dst.set_allocated_positiveendexpiredpressure(SEScalarPressure::Unload(*src.m_PositiveEndExpiredPressure));
  if (src.HasPrimaryGas())
    dst.set_primarygas(src.m_PrimaryGas);

  if (src.HasRespiratoryRate())
    dst.set_allocated_respiratoryrate(SEScalarFrequency::Unload(*src.m_RespiratoryRate));
  if (src.HasReliefValvePressure())
    dst.set_allocated_reliefvalvepressure(SEScalarPressure::Unload(*src.m_ReliefValvePressure));
  if (src.HasVentilatorPressure())
    dst.set_allocated_ventilatorpressure(SEScalarPressure::Unload(*src.m_VentilatorPressure));
  if (src.HasLeftChamber())
    dst.set_allocated_leftchamber(SEAnesthesiaMachineChamber::Unload(*src.m_LeftChamber));
  if (src.HasRightChamber())
    dst.set_allocated_rightchamber(SEAnesthesiaMachineChamber::Unload(*src.m_RightChamber));
  if (src.HasOxygenBottleOne())
    dst.set_allocated_oxygenbottleone(SEAnesthesiaMachineOxygenBottle::Unload(*src.m_OxygenBottleOne));
  if (src.HasOxygenBottleTwo())
    dst.set_allocated_oxygenbottletwo(SEAnesthesiaMachineOxygenBottle::Unload(*src.m_OxygenBottleTwo));

  SEScalarTime time;
  for (auto itr : src.m_EventState)
  {
    if (!itr.second)
      continue;

    auto it2 = src.m_EventDuration_s.find(itr.first);
    if (it2 == src.m_EventDuration_s.end())// This should not happen... 
      time.SetValue(0, TimeUnit::s);
    else
      time.SetValue(it2->second, TimeUnit::s);

    cdm::AnesthesiaMachineData_ActiveEventData* eData = dst.add_activeevent();

    eData->set_event(itr.first);
    eData->set_allocated_duration(SEScalarTime::Unload(time));
  }
}

const SEScalar* SEAnesthesiaMachine::GetScalar(const std::string& name)
{
  if (name == "InletFlow")
    return &GetInletFlow();
  if (name == "InspiratoryExpiratoryRatio")
    return &GetInspiratoryExpiratoryRatio();
  if (name == "OxygenFraction")
    return &GetOxygenFraction();
  if (name == "PositiveEndExpiredPressure")
    return &GetPositiveEndExpiredPressure();
  if (name == "ReliefValvePressure")
    return &GetReliefValvePressure();
  if (name == "RespiratoryRate")
    return &GetRespiratoryRate();
  if (name == "VentilatorPressure")
    return &GetVentilatorPressure();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == "LeftChamber")
      return GetLeftChamber().GetScalar(prop);
    if (child == "RightChamber")
      return GetRightChamber().GetScalar(prop);
    if (child == "OxygenBottleOne")
      return GetOxygenBottleOne().GetScalar(prop);
    if (child == "OxygenBottleTwo")
      return GetOxygenBottleTwo().GetScalar(prop);
  }

  return nullptr;
}

void SEAnesthesiaMachine::SetEvent(cdm::AnesthesiaMachineData_eEvent type, bool active, const SEScalarTime& time)
{
  bool b = false;// Default is off
  if (m_EventState.find(type) != m_EventState.end())
    b = m_EventState[type];
  if (b == active)
    return;//No Change
  if (active != b)
  {
    m_ss.str("");
    m_ss << "[Event] " << time << ", ";
    if (active)
    {
      switch (type)
      {        
      case cdm::AnesthesiaMachineData_eEvent_OxygenBottleOneExhausted:
        m_ss << "Oxygen Bottle 1 has been exhausted";
        break;
      case cdm::AnesthesiaMachineData_eEvent_OxygenBottleTwoExhausted:
        m_ss << "Oxygen Bottle 2 has been exhausted";
        break;
      case cdm::AnesthesiaMachineData_eEvent_ReliefValveActive:
        m_ss << "Relief valve active - pressure exceeded";
        break;
      default:
        m_ss << "Anesthesia Machine Event On : " << type;//TODO CDM::enumAnesthesiaMachineEvent::_xsd_enumAnesthesiaMachineEvent_literals_[type];
      }
    }
    else
    {
      switch (type)
      {
      case cdm::AnesthesiaMachineData_eEvent_OxygenBottleOneExhausted:
        m_ss << "Oxygen Bottle 1 has been replenished";
        break;
      case cdm::AnesthesiaMachineData_eEvent_OxygenBottleTwoExhausted:
        m_ss << "Oxygen Bottle 2 has been replenished";
        break;
      case cdm::AnesthesiaMachineData_eEvent_ReliefValveActive:
        m_ss << "Relief valve inactive - pressure below setting";
        break;
      default:
        m_ss << "Anesthesia Machine Event Off : " << type;// TODO CDM::enumAnesthesiaMachineEvent::_xsd_enumAnesthesiaMachineEvent_literals_[type];
      }
    }
    Info(m_ss);
  }
  m_EventState[type] = active;
  m_EventDuration_s[type] = 0;
  if (m_EventHandler != nullptr)
    m_EventHandler->HandleAnesthesiaMachineEvent(type, active, &time);
}

bool SEAnesthesiaMachine::IsEventActive(cdm::AnesthesiaMachineData_eEvent type) const
{
  auto b = m_EventState.find(type);
  if (b == m_EventState.end())
    return false;
  return b->second;
}

double SEAnesthesiaMachine::GetEventDuration(cdm::AnesthesiaMachineData_eEvent type, const TimeUnit& unit) const
{
  auto i = m_EventDuration_s.find(type);
  if (i == m_EventDuration_s.end())
    return 0;
  return Convert(i->second, TimeUnit::s, unit);
}

void SEAnesthesiaMachine::UpdateEvents(const SEScalarTime& timeStep)
{
  for (auto itr : m_EventDuration_s)
    itr.second += timeStep.GetValue(TimeUnit::s);
}

void SEAnesthesiaMachine::ForwardEvents(SEEventHandler* handler)
{
  m_EventHandler = handler;
}

void SEAnesthesiaMachine::SetConnection(cdm::AnesthesiaMachineData_eConnection c)
{
  m_Connection = c;
}
bool SEAnesthesiaMachine::HasConnection() const
{
  return m_Connection == ((cdm::AnesthesiaMachineData_eConnection) - 1) ? false : true;
}
cdm::AnesthesiaMachineData_eConnection SEAnesthesiaMachine::GetConnection() const
{
  return m_Connection;
}
void SEAnesthesiaMachine::InvalidateConnection()
{
  m_Connection = (cdm::AnesthesiaMachineData_eConnection) - 1;
}

bool SEAnesthesiaMachine::HasInletFlow() const
{
  return m_InletFlow == nullptr ? false : m_InletFlow->IsValid();
}
SEScalarVolumePerTime& SEAnesthesiaMachine::GetInletFlow()
{
  if (m_InletFlow == nullptr)
    m_InletFlow = new SEScalarVolumePerTime();
  return *m_InletFlow;
}
double SEAnesthesiaMachine::GetInletFlow(const VolumePerTimeUnit& unit) const
{
  if (m_InletFlow == nullptr)
    return SEScalar::dNaN();
  return m_InletFlow->GetValue(unit);
}

bool SEAnesthesiaMachine::HasInspiratoryExpiratoryRatio() const
{
  return m_InspiratoryExpiratoryRatio == nullptr ? false : m_InspiratoryExpiratoryRatio->IsValid();
}
SEScalar& SEAnesthesiaMachine::GetInspiratoryExpiratoryRatio()
{
  if (m_InspiratoryExpiratoryRatio == nullptr)
    m_InspiratoryExpiratoryRatio = new SEScalar();
  return *m_InspiratoryExpiratoryRatio;
}
double SEAnesthesiaMachine::GetInspiratoryExpiratoryRatio() const
{
  if (m_InspiratoryExpiratoryRatio == nullptr)
    return SEScalar::dNaN();
  return m_InspiratoryExpiratoryRatio->GetValue();
}

bool SEAnesthesiaMachine::HasOxygenFraction() const
{
  return m_OxygenFraction == nullptr ? false : m_OxygenFraction->IsValid();
}
SEScalar0To1& SEAnesthesiaMachine::GetOxygenFraction()
{
  if (m_OxygenFraction == nullptr)
    m_OxygenFraction = new SEScalar0To1();
  return *m_OxygenFraction;
}
double SEAnesthesiaMachine::GetOxygenFraction() const
{
  if (m_OxygenFraction == nullptr)
    return SEScalar::dNaN();
  return m_OxygenFraction->GetValue();
}

cdm::AnesthesiaMachineData_eOxygenSource SEAnesthesiaMachine::GetOxygenSource() const
{
  return m_OxygenSource;
}
void SEAnesthesiaMachine::SetOxygenSource(cdm::AnesthesiaMachineData_eOxygenSource src)
{
  m_OxygenSource = src;
}
bool SEAnesthesiaMachine::HasOxygenSource() const
{
  return m_OxygenSource == ((cdm::AnesthesiaMachineData_eOxygenSource) - 1) ? false : true;
}
void SEAnesthesiaMachine::InvalidateOxygenSource()
{
  m_OxygenSource = (cdm::AnesthesiaMachineData_eOxygenSource) - 1;
}

bool SEAnesthesiaMachine::HasPositiveEndExpiredPressure() const
{
  return m_PositiveEndExpiredPressure == nullptr ? false : m_PositiveEndExpiredPressure->IsValid();
}
SEScalarPressure& SEAnesthesiaMachine::GetPositiveEndExpiredPressure()
{
  if (m_PositiveEndExpiredPressure == nullptr)
    m_PositiveEndExpiredPressure = new SEScalarPressure();
  return *m_PositiveEndExpiredPressure;
}
double SEAnesthesiaMachine::GetPositiveEndExpiredPressure(const PressureUnit& unit) const
{
  if (m_PositiveEndExpiredPressure == nullptr)
    return SEScalar::dNaN();
  return m_PositiveEndExpiredPressure->GetValue(unit);
}

cdm::AnesthesiaMachineData_ePrimaryGas SEAnesthesiaMachine::GetPrimaryGas() const
{
  return m_PrimaryGas;
}
void SEAnesthesiaMachine::SetPrimaryGas(cdm::AnesthesiaMachineData_ePrimaryGas gas)
{
  m_PrimaryGas = gas;
}
bool SEAnesthesiaMachine::HasPrimaryGas() const
{
  return m_PrimaryGas == ((cdm::AnesthesiaMachineData_ePrimaryGas) - 1) ? false : true;
}
void SEAnesthesiaMachine::InvalidatePrimaryGas()
{
  m_PrimaryGas = (cdm::AnesthesiaMachineData_ePrimaryGas) - 1;
}

bool SEAnesthesiaMachine::HasRespiratoryRate() const
{
  return m_RespiratoryRate == nullptr ? false : m_RespiratoryRate->IsValid();
}
SEScalarFrequency& SEAnesthesiaMachine::GetRespiratoryRate()
{
  if (m_RespiratoryRate == nullptr)
    m_RespiratoryRate = new SEScalarFrequency();
  return *m_RespiratoryRate;
}
double SEAnesthesiaMachine::GetRespiratoryRate(const FrequencyUnit& unit) const
{
  if (m_RespiratoryRate == nullptr)
    return SEScalar::dNaN();
  return m_RespiratoryRate->GetValue(unit);
}

bool SEAnesthesiaMachine::HasReliefValvePressure() const
{
  return m_ReliefValvePressure == nullptr ? false : m_ReliefValvePressure->IsValid();
}
SEScalarPressure& SEAnesthesiaMachine::GetReliefValvePressure()
{
  if (m_ReliefValvePressure == nullptr)
    m_ReliefValvePressure = new SEScalarPressure();
  return *m_ReliefValvePressure;
}
double SEAnesthesiaMachine::GetReliefValvePressure(const PressureUnit& unit) const
{
  if (m_ReliefValvePressure == nullptr)
    return SEScalar::dNaN();
  return m_ReliefValvePressure->GetValue(unit);
}

bool SEAnesthesiaMachine::HasVentilatorPressure() const
{
  return m_VentilatorPressure == nullptr ? false : m_VentilatorPressure->IsValid();
}
SEScalarPressure& SEAnesthesiaMachine::GetVentilatorPressure()
{
  if (m_VentilatorPressure == nullptr)
    m_VentilatorPressure = new SEScalarPressure();
  return *m_VentilatorPressure;
}
double SEAnesthesiaMachine::GetVentilatorPressure(const PressureUnit& unit) const
{
  if (m_VentilatorPressure == nullptr)
    return SEScalar::dNaN();
  return m_VentilatorPressure->GetValue(unit);
}

bool SEAnesthesiaMachine::HasLeftChamber() const
{
  return m_LeftChamber == nullptr ? false : true;
}
SEAnesthesiaMachineChamber& SEAnesthesiaMachine::GetLeftChamber()
{
  if (m_LeftChamber == nullptr)
    m_LeftChamber = new SEAnesthesiaMachineChamber(m_Substances);
  return *m_LeftChamber;
}
const SEAnesthesiaMachineChamber* SEAnesthesiaMachine::GetLeftChamber() const
{
  return m_LeftChamber;
}
void SEAnesthesiaMachine::RemoveLeftChamber()
{
  SAFE_DELETE(m_LeftChamber);
}

bool SEAnesthesiaMachine::HasRightChamber() const
{
  return m_RightChamber == nullptr ? false : true;
}
SEAnesthesiaMachineChamber& SEAnesthesiaMachine::GetRightChamber()
{
  if (m_RightChamber == nullptr)
    m_RightChamber = new SEAnesthesiaMachineChamber(m_Substances);
  return *m_RightChamber;
}
const SEAnesthesiaMachineChamber* SEAnesthesiaMachine::GetRightChamber() const
{
  return m_RightChamber;
}
void SEAnesthesiaMachine::RemoveRightChamber()
{
  SAFE_DELETE(m_RightChamber);
}

bool SEAnesthesiaMachine::HasOxygenBottleOne() const
{
  return m_OxygenBottleOne == nullptr ? false : true;
}
SEAnesthesiaMachineOxygenBottle& SEAnesthesiaMachine::GetOxygenBottleOne()
{
  if (m_OxygenBottleOne == nullptr)
    m_OxygenBottleOne = new SEAnesthesiaMachineOxygenBottle(GetLogger());
  return *m_OxygenBottleOne;
}
const SEAnesthesiaMachineOxygenBottle* SEAnesthesiaMachine::GetOxygenBottleOne() const
{
  return m_OxygenBottleOne;
}
void SEAnesthesiaMachine::RemoveOxygenBottleOne()
{
  SAFE_DELETE(m_OxygenBottleOne);
}

bool SEAnesthesiaMachine::HasOxygenBottleTwo() const
{
  return m_OxygenBottleTwo == nullptr ? false : true;
}
SEAnesthesiaMachineOxygenBottle& SEAnesthesiaMachine::GetOxygenBottleTwo()
{
  if (m_OxygenBottleTwo == nullptr)
    m_OxygenBottleTwo = new SEAnesthesiaMachineOxygenBottle(GetLogger());
  return *m_OxygenBottleTwo;
}
const SEAnesthesiaMachineOxygenBottle* SEAnesthesiaMachine::GetOxygenBottleTwo() const
{
  return m_OxygenBottleTwo;
}
void SEAnesthesiaMachine::RemoveOxygenBottleTwo()
{
  SAFE_DELETE(m_OxygenBottleTwo);
}
