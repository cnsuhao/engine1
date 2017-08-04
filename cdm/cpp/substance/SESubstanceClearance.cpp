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
#include "substance/SESubstanceClearance.h"
#include "properties/SEScalar0To1.h"
#include "properties/SEScalarMassPerTime.h"
#include "properties/SEScalarVolumePerTimeMass.h"

SESubstanceClearance::SESubstanceClearance(Logger* logger) : Loggable(logger)
{
  m_hasSystemic = false;
  m_ChargeInBlood = cdm::eCharge::NullCharge;
  m_FractionExcretedInFeces = nullptr;
  m_FractionExcretedInUrine = nullptr;
  m_FractionMetabolizedInGut = nullptr;
  m_FractionUnboundInPlasma = nullptr;
  m_GlomerularFilterability = nullptr;
  m_IntrinsicClearance = nullptr;
  m_RenalDynamic = RenalDynamic::NullDynamic;
  m_RenalClearance = nullptr;
  m_RenalReabsorptionRatio = nullptr;
  m_RenalTransportMaximum = nullptr;
  m_RenalFiltrationRate = nullptr;
  m_RenalReabsorptionRate = nullptr;
  m_RenalExcretionRate = nullptr;
  m_SystemicClearance = nullptr;
}

SESubstanceClearance::~SESubstanceClearance()
{
  Clear();
}

void SESubstanceClearance::Clear()
{
  m_hasSystemic = false;
  m_ChargeInBlood = cdm::eCharge::NullCharge;
  SAFE_DELETE(m_FractionExcretedInFeces);
  SAFE_DELETE(m_FractionExcretedInUrine);
  SAFE_DELETE(m_FractionMetabolizedInGut);
  SAFE_DELETE(m_FractionUnboundInPlasma);
  SAFE_DELETE(m_GlomerularFilterability);
  SAFE_DELETE(m_IntrinsicClearance);
  m_RenalDynamic = RenalDynamic::NullDynamic;
  SAFE_DELETE(m_RenalClearance);
  SAFE_DELETE(m_RenalReabsorptionRatio);
  SAFE_DELETE(m_RenalTransportMaximum);
  SAFE_DELETE(m_RenalFiltrationRate);
  SAFE_DELETE(m_RenalReabsorptionRate);
  SAFE_DELETE(m_RenalExcretionRate);
  SAFE_DELETE(m_SystemicClearance);
}

bool SESubstanceClearance::IsValid() const
{
  if (HasSystemic())
  {
    if (!HasFractionExcretedInFeces())
      return false;
    if (!HasFractionUnboundInPlasma())
      return false;
    if (!HasIntrinsicClearance())
      return false;
    if (!HasRenalClearance())
      return false;
    if (!HasSystemicClearance())
      return false;
  }

  if (HasRenalDynamic())
  {
    if (GetRenalDynamic() == RenalDynamic::Regulation)
    {
      if (!HasChargeInBlood())
        return false;
      if (!HasFractionUnboundInPlasma())
        return false;
      if (!HasRenalReabsorptionRatio())
        return false;
      if (!HasRenalTransportMaximum())
        return false;
    }
    else  if (GetRenalDynamic() == RenalDynamic::Clearance)
    {
      if (!HasRenalClearance())
        return false;
    }
    else
      return false;
  }
  return true;
}

const SEScalar* SESubstanceClearance::GetScalar(const std::string& name)
{
  if (name.compare("FractionExcretedInFeces") == 0)
    return &GetFractionExcretedInFeces();
  if (name.compare("FractionExcretedInUrine") == 0)
    return &GetFractionExcretedInUrine();
  if (name.compare("FractionMetabolizedInGut") == 0)
    return &GetFractionMetabolizedInGut();
  if (name.compare("FractionUnboundInPlasma") == 0)
    return &GetFractionUnboundInPlasma();
  if (name.compare("IntrinsicClearance") == 0)
    return &GetIntrinsicClearance();  
  if (name.compare("GlomerularFilterability") == 0)
    return &GetGlomerularFilterability();
  if(name.compare("RenalClearance") == 0)
    return &GetRenalClearance();
  if (name.compare("RenalReabsorptionRatio") == 0)
    return &GetRenalReabsorptionRatio();
  if (name.compare("RenalTransportMaximum") == 0)
    return &GetRenalTransportMaximum();
  if (name.compare("RenalFiltrationRate") == 0)
    return &GetRenalFiltrationRate();
  if (name.compare("RenalReabsorptionRate") == 0)
    return &GetRenalReabsorptionRate();
  if (name.compare("RenalExcretionRate") == 0)
    return &GetRenalExcretionRate();
  if (name.compare("SystemicClearance") == 0)
    return &GetSystemicClearance();

  return nullptr;
}

void SESubstanceClearance::Load(const cdm::SubstanceData_ClearanceData& src, SESubstanceClearance& dst)
{
  SESubstanceClearance::Serialize(src, dst);
}
void SESubstanceClearance::Serialize(const cdm::SubstanceData_ClearanceData& src, SESubstanceClearance& dst)
{
  dst.Clear();
  
  // Make sure dups match
  if (src.has_systemicclearance() && src.systemicclearance().has_renalclearance() && src.systemicclearance().renalclearance().has_scalarvolumepertimemass() &&
      src.has_renalclearance() && src.renalclearance().has_clearance() && src.renalclearance().clearance().has_scalarvolumepertimemass() &&
      src.systemicclearance().renalclearance().scalarvolumepertimemass().value() != src.renalclearance().clearance().scalarvolumepertimemass().value())
  {// This is assuming the same unit, so make sure that is not your problem - lazy developer
    dst.Fatal("Multiple Renal Clearances specified, but not the same. These must match at this time.");
  }
  if (src.has_systemicclearance() && src.systemicclearance().has_fractionunboundinplasma() &&
      src.has_renalclearance() && src.renalclearance().has_regulation() && src.renalclearance().regulation().has_fractionunboundinplasma() &&
      src.systemicclearance().fractionunboundinplasma().scalar0to1().value() != src.renalclearance().regulation().fractionunboundinplasma().scalar0to1().value())
  {
    dst.Fatal("Multiple FractionUnboundInPlasma values specified, but not the same. These must match at this time.");
  }

  if (src.has_systemicclearance())
  {
    dst.SetSystemic(true);
    SEScalar0To1::Load(src.systemicclearance().fractionexcretedinfeces(), dst.GetFractionExcretedInFeces());
    SEScalar0To1::Load(src.systemicclearance().fractionexcretedinurine(), dst.GetFractionExcretedInUrine());
    SEScalar0To1::Load(src.systemicclearance().fractionmetabolizedingut(), dst.GetFractionMetabolizedInGut());
    SEScalar0To1::Load(src.systemicclearance().fractionunboundinplasma(), dst.GetFractionUnboundInPlasma());
    SEScalarVolumePerTimeMass::Load(src.systemicclearance().intrinsicclearance(), dst.GetIntrinsicClearance());
    SEScalarVolumePerTimeMass::Load(src.systemicclearance().renalclearance(), dst.GetRenalClearance());
    SEScalarVolumePerTimeMass::Load(src.systemicclearance().systemicclearance(), dst.GetSystemicClearance());
  }

  if (src.has_renalclearance())
  {    
    if (src.renalclearance().has_regulation())
    {
      dst.m_RenalDynamic = RenalDynamic::Regulation;
      dst.SetChargeInBlood(src.renalclearance().regulation().chargeinblood());
      SEScalar0To1::Load(src.renalclearance().regulation().fractionunboundinplasma(), dst.GetFractionUnboundInPlasma());
      SEScalar::Load(src.renalclearance().regulation().reabsorptionratio(), dst.GetRenalReabsorptionRate());
      SEScalarMassPerTime::Load(src.renalclearance().regulation().transportmaximum(), dst.GetRenalTransportMaximum());
    }
    else if (src.renalclearance().has_clearance())
    {
      dst.m_RenalDynamic = RenalDynamic::Clearance;
      SEScalarVolumePerTimeMass::Load(src.renalclearance().clearance(), dst.GetRenalClearance());
    }

    if (src.renalclearance().has_filtrationrate())
      SEScalarMassPerTime::Load(src.renalclearance().filtrationrate(), dst.GetRenalFiltrationRate());
    if (src.renalclearance().has_glomerularfilterability())
      SEScalar::Load(src.renalclearance().glomerularfilterability(), dst.GetGlomerularFilterability());
    if (src.renalclearance().has_reabsorptionrate())
      SEScalarMassPerTime::Load(src.renalclearance().reabsorptionrate(), dst.GetRenalReabsorptionRate());
    if (src.renalclearance().has_excretionrate())
      SEScalarMassPerTime::Load(src.renalclearance().excretionrate(), dst.GetRenalExcretionRate());
  }
}

cdm::SubstanceData_ClearanceData* SESubstanceClearance::Unload(const SESubstanceClearance& src)
{
  cdm::SubstanceData_ClearanceData* dst = new cdm::SubstanceData_ClearanceData();
  SESubstanceClearance::Serialize(src, *dst);
  return dst;
}
void SESubstanceClearance::Serialize(const SESubstanceClearance& src, cdm::SubstanceData_ClearanceData& dst)
{
  if (src.HasSystemicClearance())
  {
    cdm::SubstanceData_SystemicClearanceData* sys = new cdm::SubstanceData_SystemicClearanceData();
    dst.set_allocated_systemicclearance(sys);

    if (src.HasFractionExcretedInFeces())
      sys->set_allocated_fractionexcretedinfeces(SEScalar0To1::Unload(*src.m_FractionExcretedInFeces));
    if (src.HasFractionExcretedInUrine())
      sys->set_allocated_fractionexcretedinurine(SEScalar0To1::Unload(*src.m_FractionExcretedInUrine));
    if (src.HasFractionMetabolizedInGut())
      sys->set_allocated_fractionmetabolizedingut(SEScalar0To1::Unload(*src.m_FractionMetabolizedInGut));
    if (src.HasFractionUnboundInPlasma())
      sys->set_allocated_fractionunboundinplasma(SEScalar0To1::Unload(*src.m_FractionUnboundInPlasma));
    if (src.HasRenalClearance())
      sys->set_allocated_renalclearance(SEScalarVolumePerTimeMass::Unload(*src.m_RenalClearance));
    if (src.HasIntrinsicClearance())
      sys->set_allocated_intrinsicclearance(SEScalarVolumePerTimeMass::Unload(*src.m_IntrinsicClearance));
    if (src.HasSystemicClearance())
      sys->set_allocated_systemicclearance(SEScalarVolumePerTimeMass::Unload(*src.m_SystemicClearance));
  }

  if (src.HasRenalDynamic())
  {
    cdm::SubstanceData_RenalClearanceData* rc = new cdm::SubstanceData_RenalClearanceData();
    dst.set_allocated_renalclearance(rc);

    if (src.m_RenalDynamic == RenalDynamic::Clearance && src.HasRenalClearance())
      rc->set_allocated_clearance(SEScalarVolumePerTimeMass::Unload(*src.m_RenalClearance));
    else if (src.m_RenalDynamic == RenalDynamic::Regulation)
    {
      cdm::SubstanceData_RenalRegulationData* rr = new cdm::SubstanceData_RenalRegulationData();
      rc->set_allocated_regulation(rr);

      if (src.HasChargeInBlood())
        rr->set_chargeinblood(src.m_ChargeInBlood);
      if (src.HasFractionUnboundInPlasma())
        rr->set_allocated_fractionunboundinplasma(SEScalar0To1::Unload(*src.m_FractionUnboundInPlasma));
      if (src.HasRenalReabsorptionRatio())
        rr->set_allocated_reabsorptionratio(SEScalar::Unload(*src.m_RenalReabsorptionRatio));
      if (src.HasRenalTransportMaximum())
        rr->set_allocated_transportmaximum(SEScalarMassPerTime::Unload(*src.m_RenalTransportMaximum));
    }
    if (src.HasGlomerularFilterability())
      rc->set_allocated_glomerularfilterability(SEScalar::Unload(*src.m_GlomerularFilterability));
    if (src.HasRenalFiltrationRate())
      rc->set_allocated_filtrationrate(SEScalarMassPerTime::Unload(*src.m_RenalFiltrationRate));
    if (src.HasRenalReabsorptionRate())
      rc->set_allocated_reabsorptionrate(SEScalarMassPerTime::Unload(*src.m_RenalReabsorptionRate));
    if (src.HasRenalExcretionRate())
      rc->set_allocated_excretionrate(SEScalarMassPerTime::Unload(*src.m_RenalExcretionRate));
  }
}

cdm::eCharge SESubstanceClearance::GetChargeInBlood() const
{
  return m_ChargeInBlood;
}
void SESubstanceClearance::SetChargeInBlood(cdm::eCharge c)
{
  m_ChargeInBlood = c;
}
bool SESubstanceClearance::HasChargeInBlood() const
{
  return m_ChargeInBlood == cdm::eCharge::NullCharge ? false : true;
}
void SESubstanceClearance::InvalidateChargeInBlood()
{
  m_ChargeInBlood = cdm::eCharge::NullCharge;
}

bool SESubstanceClearance::HasFractionExcretedInFeces() const
{
  return (m_FractionExcretedInFeces == nullptr) ? false : m_FractionExcretedInFeces->IsValid();
}
SEScalar0To1& SESubstanceClearance::GetFractionExcretedInFeces()
{
  if (m_FractionExcretedInFeces == nullptr)
    m_FractionExcretedInFeces = new SEScalar0To1();
  return *m_FractionExcretedInFeces;
}
double SESubstanceClearance::GetFractionExcretedInFeces() const
{
  if (m_FractionExcretedInFeces == nullptr)
    return SEScalar::dNaN();
  return m_FractionExcretedInFeces->GetValue();
}

bool SESubstanceClearance::HasFractionExcretedInUrine() const
{
  return (m_FractionExcretedInUrine == nullptr) ? false : m_FractionExcretedInUrine->IsValid();
}
SEScalar0To1& SESubstanceClearance::GetFractionExcretedInUrine()
{
  if (m_FractionExcretedInUrine == nullptr)
    m_FractionExcretedInUrine = new SEScalar0To1();
  return *m_FractionExcretedInUrine;
}
double SESubstanceClearance::GetFractionExcretedInUrine() const
{
  if (m_FractionExcretedInUrine == nullptr)
    return SEScalar::dNaN();
  return m_FractionExcretedInUrine->GetValue();
}

bool SESubstanceClearance::HasFractionMetabolizedInGut() const
{
  return (m_FractionMetabolizedInGut == nullptr) ? false : m_FractionMetabolizedInGut->IsValid();
}
SEScalar0To1& SESubstanceClearance::GetFractionMetabolizedInGut()
{
  if (m_FractionMetabolizedInGut == nullptr)
    m_FractionMetabolizedInGut = new SEScalar0To1();
  return *m_FractionMetabolizedInGut;
}
double SESubstanceClearance::GetFractionMetabolizedInGut() const
{
  if (m_FractionMetabolizedInGut == nullptr)
    return SEScalar::dNaN();
  return m_FractionMetabolizedInGut->GetValue();
}

bool SESubstanceClearance::HasFractionUnboundInPlasma() const
{
  return (m_FractionUnboundInPlasma == nullptr) ? false : m_FractionUnboundInPlasma->IsValid();
}
SEScalar0To1& SESubstanceClearance::GetFractionUnboundInPlasma()
{
  if (m_FractionUnboundInPlasma == nullptr)
    m_FractionUnboundInPlasma = new SEScalar0To1();
  return *m_FractionUnboundInPlasma;
}
double SESubstanceClearance::GetFractionUnboundInPlasma() const
{
  if (m_FractionUnboundInPlasma == nullptr)
    return SEScalar::dNaN();
  return m_FractionUnboundInPlasma->GetValue();
}

bool SESubstanceClearance::HasIntrinsicClearance() const
{
  return (m_IntrinsicClearance == nullptr) ? false : m_IntrinsicClearance->IsValid();
}
SEScalarVolumePerTimeMass& SESubstanceClearance::GetIntrinsicClearance()
{
  if (m_IntrinsicClearance == nullptr)
    m_IntrinsicClearance = new SEScalarVolumePerTimeMass();
  return *m_IntrinsicClearance;
}
double SESubstanceClearance::GetIntrinsicClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_IntrinsicClearance == nullptr)
    return SEScalar::dNaN();
  return m_IntrinsicClearance->GetValue(unit);
}

RenalDynamic SESubstanceClearance::GetRenalDynamic() const
{
  return m_RenalDynamic;
}
void SESubstanceClearance::SetRenalDynamic(RenalDynamic d)
{
  m_RenalDynamic = d;
}
bool SESubstanceClearance::HasRenalDynamic() const
{
  return m_RenalDynamic == RenalDynamic::NullDynamic ? false : true;
}
void SESubstanceClearance::InvalidateRenalDynamic()
{
  m_RenalDynamic = RenalDynamic::NullDynamic;
}

bool SESubstanceClearance::HasRenalClearance() const
{
  return (m_RenalClearance == nullptr) ? false : m_RenalClearance->IsValid();
}
SEScalarVolumePerTimeMass& SESubstanceClearance::GetRenalClearance()
{
  if (m_RenalClearance == nullptr)
    m_RenalClearance = new SEScalarVolumePerTimeMass();
  return *m_RenalClearance;
}
double SESubstanceClearance::GetRenalClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_RenalClearance == nullptr)
    return SEScalar::dNaN();
  return m_RenalClearance->GetValue(unit);
}

bool SESubstanceClearance::HasRenalReabsorptionRatio() const
{
  return (m_RenalReabsorptionRatio == nullptr) ? false : m_RenalReabsorptionRatio->IsValid();
}
SEScalar& SESubstanceClearance::GetRenalReabsorptionRatio()
{
  if (m_RenalReabsorptionRatio == nullptr)
    m_RenalReabsorptionRatio = new SEScalar();
  return *m_RenalReabsorptionRatio;
}
double SESubstanceClearance::GetRenalReabsorptionRatio() const
{
  if (m_RenalReabsorptionRatio == nullptr)
    return SEScalar::dNaN();
  return m_RenalReabsorptionRatio->GetValue();
}

bool SESubstanceClearance::HasRenalTransportMaximum() const
{
  return (m_RenalTransportMaximum == nullptr) ? false : m_RenalTransportMaximum->IsValid();
}
SEScalarMassPerTime& SESubstanceClearance::GetRenalTransportMaximum()
{
  if (m_RenalTransportMaximum == nullptr)
    m_RenalTransportMaximum = new SEScalarMassPerTime();
  return *m_RenalTransportMaximum;
}
double SESubstanceClearance::GetRenalTransportMaximum(const MassPerTimeUnit& unit) const
{
  if (m_RenalTransportMaximum == nullptr)
    return SEScalar::dNaN();
  return m_RenalTransportMaximum->GetValue(unit);
}

bool SESubstanceClearance::HasRenalFiltrationRate() const
{
  return (m_RenalFiltrationRate == nullptr) ? false : m_RenalFiltrationRate->IsValid();
}
SEScalarMassPerTime& SESubstanceClearance::GetRenalFiltrationRate()
{
  if (m_RenalFiltrationRate == nullptr)
    m_RenalFiltrationRate = new SEScalarMassPerTime();
  return *m_RenalFiltrationRate;
}
double SESubstanceClearance::GetRenalFiltrationRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalFiltrationRate == nullptr)
    return SEScalar::dNaN();
  return m_RenalFiltrationRate->GetValue(unit);
}

bool SESubstanceClearance::HasRenalReabsorptionRate() const
{
  return (m_RenalReabsorptionRate == nullptr) ? false : m_RenalReabsorptionRate->IsValid();
}
SEScalarMassPerTime& SESubstanceClearance::GetRenalReabsorptionRate()
{
  if (m_RenalReabsorptionRate == nullptr)
    m_RenalReabsorptionRate = new SEScalarMassPerTime();
  return *m_RenalReabsorptionRate;
}
double SESubstanceClearance::GetRenalReabsorptionRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalReabsorptionRate == nullptr)
    return SEScalar::dNaN();
  return m_RenalReabsorptionRate->GetValue(unit);
}

bool SESubstanceClearance::HasRenalExcretionRate() const
{
  return (m_RenalExcretionRate == nullptr) ? false : m_RenalExcretionRate->IsValid();
}
SEScalarMassPerTime& SESubstanceClearance::GetRenalExcretionRate()
{
  if (m_RenalExcretionRate == nullptr)
    m_RenalExcretionRate = new SEScalarMassPerTime();
  return *m_RenalExcretionRate;
}
double SESubstanceClearance::GetRenalExcretionRate(const MassPerTimeUnit& unit) const
{
  if (m_RenalExcretionRate == nullptr)
    return SEScalar::dNaN();
  return m_RenalExcretionRate->GetValue(unit);
}

bool SESubstanceClearance::HasGlomerularFilterability() const
{
  return (m_GlomerularFilterability == nullptr) ? false : m_GlomerularFilterability->IsValid();
}
SEScalar& SESubstanceClearance::GetGlomerularFilterability()
{
  if (m_GlomerularFilterability == nullptr)
    m_GlomerularFilterability = new SEScalar();
  return *m_GlomerularFilterability;
}
double SESubstanceClearance::GetGlomerularFilterability() const
{
  if (m_GlomerularFilterability == nullptr)
    return SEScalar::dNaN();
  return m_GlomerularFilterability->GetValue();
}

bool SESubstanceClearance::HasSystemicClearance() const
{
  return (m_SystemicClearance == nullptr) ? false : m_SystemicClearance->IsValid();
}
SEScalarVolumePerTimeMass& SESubstanceClearance::GetSystemicClearance()
{
  if (m_SystemicClearance == nullptr)
    m_SystemicClearance = new SEScalarVolumePerTimeMass();
  return *m_SystemicClearance;
}
double SESubstanceClearance::GetSystemicClearance(const VolumePerTimeMassUnit& unit) const
{
  if (m_SystemicClearance == nullptr)
    return SEScalar::dNaN();
  return m_SystemicClearance->GetValue(unit);
}
