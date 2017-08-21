/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/conditions/SEChronicVentricularSystolicDysfunction.h"

SEChronicVentricularSystolicDysfunction::SEChronicVentricularSystolicDysfunction() : SEChronicHeartFailure()
{
}

SEChronicVentricularSystolicDysfunction::~SEChronicVentricularSystolicDysfunction()
{
  Clear();
}

void SEChronicVentricularSystolicDysfunction::Clear()
{
  SEChronicHeartFailure::Clear();
}

bool SEChronicVentricularSystolicDysfunction::IsValid() const
{
  return SEChronicHeartFailure::IsValid();
}

void SEChronicVentricularSystolicDysfunction::Load(const cdm::ChronicVentricularSystolicDysfunctionData& src, SEChronicVentricularSystolicDysfunction& dst)
{
  SEChronicVentricularSystolicDysfunction::Serialize(src, dst);
}
void SEChronicVentricularSystolicDysfunction::Serialize(const cdm::ChronicVentricularSystolicDysfunctionData& src, SEChronicVentricularSystolicDysfunction& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
}

cdm::ChronicVentricularSystolicDysfunctionData* SEChronicVentricularSystolicDysfunction::Unload(const SEChronicVentricularSystolicDysfunction& src)
{
  cdm::ChronicVentricularSystolicDysfunctionData* dst = new cdm::ChronicVentricularSystolicDysfunctionData();
  SEChronicVentricularSystolicDysfunction::Serialize(src, *dst);
  return dst;
}
void SEChronicVentricularSystolicDysfunction::Serialize(const SEChronicVentricularSystolicDysfunction& src, cdm::ChronicVentricularSystolicDysfunctionData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
}

void SEChronicVentricularSystolicDysfunction::ToString(std::ostream &str) const
{
  str << "Patient Condition : Ventricular Systolic Dysfunction Heart Failure"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << std::flush;
}