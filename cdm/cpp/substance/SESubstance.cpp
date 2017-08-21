/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "substance/SESubstance.h"
#include "substance/SESubstanceAerosolization.h"
#include "substance/SESubstanceClearance.h"
#include "substance/SESubstancePharmacokinetics.h"
#include "substance/SESubstancePharmacodynamics.h"
#include "properties/SEScalarMassPerAmount.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarInversePressure.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerAreaTime.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarVolumePerTimePressure.h"

SESubstance::SESubstance(Logger* logger) : Loggable(logger)
{
  m_Name = "";
  m_State = cdm::SubstanceData_eState_NullState;
  m_Density = nullptr;
  m_MolarMass = nullptr;

  m_MaximumDiffusionFlux = nullptr;
  m_MichaelisCoefficient = nullptr;

  m_Aerosolization = nullptr;
  m_BloodConcentration = nullptr;
  m_MassInBody = nullptr;
  m_MassInBlood = nullptr;
  m_MassInTissue = nullptr;
  m_PlasmaConcentration = nullptr;
  m_SystemicMassCleared = nullptr;
  m_TissueConcentration = nullptr;

  m_AlveolarTransfer = nullptr;
  m_DiffusingCapacity = nullptr;
  m_EndTidalFraction = nullptr;
  m_EndTidalPressure = nullptr;
  m_SolubilityCoefficient = nullptr;
  m_RelativeDiffusionCoefficient = nullptr;

  m_Clearance = nullptr;
  m_PK = nullptr;
  m_PD = nullptr;
}

SESubstance::~SESubstance()
{
  Clear();
}

void SESubstance::Clear()
{
  m_Name = "";
  m_State = cdm::SubstanceData_eState_NullState;
  SAFE_DELETE(m_Density); 
  SAFE_DELETE(m_MolarMass);
  
  SAFE_DELETE(m_MaximumDiffusionFlux);
  SAFE_DELETE(m_MichaelisCoefficient);

  SAFE_DELETE(m_BloodConcentration);
  SAFE_DELETE(m_MassInBody);
  SAFE_DELETE(m_MassInBlood);
  SAFE_DELETE(m_MassInTissue);
  SAFE_DELETE(m_PlasmaConcentration);
  SAFE_DELETE(m_SystemicMassCleared);
  SAFE_DELETE(m_TissueConcentration);

  SAFE_DELETE(m_AlveolarTransfer);
  SAFE_DELETE(m_DiffusingCapacity);
  SAFE_DELETE(m_EndTidalFraction);
  SAFE_DELETE(m_EndTidalPressure);
  SAFE_DELETE(m_SolubilityCoefficient);
  SAFE_DELETE(m_RelativeDiffusionCoefficient);

  SAFE_DELETE(m_Aerosolization);
  SAFE_DELETE(m_Clearance);
  SAFE_DELETE(m_PK);
  SAFE_DELETE(m_PD);
  
}


const SEScalar* SESubstance::GetScalar(const std::string& name)
{
  if (name.compare("Density") == 0)
    return &GetDensity();
  if (name.compare("MolarMass") == 0)
    return &GetMolarMass();

  if (name.compare("MaximumDiffusionFlux") == 0)
    return &GetMaximumDiffusionFlux();
  if (name.compare("MichaelisCoefficient") == 0)
    return &GetMichaelisCoefficient();

  if (name.compare("BloodConcentration") == 0)
    return &GetBloodConcentration();
  if (name.compare("MassInBody") == 0)
    return &GetMassInBody();
  if (name.compare("MassInBlood") == 0)
    return &GetMassInBlood();
  if (name.compare("MassInTissue") == 0)
    return &GetMassInTissue();
  if (name.compare("PlasmaConcentration") == 0)
    return &GetPlasmaConcentration();
  if (name.compare("SystemicMassCleared") == 0)
    return &GetSystemicMassCleared();
  if (name.compare("TissueConcentration") == 0)
    return &GetTissueConcentration();

  if (name.compare("AlveolarTransfer") == 0)
    return &GetAlveolarTransfer();
  if (name.compare("DiffusingCapacity") == 0)
    return &GetDiffusingCapacity();
  if (name.compare("EndTidalFraction") == 0)
    return &GetEndTidalFraction();
  if (name.compare("EndTidalPressure") == 0)
    return &GetEndTidalPressure();
  if (name.compare("RelativeDiffusionCoefficient") == 0)
    return &GetRelativeDiffusionCoefficient();
  if (name.compare("SolubilityCoefficient") == 0)
    return &GetSolubilityCoefficient();

  size_t split = name.find('-');
  if (split != name.npos)
  {
    std::string child = name.substr(0, split);
    std::string prop = name.substr(split + 1, name.npos);
    if (child == "Aerosolization")
      return GetAerosolization().GetScalar(prop);
    if (child == "Clearance")
        return GetClearance().GetScalar(prop);
    if (child == "PK")
      return GetPK().GetScalar(prop);
    if (child == "PD")
      return GetPD().GetScalar(prop);
  }

  return nullptr;
}

void SESubstance::Load(const cdm::SubstanceData& src, SESubstance& dst)
{
  SESubstance::Serialize(src, dst);

  if (dst.HasClearance() && dst.HasPK() && dst.GetPK().HasPhysicochemicals() &&
    dst.GetClearance().HasFractionUnboundInPlasma() &&
    !dst.GetClearance().GetFractionUnboundInPlasma().Equals(dst.GetPK().GetPhysicochemicals().GetFractionUnboundInPlasma()))
  {
    dst.Fatal("Multiple FractionUnboundInPlasma values specified, but not the same. These must match at this time.");
  }
}
void SESubstance::Serialize(const cdm::SubstanceData& src, SESubstance& dst)
{
  dst.Clear();
  dst.SetName(src.name());
  dst.SetState(src.state());
  if (src.has_density())
    SEScalarMassPerVolume::Load(src.density(), dst.GetDensity());
  if (src.has_molarmass())
    SEScalarMassPerAmount::Load(src.molarmass(), dst.GetMolarMass());

  if (src.has_maximumdiffusionflux())
    SEScalarMassPerAreaTime::Load(src.maximumdiffusionflux(), dst.GetMaximumDiffusionFlux());
  if (src.has_michaeliscoefficient())
    SEScalar::Load(src.michaeliscoefficient(), dst.GetMichaelisCoefficient());

  if (src.has_aerosolization())
    SESubstanceAerosolization::Load(src.aerosolization(), dst.GetAerosolization());
  if (src.has_bloodconcentration())
    SEScalarMassPerVolume::Load(src.bloodconcentration(), dst.GetBloodConcentration());
  if (src.has_massinbody())
    SEScalarMass::Load(src.massinbody(), dst.GetMassInBody());
  if (src.has_massinblood())
    SEScalarMass::Load(src.massinblood(), dst.GetMassInBlood());
  if (src.has_massintissue())
    SEScalarMass::Load(src.massintissue(), dst.GetMassInTissue());
  if (src.has_plasmaconcentration())
    SEScalarMassPerVolume::Load(src.plasmaconcentration(), dst.GetPlasmaConcentration());
  if (src.has_systemicmasscleared())
    SEScalarMass::Load(src.systemicmasscleared(), dst.GetSystemicMassCleared());
  if (src.has_tissueconcentration())
    SEScalarMassPerVolume::Load(src.tissueconcentration(), dst.GetTissueConcentration());

  if (src.has_alveolartransfer())
    SEScalarVolumePerTime::Load(src.alveolartransfer(), dst.GetAlveolarTransfer());
  if (src.has_diffusingcapacity())
    SEScalarVolumePerTimePressure::Load(src.diffusingcapacity(), dst.GetDiffusingCapacity());
  if (src.has_endtidalfraction())
    SEScalar0To1::Load(src.endtidalfraction(), dst.GetEndTidalFraction());
  if (src.has_endtidalpressure())
    SEScalarPressure::Load(src.endtidalpressure(), dst.GetEndTidalPressure());
  if (src.has_relativediffusioncoefficient())
    SEScalar::Load(src.relativediffusioncoefficient(), dst.GetRelativeDiffusionCoefficient());
  if (src.has_solubilitycoefficient())
    SEScalarInversePressure::Load(src.solubilitycoefficient(), dst.GetSolubilityCoefficient());

  if (src.has_clearance())
    SESubstanceClearance::Load(src.clearance(), dst.GetClearance());
  if (src.has_pharmacokinetics())
    SESubstancePharmacokinetics::Load(src.pharmacokinetics(), dst.GetPK());
  if (src.has_pharmacodynamics())
    SESubstancePharmacodynamics::Load(src.pharmacodynamics(), dst.GetPD());
}

cdm::SubstanceData* SESubstance::Unload(const SESubstance& src)
{
  cdm::SubstanceData* dst = new cdm::SubstanceData();
  SESubstance::Serialize(src,*dst);
  return dst;
}
void SESubstance::Serialize(const SESubstance& src, cdm::SubstanceData& dst)
{
  if (src.HasName())
    dst.set_name(src.m_Name);
  if (src.HasState())
    dst.set_state(src.m_State);
  if (src.HasDensity())
    dst.set_allocated_density(SEScalarMassPerVolume::Unload(*src.m_Density));
  if (src.HasMolarMass())
    dst.set_allocated_molarmass(SEScalarMassPerAmount::Unload(*src.m_MolarMass));

  if (src.HasMaximumDiffusionFlux())
    dst.set_allocated_maximumdiffusionflux(SEScalarMassPerAreaTime::Unload(*src.m_MaximumDiffusionFlux));
  if (src.HasMichaelisCoefficient())
    dst.set_allocated_michaeliscoefficient(SEScalar::Unload(*src.m_MichaelisCoefficient));

  if (src.HasAerosolization())
    dst.set_allocated_aerosolization(SESubstanceAerosolization::Unload(*src.m_Aerosolization));
  if (src.HasBloodConcentration())
    dst.set_allocated_bloodconcentration(SEScalarMassPerVolume::Unload(*src.m_BloodConcentration));
  if (src.HasMassInBody())
    dst.set_allocated_massinbody(SEScalarMass::Unload(*src.m_MassInBody));
  if (src.HasMassInBlood())
    dst.set_allocated_massinblood(SEScalarMass::Unload(*src.m_MassInBlood));
  if (src.HasMassInTissue())
    dst.set_allocated_massintissue(SEScalarMass::Unload(*src.m_MassInTissue));
  if (src.HasPlasmaConcentration())
    dst.set_allocated_plasmaconcentration(SEScalarMassPerVolume::Unload(*src.m_PlasmaConcentration));
  if (src.HasSystemicMassCleared())
    dst.set_allocated_systemicmasscleared(SEScalarMass::Unload(*src.m_SystemicMassCleared));
  if (src.HasTissueConcentration())
    dst.set_allocated_tissueconcentration(SEScalarMassPerVolume::Unload(*src.m_TissueConcentration));

  if (src.HasAlveolarTransfer())
    dst.set_allocated_alveolartransfer(SEScalarVolumePerTime::Unload(*src.m_AlveolarTransfer));
  if (src.HasDiffusingCapacity())
    dst.set_allocated_diffusingcapacity(SEScalarVolumePerTimePressure::Unload(*src.m_DiffusingCapacity));
  if (src.HasEndTidalFraction())
    dst.set_allocated_endtidalfraction(SEScalar0To1::Unload(*src.m_EndTidalFraction));
  if (src.HasEndTidalPressure())
    dst.set_allocated_endtidalpressure(SEScalarPressure::Unload(*src.m_EndTidalPressure));
  if (src.HasRelativeDiffusionCoefficient())
    dst.set_allocated_relativediffusioncoefficient(SEScalar::Unload(*src.m_RelativeDiffusionCoefficient));
  if (src.HasSolubilityCoefficient())
    dst.set_allocated_solubilitycoefficient(SEScalarInversePressure::Unload(*src.m_SolubilityCoefficient));

  if (src.HasClearance())
    dst.set_allocated_clearance(SESubstanceClearance::Unload(*src.m_Clearance));
  if (src.HasPK())
    dst.set_allocated_pharmacokinetics(SESubstancePharmacokinetics::Unload(*src.m_PK));
  if (src.HasPD())
    dst.set_allocated_pharmacodynamics(SESubstancePharmacodynamics::Unload(*src.m_PD));
}

std::string SESubstance::GetName() const
{
  return m_Name;
}
void SESubstance::SetName(const std::string& name)
{
  m_Name = name;
}
bool SESubstance::HasName() const
{
  return m_Name.empty() ? false : true;
}
void SESubstance::InvalidateName()
{
  m_Name = "";
}

cdm::SubstanceData_eState SESubstance::GetState() const
{
  return m_State;
}
void SESubstance::SetState(cdm::SubstanceData_eState state)
{
  m_State = state;
}
bool SESubstance::HasState() const
{
  return m_State == cdm::SubstanceData_eState_NullState ? false : true;
}
void SESubstance::InvalidateState()
{
  m_State = cdm::SubstanceData_eState_NullState;
}

bool SESubstance::HasDensity() const
{
  return (m_Density == nullptr) ? false : m_Density->IsValid();
}
SEScalarMassPerVolume& SESubstance::GetDensity()
{
  if (m_Density == nullptr)
    m_Density = new SEScalarMassPerVolume();
  return *m_Density;
}
double SESubstance::GetDensity(const MassPerVolumeUnit& unit) const
{
  if (m_Density == nullptr)
    return SEScalar::dNaN();
  return m_Density->GetValue(unit);
}

bool SESubstance::HasMolarMass() const
{
  return (m_MolarMass == nullptr) ? false : m_MolarMass->IsValid();
}
SEScalarMassPerAmount& SESubstance::GetMolarMass()
{
  if (m_MolarMass == nullptr)
    m_MolarMass = new SEScalarMassPerAmount();
  return *m_MolarMass;
}
double SESubstance::GetMolarMass(const MassPerAmountUnit& unit) const
{
  if (m_MolarMass == nullptr)
    return SEScalar::dNaN();
  return m_MolarMass->GetValue(unit);
}

bool SESubstance::HasMaximumDiffusionFlux() const
{
  return (m_MaximumDiffusionFlux == nullptr) ? false : m_MaximumDiffusionFlux->IsValid();
}
SEScalarMassPerAreaTime& SESubstance::GetMaximumDiffusionFlux()
{
  if (m_MaximumDiffusionFlux == nullptr)
    m_MaximumDiffusionFlux = new SEScalarMassPerAreaTime();
  return *m_MaximumDiffusionFlux;
}
double SESubstance::GetMaximumDiffusionFlux(const MassPerAreaTimeUnit& unit) const
{
  if (m_MaximumDiffusionFlux == nullptr)
    return SEScalar::dNaN();
  return m_MaximumDiffusionFlux->GetValue(unit);
}

bool SESubstance::HasMichaelisCoefficient() const
{
  return (m_MichaelisCoefficient == nullptr) ? false : m_MichaelisCoefficient->IsValid();
}
SEScalar& SESubstance::GetMichaelisCoefficient()
{
  if (m_MichaelisCoefficient == nullptr)
    m_MichaelisCoefficient = new SEScalar();
  return *m_MichaelisCoefficient;
}
double SESubstance::GetMichaelisCoefficient() const
{
  if (m_MichaelisCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_MichaelisCoefficient->GetValue();
}

bool SESubstance::HasAerosolization() const
{
  return (m_Aerosolization != nullptr && m_Aerosolization->IsValid());
}
SESubstanceAerosolization& SESubstance::GetAerosolization()
{
  if (m_Aerosolization == nullptr)
    m_Aerosolization = new SESubstanceAerosolization(GetLogger());
  return *m_Aerosolization;
}
const SESubstanceAerosolization* SESubstance::GetAerosolization() const
{
  return m_Aerosolization;
}
void SESubstance::RemoveAerosolization()
{
  SAFE_DELETE(m_Aerosolization);
}

bool SESubstance::HasBloodConcentration() const
{
  return (m_BloodConcentration == nullptr) ? false : m_BloodConcentration->IsValid();
}
SEScalarMassPerVolume& SESubstance::GetBloodConcentration()
{
  if (m_BloodConcentration == nullptr)
    m_BloodConcentration = new SEScalarMassPerVolume();
  return *m_BloodConcentration;
}
double SESubstance::GetBloodConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_BloodConcentration == nullptr)
    return SEScalar::dNaN();
  return m_BloodConcentration->GetValue(unit);
}

bool SESubstance::HasMassInBody() const
{
  return (m_MassInBody == nullptr) ? false : m_MassInBody->IsValid();
}
SEScalarMass& SESubstance::GetMassInBody()
{
  if (m_MassInBody == nullptr)
    m_MassInBody = new SEScalarMass();
  return *m_MassInBody;
}
double SESubstance::GetMassInBody(const MassUnit& unit) const
{
  if (m_MassInBody == nullptr)
    return SEScalar::dNaN();
  return m_MassInBody->GetValue(unit);
}

bool SESubstance::HasMassInBlood() const
{
  return (m_MassInBlood == nullptr) ? false : m_MassInBlood->IsValid();
}
SEScalarMass& SESubstance::GetMassInBlood()
{
  if (m_MassInBlood == nullptr)
    m_MassInBlood = new SEScalarMass();
  return *m_MassInBlood;
}
double SESubstance::GetMassInBlood(const MassUnit& unit) const
{
  if (m_MassInBlood == nullptr)
    return SEScalar::dNaN();
  return m_MassInBlood->GetValue(unit);
}

bool SESubstance::HasMassInTissue() const
{
  return (m_MassInTissue == nullptr) ? false : m_MassInTissue->IsValid();
}
SEScalarMass& SESubstance::GetMassInTissue()
{
  if (m_MassInTissue == nullptr)
    m_MassInTissue = new SEScalarMass();
  return *m_MassInTissue;
}
double SESubstance::GetMassInTissue(const MassUnit& unit) const
{
  if (m_MassInTissue == nullptr)
    return SEScalar::dNaN();
  return m_MassInTissue->GetValue(unit);
}

bool SESubstance::HasPlasmaConcentration() const
{
  return (m_PlasmaConcentration == nullptr) ? false : m_PlasmaConcentration->IsValid();
}
SEScalarMassPerVolume& SESubstance::GetPlasmaConcentration()
{
  if (m_PlasmaConcentration == nullptr)
    m_PlasmaConcentration = new SEScalarMassPerVolume();
  return *m_PlasmaConcentration;
}
double SESubstance::GetPlasmaConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_PlasmaConcentration == nullptr)
    return SEScalar::dNaN();
  return m_PlasmaConcentration->GetValue(unit);
}

bool SESubstance::HasSystemicMassCleared() const
{
  return (m_SystemicMassCleared == nullptr) ? false : m_SystemicMassCleared->IsValid();
}
SEScalarMass& SESubstance::GetSystemicMassCleared()
{
  if (m_SystemicMassCleared == nullptr)
    m_SystemicMassCleared = new SEScalarMass();
  return *m_SystemicMassCleared;
}
double SESubstance::GetSystemicMassCleared(const MassUnit& unit) const
{
  if (m_SystemicMassCleared == nullptr)
    return SEScalar::dNaN();
  return m_SystemicMassCleared->GetValue(unit);
}

bool SESubstance::HasTissueConcentration() const
{
  return (m_TissueConcentration == nullptr) ? false : m_TissueConcentration->IsValid();
}
SEScalarMassPerVolume& SESubstance::GetTissueConcentration()
{
  if (m_TissueConcentration == nullptr)
    m_TissueConcentration = new SEScalarMassPerVolume();
  return *m_TissueConcentration;
}
double SESubstance::GetTissueConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_TissueConcentration == nullptr)
    return SEScalar::dNaN();
  return m_TissueConcentration->GetValue(unit);
}


bool SESubstance::HasAlveolarTransfer() const
{
  return m_AlveolarTransfer == nullptr ? false : m_AlveolarTransfer->IsValid();
}
SEScalarVolumePerTime& SESubstance::GetAlveolarTransfer()
{
  if (m_AlveolarTransfer == nullptr)
    m_AlveolarTransfer = new SEScalarVolumePerTime();
  return *m_AlveolarTransfer;
}
double SESubstance::GetAlveolarTransfer(const VolumePerTimeUnit& unit) const
{
  if (m_AlveolarTransfer == nullptr)
    return SEScalar::dNaN();
  return m_AlveolarTransfer->GetValue(unit);
}

bool SESubstance::HasDiffusingCapacity() const
{
  return m_DiffusingCapacity == nullptr ? false : m_DiffusingCapacity->IsValid();
}
SEScalarVolumePerTimePressure& SESubstance::GetDiffusingCapacity()
{
  if (m_DiffusingCapacity == nullptr)
    m_DiffusingCapacity = new SEScalarVolumePerTimePressure();
  return *m_DiffusingCapacity;
}
double SESubstance::GetDiffusingCapacity(const VolumePerTimePressureUnit& unit) const
{
  if (m_DiffusingCapacity == nullptr)
    return SEScalar::dNaN();
  return m_DiffusingCapacity->GetValue(unit);
}

bool SESubstance::HasEndTidalFraction() const
{
  return (m_EndTidalFraction == nullptr) ? false : m_EndTidalFraction->IsValid();
}
SEScalar0To1& SESubstance::GetEndTidalFraction()
{
  if (m_EndTidalFraction == nullptr)
    m_EndTidalFraction = new SEScalar0To1();
  return *m_EndTidalFraction;
}
double SESubstance::GetEndTidalFraction() const
{
  if (m_EndTidalFraction == nullptr)
    return SEScalar::dNaN();
  return m_EndTidalFraction->GetValue();
}

bool SESubstance::HasEndTidalPressure() const
{
  return (m_EndTidalPressure == nullptr) ? false : m_EndTidalPressure->IsValid();
}
SEScalarPressure& SESubstance::GetEndTidalPressure()
{
  if (m_EndTidalPressure == nullptr)
    m_EndTidalPressure = new SEScalarPressure();
  return *m_EndTidalPressure;
}
double SESubstance::GetEndTidalPressure(const PressureUnit& unit) const
{
  if (m_EndTidalPressure == nullptr)
    return SEScalar::dNaN();
  return m_EndTidalPressure->GetValue(unit);
}

bool SESubstance::HasRelativeDiffusionCoefficient() const
{
  return (m_RelativeDiffusionCoefficient == nullptr) ? false : m_RelativeDiffusionCoefficient->IsValid();
}
SEScalar& SESubstance::GetRelativeDiffusionCoefficient()
{
  if (m_RelativeDiffusionCoefficient == nullptr)
    m_RelativeDiffusionCoefficient = new SEScalar();
  return *m_RelativeDiffusionCoefficient;
}
double SESubstance::GetRelativeDiffusionCoefficient() const
{
  if (m_RelativeDiffusionCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_RelativeDiffusionCoefficient->GetValue();
}

bool SESubstance::HasSolubilityCoefficient() const
{
  return (m_SolubilityCoefficient == nullptr) ? false : m_SolubilityCoefficient->IsValid();
}
SEScalarInversePressure& SESubstance::GetSolubilityCoefficient()
{
  if (m_SolubilityCoefficient == nullptr)
    m_SolubilityCoefficient = new SEScalarInversePressure();
  return *m_SolubilityCoefficient;
}
double SESubstance::GetSolubilityCoefficient(const InversePressureUnit& unit) const
{
  if (m_SolubilityCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_SolubilityCoefficient->GetValue(unit);
}

bool SESubstance::HasClearance() const
{
  return (m_Clearance != nullptr && m_Clearance->IsValid());
}
SESubstanceClearance& SESubstance::GetClearance()
{
  if (m_Clearance == nullptr)
    m_Clearance = new SESubstanceClearance(GetLogger());
  return *m_Clearance;
}
const SESubstanceClearance* SESubstance::GetClearance() const
{
  return m_Clearance;
}
void SESubstance::RemoveClearance()
{
  SAFE_DELETE(m_Clearance);
}

bool SESubstance::HasPK() const
{
  return (m_PK != nullptr && m_PK->IsValid());
}
SESubstancePharmacokinetics& SESubstance::GetPK()
{
  if (m_PK == nullptr)
    m_PK = new SESubstancePharmacokinetics(GetLogger());
  return *m_PK;
}
const SESubstancePharmacokinetics* SESubstance::GetPK() const
{
  return m_PK;
}
void SESubstance::RemovePK()
{
  SAFE_DELETE(m_PK);
}

bool SESubstance::HasPD() const
{
  return (m_PD != nullptr && m_PD->IsValid());
}
SESubstancePharmacodynamics& SESubstance::GetPD()
{
  if (m_PD == nullptr)
    m_PD = new SESubstancePharmacodynamics(GetLogger());
  return *m_PD;
}
const SESubstancePharmacodynamics* SESubstance::GetPD() const
{
  return m_PD;
}
void SESubstance::RemovePD()
{
  SAFE_DELETE(m_PD);
}

