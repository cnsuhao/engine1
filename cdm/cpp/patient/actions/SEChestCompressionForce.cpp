/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEChestCompressionForce.h"
#include "properties/SEScalarForce.h"

SEChestCompressionForce::SEChestCompressionForce() : SEChestCompression()
{
  m_Force = nullptr;
}

SEChestCompressionForce::~SEChestCompressionForce()
{
  Clear();
}

void SEChestCompressionForce::Clear()
{
  SEChestCompression::Clear();
  SAFE_DELETE(m_Force);
}

bool SEChestCompressionForce::IsValid() const
{
  return SEChestCompression::IsValid() && HasForce();
}

bool SEChestCompressionForce::IsActive() const
{
  return IsValid() ? !m_Force->IsZero() : false;
}

void SEChestCompressionForce::Load(const cdm::ChestCompressionForceData& src, SEChestCompressionForce& dst)
{
  SEChestCompressionForce::Serialize(src, dst);
}
void SEChestCompressionForce::Serialize(const cdm::ChestCompressionForceData& src, SEChestCompressionForce& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  if (src.has_force())
    SEScalarForce::Load(src.force(), dst.GetForce());
}

cdm::ChestCompressionForceData* SEChestCompressionForce::Unload(const SEChestCompressionForce& src)
{
  cdm::ChestCompressionForceData* dst = new cdm::ChestCompressionForceData();
  SEChestCompressionForce::Serialize(src, *dst);
  return dst;
}
void SEChestCompressionForce::Serialize(const SEChestCompressionForce& src, cdm::ChestCompressionForceData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  if (src.HasForce())
    dst.set_allocated_force(SEScalarForce::Unload(*src.m_Force));
}

bool SEChestCompressionForce::HasForce() const
{
  return m_Force == nullptr ? false : m_Force->IsValid();
}

SEScalarForce& SEChestCompressionForce::GetForce()
{
  if (m_Force == nullptr)
    m_Force = new SEScalarForce();
  return *m_Force;
}

void SEChestCompressionForce::ToString(std::ostream &str) const
{
  str << "Patient Action : Chest Compression";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tForce: "; HasForce() ? str << *m_Force : str << "NaN";
  str << std::flush;
}