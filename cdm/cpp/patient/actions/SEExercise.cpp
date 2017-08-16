/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEExercise.h"
#include "properties/SEScalar0To1.h"

SEExercise::SEExercise() : SEPatientAction()
{
  m_Intensity = nullptr;
}

SEExercise::~SEExercise()
{
  Clear();
}

void SEExercise::Clear()
{
  SEPatientAction::Clear();
  SAFE_DELETE(m_Intensity);
}

bool SEExercise::IsValid() const
{
  return SEPatientAction::IsValid() && HasIntensity();
}

bool SEExercise::IsActive() const
{
  if (HasIntensity())
    return m_Intensity->IsPositive();
  return false;  
}

void SEExercise::Load(const cdm::ExerciseData& src, SEExercise& dst)
{
  SEExercise::Serialize(src, dst);
}
void SEExercise::Serialize(const cdm::ExerciseData& src, SEExercise& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_intensity())
    SEScalar0To1::Load(src.intensity(), dst.GetIntensity());
}

cdm::ExerciseData* SEExercise::Unload(const SEExercise& src)
{
  cdm::ExerciseData* dst = new cdm::ExerciseData();
  SEExercise::Serialize(src, *dst);
  return dst;
}
void SEExercise::Serialize(const SEExercise& src, cdm::ExerciseData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasIntensity())
    dst.set_allocated_intensity(SEScalar0To1::Unload(*src.m_Intensity));
}

bool SEExercise::HasIntensity() const
{
  return m_Intensity == nullptr ? false : m_Intensity->IsValid();
}
SEScalar0To1& SEExercise::GetIntensity()
{
  if (m_Intensity == nullptr)
    m_Intensity = new SEScalar0To1();
  return *m_Intensity;
}

void SEExercise::ToString(std::ostream &str) const
{
  str << "Patient Action : Exercise";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tIntensity: "; HasIntensity() ? str << *m_Intensity : str << "NaN";
  str << std::flush;
}
