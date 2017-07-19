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
#include "compartment/tissue/SETissueCompartment.h"
#include "compartment/fluid/SELiquidCompartment.h"
#include "compartment/fluid/SELiquidCompartmentLink.h"
#include "substance/SESubstanceManager.h"

#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerMass.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarVolume.h"

SETissueCompartment::SETissueCompartment(const std::string& name, Logger* logger) : SECompartment(name, logger)
{
  m_AcidicPhospohlipidConcentration = nullptr;
  m_MatrixVolume = nullptr;
  m_NeutralLipidsVolumeFraction = nullptr;
  m_NeutralPhospholipidsVolumeFraction = nullptr;
  m_TissueToPlasmaAlbuminRatio = nullptr;
  m_TissueToPlasmaAlphaAcidGlycoproteinRatio = nullptr;
  m_TissueToPlasmaLipoproteinRatio = nullptr;
  m_TotalMass = nullptr;
}

SETissueCompartment::~SETissueCompartment()
{
  Clear();
}

void SETissueCompartment::Clear()
{
  SECompartment::Clear();
  SAFE_DELETE(m_AcidicPhospohlipidConcentration);
  SAFE_DELETE(m_MatrixVolume);
  SAFE_DELETE(m_NeutralLipidsVolumeFraction);
  SAFE_DELETE(m_NeutralPhospholipidsVolumeFraction);
  SAFE_DELETE(m_TissueToPlasmaAlbuminRatio);
  SAFE_DELETE(m_TissueToPlasmaAlphaAcidGlycoproteinRatio);
  SAFE_DELETE(m_TissueToPlasmaLipoproteinRatio);
  SAFE_DELETE(m_TotalMass);
}

void SETissueCompartment::Load(const cdm::TissueCompartmentData& src, SETissueCompartment& dst)
{
  SETissueCompartment::Serialize(src, dst);
}
void SETissueCompartment::Serialize(const cdm::TissueCompartmentData& src, SETissueCompartment& dst)
{
  SECompartment::Serialize(src.compartment(), dst);
  if (src.has_acidicphospohlipidconcentration())
    SEScalarMassPerMass::Load(src.acidicphospohlipidconcentration(), dst.GetAcidicPhospohlipidConcentration());
  if (src.has_matrixvolume())
    SEScalarVolume::Load(src.matrixvolume(), dst.GetMatrixVolume());
  if (src.has_neutrallipidsvolumefraction())
    SEScalar0To1::Load(src.neutrallipidsvolumefraction(), dst.GetNeutralLipidsVolumeFraction());
  if (src.has_neutralphospholipidsvolumefraction())
    SEScalar0To1::Load(src.neutralphospholipidsvolumefraction(), dst.GetNeutralPhospholipidsVolumeFraction());
  if (src.has_tissuetoplasmaalbuminratio())
    SEScalar::Load(src.tissuetoplasmaalbuminratio(), dst.GetTissueToPlasmaAlbuminRatio());
  if (src.has_tissuetoplasmaalphaacidglycoproteinratio())
    SEScalar::Load(src.tissuetoplasmaalphaacidglycoproteinratio(), dst.GetTissueToPlasmaAlphaAcidGlycoproteinRatio());
  if (src.has_tissuetoplasmalipoproteinratio())
    SEScalar::Load(src.tissuetoplasmalipoproteinratio(), dst.GetTissueToPlasmaLipoproteinRatio());
  if (src.has_totalmass())
    SEScalarMass::Load(src.totalmass(), dst.GetTotalMass());
}

cdm::TissueCompartmentData* SETissueCompartment::Unload(const SETissueCompartment& src)
{
  cdm::TissueCompartmentData* dst = new cdm::TissueCompartmentData();
  SETissueCompartment::Serialize(src,*dst);
  return dst;
}
void SETissueCompartment::Serialize(const SETissueCompartment& src, cdm::TissueCompartmentData& dst)
{
  SECompartment::Serialize(src,*dst.mutable_compartment());
  if (src.HasAcidicPhospohlipidConcentration())
    dst.set_allocated_acidicphospohlipidconcentration(SEScalarMassPerMass::Unload(*src.m_AcidicPhospohlipidConcentration));
  if (src.HasMatrixVolume())
    dst.set_allocated_matrixvolume(SEScalarVolume::Unload(*src.m_MatrixVolume));
  if (src.HasNeutralLipidsVolumeFraction())
    dst.set_allocated_neutrallipidsvolumefraction(SEScalar0To1::Unload(*src.m_NeutralLipidsVolumeFraction));
  if (src.HasNeutralPhospholipidsVolumeFraction())
    dst.set_allocated_neutralphospholipidsvolumefraction(SEScalar0To1::Unload(*src.m_NeutralPhospholipidsVolumeFraction));
  if (src.HasTissueToPlasmaAlbuminRatio())
    dst.set_allocated_tissuetoplasmaalbuminratio(SEScalar::Unload(*src.m_TissueToPlasmaAlbuminRatio));
  if (src.HasTissueToPlasmaAlphaAcidGlycoproteinRatio())
    dst.set_allocated_tissuetoplasmaalphaacidglycoproteinratio(SEScalar::Unload(*src.m_TissueToPlasmaAlphaAcidGlycoproteinRatio));
  if (src.HasTissueToPlasmaLipoproteinRatio())
    dst.set_allocated_tissuetoplasmalipoproteinratio(SEScalar::Unload(*src.m_TissueToPlasmaLipoproteinRatio));
  if (src.HasTotalMass())
    dst.set_allocated_totalmass(SEScalarMass::Unload(*src.m_TotalMass));
}

const SEScalar* SETissueCompartment::GetScalar(const std::string& name)
{
  if (name.compare("AcidicPhospohlipidConcentration") == 0)
    return &GetAcidicPhospohlipidConcentration();
  if (name.compare("MatrixVolume") == 0)
    return &GetMatrixVolume();  
  if (name.compare("NeutralLipidsVolumeFraction") == 0)
    return &GetNeutralLipidsVolumeFraction();
  if (name.compare("NeutralPhospholipidsVolumeFraction") == 0)
    return &GetNeutralPhospholipidsVolumeFraction();
  if (name.compare("TissueToPlasmaAlbuminRatio") == 0)
    return &GetTissueToPlasmaAlbuminRatio();
  if (name.compare("TissueToPlasmaAlphaAcidGlycoproteinRatio") == 0)
    return &GetTissueToPlasmaAlphaAcidGlycoproteinRatio();
  if (name.compare("TissueToPlasmaLipoproteinRatio") == 0)
    return &GetTissueToPlasmaLipoproteinRatio();
  if (name.compare("TotalMass") == 0)
    return &GetTotalMass();
  return nullptr;
}

void SETissueCompartment::StateChange()
{
 
}

bool SETissueCompartment::HasAcidicPhospohlipidConcentration() const
{
  return m_AcidicPhospohlipidConcentration == nullptr ? false : m_AcidicPhospohlipidConcentration->IsValid();
}
SEScalarMassPerMass& SETissueCompartment::GetAcidicPhospohlipidConcentration()
{
  if (m_AcidicPhospohlipidConcentration == nullptr)
    m_AcidicPhospohlipidConcentration = new SEScalarMassPerMass();
  return *m_AcidicPhospohlipidConcentration;
}
double SETissueCompartment::GetAcidicPhospohlipidConcentration(const MassPerMassUnit& unit) const
{
  if (m_AcidicPhospohlipidConcentration == nullptr)
    return SEScalar::dNaN();
  return m_AcidicPhospohlipidConcentration->GetValue(unit);
}

bool SETissueCompartment::HasMatrixVolume() const
{
  return m_MatrixVolume == nullptr ? false : m_MatrixVolume->IsValid();
}
SEScalarVolume& SETissueCompartment::GetMatrixVolume()
{
  if (m_MatrixVolume == nullptr)
    m_MatrixVolume = new SEScalarVolume();
  return *m_MatrixVolume;
}
double SETissueCompartment::GetMatrixVolume(const VolumeUnit& unit) const
{
  if (m_MatrixVolume == nullptr)
    return SEScalar::dNaN();
  return m_MatrixVolume->GetValue(unit);
}

bool SETissueCompartment::HasNeutralLipidsVolumeFraction() const
{
  return m_NeutralLipidsVolumeFraction == nullptr ? false : m_NeutralLipidsVolumeFraction->IsValid();
}
SEScalar0To1& SETissueCompartment::GetNeutralLipidsVolumeFraction()
{
  if (m_NeutralLipidsVolumeFraction == nullptr)
    m_NeutralLipidsVolumeFraction = new SEScalar0To1();
  return *m_NeutralLipidsVolumeFraction;
}
double SETissueCompartment::GetNeutralLipidsVolumeFraction() const
{
  if (m_NeutralLipidsVolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_NeutralLipidsVolumeFraction->GetValue();
}

bool SETissueCompartment::HasNeutralPhospholipidsVolumeFraction() const
{
  return m_NeutralPhospholipidsVolumeFraction == nullptr ? false : m_NeutralPhospholipidsVolumeFraction->IsValid();
}
SEScalar0To1& SETissueCompartment::GetNeutralPhospholipidsVolumeFraction()
{
  if (m_NeutralPhospholipidsVolumeFraction == nullptr)
    m_NeutralPhospholipidsVolumeFraction = new SEScalar0To1();
  return *m_NeutralPhospholipidsVolumeFraction;
}
double SETissueCompartment::GetNeutralPhospholipidsVolumeFraction() const
{
  if (m_NeutralPhospholipidsVolumeFraction == nullptr)
    return SEScalar::dNaN();
  return m_NeutralPhospholipidsVolumeFraction->GetValue();
}

bool SETissueCompartment::HasTissueToPlasmaAlbuminRatio() const
{
  return m_TissueToPlasmaAlbuminRatio == nullptr ? false : m_TissueToPlasmaAlbuminRatio->IsValid();
}
SEScalar& SETissueCompartment::GetTissueToPlasmaAlbuminRatio()
{
  if (m_TissueToPlasmaAlbuminRatio == nullptr)
    m_TissueToPlasmaAlbuminRatio = new SEScalar();
  return *m_TissueToPlasmaAlbuminRatio;
}
double SETissueCompartment::GetTissueToPlasmaAlbuminRatio() const
{
  if (m_TissueToPlasmaAlbuminRatio == nullptr)
    return SEScalar::dNaN();
  return m_TissueToPlasmaAlbuminRatio->GetValue();
}

bool SETissueCompartment::HasTissueToPlasmaAlphaAcidGlycoproteinRatio() const
{
  return m_TissueToPlasmaAlphaAcidGlycoproteinRatio == nullptr ? false : m_TissueToPlasmaAlphaAcidGlycoproteinRatio->IsValid();
}
SEScalar& SETissueCompartment::GetTissueToPlasmaAlphaAcidGlycoproteinRatio()
{
  if (m_TissueToPlasmaAlphaAcidGlycoproteinRatio == nullptr)
    m_TissueToPlasmaAlphaAcidGlycoproteinRatio = new SEScalar();
  return *m_TissueToPlasmaAlphaAcidGlycoproteinRatio;
}
double SETissueCompartment::GetTissueToPlasmaAlphaAcidGlycoproteinRatio() const
{
  if (m_TissueToPlasmaAlphaAcidGlycoproteinRatio == nullptr)
    return SEScalar::dNaN();
  return m_TissueToPlasmaAlphaAcidGlycoproteinRatio->GetValue();
}

bool SETissueCompartment::HasTissueToPlasmaLipoproteinRatio() const
{
  return m_TissueToPlasmaLipoproteinRatio == nullptr ? false : m_TissueToPlasmaLipoproteinRatio->IsValid();
}
SEScalar& SETissueCompartment::GetTissueToPlasmaLipoproteinRatio()
{
  if (m_TissueToPlasmaLipoproteinRatio == nullptr)
    m_TissueToPlasmaLipoproteinRatio = new SEScalar();
  return *m_TissueToPlasmaLipoproteinRatio;
}
double SETissueCompartment::GetTissueToPlasmaLipoproteinRatio() const
{
  if (m_TissueToPlasmaLipoproteinRatio == nullptr)
    return SEScalar::dNaN();
  return m_TissueToPlasmaLipoproteinRatio->GetValue();
}

bool SETissueCompartment::HasTotalMass() const
{
  return m_TotalMass == nullptr ? false : m_TotalMass->IsValid();
}
SEScalarMass& SETissueCompartment::GetTotalMass()
{
  if (m_TotalMass == nullptr)
    m_TotalMass = new SEScalarMass();  
  return *m_TotalMass;
}
double SETissueCompartment::GetTotalMass(const MassUnit& unit) const
{
  if (m_TotalMass == nullptr)
    return SEScalar::dNaN();
  return m_TotalMass->GetValue(unit);
}