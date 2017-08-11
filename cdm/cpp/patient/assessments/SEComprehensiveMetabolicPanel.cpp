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
#include "patient/assessments/SEComprehensiveMetabolicPanel.h"
#include "system/physiology/SEBloodChemistrySystem.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include <google/protobuf/text_format.h>


SEComprehensiveMetabolicPanel::SEComprehensiveMetabolicPanel(Logger* logger) : SEPatientAssessment(logger)
{
  m_Albumin = nullptr;
  m_ALP = nullptr;
  m_ALT = nullptr;
  m_AST = nullptr;
  m_BUN = nullptr;
  m_Calcium = nullptr;
  m_Chloride = nullptr;
  m_CO2 = nullptr;
  m_Creatinine = nullptr;
  m_Glucose = nullptr;
  m_Potassium = nullptr;
  m_Sodium = nullptr;
  m_TotalBilirubin = nullptr;
  m_TotalProtein = nullptr;
}

SEComprehensiveMetabolicPanel::~SEComprehensiveMetabolicPanel()
{
  Clear();
}

void SEComprehensiveMetabolicPanel::Clear()
{
  SEPatientAssessment::Clear();
  SAFE_DELETE(m_Albumin);
  SAFE_DELETE(m_ALP);
  SAFE_DELETE(m_ALT);
  SAFE_DELETE(m_AST);
  SAFE_DELETE(m_BUN);
  SAFE_DELETE(m_Calcium);
  SAFE_DELETE(m_Chloride);
  SAFE_DELETE(m_CO2);
  SAFE_DELETE(m_Creatinine);
  SAFE_DELETE(m_Glucose);
  SAFE_DELETE(m_Potassium);
  SAFE_DELETE(m_Sodium);
  SAFE_DELETE(m_TotalBilirubin);
  SAFE_DELETE(m_TotalProtein);
}

std::string SEComprehensiveMetabolicPanel::Save() const
{
  std::string content;
  cdm::ComprehensiveMetabolicPanelData* src = SEComprehensiveMetabolicPanel::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  return content;
}
void SEComprehensiveMetabolicPanel::SaveFile(const std::string& filename) const
{
  std::string content;
  cdm::ComprehensiveMetabolicPanelData* src = SEComprehensiveMetabolicPanel::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  delete src;
}

void SEComprehensiveMetabolicPanel::Load(const cdm::ComprehensiveMetabolicPanelData& src, SEComprehensiveMetabolicPanel& dst)
{
  SEComprehensiveMetabolicPanel::Serialize(src, dst);
}
void SEComprehensiveMetabolicPanel::Serialize(const cdm::ComprehensiveMetabolicPanelData& src, SEComprehensiveMetabolicPanel& dst)
{
  SEPatientAssessment::Serialize(src.patientassessment(), dst);
  if (src.has_albumin())
    SEScalarMassPerVolume::Load(src.albumin(), dst.GetAlbumin());
  if (src.has_alp())
    SEScalarMassPerVolume::Load(src.alp(), dst.GetALP());
  if (src.has_alt())
    SEScalarMassPerVolume::Load(src.alt(), dst.GetALT());
  if (src.has_ast())
    SEScalarMassPerVolume::Load(src.ast(), dst.GetAST());
  if (src.has_bun())
    SEScalarMassPerVolume::Load(src.bun(), dst.GetBUN());
  if (src.has_calcium())
    SEScalarMassPerVolume::Load(src.calcium(), dst.GetCalcium());
  if (src.has_chloride())
    SEScalarAmountPerVolume::Load(src.chloride(), dst.GetChloride());
  if (src.has_co2())
    SEScalarAmountPerVolume::Load(src.co2(), dst.GetCO2());
  if (src.has_creatinine())
    SEScalarMassPerVolume::Load(src.creatinine(), dst.GetCreatinine());
  if (src.has_glucose())
    SEScalarMassPerVolume::Load(src.glucose(), dst.GetGlucose());
  if (src.has_potassium())
    SEScalarAmountPerVolume::Load(src.potassium(), dst.GetPotassium());
  if (src.has_sodium())
    SEScalarAmountPerVolume::Load(src.sodium(), dst.GetSodium());
  if (src.has_totalbilirubin())
    SEScalarMassPerVolume::Load(src.totalbilirubin(), dst.GetTotalBilirubin());
  if (src.has_totalprotein())
    SEScalarMassPerVolume::Load(src.totalprotein(), dst.GetTotalProtein());
}

cdm::ComprehensiveMetabolicPanelData* SEComprehensiveMetabolicPanel::Unload(const SEComprehensiveMetabolicPanel& src)
{
  cdm::ComprehensiveMetabolicPanelData* dst = new cdm::ComprehensiveMetabolicPanelData();
  SEComprehensiveMetabolicPanel::Serialize(src, *dst);
  return dst;
}
void SEComprehensiveMetabolicPanel::Serialize(const SEComprehensiveMetabolicPanel& src, cdm::ComprehensiveMetabolicPanelData& dst)
{
  SEPatientAssessment::Serialize(src, *dst.mutable_patientassessment());
  if (src.HasAlbumin())
    dst.set_allocated_albumin(SEScalarMassPerVolume::Unload(*src.m_Albumin));
  if (src.HasALP())
    dst.set_allocated_alp(SEScalarMassPerVolume::Unload(*src.m_ALP));
  if (src.HasALT())
      dst.set_allocated_alt(SEScalarMassPerVolume::Unload(*src.m_ALT));
  if (src.HasAST())
    dst.set_allocated_ast(SEScalarMassPerVolume::Unload(*src.m_AST));
  if (src.HasBUN())
    dst.set_allocated_bun(SEScalarMassPerVolume::Unload(*src.m_BUN));
  if (src.HasCalcium())
    dst.set_allocated_calcium(SEScalarMassPerVolume::Unload(*src.m_Calcium));
  if (src.HasChloride())
    dst.set_allocated_chloride(SEScalarAmountPerVolume::Unload(*src.m_Chloride));
  if (src.HasCO2())
    dst.set_allocated_co2(SEScalarAmountPerVolume::Unload(*src.m_CO2));
  if (src.HasCreatinine())
    dst.set_allocated_creatinine(SEScalarMassPerVolume::Unload(*src.m_Creatinine));
  if (src.HasGlucose())
    dst.set_allocated_glucose(SEScalarMassPerVolume::Unload(*src.m_Glucose));
  if (src.HasPotassium())
    dst.set_allocated_potassium(SEScalarAmountPerVolume::Unload(*src.m_Potassium));
  if (src.HasSodium())
    dst.set_allocated_sodium(SEScalarAmountPerVolume::Unload(*src.m_Sodium));
  if (src.HasTotalBilirubin())
    dst.set_allocated_totalbilirubin(SEScalarMassPerVolume::Unload(*src.m_TotalBilirubin));
  if (src.HasTotalProtein())
    dst.set_allocated_totalprotein(SEScalarMassPerVolume::Unload(*src.m_TotalProtein));
}

bool SEComprehensiveMetabolicPanel::HasAlbumin() const
{
  return m_Albumin == nullptr ? false : m_Albumin->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetAlbumin()
{
  if (m_Albumin == nullptr)
    m_Albumin = new SEScalarMassPerVolume();
  return *m_Albumin;
}
double SEComprehensiveMetabolicPanel::GetAlbumin(const MassPerVolumeUnit& unit) const
{
  if (!HasAlbumin())
    return SEScalar::dNaN();
  return m_Albumin->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasALP() const
{
  return m_ALP == nullptr ? false : m_ALP->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetALP()
{
  if (m_ALP == nullptr)
    m_ALP = new SEScalarMassPerVolume();
  return *m_ALP;
}
double SEComprehensiveMetabolicPanel::GetALP(const MassPerVolumeUnit& unit) const
{
  if (!HasALP())
    return SEScalar::dNaN();
  return m_ALP->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasALT() const
{
  return m_ALT == nullptr ? false : m_ALT->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetALT()
{
  if (m_ALT == nullptr)
    m_ALT = new SEScalarMassPerVolume();
  return *m_ALT;
}
double SEComprehensiveMetabolicPanel::GetALT(const MassPerVolumeUnit& unit) const
{
  if (!HasALT())
    return SEScalar::dNaN();
  return m_ALT->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasAST() const
{
  return m_AST == nullptr ? false : m_AST->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetAST()
{
  if (m_AST == nullptr)
    m_AST = new SEScalarMassPerVolume();
  return *m_AST;
}
double SEComprehensiveMetabolicPanel::GetAST(const MassPerVolumeUnit& unit) const
{
  if (!HasAST())
    return SEScalar::dNaN();
  return m_AST->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasBUN() const
{
  return m_BUN == nullptr ? false : m_BUN->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetBUN()
{
  if (m_BUN == nullptr)
    m_BUN = new SEScalarMassPerVolume();
  return *m_BUN;
}
double SEComprehensiveMetabolicPanel::GetBUN(const MassPerVolumeUnit& unit) const
{
  if (!HasBUN())
    return SEScalar::dNaN();
  return m_BUN->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasCalcium() const
{
  return m_Calcium == nullptr ? false : m_Calcium->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetCalcium()
{
  if (m_Calcium == nullptr)
    m_Calcium = new SEScalarMassPerVolume();
  return *m_Calcium;
}
double SEComprehensiveMetabolicPanel::GetCalcium(const MassPerVolumeUnit& unit) const
{
  if (!HasCalcium())
    return SEScalar::dNaN();
  return m_Calcium->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasChloride() const
{
  return m_Chloride == nullptr ? false : m_Chloride->IsValid();
}
SEScalarAmountPerVolume& SEComprehensiveMetabolicPanel::GetChloride()
{
  if (m_Chloride == nullptr)
    m_Chloride = new SEScalarAmountPerVolume();
  return *m_Chloride;
}
double SEComprehensiveMetabolicPanel::GetChloride(const AmountPerVolumeUnit& unit) const
{
  if (!HasChloride())
    return SEScalar::dNaN();
  return m_Chloride->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasCO2() const
{
  return m_CO2 == nullptr ? false : m_CO2->IsValid();
}
SEScalarAmountPerVolume& SEComprehensiveMetabolicPanel::GetCO2()
{
  if (m_CO2 == nullptr)
    m_CO2 = new SEScalarAmountPerVolume();
  return *m_CO2;
}
double SEComprehensiveMetabolicPanel::GetCO2(const AmountPerVolumeUnit& unit) const
{
  if (!HasCO2())
    return SEScalar::dNaN();
  return m_CO2->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasCreatinine() const
{
  return m_Creatinine == nullptr ? false : m_Creatinine->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetCreatinine()
{
  if (m_Creatinine == nullptr)
    m_Creatinine = new SEScalarMassPerVolume();
  return *m_Creatinine;
}
double SEComprehensiveMetabolicPanel::GetCreatinine(const MassPerVolumeUnit& unit) const
{
  if (!HasCreatinine())
    return SEScalar::dNaN();
  return m_Creatinine->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasGlucose() const
{
  return m_Glucose == nullptr ? false : m_Glucose->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetGlucose()
{
  if (m_Glucose == nullptr)
    m_Glucose = new SEScalarMassPerVolume();
  return *m_Glucose;
}
double SEComprehensiveMetabolicPanel::GetGlucose(const MassPerVolumeUnit& unit) const
{
  if (!HasGlucose())
    return SEScalar::dNaN();
  return m_Glucose->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasPotassium() const
{
  return m_Potassium == nullptr ? false : m_Potassium->IsValid();
}
SEScalarAmountPerVolume& SEComprehensiveMetabolicPanel::GetPotassium()
{
  if (m_Potassium == nullptr)
    m_Potassium = new SEScalarAmountPerVolume();
  return *m_Potassium;
}
double SEComprehensiveMetabolicPanel::GetPotassium(const AmountPerVolumeUnit& unit) const
{
  if (!HasPotassium())
    return SEScalar::dNaN();
  return m_Potassium->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasSodium() const
{
  return m_Sodium == nullptr ? false : m_Sodium->IsValid();
}
SEScalarAmountPerVolume& SEComprehensiveMetabolicPanel::GetSodium()
{
  if (m_Sodium == nullptr)
    m_Sodium = new SEScalarAmountPerVolume();
  return *m_Sodium;
}
double SEComprehensiveMetabolicPanel::GetSodium(const AmountPerVolumeUnit& unit) const
{
  if (!HasSodium())
    return SEScalar::dNaN();
  return m_Sodium->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasTotalBilirubin() const
{
  return m_TotalBilirubin == nullptr ? false : m_TotalBilirubin->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetTotalBilirubin()
{
  if (m_TotalBilirubin == nullptr)
    m_TotalBilirubin = new SEScalarMassPerVolume();
  return *m_TotalBilirubin;
}
double SEComprehensiveMetabolicPanel::GetTotalBilirubin(const MassPerVolumeUnit& unit) const
{
  if (!HasTotalBilirubin())
    return SEScalar::dNaN();
  return m_TotalBilirubin->GetValue(unit);
}

bool SEComprehensiveMetabolicPanel::HasTotalProtein() const
{
  return m_TotalProtein == nullptr ? false : m_TotalProtein->IsValid();
}
SEScalarMassPerVolume& SEComprehensiveMetabolicPanel::GetTotalProtein()
{
  if (m_TotalProtein == nullptr)
    m_TotalProtein = new SEScalarMassPerVolume();
  return *m_TotalProtein;
}
double SEComprehensiveMetabolicPanel::GetTotalProtein(const MassPerVolumeUnit& unit) const
{
  if (!HasTotalProtein())
    return SEScalar::dNaN();
  return m_TotalProtein->GetValue(unit);
}