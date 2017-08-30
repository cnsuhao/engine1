/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEPericardialEffusion.h"
#include "properties/SEScalarVolumePerTime.h"
PROTO_PUSH
#include "bind/cdm/PatientActions.pb.h"
PROTO_POP

SEPericardialEffusion::SEPericardialEffusion() : SEPatientAction()
{
  m_EffusionRate = nullptr;
}

SEPericardialEffusion::~SEPericardialEffusion()
{
  Clear();
}

void SEPericardialEffusion::Clear()
{
  SEPatientAction::Clear();
  SAFE_DELETE(m_EffusionRate);
}

bool SEPericardialEffusion::IsValid() const
{
  return SEPatientAction::IsValid() && HasEffusionRate();
}

bool SEPericardialEffusion::IsActive() const
{
  return IsValid() ? !m_EffusionRate->IsZero() : false;
}

void SEPericardialEffusion::Load(const cdm::PericardialEffusionData& src, SEPericardialEffusion& dst)
{
  SEPericardialEffusion::Serialize(src, dst);
}
void SEPericardialEffusion::Serialize(const cdm::PericardialEffusionData& src, SEPericardialEffusion& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_effusionrate())
    SEScalarVolumePerTime::Load(src.effusionrate(), dst.GetEffusionRate());
}

cdm::PericardialEffusionData* SEPericardialEffusion::Unload(const SEPericardialEffusion& src)
{
  cdm::PericardialEffusionData* dst = new cdm::PericardialEffusionData();
  SEPericardialEffusion::Serialize(src, *dst);
  return dst;
}
void SEPericardialEffusion::Serialize(const SEPericardialEffusion& src, cdm::PericardialEffusionData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasEffusionRate())
    dst.set_allocated_effusionrate(SEScalarVolumePerTime::Unload(*src.m_EffusionRate));
}

bool SEPericardialEffusion::HasEffusionRate() const
{
  return m_EffusionRate == nullptr ? false : m_EffusionRate->IsValid();
}

SEScalarVolumePerTime& SEPericardialEffusion::GetEffusionRate()
{
  if (m_EffusionRate == nullptr)
    m_EffusionRate = new SEScalarVolumePerTime();
  return *m_EffusionRate;
}

void SEPericardialEffusion::ToString(std::ostream &str) const
{
  str << "Patient Action : Pericardial Effusion"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tEffusion Rate: "; HasEffusionRate() ? str << *m_EffusionRate : str << "NaN";
  str << std::flush;
}