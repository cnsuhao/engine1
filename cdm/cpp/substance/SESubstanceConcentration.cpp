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
#include "substance/SESubstance.h"
#include "substance/SESubstanceManager.h"
#include "substance/SESubstanceConcentration.h"
#include "properties/SEScalarMassPerVolume.h"

SESubstanceConcentration::SESubstanceConcentration(SESubstance& substance) : Loggable(substance.GetLogger()), m_Substance(substance)
{
  m_Concentration=nullptr;
}

SESubstanceConcentration::~SESubstanceConcentration()
{
  Clear();
}

void SESubstanceConcentration::Clear()
{
  SAFE_DELETE(m_Concentration);
}

void SESubstanceConcentration::Load(const cdm::SubstanceData_ConcentrationData& src, SESubstanceConcentration& dst)
{
  dst.Clear();
  if(src.has_concentration())
    SEScalarMassPerVolume::Load(src.concentration(),dst.GetConcentration());
}
void SESubstanceConcentration::Serialize(const cdm::SubstanceData_ConcentrationData& src, SESubstanceConcentration& dst)
{

}

cdm::SubstanceData_ConcentrationData* SESubstanceConcentration::Unload(const SESubstanceConcentration& src)
{
  cdm::SubstanceData_ConcentrationData* dst = new cdm::SubstanceData_ConcentrationData();
  SESubstanceConcentration::Serialize(src,*dst);
  return dst;
}

void SESubstanceConcentration::Serialize(const SESubstanceConcentration& src, cdm::SubstanceData_ConcentrationData& dst)
{
  dst.set_name(src.m_Substance.GetName());
  if (src.HasConcentration())
    dst.set_allocated_concentration(SEScalarMassPerVolume::Unload(*src.m_Concentration));
}


bool SESubstanceConcentration::HasConcentration() const
{
  return (m_Concentration==nullptr)?false:m_Concentration->IsValid();
}
SEScalarMassPerVolume& SESubstanceConcentration::GetConcentration()
{
  if(m_Concentration==nullptr)
    m_Concentration=new SEScalarMassPerVolume();
  return *m_Concentration;
}
double SESubstanceConcentration::GetConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_Concentration == nullptr)
    return SEScalar::dNaN();
  return m_Concentration->GetValue(unit);
}

SESubstance& SESubstanceConcentration::GetSubstance() const
{
  return m_Substance;
}
