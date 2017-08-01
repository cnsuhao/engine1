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
#include "patient/actions/SESubstanceBolus.h"
#include "substance/SESubstance.h"
#include "properties/SEScalarMassPerVolume.h"

SESubstanceBolus::SESubstanceBolus(const SESubstance& substance) : SESubstanceAdministration(), m_Substance(substance)
{
  m_AdminRoute=(cdm::SubstanceBolusData_eAdministrationRoute)-1;
  m_Dose=nullptr;
  m_Concentration=nullptr;
}

SESubstanceBolus::~SESubstanceBolus()
{
  Clear();
}


void SESubstanceBolus::Clear()
{
  SESubstanceAdministration::Clear();
  m_AdminRoute=(cdm::SubstanceBolusData_eAdministrationRoute)-1;
  SAFE_DELETE(m_Dose);
  SAFE_DELETE(m_Concentration);
  // m_Substance=nullptr; Keeping mapping!!
}

bool SESubstanceBolus::IsValid() const
{
  return SESubstanceAdministration::IsValid() && HasDose() && HasConcentration() && HasAdminRoute();
}

bool SESubstanceBolus::IsActive() const
{
  return IsValid();
}

void SESubstanceBolus::Load(const cdm::SubstanceBolusData& src, SESubstanceBolus& dst)
{
  SESubstanceBolus::Serialize(src, dst);
}
void SESubstanceBolus::Serialize(const cdm::SubstanceBolusData& src, SESubstanceBolus& dst)
{
  SEPatientAction::Serialize(src.patientaction(), dst);
  dst.SetAdminRoute(src.administrationroute());
  if (src.has_dose())
    SEScalarVolume::Load(src.dose(), dst.GetDose());
  if (src.has_concentration())
    SEScalarMassPerVolume::Load(src.concentration(), dst.GetConcentration());
}

cdm::SubstanceBolusData* SESubstanceBolus::Unload(const SESubstanceBolus& src)
{
  cdm::SubstanceBolusData* dst = new cdm::SubstanceBolusData();
  SESubstanceBolus::Serialize(src, *dst);
  return dst;
}
void SESubstanceBolus::Serialize(const SESubstanceBolus& src, cdm::SubstanceBolusData& dst)
{
  SEPatientAction::Serialize(src, *dst.mutable_patientaction());
  dst.set_substance(src.m_Substance.GetName());
  if (src.HasAdminRoute())
    dst.set_administrationroute(src.m_AdminRoute);
  if(src.HasDose())
    dst.set_allocated_dose(SEScalarVolume::Unload(*src.m_Dose));
  if (src.HasConcentration())
    dst.set_allocated_concentration(SEScalarMassPerVolume::Unload(*src.m_Concentration));
}

cdm::SubstanceBolusData_eAdministrationRoute SESubstanceBolus::GetAdminRoute() const
{
  return m_AdminRoute;
}
void SESubstanceBolus::SetAdminRoute(cdm::SubstanceBolusData_eAdministrationRoute route)
{
  m_AdminRoute = route;
}
bool SESubstanceBolus::HasAdminRoute() const
{
  return m_AdminRoute==((cdm::SubstanceBolusData_eAdministrationRoute)-1)?false:true;
}
void SESubstanceBolus::InvalidateAdminRoute()
{
  m_AdminRoute = (cdm::SubstanceBolusData_eAdministrationRoute)-1;
}

bool SESubstanceBolus::HasDose() const
{
  return m_Dose==nullptr?false:m_Dose->IsValid();
}
SEScalarVolume& SESubstanceBolus::GetDose()
{
  if(m_Dose==nullptr)
    m_Dose=new SEScalarVolume();
  return *m_Dose;
}


bool SESubstanceBolus::HasConcentration() const
{
  return m_Concentration==nullptr?false:m_Concentration->IsValid();
}
SEScalarMassPerVolume& SESubstanceBolus::GetConcentration()
{
  if(m_Concentration==nullptr)
    m_Concentration=new SEScalarMassPerVolume();
  return *m_Concentration;
}

SESubstance& SESubstanceBolus::GetSubstance() const
{
  return (SESubstance&)m_Substance;
}

void SESubstanceBolus::ToString(std::ostream &str) const
{
  str << "Patient Action : Substance Bolus"; 
  if(HasComment())
    str<<"\n\tComment: "<<m_Comment;
  str  << "\n\tDose: "; HasDose()? str << *m_Dose : str << "No Dose Set";
  str  << "\n\tConcentration: "; HasConcentration()? str << *m_Concentration : str << "NaN";
  str << "\n\tSubstance: " << m_Substance.GetName();
  str  << "\n\tAdministration Route: "; HasAdminRoute()? str << GetAdminRoute() : str << "Not Set";
  str << std::flush;
}

SESubstanceBolusState::SESubstanceBolusState(const SESubstance& sub) : m_Substance(sub)
{
  m_ElapsedTime.SetValue(0, TimeUnit::s);
  m_AdministeredDose.SetValue(0, VolumeUnit::mL);
}
SESubstanceBolusState::~SESubstanceBolusState()
{

}

void SESubstanceBolusState::Load(const cdm::SubstanceBolusData_StateData& src, SESubstanceBolusState& dst)
{
  SESubstanceBolusState::Serialize(src, dst);
}
void SESubstanceBolusState::Serialize(const cdm::SubstanceBolusData_StateData& src, SESubstanceBolusState& dst)
{
  if (src.has_elapsedtime())
    SEScalarTime::Load(src.elapsedtime(), dst.GetElapsedTime());
  if (src.has_administereddose())
    SEScalarVolume::Load(src.administereddose(), dst.GetAdministeredDose());
}

cdm::SubstanceBolusData_StateData* SESubstanceBolusState::Unload(const SESubstanceBolusState& src)
{
  cdm::SubstanceBolusData_StateData* dst = new cdm::SubstanceBolusData_StateData();
  SESubstanceBolusState::Serialize(src, *dst);
  return dst;
}

void SESubstanceBolusState::Serialize(const SESubstanceBolusState& src, cdm::SubstanceBolusData_StateData& dst)
{
  //jbw - How do we do substance?
  dst.set_substance(src.m_Substance.GetName());
  dst.set_allocated_elapsedtime(SEScalarTime::Unload(src.m_ElapsedTime));
  dst.set_allocated_administereddose(SEScalarVolume::Unload(src.m_AdministeredDose));
}