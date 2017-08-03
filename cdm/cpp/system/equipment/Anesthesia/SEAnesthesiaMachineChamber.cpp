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
#include "system/equipment/Anesthesia/SEAnesthesiaMachineChamber.h"
#include "substance/SESubstance.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalar0To1.h"

SEAnesthesiaMachineChamber::SEAnesthesiaMachineChamber(SESubstanceManager& substances) : Loggable(substances.GetLogger()), m_Substances(substances)
{
  m_State = (cdm::eSwitch)-1;
  m_SubstanceFraction = nullptr;
  m_Substance = nullptr;
}

SEAnesthesiaMachineChamber::~SEAnesthesiaMachineChamber()
{
  Clear();
}

void SEAnesthesiaMachineChamber::Clear()
{
  m_State = (cdm::eSwitch)-1;
  SAFE_DELETE(m_SubstanceFraction);
  m_Substance=nullptr;
}

void SEAnesthesiaMachineChamber::Load(const cdm::AnesthesiaMachineData_ChamberData& src, SEAnesthesiaMachineChamber& dst)
{
  SEAnesthesiaMachineChamber::Serialize(src, dst);
}
void SEAnesthesiaMachineChamber::Serialize(const cdm::AnesthesiaMachineData_ChamberData& src, SEAnesthesiaMachineChamber& dst)
{
  dst.Clear();
  dst.SetState(src.state());
  if (src.has_substancefraction())
    SEScalar0To1::Load(src.substancefraction(), dst.GetSubstanceFraction());
  
  if (src.substance() != nullptr)
  {
    dst.m_Substance = dst.m_Substances.GetSubstance(src.substance());
    if (dst.m_Substance == nullptr)
    {
      dst.Error("Do not have substance : " + src.substance(),"SEAnesthesiaMachineChamber::Serialize");
    }
  }
}

cdm::AnesthesiaMachineData_ChamberData* SEAnesthesiaMachineChamber::Unload(const SEAnesthesiaMachineChamber& src)
{
  cdm::AnesthesiaMachineData_ChamberData* dst = new cdm::AnesthesiaMachineData_ChamberData();
  SEAnesthesiaMachineChamber::Serialize(src, *dst);
  return dst;
}
void SEAnesthesiaMachineChamber::Serialize(const SEAnesthesiaMachineChamber& src, cdm::AnesthesiaMachineData_ChamberData& dst)
{
  if (src.HasState())
    dst.set_state(src.m_State);
  if (src.HasSubstanceFraction())
    dst.set_allocated_substancefraction(SEScalar0To1::Unload(*src.m_SubstanceFraction));
  dst.set_substance(src.m_Substance->GetName());
}

void SEAnesthesiaMachineChamber::Merge(const SEAnesthesiaMachineChamber& from)
{
  if (from.HasState())
    SetState(from.m_State);
  if (from.HasSubstanceFraction())
    GetSubstanceFraction().Set(*from.m_SubstanceFraction);
  if (from.m_Substance != nullptr)
  {
    if (&m_Substances != &from.m_Substances)
    {
      m_Substance = m_Substances.GetSubstance(from.m_Substance->GetName());
      if (m_Substance == nullptr)
      {
        std::stringstream ss;
        ss << "Do not have substance : " << from.m_Substance->GetName();
        Error(ss);
      }
    }
    else
      m_Substance = from.m_Substance;
  }
}

const SEScalar* SEAnesthesiaMachineChamber::GetScalar(const std::string& name)
{
  if (name == "SubstanceFraction")
    return &GetSubstanceFraction();
  return nullptr;
}

cdm::eSwitch SEAnesthesiaMachineChamber::GetState() const
{
  return m_State;
}
void SEAnesthesiaMachineChamber::SetState(cdm::eSwitch state)
{
  m_State = state;
}
bool SEAnesthesiaMachineChamber::HasState() const
{
  return m_State==((cdm::eSwitch)-1)?false:true;
}
void SEAnesthesiaMachineChamber::InvalidateState()
{
  m_State = (cdm::eSwitch)-1;
}

bool SEAnesthesiaMachineChamber::HasSubstanceFraction() const
{
  return m_SubstanceFraction==nullptr?false:m_SubstanceFraction->IsValid();
}
SEScalar0To1& SEAnesthesiaMachineChamber::GetSubstanceFraction()
{
  if(m_SubstanceFraction==nullptr)
    m_SubstanceFraction = new SEScalar0To1();
  return *m_SubstanceFraction;
}
double SEAnesthesiaMachineChamber::GetSubstanceFraction() const
{
  if (m_SubstanceFraction == nullptr)
    return SEScalar::dNaN();
  return m_SubstanceFraction->GetValue();
}

bool SEAnesthesiaMachineChamber::HasSubstance() const
{
  return m_Substance==nullptr?false:true;
}
SESubstance* SEAnesthesiaMachineChamber::GetSubstance() const
{
  return (SESubstance*)m_Substance;
}
void SEAnesthesiaMachineChamber::SetSubstance(const SESubstance& substance)
{
  m_Substance=&substance;
}
void SEAnesthesiaMachineChamber::RemoveSubstance()
{
  m_Substance=nullptr;;
}

void SEAnesthesiaMachineChamber::ToString(std::ostream &str) const
{
  if (m_SubstanceFraction != nullptr)
    str << " Anesthesia Machine Chamber, Substance Fraction" << m_SubstanceFraction
      <<", Substance :"<<GetSubstance()->GetName()<<std::flush;
  else
    str<<"Action not specified properly"<<std::flush;
}
