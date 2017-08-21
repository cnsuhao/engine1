/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "system/physiology/SENervousSystem.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarPressurePerVolume.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarLength.h"

SENervousSystem::SENervousSystem(Logger* logger) : SESystem(logger)
{
  m_BaroreceptorHeartRateScale = nullptr;
  m_BaroreceptorHeartElastanceScale = nullptr;
  m_BaroreceptorResistanceScale = nullptr;
  m_BaroreceptorComplianceScale = nullptr;
  m_ChemoreceptorHeartRateScale = nullptr;
  m_ChemoreceptorHeartElastanceScale = nullptr;
  m_LeftEyePupillaryResponse = nullptr;
  m_RightEyePupillaryResponse = nullptr;
}

SENervousSystem::~SENervousSystem()
{
  Clear();
}

void SENervousSystem::Clear()
{
  SESystem::Clear();
  SAFE_DELETE(m_BaroreceptorHeartRateScale);
  SAFE_DELETE(m_BaroreceptorHeartElastanceScale);
  SAFE_DELETE(m_BaroreceptorResistanceScale);
  SAFE_DELETE(m_BaroreceptorComplianceScale);
  SAFE_DELETE(m_ChemoreceptorHeartRateScale);
  SAFE_DELETE(m_ChemoreceptorHeartElastanceScale);
  SAFE_DELETE(m_LeftEyePupillaryResponse);
  SAFE_DELETE(m_RightEyePupillaryResponse);
}

const SEScalar* SENervousSystem::GetScalar(const std::string& name)
{
  if (name.compare("BaroreceptorHeartRateScale") == 0)
    return &GetBaroreceptorHeartRateScale();
  if (name.compare("BaroreceptorHeartElastanceScale") == 0)
    return &GetBaroreceptorHeartElastanceScale();
  if (name.compare("BaroreceptorResistanceScale") == 0)
    return &GetBaroreceptorResistanceScale();
  if (name.compare("BaroreceptorComplianceScale") == 0)
    return &GetBaroreceptorComplianceScale();
  if (name.compare("ChemoreceptorHeartRateScale") == 0)
    return &GetChemoreceptorHeartRateScale();
  if (name.compare("ChemoreceptorHeartElastanceScale") == 0)
    return &GetChemoreceptorHeartElastanceScale();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop  = name.substr(split+1, name.npos);
    if (child == "LeftEyePupillaryResponse")
      return GetLeftEyePupillaryResponse().GetScalar(prop);
    if (child == "RightEyePupillaryResponse")
      return GetRightEyePupillaryResponse().GetScalar(prop);
  }
  return nullptr;
}

void SENervousSystem::Load(const cdm::NervousSystemData& src, SENervousSystem& dst)
{
  SENervousSystem::Serialize(src, dst);
}
void SENervousSystem::Serialize(const cdm::NervousSystemData& src, SENervousSystem& dst)
{
  dst.Clear();
  if (src.has_baroreceptorheartratescale())
    SEScalar::Load(src.baroreceptorheartratescale(), dst.GetBaroreceptorHeartRateScale());
  if (src.has_baroreceptorheartelastancescale())
    SEScalar::Load(src.baroreceptorheartelastancescale(), dst.GetBaroreceptorHeartElastanceScale());
  if (src.has_baroreceptorresistancescale())
    SEScalar::Load(src.baroreceptorresistancescale(), dst.GetBaroreceptorResistanceScale());
  if (src.has_baroreceptorcompliancescale())
    SEScalar::Load(src.baroreceptorcompliancescale(), dst.GetBaroreceptorComplianceScale());
  if (src.has_chemoreceptorheartratescale())
    SEScalar::Load(src.chemoreceptorheartratescale(), dst.GetChemoreceptorHeartRateScale());
  if (src.has_chemoreceptorheartelastancescale())
    SEScalar::Load(src.chemoreceptorheartelastancescale(), dst.GetChemoreceptorHeartElastanceScale());
  if (src.has_lefteyepupillaryresponse())
    SEPupillaryResponse::Load(src.lefteyepupillaryresponse(), dst.GetLeftEyePupillaryResponse());
  if (src.has_righteyepupillaryresponse())
    SEPupillaryResponse::Load(src.righteyepupillaryresponse(), dst.GetRightEyePupillaryResponse());
}

cdm::NervousSystemData* SENervousSystem::Unload(const SENervousSystem& src)
{
  cdm::NervousSystemData* dst = new cdm::NervousSystemData();
  SENervousSystem::Serialize(src, *dst);
  return dst;
}
void SENervousSystem::Serialize(const SENervousSystem& src, cdm::NervousSystemData& dst)
{
  if (src.HasBaroreceptorHeartRateScale())
    dst.set_allocated_baroreceptorheartratescale(SEScalar::Unload(*src.m_BaroreceptorHeartRateScale));
  if (src.HasBaroreceptorHeartElastanceScale())
    dst.set_allocated_baroreceptorheartelastancescale(SEScalar::Unload(*src.m_BaroreceptorHeartElastanceScale));
  if (src.HasBaroreceptorResistanceScale())
    dst.set_allocated_baroreceptorresistancescale(SEScalar::Unload(*src.m_BaroreceptorResistanceScale));
  if (src.HasBaroreceptorComplianceScale())
    dst.set_allocated_baroreceptorcompliancescale(SEScalar::Unload(*src.m_BaroreceptorComplianceScale));
  if (src.HasChemoreceptorHeartRateScale())
    dst.set_allocated_chemoreceptorheartratescale(SEScalar::Unload(*src.m_ChemoreceptorHeartRateScale));
  if (src.HasChemoreceptorHeartElastanceScale())
    dst.set_allocated_chemoreceptorheartelastancescale(SEScalar::Unload(*src.m_ChemoreceptorHeartElastanceScale));
  if (src.HasLeftEyePupillaryResponse())
    dst.set_allocated_lefteyepupillaryresponse(SEPupillaryResponse::Unload(*src.m_LeftEyePupillaryResponse));
  if (src.HasRightEyePupillaryResponse())
    dst.set_allocated_righteyepupillaryresponse(SEPupillaryResponse::Unload(*src.m_RightEyePupillaryResponse));
}

bool SENervousSystem::HasBaroreceptorHeartRateScale() const
{
  return m_BaroreceptorHeartRateScale == nullptr ? false : m_BaroreceptorHeartRateScale->IsValid();
}
SEScalar& SENervousSystem::GetBaroreceptorHeartRateScale()
{
  if (m_BaroreceptorHeartRateScale == nullptr)
    m_BaroreceptorHeartRateScale = new SEScalar();
  return *m_BaroreceptorHeartRateScale;
}
double SENervousSystem::GetBaroreceptorHeartRateScale() const
{
  if (m_BaroreceptorHeartRateScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorHeartRateScale->GetValue();
}

bool SENervousSystem::HasBaroreceptorHeartElastanceScale() const
{
  return m_BaroreceptorHeartElastanceScale == nullptr ? false : m_BaroreceptorHeartElastanceScale->IsValid();
}
SEScalar& SENervousSystem::GetBaroreceptorHeartElastanceScale()
{
  if (m_BaroreceptorHeartElastanceScale == nullptr)
    m_BaroreceptorHeartElastanceScale = new SEScalar();
  return *m_BaroreceptorHeartElastanceScale;
}
double SENervousSystem::GetBaroreceptorHeartElastanceScale() const
{
  if (m_BaroreceptorHeartElastanceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorHeartElastanceScale->GetValue();
}

bool SENervousSystem::HasBaroreceptorResistanceScale() const
{
  return m_BaroreceptorResistanceScale == nullptr ? false : m_BaroreceptorResistanceScale->IsValid();
}
SEScalar& SENervousSystem::GetBaroreceptorResistanceScale()
{
  if (m_BaroreceptorResistanceScale == nullptr)
    m_BaroreceptorResistanceScale = new SEScalar();
  return *m_BaroreceptorResistanceScale;
}
double SENervousSystem::GetBaroreceptorResistanceScale() const
{
  if (m_BaroreceptorResistanceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorResistanceScale->GetValue();
}

bool SENervousSystem::HasBaroreceptorComplianceScale() const
{
  return m_BaroreceptorComplianceScale == nullptr ? false : m_BaroreceptorComplianceScale->IsValid();
}
SEScalar& SENervousSystem::GetBaroreceptorComplianceScale()
{
  if (m_BaroreceptorComplianceScale == nullptr)
    m_BaroreceptorComplianceScale = new SEScalar();
  return *m_BaroreceptorComplianceScale;
}
double SENervousSystem::GetBaroreceptorComplianceScale() const
{
  if (m_BaroreceptorComplianceScale == nullptr)
    return SEScalar::dNaN();
  return m_BaroreceptorComplianceScale->GetValue();
}

bool SENervousSystem::HasChemoreceptorHeartRateScale() const
{
  return m_ChemoreceptorHeartRateScale == nullptr ? false : m_ChemoreceptorHeartRateScale->IsValid();
}
SEScalar& SENervousSystem::GetChemoreceptorHeartRateScale()
{
  if (m_ChemoreceptorHeartRateScale == nullptr)
    m_ChemoreceptorHeartRateScale = new SEScalar();
  return *m_ChemoreceptorHeartRateScale;
}
double SENervousSystem::GetChemoreceptorHeartRateScale() const
{
  if (m_ChemoreceptorHeartRateScale == nullptr)
    return SEScalar::dNaN();
  return m_ChemoreceptorHeartRateScale->GetValue();
}

bool SENervousSystem::HasChemoreceptorHeartElastanceScale() const
{
  return m_ChemoreceptorHeartElastanceScale == nullptr ? false : m_ChemoreceptorHeartElastanceScale->IsValid();
}
SEScalar& SENervousSystem::GetChemoreceptorHeartElastanceScale()
{
  if (m_ChemoreceptorHeartElastanceScale == nullptr)
    m_ChemoreceptorHeartElastanceScale = new SEScalar();
  return *m_ChemoreceptorHeartElastanceScale;
}
double SENervousSystem::GetChemoreceptorHeartElastanceScale() const
{
  if (m_ChemoreceptorHeartElastanceScale == nullptr)
    return SEScalar::dNaN();
  return m_ChemoreceptorHeartElastanceScale->GetValue();
}
bool SENervousSystem::HasLeftEyePupillaryResponse() const
{
  return (m_LeftEyePupillaryResponse != nullptr);
}
SEPupillaryResponse& SENervousSystem::GetLeftEyePupillaryResponse()
{
  if (m_LeftEyePupillaryResponse == nullptr)
    m_LeftEyePupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_LeftEyePupillaryResponse;
}
const SEPupillaryResponse* SENervousSystem::GetLeftEyePupillaryResponse() const
{
  return m_LeftEyePupillaryResponse;
}
void SENervousSystem::RemoveLeftEyePupillaryResponse()
{
  SAFE_DELETE(m_LeftEyePupillaryResponse);
}

bool SENervousSystem::HasRightEyePupillaryResponse() const
{
  return (m_RightEyePupillaryResponse != nullptr);
}
SEPupillaryResponse& SENervousSystem::GetRightEyePupillaryResponse()
{
  if (m_RightEyePupillaryResponse == nullptr)
    m_RightEyePupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_RightEyePupillaryResponse;
}
const SEPupillaryResponse* SENervousSystem::GetRightEyePupillaryResponse() const
{
  return m_RightEyePupillaryResponse;
}
void SENervousSystem::RemoveRightEyePupillaryResponse()
{
  SAFE_DELETE(m_RightEyePupillaryResponse);
}