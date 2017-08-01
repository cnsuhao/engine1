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
#include "patient/assessments/SEUrinalysisMicroscopic.h"
#include "properties/SEScalarAmount.h"

SEUrinalysisMicroscopic::SEUrinalysisMicroscopic(Logger* logger) : SEPatientAssessment(logger)
{
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType(-1);
  m_RedBloodCells = nullptr;
  m_WhiteBloodCells = nullptr;
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Casts = nullptr;
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}

SEUrinalysisMicroscopic::~SEUrinalysisMicroscopic()
{
  Clear();
}

void SEUrinalysisMicroscopic::Clear()
{
  SEPatientAssessment::Clear();
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType(-1);
  SAFE_DELETE(m_RedBloodCells);
  SAFE_DELETE(m_WhiteBloodCells);
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  SAFE_DELETE(m_Casts);
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}

void SEUrinalysisMicroscopic::Reset()
{
  SEPatientAssessment::Reset();
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType(-1);
  INVALIDATE_PROPERTY(m_RedBloodCells);
  INVALIDATE_PROPERTY(m_WhiteBloodCells);
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  INVALIDATE_PROPERTY(m_Casts);
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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

bool SEUrinalysisMicroscopic::HasObservationType() const
{
  return m_ObservationType != cdm::UrinalysisData_eMicroscopicObservationType(-1);
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
  m_ObservationType = cdm::UrinalysisData_eMicroscopicObservationType(-1);
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

bool SEUrinalysisMicroscopic::HasEpithelialCellsResult() const
{
  return m_EpithelialCells != cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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
  m_EpithelialCells = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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

bool SEUrinalysisMicroscopic::HasCrystalsResult() const
{
  return m_Crystals != cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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
  m_Crystals = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}

bool SEUrinalysisMicroscopic::HasBacteriaResult() const
{
  return m_Bacteria != cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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
  m_Bacteria = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}

bool SEUrinalysisMicroscopic::HasTrichomonadsResult() const
{
  return m_Trichomonads != cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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
  m_Trichomonads = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}

bool SEUrinalysisMicroscopic::HasYeastResult() const
{
  return m_Yeast != cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
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
  m_Yeast = cdm::UrinalysisData_eMicroscopicObservationAmount(-1);
}