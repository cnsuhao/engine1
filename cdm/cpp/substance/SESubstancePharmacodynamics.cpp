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
#include "substance/SESubstancePharmacodynamics.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMassPerVolume.h"

SESubstancePharmacodynamics::SESubstancePharmacodynamics(Logger* logger) : Loggable(logger)
{
  m_Bronchodilation = nullptr;
  m_DiastolicPressureModifier = nullptr;
  m_EC50 = nullptr;
  m_EMaxShapeParameter = nullptr;
  m_HeartRateModifier = nullptr;
  m_NeuromuscularBlock = nullptr;
  m_PupillaryResponse = nullptr;
  m_RespirationRateModifier = nullptr;
  m_Sedation = nullptr;
  m_SystolicPressureModifier = nullptr;
  m_TidalVolumeModifier = nullptr;
  m_TubularPermeabilityModifier = nullptr;
}

SESubstancePharmacodynamics::~SESubstancePharmacodynamics() 
{
  Clear();
}

void SESubstancePharmacodynamics::Clear()
{
  SAFE_DELETE(m_Bronchodilation);
  SAFE_DELETE(m_DiastolicPressureModifier);
  SAFE_DELETE(m_EC50);
  SAFE_DELETE(m_EMaxShapeParameter);
  SAFE_DELETE(m_HeartRateModifier);
  SAFE_DELETE(m_NeuromuscularBlock);
  SAFE_DELETE(m_PupillaryResponse);
  SAFE_DELETE(m_RespirationRateModifier);
  SAFE_DELETE(m_Sedation);
  SAFE_DELETE(m_SystolicPressureModifier);
  SAFE_DELETE(m_TidalVolumeModifier);
  SAFE_DELETE(m_TubularPermeabilityModifier);
}

bool SESubstancePharmacodynamics::IsValid() const
{
  if (!HasBronchodilation())
    return false;
  if (!HasDiastolicPressureModifier())
    return false;
  if (!HasEC50())
    return false;
  if (!HasEMaxShapeParameter())
    return false;
  if (!HasHeartRateModifier())
    return false;
  if (!HasNeuromuscularBlock())
    return false;
  if (!HasPupillaryResponse())
    return false;
  if (!HasRespirationRateModifier())
    return false;
  if (!HasSedation())
    return false;
  if (!HasSystolicPressureModifier())
    return false;
  if (!HasTidalVolumeModifier())
    return false;
  if (!HasTubularPermeabilityModifier())
    return false;
  return true;
}

const SEScalar* SESubstancePharmacodynamics::GetScalar(const std::string& name)
{
  if (name.compare("Bronchodilation") == 0)
    return &GetBronchodilation();
  if (name.compare("DiastolicPressureModifier") == 0)
    return &GetDiastolicPressureModifier();
  if (name.compare("EC50") == 0)
    return &GetEC50();
  if (name.compare("EMaxShapeParameter") == 0)
    return &GetEMaxShapeParameter();
  if (name.compare("HeartRateModifier") == 0)
    return &GetHeartRateModifier();
  if (name.compare("NeuromuscularBlock") == 0)
    return &GetNeuromuscularBlock();
  if (name.compare("RespirationRateModifier") == 0)
    return &GetRespirationRateModifier();
  if (name.compare("Sedation") == 0)
    return &GetSedation();
  if (name.compare("SystolicPressureModifier") == 0)
    return &GetSystolicPressureModifier();
  if (name.compare("TidalVolumeModifier") == 0)
    return &GetTidalVolumeModifier();
  if (name.compare("TubularPermeabilityModifier") == 0)
    return &GetTubularPermeabilityModifier();

  return GetPupillaryResponse().GetScalar(name);
}

void SESubstancePharmacodynamics::Load(const cdm::SubstanceData_PharmacodynamicsData& src, SESubstancePharmacodynamics& dst)
{
  SESubstancePharmacodynamics::Serialize(src, dst);
  dst.CalculateDerived();
}
void SESubstancePharmacodynamics::Serialize(const cdm::SubstanceData_PharmacodynamicsData& src, SESubstancePharmacodynamics& dst)
{
  dst.Clear();

  if (src.has_bronchodilation())
    SEScalar0To1::Load(src.bronchodilation(), dst.GetBronchodilation());
  if (src.has_diastolicpressuremodifier())
    SEScalar0To1::Load(src.diastolicpressuremodifier(), dst.GetDiastolicPressureModifier());
  if (src.has_ec50())
    SEScalarMassPerVolume::Load(src.ec50(), dst.GetEC50());
  if (src.has_emaxshapeparameter())
    SEScalar::Load(src.emaxshapeparameter(), dst.GetEMaxShapeParameter());
  if (src.has_heartratemodifier())
    SEScalar0To1::Load(src.heartratemodifier(), dst.GetHeartRateModifier());
  if (src.has_neuromuscularblock())
    SEScalar0To1::Load(src.neuromuscularblock(), dst.GetNeuromuscularBlock());
  if (src.has_pupillaryresponse())
    SEPupillaryResponse::Load(src.pupillaryresponse(), dst.GetPupillaryResponse());
  if (src.has_respirationratemodifier())
    SEScalar0To1::Load(src.respirationratemodifier(), dst.GetRespirationRateModifier());
  if (src.has_sedation())
    SEScalar0To1::Load(src.sedation(), dst.GetSedation());
  if (src.has_systolicpressuremodifier())
    SEScalar0To1::Load(src.systolicpressuremodifier(), dst.GetSystolicPressureModifier());
  if (src.has_tidalvolumemodifier())
    SEScalar0To1::Load(src.tidalvolumemodifier(), dst.GetTidalVolumeModifier());
  if (src.has_tubularpermeabilitymodifier())
    SEScalar0To1::Load(src.tubularpermeabilitymodifier(), dst.GetTubularPermeabilityModifier());
}

cdm::SubstanceData_PharmacodynamicsData* SESubstancePharmacodynamics::Unload(const SESubstancePharmacodynamics& src)
{
  if (!src.IsValid())
    return nullptr;
  cdm::SubstanceData_PharmacodynamicsData* dst = new cdm::SubstanceData_PharmacodynamicsData();
  SESubstancePharmacodynamics::Serialize(src,*dst);
  return dst;
}
void SESubstancePharmacodynamics::Serialize(const SESubstancePharmacodynamics& src, cdm::SubstanceData_PharmacodynamicsData& dst)
{
  if (src.HasBronchodilation())
    dst.set_allocated_bronchodilation(SEScalar0To1::Unload(*src.m_Bronchodilation));
  if (src.HasDiastolicPressureModifier())
    dst.set_allocated_diastolicpressuremodifier(SEScalar0To1::Unload(*src.m_DiastolicPressureModifier));
  if (src.HasEC50())
    dst.set_allocated_ec50(SEScalarMassPerVolume::Unload(*src.m_EC50));
  if (src.HasEMaxShapeParameter())
    dst.set_allocated_emaxshapeparameter(SEScalar::Unload(*src.m_EMaxShapeParameter));
  if (src.HasHeartRateModifier())
    dst.set_allocated_heartratemodifier(SEScalar0To1::Unload(*src.m_HeartRateModifier));
  if (src.HasNeuromuscularBlock())
    dst.set_allocated_neuromuscularblock(SEScalar0To1::Unload(*src.m_NeuromuscularBlock));
  if (src.HasPupillaryResponse())
    dst.set_allocated_pupillaryresponse(SEPupillaryResponse::Unload(*src.m_PupillaryResponse));
  if (src.HasRespirationRateModifier())
    dst.set_allocated_respirationratemodifier(SEScalar0To1::Unload(*src.m_RespirationRateModifier));
  if (src.HasSedation())
    dst.set_allocated_sedation(SEScalar0To1::Unload(*src.m_Sedation));
  if (src.HasSystolicPressureModifier())
    dst.set_allocated_systolicpressuremodifier(SEScalar0To1::Unload(*src.m_SystolicPressureModifier));
  if (src.HasTidalVolumeModifier())
    dst.set_allocated_tidalvolumemodifier(SEScalar0To1::Unload(*src.m_TidalVolumeModifier));
  if (src.HasTubularPermeabilityModifier())
    dst.set_allocated_tubularpermeabilitymodifier(SEScalar0To1::Unload(*src.m_TubularPermeabilityModifier));
}

void SESubstancePharmacodynamics::CalculateDerived()
{
  
}

bool SESubstancePharmacodynamics::HasBronchodilation() const
{
  return (m_Bronchodilation == nullptr) ? false : m_Bronchodilation->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetBronchodilation()
{
  if (m_Bronchodilation == nullptr)
    m_Bronchodilation = new SEScalar0To1();
  return *m_Bronchodilation;
}
double SESubstancePharmacodynamics::GetBronchodilation() const
{
  if (m_Bronchodilation == nullptr)
    return SEScalar::dNaN();
  return m_Bronchodilation->GetValue();
}

bool SESubstancePharmacodynamics::HasDiastolicPressureModifier() const
{
  return (m_DiastolicPressureModifier == nullptr) ? false : m_DiastolicPressureModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetDiastolicPressureModifier()
{
  if (m_DiastolicPressureModifier == nullptr)
    m_DiastolicPressureModifier = new SEScalar0To1();
  return *m_DiastolicPressureModifier;
}
double SESubstancePharmacodynamics::GetDiastolicPressureModifier() const
{
  if (m_DiastolicPressureModifier == nullptr)
    return SEScalar::dNaN();
  return m_DiastolicPressureModifier->GetValue();
}

bool SESubstancePharmacodynamics::HasEC50() const
{
  return (m_EC50 == nullptr) ? false : m_EC50->IsValid();
}
SEScalarMassPerVolume& SESubstancePharmacodynamics::GetEC50()
{
  if (m_EC50 == nullptr)
    m_EC50 = new SEScalarMassPerVolume();
  return *m_EC50;
}
double SESubstancePharmacodynamics::GetEC50(const MassPerVolumeUnit& unit) const
{
  if (m_EC50 == nullptr)
    return SEScalar::dNaN();
  return m_EC50->GetValue(unit);
}

bool SESubstancePharmacodynamics::HasEMaxShapeParameter() const
{
  return (m_EMaxShapeParameter == nullptr) ? false : m_EMaxShapeParameter->IsValid();
}
SEScalar& SESubstancePharmacodynamics::GetEMaxShapeParameter()
{
  if (m_EMaxShapeParameter == nullptr)
    m_EMaxShapeParameter = new SEScalar();
  return *m_EMaxShapeParameter;
}
double SESubstancePharmacodynamics::GetEMaxShapeParameter() const
{
  if (m_EMaxShapeParameter == nullptr)
    return SEScalar::dNaN();
  return m_EMaxShapeParameter->GetValue();
}

bool SESubstancePharmacodynamics::HasHeartRateModifier() const
{
  return (m_HeartRateModifier == nullptr) ? false : m_HeartRateModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetHeartRateModifier()
{
  if (m_HeartRateModifier == nullptr)
    m_HeartRateModifier = new SEScalar0To1();
  return *m_HeartRateModifier;
}
double SESubstancePharmacodynamics::GetHeartRateModifier() const
{
  if (m_HeartRateModifier == nullptr)
    return SEScalar::dNaN();
  return m_HeartRateModifier->GetValue();
}

bool SESubstancePharmacodynamics::HasNeuromuscularBlock() const
{
  return (m_NeuromuscularBlock == nullptr) ? false : m_NeuromuscularBlock->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetNeuromuscularBlock()
{
  if (m_NeuromuscularBlock == nullptr)
    m_NeuromuscularBlock = new SEScalar0To1();
  return *m_NeuromuscularBlock;
}
double SESubstancePharmacodynamics::GetNeuromuscularBlock() const
{
  if (m_NeuromuscularBlock == nullptr)
    return SEScalar::dNaN();
  return m_NeuromuscularBlock->GetValue();
}

bool SESubstancePharmacodynamics::HasPupillaryResponse() const
{
  return (m_PupillaryResponse != nullptr);
}
SEPupillaryResponse& SESubstancePharmacodynamics::GetPupillaryResponse()
{
  if (m_PupillaryResponse == nullptr)
    m_PupillaryResponse = new SEPupillaryResponse(GetLogger());
  return *m_PupillaryResponse;
}
const SEPupillaryResponse* SESubstancePharmacodynamics::GetPupillaryResponse() const
{
  return m_PupillaryResponse;
}
void SESubstancePharmacodynamics::RemovePupillaryResponse()
{
  SAFE_DELETE(m_PupillaryResponse);
}

bool SESubstancePharmacodynamics::HasRespirationRateModifier() const
{
  return (m_RespirationRateModifier == nullptr) ? false : m_RespirationRateModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetRespirationRateModifier()
{
  if (m_RespirationRateModifier == nullptr)
    m_RespirationRateModifier = new SEScalar0To1();
  return *m_RespirationRateModifier;
}
double SESubstancePharmacodynamics::GetRespirationRateModifier() const
{
  if (m_RespirationRateModifier == nullptr)
    return SEScalar::dNaN();
  return m_RespirationRateModifier->GetValue();
}

bool SESubstancePharmacodynamics::HasSedation() const
{
  return (m_Sedation == nullptr) ? false : m_Sedation->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetSedation()
{
  if (m_Sedation == nullptr)
    m_Sedation = new SEScalar0To1();
  return *m_Sedation;
}
double SESubstancePharmacodynamics::GetSedation() const
{
  if (m_Sedation == nullptr)
    return SEScalar::dNaN();
  return m_Sedation->GetValue();
}

bool SESubstancePharmacodynamics::HasSystolicPressureModifier() const
{
  return (m_SystolicPressureModifier == nullptr) ? false : m_SystolicPressureModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetSystolicPressureModifier()
{
  if (m_SystolicPressureModifier == nullptr)
    m_SystolicPressureModifier = new SEScalar0To1();
  return *m_SystolicPressureModifier;
}
double SESubstancePharmacodynamics::GetSystolicPressureModifier() const
{
  if (m_SystolicPressureModifier == nullptr)
    return SEScalar::dNaN();
  return m_SystolicPressureModifier->GetValue();
}

bool SESubstancePharmacodynamics::HasTidalVolumeModifier() const
{
  return (m_TidalVolumeModifier == nullptr) ? false : m_TidalVolumeModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetTidalVolumeModifier()
{
  if (m_TidalVolumeModifier == nullptr)
    m_TidalVolumeModifier = new SEScalar0To1();
  return *m_TidalVolumeModifier;
}
double SESubstancePharmacodynamics::GetTidalVolumeModifier() const
{
  if (m_TidalVolumeModifier == nullptr)
    return SEScalar::dNaN();
  return m_TidalVolumeModifier->GetValue();
}

bool SESubstancePharmacodynamics::HasTubularPermeabilityModifier() const
{
  return (m_TubularPermeabilityModifier == nullptr) ? false : m_TubularPermeabilityModifier->IsValid();
}
SEScalar0To1& SESubstancePharmacodynamics::GetTubularPermeabilityModifier()
{
  if (m_TubularPermeabilityModifier == nullptr)
    m_TubularPermeabilityModifier = new SEScalar0To1();
  return *m_TubularPermeabilityModifier;
}
double SESubstancePharmacodynamics::GetTubularPermeabilityModifier() const
{
  if (m_TubularPermeabilityModifier == nullptr)
    return SEScalar::dNaN();
  return m_TubularPermeabilityModifier->GetValue();
}