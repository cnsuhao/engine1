/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/assessments/SEUrinalysisMicroscopic.h"
#include "properties/SEScalarAmount.h"

SEUrinalysisMicroscopic::SEUrinalysisMicroscopic(Logger* logger) : Loggable(logger)
{
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType_NullObservationType;
  m_RedBloodCells = nullptr;
  m_WhiteBloodCells = nullptr;
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Casts = nullptr;
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

SEUrinalysisMicroscopic::~SEUrinalysisMicroscopic()
{
  Clear();
}

void SEUrinalysisMicroscopic::Clear()
{
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType_NullObservationType;
  SAFE_DELETE(m_RedBloodCells);
  SAFE_DELETE(m_WhiteBloodCells);
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  SAFE_DELETE(m_Casts);
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

void SEUrinalysisMicroscopic::Load(const cdm::UrinalysisData_UrinalysisMicroscopicData& src, SEUrinalysisMicroscopic& dst)
{
  SEUrinalysisMicroscopic::Serialize(src, dst);
}
void SEUrinalysisMicroscopic::Serialize(const cdm::UrinalysisData_UrinalysisMicroscopicData& src, SEUrinalysisMicroscopic& dst)
{
  dst.Clear();
  dst.SetObservationType(src.observationtype());
  dst.SetEpithelialCellsResult(src.epithelialcells());
  dst.SetCrystalsResult(src.crystals());
  dst.SetBacteriaResult(src.bacteria());
  dst.SetTrichomonadsResult(src.trichomonads());
  dst.SetYeastResult(src.yeast());  
  if (src.has_redbloodcells())
    SEScalarAmount::Load(src.redbloodcells(), dst.GetRedBloodCellsResult());
  if (src.has_whitebloodcells())
    SEScalarAmount::Load(src.whitebloodcells(), dst.GetWhiteBloodCellsResult());
  if (src.has_casts())
    SEScalarAmount::Load(src.casts(), dst.GetCastsResult());
}

cdm::UrinalysisData_UrinalysisMicroscopicData* SEUrinalysisMicroscopic::Unload(const SEUrinalysisMicroscopic& src)
{
  cdm::UrinalysisData_UrinalysisMicroscopicData* dst = new cdm::UrinalysisData_UrinalysisMicroscopicData();
  SEUrinalysisMicroscopic::Serialize(src, *dst);
  return dst;
}
void SEUrinalysisMicroscopic::Serialize(const SEUrinalysisMicroscopic& src, cdm::UrinalysisData_UrinalysisMicroscopicData& dst)
{
  if (src.HasObservationType())
    dst.set_observationtype(src.m_ObservationType);
  if (src.HasEpithelialCellsResult())
    dst.set_epithelialcells(src.m_EpithelialCells);
  if (src.HasCrystalsResult())
    dst.set_crystals(src.m_Crystals);
  if (src.HasBacteriaResult())
    dst.set_bacteria(src.m_Bacteria);
  if (src.HasTrichomonadsResult())
    dst.set_trichomonads(src.m_Trichomonads);
  if (src.HasYeastResult())
    dst.set_yeast(src.m_Yeast);  
  if (src.HasRedBloodCellsResult())
    dst.set_allocated_redbloodcells(SEScalarAmount::Unload(*src.m_RedBloodCells));
  if (src.HasWhiteBloodCellsResult())
    dst.set_allocated_whitebloodcells(SEScalarAmount::Unload(*src.m_WhiteBloodCells));
  if (src.HasCastsResult())
    dst.set_allocated_casts(SEScalarAmount::Unload(*src.m_Casts));
}

bool SEUrinalysisMicroscopic::HasRedBloodCellsResult() const
{
  return m_RedBloodCells == nullptr ? false : m_RedBloodCells->IsValid();
}
SEScalarAmount& SEUrinalysisMicroscopic::GetRedBloodCellsResult()
{
  if (m_RedBloodCells == nullptr)
    m_RedBloodCells = new SEScalarAmount();
  return *m_RedBloodCells;
}
double SEUrinalysisMicroscopic::GetRedBloodCellsResult(const AmountUnit& unit) const
{
  if (!HasRedBloodCellsResult())
    return SEScalar::dNaN();
  return m_RedBloodCells->GetValue(unit);
}

bool SEUrinalysisMicroscopic::HasObservationType() const
{
  return m_ObservationType != cdm::UrinalysisData_eMicroscopicObservationType_NullObservationType;
}
cdm::UrinalysisData_eMicroscopicObservationType SEUrinalysisMicroscopic::GetObservationType() const
{
  return m_ObservationType;
}
void SEUrinalysisMicroscopic::SetObservationType(cdm::UrinalysisData_eMicroscopicObservationType c)
{
  m_ObservationType = c;
}
void SEUrinalysisMicroscopic::InvalidateObservationType()
{
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType_NullObservationType;
}

bool SEUrinalysisMicroscopic::HasWhiteBloodCellsResult() const
{
  return m_WhiteBloodCells == nullptr ? false : m_WhiteBloodCells->IsValid();
}
SEScalarAmount& SEUrinalysisMicroscopic::GetWhiteBloodCellsResult()
{
  if (m_WhiteBloodCells == nullptr)
    m_WhiteBloodCells = new SEScalarAmount();
  return *m_WhiteBloodCells;
}
double SEUrinalysisMicroscopic::GetWhiteBloodCellsResult(const AmountUnit& unit) const
{
  if (!HasWhiteBloodCellsResult())
    return SEScalar::dNaN();
  return m_WhiteBloodCells->GetValue(unit);
}

bool SEUrinalysisMicroscopic::HasEpithelialCellsResult() const
{
  return m_EpithelialCells != cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}
cdm::UrinalysisData_eMicroscopicObservationAmount SEUrinalysisMicroscopic::GetEpithelialCellsResult() const
{
  return m_EpithelialCells;
}
void SEUrinalysisMicroscopic::SetEpithelialCellsResult(cdm::UrinalysisData_eMicroscopicObservationAmount c)
{
  m_EpithelialCells = c;
}
void SEUrinalysisMicroscopic::InvalidateEpithelialCellsResult()
{
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

bool SEUrinalysisMicroscopic::HasCastsResult() const
{
  return m_Casts == nullptr ? false : m_Casts->IsValid();
}
SEScalarAmount& SEUrinalysisMicroscopic::GetCastsResult()
{
  if (m_Casts == nullptr)
    m_Casts = new SEScalarAmount();
  return *m_Casts;
}
double SEUrinalysisMicroscopic::GetCastsResult(const AmountUnit& unit) const
{
  if (!HasCastsResult())
    return SEScalar::dNaN();
  return m_Casts->GetValue(unit);
}

bool SEUrinalysisMicroscopic::HasCrystalsResult() const
{
  return m_Crystals != cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}
cdm::UrinalysisData_eMicroscopicObservationAmount SEUrinalysisMicroscopic::GetCrystalsResult() const
{
  return m_Crystals;
}
void SEUrinalysisMicroscopic::SetCrystalsResult(cdm::UrinalysisData_eMicroscopicObservationAmount c)
{
  m_Crystals = c;
}
void SEUrinalysisMicroscopic::InvalidateCrystalsResult()
{
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

bool SEUrinalysisMicroscopic::HasBacteriaResult() const
{
  return m_Bacteria != cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}
cdm::UrinalysisData_eMicroscopicObservationAmount SEUrinalysisMicroscopic::GetBacteriaResult() const
{
  return m_Bacteria;
}
void SEUrinalysisMicroscopic::SetBacteriaResult(cdm::UrinalysisData_eMicroscopicObservationAmount c)
{
  m_Bacteria = c;
}
void SEUrinalysisMicroscopic::InvalidateBacteriaResult()
{
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

bool SEUrinalysisMicroscopic::HasTrichomonadsResult() const
{
  return m_Trichomonads != cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}
cdm::UrinalysisData_eMicroscopicObservationAmount SEUrinalysisMicroscopic::GetTrichomonadsResult() const
{
  return m_Trichomonads;
}
void SEUrinalysisMicroscopic::SetTrichomonadsResult(cdm::UrinalysisData_eMicroscopicObservationAmount c)
{
  m_Trichomonads = c;
}
void SEUrinalysisMicroscopic::InvalidateTrichomonadsResult()
{
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}

bool SEUrinalysisMicroscopic::HasYeastResult() const
{
  return m_Yeast != cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}
cdm::UrinalysisData_eMicroscopicObservationAmount SEUrinalysisMicroscopic::GetYeastResult() const
{
  return m_Yeast;
}
void SEUrinalysisMicroscopic::SetYeastResult(cdm::UrinalysisData_eMicroscopicObservationAmount c)
{
  m_Yeast = c;
}
void SEUrinalysisMicroscopic::InvalidateYeastResult()
{
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount_NullObservationAmount;
}