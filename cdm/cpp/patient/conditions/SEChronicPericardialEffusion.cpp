/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/conditions/SEChronicPericardialEffusion.h"
#include "properties/SEScalarVolume.h"

SEChronicPericardialEffusion::SEChronicPericardialEffusion() : SEPatientCondition()
{
  m_AccumulatedVolume = nullptr;
}

SEChronicPericardialEffusion::~SEChronicPericardialEffusion()
{
  Clear();
}

void SEChronicPericardialEffusion::Clear()
{
  SEPatientCondition::Clear();
  SAFE_DELETE(m_AccumulatedVolume);
}

bool SEChronicPericardialEffusion::IsValid() const
{
  return SEPatientCondition::IsValid() && HasAccumulatedVolume();
}

void SEChronicPericardialEffusion::Load(const cdm::ChronicPericardialEffusionData& src, SEChronicPericardialEffusion& dst)
{
  SEChronicPericardialEffusion::Serialize(src, dst);
}
void SEChronicPericardialEffusion::Serialize(const cdm::ChronicPericardialEffusionData& src, SEChronicPericardialEffusion& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
  if (src.has_accumulatedvolume())
    SEScalarVolume::Load(src.accumulatedvolume(), dst.GetAccumulatedVolume());
}

cdm::ChronicPericardialEffusionData* SEChronicPericardialEffusion::Unload(const SEChronicPericardialEffusion& src)
{
  cdm::ChronicPericardialEffusionData* dst = new cdm::ChronicPericardialEffusionData();
  SEChronicPericardialEffusion::Serialize(src, *dst);
  return dst;
}
void SEChronicPericardialEffusion::Serialize(const SEChronicPericardialEffusion& src, cdm::ChronicPericardialEffusionData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
  if (src.HasAccumulatedVolume())
    dst.set_allocated_accumulatedvolume(SEScalarVolume::Unload(*src.m_AccumulatedVolume));
}

bool SEChronicPericardialEffusion::HasAccumulatedVolume() const
{
  return m_AccumulatedVolume == nullptr ? false : m_AccumulatedVolume->IsValid();
}

SEScalarVolume& SEChronicPericardialEffusion::GetAccumulatedVolume()
{
  if (m_AccumulatedVolume == nullptr)
    m_AccumulatedVolume = new SEScalarVolume();
  return *m_AccumulatedVolume;
}


void SEChronicPericardialEffusion::ToString(std::ostream &str) const
{
  str << "Patient Condition : Pericardial Effusion";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << std::flush;
}