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
#include "system/physiology/SEBloodChemistrySystem.h"
#include "substance/SESubstanceManager.h"
#include "properties/SEScalarAmountPerVolume.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMass.h"
#include "properties/SEScalarMassPerVolume.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarPressure.h"
#include "properties/SEScalarHeatCapacitancePerMass.h"

SEBloodChemistrySystem::SEBloodChemistrySystem(Logger* logger) : SESystem(logger)
{
  m_BloodDensity = nullptr;
  
  m_BloodPH = nullptr;
  m_BloodSpecificHeat = nullptr;
  m_BloodUreaNitrogenConcentration = nullptr;
  m_CarbonDioxideSaturation = nullptr;
  m_CarbonMonoxideSaturation = nullptr;
  m_Hematocrit = nullptr;
  m_HemoglobinContent = nullptr;
  m_OxygenSaturation = nullptr;
  m_Phosphate = nullptr;
  m_PlasmaVolume = nullptr;
  m_PulseOximetry = nullptr;
  m_RedBloodCellCount = nullptr;
  m_ShuntFraction = nullptr;
  m_StrongIonDifference = nullptr;
  m_TotalProteinConcentration = nullptr;
  m_VolumeFractionNeutralPhospholipidInPlasma = nullptr;
  m_VolumeFractionNeutralLipidInPlasma = nullptr;
  m_WhiteBloodCellCount = nullptr;

  m_ArterialCarbonDioxidePressure = nullptr;
  m_ArterialOxygenPressure = nullptr;
  m_PulmonaryArterialCarbonDioxidePressure = nullptr;
  m_PulmonaryArterialOxygenPressure = nullptr;
  m_PulmonaryVenousCarbonDioxidePressure = nullptr;
  m_PulmonaryVenousOxygenPressure = nullptr;
  m_VenousCarbonDioxidePressure = nullptr;
  m_VenousOxygenPressure = nullptr;
}

SEBloodChemistrySystem::~SEBloodChemistrySystem()
{
  Clear();
}

void SEBloodChemistrySystem::Clear()
{
  SESystem::Clear();

  SAFE_DELETE(m_BloodDensity);
  SAFE_DELETE(m_BloodPH);
  SAFE_DELETE(m_BloodSpecificHeat);
  SAFE_DELETE(m_BloodUreaNitrogenConcentration);
  SAFE_DELETE(m_CarbonDioxideSaturation);
  SAFE_DELETE(m_CarbonMonoxideSaturation);
  SAFE_DELETE(m_Hematocrit);
  SAFE_DELETE(m_HemoglobinContent);
  SAFE_DELETE(m_OxygenSaturation);
  SAFE_DELETE(m_Phosphate);
  SAFE_DELETE(m_PlasmaVolume);
  SAFE_DELETE(m_PulseOximetry);
  SAFE_DELETE(m_RedBloodCellCount);
  SAFE_DELETE(m_ShuntFraction);
  SAFE_DELETE(m_StrongIonDifference);
  SAFE_DELETE(m_TotalProteinConcentration);
  SAFE_DELETE(m_VolumeFractionNeutralPhospholipidInPlasma);
  SAFE_DELETE(m_VolumeFractionNeutralLipidInPlasma);
  SAFE_DELETE(m_WhiteBloodCellCount);

  SAFE_DELETE(m_PulmonaryVenousOxygenPressure);
  SAFE_DELETE(m_PulmonaryArterialOxygenPressure);
  SAFE_DELETE(m_PulmonaryVenousCarbonDioxidePressure);
  SAFE_DELETE(m_PulmonaryArterialCarbonDioxidePressure);
  SAFE_DELETE(m_ArterialOxygenPressure);
  SAFE_DELETE(m_VenousOxygenPressure);
  SAFE_DELETE(m_ArterialCarbonDioxidePressure);
  SAFE_DELETE(m_VenousCarbonDioxidePressure);
}

const SEScalar* SEBloodChemistrySystem::GetScalar(const std::string& name)
{
  if (name.compare("BloodDensity") == 0)
    return &GetBloodDensity();
  if (name.compare("BloodPH") == 0)
    return &GetBloodPH();
  if (name.compare("BloodSpecificHeat") == 0)
    return &GetBloodSpecificHeat();
  if (name.compare("BloodUreaNitrogenConcentration") == 0)
    return &GetBloodUreaNitrogenConcentration();
  if (name.compare("CarbonDioxideSaturation") == 0)
    return &GetCarbonDioxideSaturation();
  if (name.compare("CarbonMonoxideSaturation") == 0)
    return &GetCarbonMonoxideSaturation();
  if (name.compare("Hematocrit") == 0)
    return &GetHematocrit();
  if (name.compare("HemoglobinContent") == 0)
    return &GetHemoglobinContent();
  if (name.compare("OxygenSaturation") == 0)
    return &GetOxygenSaturation();
  if (name.compare("Phosphate") == 0)
    return &GetPhosphate();
  if (name.compare("PlasmaVolume") == 0)
    return &GetPlasmaVolume();
  if (name.compare("PulseOximetry") == 0)
    return &GetPulseOximetry();
  if (name.compare("RedBloodCellCount") == 0)
    return &GetRedBloodCellCount();
  if (name.compare("ShuntFraction") == 0)
    return &GetShuntFraction();  
  if (name.compare("StrongIonDifference") == 0)
    return &GetStrongIonDifference();
  if (name.compare("TotalProteinConcentration") == 0)
    return &GetTotalProteinConcentration();
  if (name.compare("VolumeFractionNeutralPhospholipidInPlasma") == 0)
    return &GetVolumeFractionNeutralPhospholipidInPlasma();
  if (name.compare("VolumeFractionNeutralLipidInPlasma") == 0)
    return &GetVolumeFractionNeutralLipidInPlasma();
  if (name.compare("WhiteBloodCellCount") == 0)
    return &GetWhiteBloodCellCount();  
  if (name.compare("ArterialCarbonDioxidePressure") == 0)
    return &GetArterialCarbonDioxidePressure();
  if (name.compare("ArterialOxygenPressure") == 0)
    return &GetArterialOxygenPressure();
  if (name.compare("PulmonaryArterialCarbonDioxidePressure") == 0)
    return &GetPulmonaryArterialCarbonDioxidePressure();
  if (name.compare("PulmonaryArterialOxygenPressure") == 0)
    return &GetPulmonaryArterialOxygenPressure();
  if (name.compare("PulmonaryVenousCarbonDioxidePressure") == 0)
    return &GetPulmonaryVenousCarbonDioxidePressure();
  if (name.compare("PulmonaryVenousOxygenPressure") == 0)
    return &GetPulmonaryVenousOxygenPressure();
  if (name.compare("VenousCarbonDioxidePressure") == 0)
    return &GetVenousCarbonDioxidePressure();
  if (name.compare("VenousOxygenPressure") == 0)
    return &GetVenousOxygenPressure();

  return nullptr;
}

void SEBloodChemistrySystem::Load(const cdm::BloodChemistrySystemData& src, SEBloodChemistrySystem& dst)
{
  SEBloodChemistrySystem::Serialize(src, dst);
}
void SEBloodChemistrySystem::Serialize(const cdm::BloodChemistrySystemData& src, SEBloodChemistrySystem& dst)
{
  dst.Clear();
  if (src.has_blooddensity())
    SEScalarMassPerVolume::Load(src.blooddensity(), dst.GetBloodDensity());
  if (src.has_bloodph())
    SEScalar::Load(src.bloodph(), dst.GetBloodPH());
  if (src.has_bloodspecificheat())
    SEScalarHeatCapacitancePerMass::Load(src.bloodspecificheat(), dst.GetBloodSpecificHeat());
  if (src.has_bloodureanitrogenconcentration())
    SEScalarMassPerVolume::Load(src.bloodureanitrogenconcentration(), dst.GetBloodUreaNitrogenConcentration());
  if (src.has_carbondioxidesaturation())
    SEScalar0To1::Load(src.carbondioxidesaturation(), dst.GetCarbonDioxideSaturation());
  if (src.has_carbonmonoxidesaturation())
    SEScalar0To1::Load(src.carbonmonoxidesaturation(), dst.GetCarbonMonoxideSaturation());
  if (src.has_hematocrit())
    SEScalar0To1::Load(src.hematocrit(), dst.GetHematocrit());
  if (src.has_hemoglobincontent())
    SEScalarMass::Load(src.hemoglobincontent(), dst.GetHemoglobinContent());
  if (src.has_oxygensaturation())
    SEScalar0To1::Load(src.oxygensaturation(), dst.GetOxygenSaturation());
  if (src.has_phosphate())
    SEScalarAmountPerVolume::Load(src.phosphate(), dst.GetPhosphate());
  if (src.has_plasmavolume())
    SEScalarVolume::Load(src.plasmavolume(), dst.GetPlasmaVolume());
  if (src.has_pulseoximetry())
    SEScalar0To1::Load(src.pulseoximetry(), dst.GetPulseOximetry());
  if (src.has_redbloodcellcount())
    SEScalarAmountPerVolume::Load(src.redbloodcellcount(), dst.GetRedBloodCellCount());
  if (src.has_shuntfraction())
    SEScalar0To1::Load(src.shuntfraction(), dst.GetShuntFraction());
  if (src.has_strongiondifference())
    SEScalarAmountPerVolume::Load(src.strongiondifference(), dst.GetStrongIonDifference());
  if (src.has_totalproteinconcentration())
    SEScalarMassPerVolume::Load(src.totalproteinconcentration(), dst.GetTotalProteinConcentration());
  if (src.has_volumefractionneutralphospholipidinplasma())
    SEScalar0To1::Load(src.volumefractionneutralphospholipidinplasma(), dst.GetVolumeFractionNeutralPhospholipidInPlasma());
  if (src.has_volumefractionneutrallipidinplasma())
    SEScalar0To1::Load(src.volumefractionneutrallipidinplasma(), dst.GetVolumeFractionNeutralLipidInPlasma());
  if (src.has_whitebloodcellcount())
    SEScalarAmountPerVolume::Load(src.whitebloodcellcount(), dst.GetWhiteBloodCellCount());

  if (src.has_arterialcarbondioxidepressure())
    SEScalarPressure::Load(src.arterialcarbondioxidepressure(), dst.GetArterialCarbonDioxidePressure());
  if (src.has_arterialoxygenpressure())
    SEScalarPressure::Load(src.arterialoxygenpressure(), dst.GetArterialOxygenPressure());
  if (src.has_pulmonaryarterialcarbondioxidepressure())
    SEScalarPressure::Load(src.pulmonaryarterialcarbondioxidepressure(), dst.GetPulmonaryArterialCarbonDioxidePressure());
  if (src.has_pulmonaryarterialoxygenpressure())
    SEScalarPressure::Load(src.pulmonaryarterialoxygenpressure(), dst.GetPulmonaryArterialOxygenPressure());
  if (src.has_pulmonaryvenousoxygenpressure())
    SEScalarPressure::Load(src.pulmonaryvenousoxygenpressure(), dst.GetPulmonaryVenousOxygenPressure());
  if (src.has_pulmonaryvenouscarbondioxidepressure())
    SEScalarPressure::Load(src.pulmonaryvenouscarbondioxidepressure(), dst.GetPulmonaryVenousCarbonDioxidePressure());
  if (src.has_venouscarbondioxidepressure())
    SEScalarPressure::Load(src.venouscarbondioxidepressure(), dst.GetVenousCarbonDioxidePressure());
  if (src.has_venousoxygenpressure())
    SEScalarPressure::Load(src.venousoxygenpressure(), dst.GetVenousOxygenPressure());
}

cdm::BloodChemistrySystemData* SEBloodChemistrySystem::Unload(const SEBloodChemistrySystem& src)
{
  cdm::BloodChemistrySystemData* dst = new cdm::BloodChemistrySystemData();
  SEBloodChemistrySystem::Serialize(src, *dst);
  return dst;
}
void SEBloodChemistrySystem::Serialize(const SEBloodChemistrySystem& src, cdm::BloodChemistrySystemData& dst)
{
  if (src.HasBloodDensity())
    dst.set_allocated_blooddensity(SEScalarMassPerVolume::Unload(*src.m_BloodDensity));
  if (src.HasBloodPH())
    dst.set_allocated_bloodph(SEScalar::Unload(*src.m_BloodPH));
  if (src.HasBloodSpecificHeat())
    dst.set_allocated_bloodspecificheat(SEScalarHeatCapacitancePerMass::Unload(*src.m_BloodSpecificHeat));
  if (src.HasBloodUreaNitrogenConcentration())
    dst.set_allocated_bloodureanitrogenconcentration(SEScalarMassPerVolume::Unload(*src.m_BloodUreaNitrogenConcentration));
  if (src.HasCarbonDioxideSaturation())
    dst.set_allocated_carbondioxidesaturation(SEScalar0To1::Unload(*src.m_CarbonDioxideSaturation));
  if (src.HasCarbonMonoxideSaturation())
    dst.set_allocated_carbonmonoxidesaturation(SEScalar0To1::Unload(*src.m_CarbonMonoxideSaturation));
  if (src.HasHematocrit())
    dst.set_allocated_hematocrit(SEScalar0To1::Unload(*src.m_Hematocrit));
  if (src.HasHemoglobinContent())
    dst.set_allocated_hemoglobincontent(SEScalarMass::Unload(*src.m_HemoglobinContent));
  if (src.HasOxygenSaturation())
    dst.set_allocated_oxygensaturation(SEScalar0To1::Unload(*src.m_OxygenSaturation));
  if (src.HasPhosphate())
    dst.set_allocated_phosphate(SEScalarAmountPerVolume::Unload(*src.m_Phosphate));
  if (src.HasPlasmaVolume())
    dst.set_allocated_plasmavolume(SEScalarVolume::Unload(*src.m_PlasmaVolume));
  if (src.HasPulseOximetry())
    dst.set_allocated_pulseoximetry(SEScalar0To1::Unload(*src.m_PulseOximetry));
  if (src.HasRedBloodCellCount())
    dst.set_allocated_redbloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_RedBloodCellCount));
  if (src.HasShuntFraction())
    dst.set_allocated_shuntfraction(SEScalar0To1::Unload(*src.m_ShuntFraction));
  if (src.HasStrongIonDifference())
    dst.set_allocated_strongiondifference(SEScalarAmountPerVolume::Unload(*src.m_StrongIonDifference));
  if (src.HasTotalProteinConcentration())
    dst.set_allocated_totalproteinconcentration(SEScalarMassPerVolume::Unload(*src.m_TotalProteinConcentration));
  if (src.HasVolumeFractionNeutralPhospholipidInPlasma())
    dst.set_allocated_volumefractionneutralphospholipidinplasma(SEScalar0To1::Unload(*src.m_VolumeFractionNeutralPhospholipidInPlasma));
  if (src.HasVolumeFractionNeutralLipidInPlasma())
    dst.set_allocated_volumefractionneutrallipidinplasma(SEScalar0To1::Unload(*src.m_VolumeFractionNeutralLipidInPlasma));
  if (src.HasWhiteBloodCellCount())
    dst.set_allocated_whitebloodcellcount(SEScalarAmountPerVolume::Unload(*src.m_WhiteBloodCellCount));

  if (src.HasArterialCarbonDioxidePressure())
    dst.set_allocated_arterialcarbondioxidepressure(SEScalarPressure::Unload(*src.m_ArterialCarbonDioxidePressure));
  if (src.HasArterialOxygenPressure())
    dst.set_allocated_arterialoxygenpressure(SEScalarPressure::Unload(*src.m_ArterialOxygenPressure));
  if (src.HasPulmonaryArterialCarbonDioxidePressure())
    dst.set_allocated_pulmonaryarterialcarbondioxidepressure(SEScalarPressure::Unload(*src.m_PulmonaryArterialCarbonDioxidePressure));
  if (src.HasPulmonaryArterialOxygenPressure())
    dst.set_allocated_pulmonaryarterialoxygenpressure(SEScalarPressure::Unload(*src.m_PulmonaryArterialOxygenPressure));
  if (src.HasPulmonaryVenousCarbonDioxidePressure())
    dst.set_allocated_pulmonaryvenouscarbondioxidepressure(SEScalarPressure::Unload(*src.m_PulmonaryVenousCarbonDioxidePressure));
  if (src.HasPulmonaryVenousOxygenPressure())
    dst.set_allocated_pulmonaryvenousoxygenpressure(SEScalarPressure::Unload(*src.m_PulmonaryVenousOxygenPressure));
  if (src.HasVenousCarbonDioxidePressure())
    dst.set_allocated_venouscarbondioxidepressure(SEScalarPressure::Unload(*src.m_VenousCarbonDioxidePressure));
  if (src.HasVenousOxygenPressure())
    dst.set_allocated_venousoxygenpressure(SEScalarPressure::Unload(*src.m_VenousOxygenPressure));
}

bool SEBloodChemistrySystem::HasBloodDensity() const
{
  return m_BloodDensity == nullptr ? false : m_BloodDensity->IsValid();
}
SEScalarMassPerVolume& SEBloodChemistrySystem::GetBloodDensity()
{
  if (m_BloodDensity == nullptr)
    m_BloodDensity = new SEScalarMassPerVolume();
  return *m_BloodDensity;
}
double SEBloodChemistrySystem::GetBloodDensity(const MassPerVolumeUnit& unit) const
{
  if (m_BloodDensity == nullptr)
    return SEScalar::dNaN();
  return m_BloodDensity->GetValue(unit);
}

bool SEBloodChemistrySystem::HasBloodPH() const
{
  return m_BloodPH==nullptr?false:m_BloodPH->IsValid();
}
SEScalar& SEBloodChemistrySystem::GetBloodPH()
{
  if(m_BloodPH==nullptr)
    m_BloodPH=new SEScalar();
  return *m_BloodPH;
}
double SEBloodChemistrySystem::GetBloodPH() const
{
  if (m_BloodPH == nullptr)
    return SEScalar::dNaN();
  return m_BloodPH->GetValue();
}

bool SEBloodChemistrySystem::HasBloodSpecificHeat() const
{
  return m_BloodSpecificHeat == nullptr ? false : m_BloodSpecificHeat->IsValid();
}
SEScalarHeatCapacitancePerMass& SEBloodChemistrySystem::GetBloodSpecificHeat()
{
  if (m_BloodSpecificHeat == nullptr)
    m_BloodSpecificHeat = new SEScalarHeatCapacitancePerMass();
  return *m_BloodSpecificHeat;
}
double SEBloodChemistrySystem::GetBloodSpecificHeat(const HeatCapacitancePerMassUnit& unit) const
{
  if (m_BloodSpecificHeat == nullptr)
    return SEScalar::dNaN();
  return m_BloodSpecificHeat->GetValue(unit);
}

bool SEBloodChemistrySystem::HasBloodUreaNitrogenConcentration() const
{
  return m_BloodUreaNitrogenConcentration == nullptr ? false : m_BloodUreaNitrogenConcentration->IsValid();
}
SEScalarMassPerVolume& SEBloodChemistrySystem::GetBloodUreaNitrogenConcentration()
{
  if (m_BloodUreaNitrogenConcentration == nullptr)
    m_BloodUreaNitrogenConcentration = new SEScalarMassPerVolume();
  return *m_BloodUreaNitrogenConcentration;
}
double SEBloodChemistrySystem::GetBloodUreaNitrogenConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_BloodUreaNitrogenConcentration == nullptr)
    return SEScalar::dNaN();
  return m_BloodUreaNitrogenConcentration->GetValue(unit);
}

bool SEBloodChemistrySystem::HasCarbonDioxideSaturation() const
{
  return m_CarbonDioxideSaturation == nullptr ? false : m_CarbonDioxideSaturation->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetCarbonDioxideSaturation()
{
  if (m_CarbonDioxideSaturation == nullptr)
    m_CarbonDioxideSaturation = new SEScalar0To1();
  return *m_CarbonDioxideSaturation;
}
double SEBloodChemistrySystem::GetCarbonDioxideSaturation() const
{
  if (m_CarbonDioxideSaturation == nullptr)
    return SEScalar::dNaN();
  return m_CarbonDioxideSaturation->GetValue();
}

bool SEBloodChemistrySystem::HasCarbonMonoxideSaturation() const
{
  return m_CarbonMonoxideSaturation == nullptr ? false : m_CarbonMonoxideSaturation->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetCarbonMonoxideSaturation()
{
  if (m_CarbonMonoxideSaturation == nullptr)
    m_CarbonMonoxideSaturation = new SEScalar0To1();
  return *m_CarbonMonoxideSaturation;
}
double SEBloodChemistrySystem::GetCarbonMonoxideSaturation() const
{
  if (m_CarbonMonoxideSaturation == nullptr)
    return SEScalar::dNaN();
  return m_CarbonMonoxideSaturation->GetValue();
}

bool SEBloodChemistrySystem::HasHematocrit() const
{
  return m_Hematocrit==nullptr?false:m_Hematocrit->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetHematocrit()
{
  if(m_Hematocrit==nullptr)
    m_Hematocrit = new SEScalar0To1();
  return *m_Hematocrit;
}
double SEBloodChemistrySystem::GetHematocrit() const
{
  if (m_Hematocrit == nullptr)
    return SEScalar::dNaN();
  return m_Hematocrit->GetValue();
}

bool SEBloodChemistrySystem::HasHemoglobinContent() const
{
  return m_HemoglobinContent==nullptr?false:m_HemoglobinContent->IsValid();
}
SEScalarMass& SEBloodChemistrySystem::GetHemoglobinContent()
{
  if(m_HemoglobinContent==nullptr)
    m_HemoglobinContent=new SEScalarMass();
  return *m_HemoglobinContent;
}
double SEBloodChemistrySystem::GetHemoglobinContent(const MassUnit& unit) const
{
  if (m_HemoglobinContent == nullptr)
    return SEScalar::dNaN();
  return m_HemoglobinContent->GetValue(unit);
}

bool SEBloodChemistrySystem::HasOxygenSaturation() const
{
  return m_OxygenSaturation==nullptr?false:m_OxygenSaturation->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetOxygenSaturation()
{
  if(m_OxygenSaturation==nullptr)
    m_OxygenSaturation=new SEScalar0To1();
  return *m_OxygenSaturation;
}
double SEBloodChemistrySystem::GetOxygenSaturation() const
{
  if (m_OxygenSaturation == nullptr)
    return SEScalar::dNaN();
  return m_OxygenSaturation->GetValue();
}

bool SEBloodChemistrySystem::HasPhosphate() const
{
  return m_Phosphate == nullptr ? false : m_Phosphate->IsValid();
}
SEScalarAmountPerVolume& SEBloodChemistrySystem::GetPhosphate()
{
  if (m_Phosphate == nullptr)
    m_Phosphate = new SEScalarAmountPerVolume();
  return *m_Phosphate;
}
double SEBloodChemistrySystem::GetPhosphate(const AmountPerVolumeUnit& unit) const
{
  if (m_Phosphate == nullptr)
    return SEScalar::dNaN();
  return m_Phosphate->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPlasmaVolume() const
{
  return m_PlasmaVolume == nullptr ? false : m_PlasmaVolume->IsValid();
}
SEScalarVolume& SEBloodChemistrySystem::GetPlasmaVolume()
{
  if (m_PlasmaVolume == nullptr)
    m_PlasmaVolume = new SEScalarVolume();
  return *m_PlasmaVolume;
}
double SEBloodChemistrySystem::GetPlasmaVolume(const VolumeUnit& unit) const
{
  if (m_PlasmaVolume == nullptr)
    return SEScalar::dNaN();
  return m_PlasmaVolume->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPulseOximetry() const
{
  return m_PulseOximetry == nullptr ? false : m_PulseOximetry->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetPulseOximetry()
{
  if (m_PulseOximetry == nullptr)
    m_PulseOximetry = new SEScalar0To1();
  return *m_PulseOximetry;
}
double SEBloodChemistrySystem::GetPulseOximetry() const
{
  if (m_PulseOximetry == nullptr)
    return SEScalar::dNaN();
  return m_PulseOximetry->GetValue();
}

bool SEBloodChemistrySystem::HasRedBloodCellCount() const
{
  return m_RedBloodCellCount==nullptr?false:m_RedBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SEBloodChemistrySystem::GetRedBloodCellCount()
{
  if(m_RedBloodCellCount==nullptr)
    m_RedBloodCellCount = new SEScalarAmountPerVolume();
  return *m_RedBloodCellCount;
}
double SEBloodChemistrySystem::GetRedBloodCellCount(const AmountPerVolumeUnit& unit) const
{
  if (m_RedBloodCellCount == nullptr)
    return SEScalar::dNaN();
  return m_RedBloodCellCount->GetValue(unit);
}

bool SEBloodChemistrySystem::HasShuntFraction() const
{
  return m_ShuntFraction==nullptr?false:m_ShuntFraction->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetShuntFraction()
{
  if(m_ShuntFraction==nullptr)
    m_ShuntFraction=new SEScalar0To1();
  return *m_ShuntFraction;
}
double SEBloodChemistrySystem::GetShuntFraction() const
{
  if (m_ShuntFraction == nullptr)
    return SEScalar::dNaN();
  return m_ShuntFraction->GetValue();
}

bool SEBloodChemistrySystem::HasStrongIonDifference() const
{
  return m_StrongIonDifference == nullptr ? false : m_StrongIonDifference->IsValid();
}
SEScalarAmountPerVolume& SEBloodChemistrySystem::GetStrongIonDifference()
{
  if (m_StrongIonDifference == nullptr)
    m_StrongIonDifference = new SEScalarAmountPerVolume();
  return *m_StrongIonDifference;
}
double SEBloodChemistrySystem::GetStrongIonDifference(const AmountPerVolumeUnit& unit) const
{
  if (m_StrongIonDifference == nullptr)
    return SEScalar::dNaN();
  return m_StrongIonDifference->GetValue(unit);
}

bool SEBloodChemistrySystem::HasTotalProteinConcentration() const
{
  return m_TotalProteinConcentration == nullptr ? false : m_TotalProteinConcentration->IsValid();
}
SEScalarMassPerVolume& SEBloodChemistrySystem::GetTotalProteinConcentration()
{
  if (m_TotalProteinConcentration == nullptr)
    m_TotalProteinConcentration = new SEScalarMassPerVolume();
  return *m_TotalProteinConcentration;
}
double SEBloodChemistrySystem::GetTotalProteinConcentration(const MassPerVolumeUnit& unit) const
{
  if (m_TotalProteinConcentration == nullptr)
    return SEScalar::dNaN();
  return m_TotalProteinConcentration->GetValue(unit);
}

bool SEBloodChemistrySystem::HasVolumeFractionNeutralPhospholipidInPlasma() const
{
  return m_VolumeFractionNeutralPhospholipidInPlasma == nullptr ? false : m_VolumeFractionNeutralPhospholipidInPlasma->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetVolumeFractionNeutralPhospholipidInPlasma()
{
  if (m_VolumeFractionNeutralPhospholipidInPlasma == nullptr)
    m_VolumeFractionNeutralPhospholipidInPlasma = new SEScalar0To1();
  return *m_VolumeFractionNeutralPhospholipidInPlasma;
}
double SEBloodChemistrySystem::GetVolumeFractionNeutralPhospholipidInPlasma() const
{
  if (m_VolumeFractionNeutralPhospholipidInPlasma == nullptr)
    return SEScalar::dNaN();
  return m_VolumeFractionNeutralPhospholipidInPlasma->GetValue();
}

bool SEBloodChemistrySystem::HasVolumeFractionNeutralLipidInPlasma() const
{
  return m_VolumeFractionNeutralLipidInPlasma == nullptr ? false : m_VolumeFractionNeutralLipidInPlasma->IsValid();
}
SEScalar0To1& SEBloodChemistrySystem::GetVolumeFractionNeutralLipidInPlasma()
{
  if (m_VolumeFractionNeutralLipidInPlasma == nullptr)
    m_VolumeFractionNeutralLipidInPlasma = new SEScalar0To1();
  return *m_VolumeFractionNeutralLipidInPlasma;
}
double SEBloodChemistrySystem::GetVolumeFractionNeutralLipidInPlasma() const
{
  if (m_VolumeFractionNeutralLipidInPlasma == nullptr)
    return SEScalar::dNaN();
  return m_VolumeFractionNeutralLipidInPlasma->GetValue();
}

bool SEBloodChemistrySystem::HasWhiteBloodCellCount() const
{
  return m_WhiteBloodCellCount==nullptr?false:m_WhiteBloodCellCount->IsValid();
}
SEScalarAmountPerVolume& SEBloodChemistrySystem::GetWhiteBloodCellCount()
{
  if(m_WhiteBloodCellCount==nullptr)
    m_WhiteBloodCellCount = new SEScalarAmountPerVolume();
  return *m_WhiteBloodCellCount;
}
double SEBloodChemistrySystem::GetWhiteBloodCellCount(const AmountPerVolumeUnit& unit) const
{
  if (m_WhiteBloodCellCount == nullptr)
    return SEScalar::dNaN();
  return m_WhiteBloodCellCount->GetValue(unit);
}

bool SEBloodChemistrySystem::HasArterialCarbonDioxidePressure() const
{
  return m_ArterialCarbonDioxidePressure == nullptr ? false : m_ArterialCarbonDioxidePressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetArterialCarbonDioxidePressure()
{
  if (m_ArterialCarbonDioxidePressure == nullptr)
    m_ArterialCarbonDioxidePressure = new SEScalarPressure();
  return *m_ArterialCarbonDioxidePressure;
}
double SEBloodChemistrySystem::GetArterialCarbonDioxidePressure(const PressureUnit& unit) const
{
  if (m_ArterialCarbonDioxidePressure == nullptr)
    return SEScalar::dNaN();
  return m_ArterialCarbonDioxidePressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasArterialOxygenPressure() const
{
  return m_ArterialOxygenPressure == nullptr ? false : m_ArterialOxygenPressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetArterialOxygenPressure()
{
  if (m_ArterialOxygenPressure == nullptr)
    m_ArterialOxygenPressure = new SEScalarPressure();
  return *m_ArterialOxygenPressure;
}
double SEBloodChemistrySystem::GetArterialOxygenPressure(const PressureUnit& unit) const
{
  if (m_ArterialOxygenPressure == nullptr)
    return SEScalar::dNaN();
  return m_ArterialOxygenPressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPulmonaryArterialCarbonDioxidePressure() const
{
  return m_PulmonaryArterialCarbonDioxidePressure == nullptr ? false : m_PulmonaryArterialCarbonDioxidePressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetPulmonaryArterialCarbonDioxidePressure()
{
  if (m_PulmonaryArterialCarbonDioxidePressure == nullptr)
    m_PulmonaryArterialCarbonDioxidePressure = new SEScalarPressure();
  return *m_PulmonaryArterialCarbonDioxidePressure;
}
double SEBloodChemistrySystem::GetPulmonaryArterialCarbonDioxidePressure(const PressureUnit& unit) const
{
  if (m_PulmonaryArterialCarbonDioxidePressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryArterialCarbonDioxidePressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPulmonaryArterialOxygenPressure() const
{
  return m_PulmonaryArterialOxygenPressure == nullptr ? false : m_PulmonaryArterialOxygenPressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetPulmonaryArterialOxygenPressure()
{
  if (m_PulmonaryArterialOxygenPressure == nullptr)
    m_PulmonaryArterialOxygenPressure = new SEScalarPressure();
  return *m_PulmonaryArterialOxygenPressure;
}
double SEBloodChemistrySystem::GetPulmonaryArterialOxygenPressure(const PressureUnit& unit) const
{
  if (m_PulmonaryArterialOxygenPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryArterialOxygenPressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPulmonaryVenousCarbonDioxidePressure() const
{
  return m_PulmonaryVenousCarbonDioxidePressure == nullptr ? false : m_PulmonaryVenousCarbonDioxidePressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetPulmonaryVenousCarbonDioxidePressure()
{
  if (m_PulmonaryVenousCarbonDioxidePressure == nullptr)
    m_PulmonaryVenousCarbonDioxidePressure = new SEScalarPressure();
  return *m_PulmonaryVenousCarbonDioxidePressure;
}
double SEBloodChemistrySystem::GetPulmonaryVenousCarbonDioxidePressure(const PressureUnit& unit) const
{
  if (m_PulmonaryVenousCarbonDioxidePressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVenousCarbonDioxidePressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasPulmonaryVenousOxygenPressure() const
{
  return m_PulmonaryVenousOxygenPressure == nullptr ? false : m_PulmonaryVenousOxygenPressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetPulmonaryVenousOxygenPressure()
{
  if (m_PulmonaryVenousOxygenPressure == nullptr)
    m_PulmonaryVenousOxygenPressure = new SEScalarPressure();
  return *m_PulmonaryVenousOxygenPressure;
}
double SEBloodChemistrySystem::GetPulmonaryVenousOxygenPressure(const PressureUnit& unit) const
{
  if (m_PulmonaryVenousOxygenPressure == nullptr)
    return SEScalar::dNaN();
  return m_PulmonaryVenousOxygenPressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasVenousOxygenPressure() const
{
  return m_VenousOxygenPressure == nullptr ? false : m_VenousOxygenPressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetVenousOxygenPressure()
{
  if (m_VenousOxygenPressure == nullptr)
    m_VenousOxygenPressure = new SEScalarPressure();
  return *m_VenousOxygenPressure;
}
double SEBloodChemistrySystem::GetVenousOxygenPressure(const PressureUnit& unit) const
{
  if (m_VenousOxygenPressure == nullptr)
    return SEScalar::dNaN();
  return m_VenousOxygenPressure->GetValue(unit);
}

bool SEBloodChemistrySystem::HasVenousCarbonDioxidePressure() const
{
  return m_VenousCarbonDioxidePressure == nullptr ? false : m_VenousCarbonDioxidePressure->IsValid();
}
SEScalarPressure& SEBloodChemistrySystem::GetVenousCarbonDioxidePressure()
{
  if (m_VenousCarbonDioxidePressure == nullptr)
    m_VenousCarbonDioxidePressure = new SEScalarPressure();
  return *m_VenousCarbonDioxidePressure;
}
double SEBloodChemistrySystem::GetVenousCarbonDioxidePressure(const PressureUnit& unit) const
{
  if (m_VenousCarbonDioxidePressure == nullptr)
    return SEScalar::dNaN();
  return m_VenousCarbonDioxidePressure->GetValue(unit);
}
