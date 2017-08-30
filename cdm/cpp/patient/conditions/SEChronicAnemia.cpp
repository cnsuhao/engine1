/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/conditions/SEChronicAnemia.h"
#include "properties/SEScalar0To1.h"
PROTO_PUSH
#include "bind/cdm/PatientConditions.pb.h"
PROTO_POP

SEChronicAnemia::SEChronicAnemia() : SEPatientCondition()
{
  m_ReductionFactor=nullptr;
}

SEChronicAnemia::~SEChronicAnemia()
{
  Clear();
}

void SEChronicAnemia::Clear()
{
  SEPatientCondition::Clear();
  SAFE_DELETE(m_ReductionFactor);
}

bool SEChronicAnemia::IsValid() const
{
  return SEPatientCondition::IsValid() && HasReductionFactor();
}

void SEChronicAnemia::Load(const cdm::ChronicAnemiaData& src, SEChronicAnemia& dst)
{
  SEChronicAnemia::Serialize(src, dst);
}
void SEChronicAnemia::Serialize(const cdm::ChronicAnemiaData& src, SEChronicAnemia& dst)
{
  SEPatientCondition::Serialize(src.patientcondition(), dst);
  if (src.has_reductionfactor())
    SEScalar0To1::Load(src.reductionfactor(), dst.GetReductionFactor());
}

cdm::ChronicAnemiaData* SEChronicAnemia::Unload(const SEChronicAnemia& src)
{
  cdm::ChronicAnemiaData* dst = new cdm::ChronicAnemiaData();
  SEChronicAnemia::Serialize(src, *dst);
  return dst;
}
void SEChronicAnemia::Serialize(const SEChronicAnemia& src, cdm::ChronicAnemiaData& dst)
{
  SEPatientCondition::Serialize(src, *dst.mutable_patientcondition());
  if (src.HasReductionFactor())
    dst.set_allocated_reductionfactor(SEScalar0To1::Unload(*src.m_ReductionFactor));
}

bool SEChronicAnemia::HasReductionFactor() const
{
  return m_ReductionFactor==nullptr?false:m_ReductionFactor->IsValid();
}

SEScalar0To1& SEChronicAnemia::GetReductionFactor()
{
  if(m_ReductionFactor==nullptr)
    m_ReductionFactor=new SEScalar0To1();
  return *m_ReductionFactor;
}

void SEChronicAnemia::ToString(std::ostream &str) const
{
  str << "Patient Condition : Anemia"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str << "\n\tReduction Factor: "; HasReductionFactor() ? str << m_ReductionFactor : str << "NaN";
  str << std::flush;
}