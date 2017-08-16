/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "substance/SESubstanceTissuePharmacokinetics.h"
#include "properties/SEScalar.h"

SESubstanceTissuePharmacokinetics::SESubstanceTissuePharmacokinetics(const std::string& name, Logger* logger) : Loggable(logger), m_Name(name)
{
  m_PartitionCoefficient = nullptr;
}

SESubstanceTissuePharmacokinetics::~SESubstanceTissuePharmacokinetics()
{
  Clear();
}

void SESubstanceTissuePharmacokinetics::Clear()
{;
  SAFE_DELETE(m_PartitionCoefficient)
}

void SESubstanceTissuePharmacokinetics::Load(const cdm::SubstanceData_TissuePharmacokineticsData& src, SESubstanceTissuePharmacokinetics& dst)
{
  SESubstanceTissuePharmacokinetics::Serialize(src, dst);
}
void SESubstanceTissuePharmacokinetics::Serialize(const cdm::SubstanceData_TissuePharmacokineticsData& src, SESubstanceTissuePharmacokinetics& dst)
{
  dst.Clear();
  if (src.has_partitioncoefficient())
    SEScalar::Load(src.partitioncoefficient(),dst.GetPartitionCoefficient());
}

cdm::SubstanceData_TissuePharmacokineticsData* SESubstanceTissuePharmacokinetics::Unload(const SESubstanceTissuePharmacokinetics& src)
{
  cdm::SubstanceData_TissuePharmacokineticsData* dst = new cdm::SubstanceData_TissuePharmacokineticsData();
  SESubstanceTissuePharmacokinetics::Serialize(src,*dst);
  return dst;
}
void SESubstanceTissuePharmacokinetics::Serialize(const SESubstanceTissuePharmacokinetics& src, cdm::SubstanceData_TissuePharmacokineticsData& dst)
{
  dst.set_name(src.m_Name);
  if (src.HasPartitionCoefficient())
    dst.set_allocated_partitioncoefficient(SEScalar::Unload(*src.m_PartitionCoefficient));
}

const SEScalar* SESubstanceTissuePharmacokinetics::GetScalar(const std::string& name)
{
  if (name.compare("PartitionCoefficient") == 0)
    return &GetPartitionCoefficient();

  return nullptr;
}

std::string SESubstanceTissuePharmacokinetics::GetName() const
{
  return m_Name;
}

bool SESubstanceTissuePharmacokinetics::HasPartitionCoefficient() const
{
  return (m_PartitionCoefficient == nullptr) ? false : m_PartitionCoefficient->IsValid();
}
SEScalar& SESubstanceTissuePharmacokinetics::GetPartitionCoefficient()
{
  if (m_PartitionCoefficient == nullptr)
    m_PartitionCoefficient = new SEScalar();
  return *m_PartitionCoefficient;
}
double SESubstanceTissuePharmacokinetics::GetPartitionCoefficient() const
{
  if (m_PartitionCoefficient == nullptr)
    return SEScalar::dNaN();
  return m_PartitionCoefficient->GetValue();
}