/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SESubstanceInfusion.h"
#include "substance/SESubstance.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEScalarMassPerVolume.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SESubstanceInfusion::SESubstanceInfusion(const SESubstance& substance) : SESubstanceAdministration(), m_Substance(substance)
{
  m_Rate=nullptr;
  m_Concentration=nullptr;
}

SESubstanceInfusion::~SESubstanceInfusion()
{
  Clear();
}


void SESubstanceInfusion::Clear()
{
  SESubstanceAdministration::Clear();
  m_Rate=nullptr;
  m_Concentration=nullptr;  
}


bool SESubstanceInfusion::IsValid() const
{
  return SESubstanceAdministration::IsValid() && HasRate() && HasConcentration();
}

bool SESubstanceInfusion::IsActive() const
{
  return IsValid() ? !m_Rate->IsZero() : false;
}

void SESubstanceInfusion::Load(const cdm::SubstanceInfusionData& src, SESubstanceInfusion& dst)
{
  SESubstanceInfusion::Serialize(src, dst);
}
void SESubstanceInfusion::Serialize(const cdm::SubstanceInfusionData& src, SESubstanceInfusion& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_rate())
    SEScalarVolumePerTime::Load(src.rate(), dst.GetRate());
  if (src.has_concentration())
    SEScalarMassPerVolume::Load(src.concentration(), dst.GetConcentration());
}

cdm::SubstanceInfusionData* SESubstanceInfusion::Unload(const SESubstanceInfusion& src)
{
  cdm::SubstanceInfusionData* dst = new cdm::SubstanceInfusionData();
  SESubstanceInfusion::Serialize(src, *dst);
  return dst;
}
void SESubstanceInfusion::Serialize(const SESubstanceInfusion& src, cdm::SubstanceInfusionData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.set_substance(src.m_Substance.GetName());
  if (src.HasRate())
    dst.set_allocated_rate(SEScalarVolumePerTime::Unload(*src.m_Rate));
  if (src.HasConcentration())
    dst.set_allocated_concentration(SEScalarMassPerVolume::Unload(*src.m_Concentration));
}

bool SESubstanceInfusion::HasRate() const
{
  return m_Rate==nullptr?false:m_Rate->IsValid();
}
SEScalarVolumePerTime& SESubstanceInfusion::GetRate()
{
  if(m_Rate==nullptr)
    m_Rate=new SEScalarVolumePerTime();
  return *m_Rate;
}

bool SESubstanceInfusion::HasConcentration() const
{
  return m_Concentration==nullptr?false:m_Concentration->IsValid();
}
SEScalarMassPerVolume& SESubstanceInfusion::GetConcentration()
{
  if(m_Concentration==nullptr)
    m_Concentration=new SEScalarMassPerVolume();
  return *m_Concentration;
}

SESubstance& SESubstanceInfusion::GetSubstance() const
{
  return (SESubstance&)m_Substance;
}

void SESubstanceInfusion::ToString(std::ostream &str) const
{
  str << "Patient Action : Substance Infusion"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tRate: "; HasRate() ? str << *m_Rate : str << "NaN";
  str << "\n\tConcentration: "; HasConcentration() ? str << *m_Concentration : str << "NaN";
  str << "\n\tSubstance: " << m_Substance.GetName();
  str  <<std::flush;
}