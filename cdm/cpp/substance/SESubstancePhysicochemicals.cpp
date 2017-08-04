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
#include "substance/SESubstancePhysicochemicals.h"
#include "properties/SEScalar0To1.h"

SESubstancePhysicochemicals::SESubstancePhysicochemicals(Logger* logger) : Loggable(logger)
{
  m_AcidDissociationConstant = nullptr;
  m_BindingProtein = cdm::SubstanceData_eBindingProtein_NullBindingProtein;
  m_BloodPlasmaRatio = nullptr;
  m_FractionUnboundInPlasma = nullptr;
  m_IonicState = cdm::SubstanceData_eIonicState_NullIonicState;
  m_LogP = nullptr;
  m_OralAbsorptionRateConstant = nullptr;
}

SESubstancePhysicochemicals::~SESubstancePhysicochemicals()
{
  Clear();
}

void SESubstancePhysicochemicals::Clear()
{
  SAFE_DELETE(m_AcidDissociationConstant);
  m_BindingProtein = cdm::SubstanceData_eBindingProtein_NullBindingProtein;
  SAFE_DELETE(m_BloodPlasmaRatio);
  SAFE_DELETE(m_FractionUnboundInPlasma);
  m_IonicState = cdm::SubstanceData_eIonicState_NullIonicState;
  SAFE_DELETE(m_LogP);
  SAFE_DELETE(m_OralAbsorptionRateConstant);
}

bool SESubstancePhysicochemicals::IsValid() const
{
  if (!HasAcidDissociationConstant())
    return false;
  if (!HasBindingProtein())
    return false;
  if (!HasBloodPlasmaRatio())
    return false;
  if (!HasFractionUnboundInPlasma())
    return false;
  if (!HasIonicState())
    return false;
  if (!HasLogP())
    return false; 
  return true;
}

const SEScalar* SESubstancePhysicochemicals::GetScalar(const std::string& name)
{
  if (name.compare("AcidDissociationConstant") == 0)
    return &GetAcidDissociationConstant();
  if (name.compare("BloodPlasmaRatio") == 0)
    return &GetBloodPlasmaRatio();
  if (name.compare("FractionUnboundInPlasma") == 0)
    return &GetFractionUnboundInPlasma();
  if (name.compare("LogP") == 0)
    return &GetLogP();
  if (name.compare("OralAbsorptionRateConstant") == 0)
    return &GetOralAbsorptionRateConstant();
  
  return nullptr;
}

void SESubstancePhysicochemicals::Load(const cdm::SubstanceData_PhysicochemicalData& src, SESubstancePhysicochemicals& dst)
{
  SESubstancePhysicochemicals::Serialize(src, dst);
}
void SESubstancePhysicochemicals::Serialize(const cdm::SubstanceData_PhysicochemicalData& src, SESubstancePhysicochemicals& dst)
{
  dst.Clear();
  if (src.has_aciddissociationconstant())
    SEScalar::Load(src.aciddissociationconstant(), dst.GetAcidDissociationConstant());
  dst.SetBindingProtein(src.bindingprotein());
  if (src.has_bloodplasmaratio())
    SEScalar::Load(src.bloodplasmaratio(), dst.GetBloodPlasmaRatio());
  if (src.has_fractionunboundinplasma())
    SEScalar0To1::Load(src.fractionunboundinplasma(), dst.GetFractionUnboundInPlasma());
  dst.SetIonicState(src.ionicstate());
  if (src.has_logp())
    SEScalar::Load(src.logp(), dst.GetLogP());
  if (src.has_oralabsorptionrateconstant())
    SEScalar::Load(src.oralabsorptionrateconstant(), dst.GetOralAbsorptionRateConstant());
}

cdm::SubstanceData_PhysicochemicalData* SESubstancePhysicochemicals::Unload(const SESubstancePhysicochemicals& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::SubstanceData_PhysicochemicalData* dst = new cdm::SubstanceData_PhysicochemicalData();
  SESubstancePhysicochemicals::Serialize(src,*dst);
  return dst;
}
void SESubstancePhysicochemicals::Serialize(const SESubstancePhysicochemicals& src, cdm::SubstanceData_PhysicochemicalData& dst)
{
  if (src.HasAcidDissociationConstant())
    dst.set_allocated_aciddissociationconstant(SEScalar::Unload(*src.m_AcidDissociationConstant));
  if (src.HasBindingProtein())
    dst.set_bindingprotein(src.m_BindingProtein);
  if (src.HasBloodPlasmaRatio())
    dst.set_allocated_bloodplasmaratio(SEScalar::Unload(*src.m_BloodPlasmaRatio));
  if (src.HasFractionUnboundInPlasma())
    dst.set_allocated_fractionunboundinplasma(SEScalar0To1::Unload(*src.m_FractionUnboundInPlasma));
  if (src.HasIonicState())
    dst.set_ionicstate(src.m_IonicState);
  if (src.HasLogP())
    dst.set_allocated_logp(SEScalar::Unload(*src.m_LogP));
  if (src.HasOralAbsorptionRateConstant())
    dst.set_allocated_oralabsorptionrateconstant(SEScalar::Unload(*src.m_OralAbsorptionRateConstant));
}

bool SESubstancePhysicochemicals::HasAcidDissociationConstant() const
{
  return (m_AcidDissociationConstant == nullptr) ? false : m_AcidDissociationConstant->IsValid();
}
SEScalar& SESubstancePhysicochemicals::GetAcidDissociationConstant()
{
  if (m_AcidDissociationConstant == nullptr)
    m_AcidDissociationConstant = new SEScalar();
  return *m_AcidDissociationConstant;
}
double SESubstancePhysicochemicals::GetAcidDissociationConstant() const
{
  if (m_AcidDissociationConstant == nullptr)
    return SEScalar::dNaN();
  return m_AcidDissociationConstant->GetValue();
}

cdm::SubstanceData_eBindingProtein SESubstancePhysicochemicals::GetBindingProtein() const
{
  return m_BindingProtein;
}
void SESubstancePhysicochemicals::SetBindingProtein(cdm::SubstanceData_eBindingProtein protein)
{
  m_BindingProtein = protein;
}
bool SESubstancePhysicochemicals::HasBindingProtein() const
{
  return m_BindingProtein == cdm::SubstanceData_eBindingProtein_NullBindingProtein ? false : true;
}
void SESubstancePhysicochemicals::InvalidateBindingProtein()
{
  m_BindingProtein = cdm::SubstanceData_eBindingProtein_NullBindingProtein;
}

bool SESubstancePhysicochemicals::HasBloodPlasmaRatio() const
{
  return (m_BloodPlasmaRatio == nullptr) ? false : m_BloodPlasmaRatio->IsValid();
}
SEScalar& SESubstancePhysicochemicals::GetBloodPlasmaRatio()
{
  if (m_BloodPlasmaRatio == nullptr)
    m_BloodPlasmaRatio = new SEScalar();
  return *m_BloodPlasmaRatio;
}
double SESubstancePhysicochemicals::GetBloodPlasmaRatio() const
{
  if (m_BloodPlasmaRatio == nullptr)
    return SEScalar::dNaN();
  return m_BloodPlasmaRatio->GetValue();
}

bool SESubstancePhysicochemicals::HasFractionUnboundInPlasma() const
{
  return (m_FractionUnboundInPlasma == nullptr) ? false : m_FractionUnboundInPlasma->IsValid();
}
SEScalar0To1& SESubstancePhysicochemicals::GetFractionUnboundInPlasma()
{
  if (m_FractionUnboundInPlasma == nullptr)
    m_FractionUnboundInPlasma = new SEScalar0To1();
  return *m_FractionUnboundInPlasma;
}
double SESubstancePhysicochemicals::GetFractionUnboundInPlasma() const
{
  if (m_FractionUnboundInPlasma == nullptr)
    return SEScalar::dNaN();
  return m_FractionUnboundInPlasma->GetValue();
}


cdm::SubstanceData_eIonicState SESubstancePhysicochemicals::GetIonicState() const
{
  return m_IonicState;
}
void SESubstancePhysicochemicals::SetIonicState(cdm::SubstanceData_eIonicState state)
{
  m_IonicState = state;
}
bool SESubstancePhysicochemicals::HasIonicState() const
{
  return m_IonicState == cdm::SubstanceData_eIonicState_NullIonicState ? false : true;
}
void SESubstancePhysicochemicals::InvalidateIonicState()
{
  m_IonicState = cdm::SubstanceData_eIonicState_NullIonicState;
}

bool SESubstancePhysicochemicals::HasLogP() const
{
  return (m_LogP == nullptr) ? false : m_LogP->IsValid();
}
SEScalar& SESubstancePhysicochemicals::GetLogP()
{
  if (m_LogP == nullptr)
    m_LogP = new SEScalar();
  return *m_LogP;
}
double SESubstancePhysicochemicals::GetLogP() const
{
  if (m_LogP == nullptr)
    return SEScalar::dNaN();
  return m_LogP->GetValue();
}

bool SESubstancePhysicochemicals::HasOralAbsorptionRateConstant() const
{
  return (m_OralAbsorptionRateConstant == nullptr) ? false : m_OralAbsorptionRateConstant->IsValid();
}
SEScalar& SESubstancePhysicochemicals::GetOralAbsorptionRateConstant()
{
  if (m_OralAbsorptionRateConstant == nullptr)
    m_OralAbsorptionRateConstant = new SEScalar();
  return *m_OralAbsorptionRateConstant;
}
double SESubstancePhysicochemicals::GetOralAbsorptionRateConstant() const
{
  if (m_OralAbsorptionRateConstant == nullptr)
    return SEScalar::dNaN();
  return m_OralAbsorptionRateConstant->GetValue();
}
