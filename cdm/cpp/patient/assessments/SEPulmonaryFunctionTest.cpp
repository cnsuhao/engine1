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
#include "patient/assessments/SEPulmonaryFunctionTest.h"
#include "patient/SEPatient.h"
#include "system/physiology/SERespiratorySystem.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEFunctionVolumeVsTime.h"

SEPulmonaryFunctionTest::SEPulmonaryFunctionTest(Logger* logger) : SEPatientAssessment(logger)
{
  m_NumberOfPlotPoints = 100;
  m_ExpiratoryReserveVolume=nullptr;
  m_ForcedVitalCapacity=nullptr;
  m_ForcedExpiratoryVolume=nullptr;
  m_ForcedExpiratoryFlow=nullptr;
  m_InspiratoryCapacity=nullptr;
  m_InspiratoryReserveVolume=nullptr;
  m_PeakExpiratoryFlow=nullptr;
  m_MaximumVoluntaryVentilation=nullptr;
  m_SlowVitalCapacity=nullptr;
  m_TotalLungCapacity=nullptr;
  m_FunctionalResidualCapacity=nullptr;
  m_ResidualVolume=nullptr;
  m_VitalCapacity=nullptr;

  m_LungVolumePlot=nullptr;
}

SEPulmonaryFunctionTest::~SEPulmonaryFunctionTest()
{
  Clear();
}

void SEPulmonaryFunctionTest::Clear()
{
  SEPatientAssessment::Clear();
  SAFE_DELETE(m_ExpiratoryReserveVolume);
  SAFE_DELETE(m_ForcedVitalCapacity);
  SAFE_DELETE(m_ForcedExpiratoryVolume);
  SAFE_DELETE(m_ForcedExpiratoryFlow);
  SAFE_DELETE(m_InspiratoryCapacity);
  SAFE_DELETE(m_InspiratoryReserveVolume);
  SAFE_DELETE(m_PeakExpiratoryFlow);
  SAFE_DELETE(m_MaximumVoluntaryVentilation);
  SAFE_DELETE(m_SlowVitalCapacity);
  SAFE_DELETE(m_TotalLungCapacity);
  SAFE_DELETE(m_FunctionalResidualCapacity);
  SAFE_DELETE(m_ResidualVolume);
  SAFE_DELETE(m_VitalCapacity);

  SAFE_DELETE(m_LungVolumePlot);

}

void SEPulmonaryFunctionTest::Reset()
{
  SEPatientAssessment::Reset();
  INVALIDATE_PROPERTY(m_ExpiratoryReserveVolume);
  INVALIDATE_PROPERTY(m_ForcedVitalCapacity);
  INVALIDATE_PROPERTY(m_ForcedExpiratoryVolume);
  INVALIDATE_PROPERTY(m_ForcedExpiratoryFlow);
  INVALIDATE_PROPERTY(m_InspiratoryCapacity);
  INVALIDATE_PROPERTY(m_InspiratoryReserveVolume);
  INVALIDATE_PROPERTY(m_PeakExpiratoryFlow);
  INVALIDATE_PROPERTY(m_MaximumVoluntaryVentilation);
  INVALIDATE_PROPERTY(m_SlowVitalCapacity);
  INVALIDATE_PROPERTY(m_TotalLungCapacity);
  INVALIDATE_PROPERTY(m_FunctionalResidualCapacity);
  INVALIDATE_PROPERTY(m_ResidualVolume);
  INVALIDATE_PROPERTY(m_VitalCapacity);

  INVALIDATE_PROPERTY(m_LungVolumePlot);
}

void SEPulmonaryFunctionTest::Load(const cdm::PulmonaryFunctionTestData& src, SEPulmonaryFunctionTest& dst)
{
  SEPulmonaryFunctionTest::Serialize(src, dst);
}
void SEPulmonaryFunctionTest::Serialize(const cdm::PulmonaryFunctionTestData& src, SEPulmonaryFunctionTest& dst)
{
  dst.Clear();
  if (src.has_expiratoryreservevolume())
    SEScalarVolume::Load(src.expiratoryreservevolume(), dst.GetExpiratoryReserveVolume());
  if (src.has_forcedvitalcapacity())
    SEScalarVolume::Load(src.forcedvitalcapacity(), dst.GetForcedVitalCapacity());
  if (src.has_forcedexpiratoryvolume())
    SEScalarVolume::Load(src.forcedexpiratoryvolume(), dst.GetForcedExpiratoryVolume());
  if (src.has_forcedexpiratoryflow())
    SEScalarVolumePerTime::Load(src.forcedexpiratoryflow(), dst.GetForcedExpiratoryFlow());
  if (src.has_functionalresidualcapacity())
    SEScalarVolume::Load(src.functionalresidualcapacity(), dst.GetFunctionalResidualCapacity());
  if (src.has_inspiratorycapacity())
    SEScalarVolume::Load(src.inspiratorycapacity(), dst.GetInspiratoryCapacity());
  if (src.has_maximumvoluntaryventilation())
    SEScalarVolume::Load(src.maximumvoluntaryventilation(), dst.GetMaximumVoluntaryVentilation());
  if (src.has_peakexpiratoryflow())
    SEScalarVolumePerTime::Load(src.peakexpiratoryflow(), dst.GetPeakExpiratoryFlow());
  if (src.has_residualvolume())
    SEScalarVolume::Load(src.residualvolume(), dst.GetResidualVolume());
  if (src.has_slowvitalcapacity())
    SEScalarVolume::Load(src.slowvitalcapacity(), dst.GetSlowVitalCapacity());
  if (src.has_totallungcapacity())
    SEScalarVolume::Load(src.totallungcapacity(), dst.GetTotalLungCapacity());
  if (src.has_vitalcapacity())
    SEScalarVolume::Load(src.vitalcapacity(), dst.GetVitalCapacity());
  if (src.has_lungvolumeplot())
    SEFunctionVolumeVsTime::Load(src.lungvolumeplot(), dst.GetLungVolumePlot());
}

cdm::PulmonaryFunctionTestData* SEPulmonaryFunctionTest::Unload(const SEPulmonaryFunctionTest& src)
{
  cdm::PulmonaryFunctionTestData* dst = new cdm::PulmonaryFunctionTestData();
  SEPulmonaryFunctionTest::Serialize(src, *dst);
  return dst;
}
void SEPulmonaryFunctionTest::Serialize(const SEPulmonaryFunctionTest& src, cdm::PulmonaryFunctionTestData& dst)
{
  if (src.HasExpiratoryReserveVolume())
    dst.set_allocated_expiratoryreservevolume(SEScalarVolume::Unload(*src.m_ExpiratoryReserveVolume));
  if (src.HasForcedVitalCapacity())
    dst.set_allocated_forcedvitalcapacity(SEScalarVolume::Unload(*src.m_ForcedVitalCapacity));
  if (src.HasForcedExpiratoryVolume())
    dst.set_allocated_forcedexpiratoryvolume(SEScalarVolume::Unload(*src.m_ForcedExpiratoryVolume));
  if (src.HasForcedExpiratoryFlow())
    dst.set_allocated_forcedexpiratoryflow(SEScalarVolumePerTime::Unload(*src.m_ForcedExpiratoryFlow));
  if (src.HasFunctionalResidualCapacity())
    dst.set_allocated_functionalresidualcapacity(SEScalarVolume::Unload(*src.m_FunctionalResidualCapacity));
  if (src.HasInspiratoryCapacity())
    dst.set_allocated_inspiratorycapacity(SEScalarVolume::Unload(*src.m_InspiratoryCapacity));
  if (src.HasInspiratoryReserveVolume())
    dst.set_allocated_inspiratoryreservevolume(SEScalarVolume::Unload(*src.m_InspiratoryReserveVolume));
  if (src.HasMaximumVoluntaryVentilation())
    dst.set_allocated_maximumvoluntaryventilation(SEScalarVolume::Unload(*src.m_MaximumVoluntaryVentilation));
  if (src.HasPeakExpiratoryFlow())
    dst.set_allocated_peakexpiratoryflow(SEScalarVolumePerTime::Unload(*src.m_PeakExpiratoryFlow));
  if (src.HasResidualVolume())
    dst.set_allocated_residualvolume(SEScalarVolume::Unload(*src.m_ResidualVolume));
  if (src.HasSlowVitalCapacity())
    dst.set_allocated_slowvitalcapacity(SEScalarVolume::Unload(*src.m_SlowVitalCapacity));
  if (src.HasTotalLungCapacity())
    dst.set_allocated_totallungcapacity(SEScalarVolume::Unload(*src.m_TotalLungCapacity));
  if (src.HasVitalCapacity())
    dst.set_allocated_vitalcapacity(SEScalarVolume::Unload(*src.m_VitalCapacity));
  if (src.HasLungVolumePlot())
    dst.set_allocated_lungvolumeplot(SEFunctionVolumeVsTime::Unload(*src.m_LungVolumePlot));
}

bool SEPulmonaryFunctionTest::HasExpiratoryReserveVolume()
{
  return m_ExpiratoryReserveVolume==nullptr?false:m_ExpiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetExpiratoryReserveVolume()
{
  if(m_ExpiratoryReserveVolume==nullptr)
    m_ExpiratoryReserveVolume = new SEScalarVolume();
  return *m_ExpiratoryReserveVolume;
}

bool SEPulmonaryFunctionTest::HasForcedVitalCapacity()
{
  return m_ForcedVitalCapacity==nullptr?false:m_ForcedVitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetForcedVitalCapacity()
{
  if(m_ForcedVitalCapacity==nullptr)
    m_ForcedVitalCapacity = new SEScalarVolume();
  return *m_ForcedVitalCapacity;
}

bool SEPulmonaryFunctionTest::HasForcedExpiratoryVolume()
{
  return m_ForcedExpiratoryVolume==nullptr?false:m_ForcedExpiratoryVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetForcedExpiratoryVolume()
{
  if(m_ForcedExpiratoryVolume==nullptr)
    m_ForcedExpiratoryVolume = new SEScalarVolume();
  return *m_ForcedExpiratoryVolume;
}

bool SEPulmonaryFunctionTest::HasForcedExpiratoryFlow()
{
  return m_ForcedExpiratoryFlow==nullptr?false:m_ForcedExpiratoryFlow->IsValid();
}
SEScalarVolumePerTime& SEPulmonaryFunctionTest::GetForcedExpiratoryFlow()
{
  if(m_ForcedExpiratoryFlow==nullptr)
    m_ForcedExpiratoryFlow = new SEScalarVolumePerTime();
  return *m_ForcedExpiratoryFlow;
}

bool SEPulmonaryFunctionTest::HasInspiratoryCapacity()
{
  return m_InspiratoryCapacity==nullptr?false:m_InspiratoryCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetInspiratoryCapacity()
{
  if(m_InspiratoryCapacity==nullptr)
    m_InspiratoryCapacity = new SEScalarVolume();
  return *m_InspiratoryCapacity;
}

bool SEPulmonaryFunctionTest::HasInspiratoryReserveVolume()
{
  return m_InspiratoryReserveVolume==nullptr?false:m_InspiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetInspiratoryReserveVolume()
{
  if(m_InspiratoryReserveVolume==nullptr)
    m_InspiratoryReserveVolume = new SEScalarVolume();
  return *m_InspiratoryReserveVolume;
}

bool SEPulmonaryFunctionTest::HasPeakExpiratoryFlow()
{
  return m_PeakExpiratoryFlow==nullptr?false:m_PeakExpiratoryFlow->IsValid();
}
SEScalarVolumePerTime& SEPulmonaryFunctionTest::GetPeakExpiratoryFlow()
{
  if(m_PeakExpiratoryFlow==nullptr)
    m_PeakExpiratoryFlow = new SEScalarVolumePerTime();
  return *m_PeakExpiratoryFlow;
}

bool SEPulmonaryFunctionTest::HasMaximumVoluntaryVentilation()
{
  return m_MaximumVoluntaryVentilation==nullptr?false:m_MaximumVoluntaryVentilation->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetMaximumVoluntaryVentilation()
{
  if(m_MaximumVoluntaryVentilation==nullptr)
    m_MaximumVoluntaryVentilation = new SEScalarVolume();
  return *m_MaximumVoluntaryVentilation;
}

bool SEPulmonaryFunctionTest::HasSlowVitalCapacity()
{
  return m_SlowVitalCapacity==nullptr?false:m_SlowVitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetSlowVitalCapacity()
{
  if(m_SlowVitalCapacity==nullptr)
    m_SlowVitalCapacity = new SEScalarVolume();
  return *m_SlowVitalCapacity;
}

bool SEPulmonaryFunctionTest::HasTotalLungCapacity()
{
  return m_TotalLungCapacity==nullptr?false:m_TotalLungCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetTotalLungCapacity()
{
  if(m_TotalLungCapacity==nullptr)
    m_TotalLungCapacity = new SEScalarVolume();
  return *m_TotalLungCapacity;
}

bool SEPulmonaryFunctionTest::HasFunctionalResidualCapacity()
{
  return m_FunctionalResidualCapacity==nullptr?false:m_FunctionalResidualCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetFunctionalResidualCapacity()
{
  if(m_FunctionalResidualCapacity==nullptr)
    m_FunctionalResidualCapacity = new SEScalarVolume();
  return *m_FunctionalResidualCapacity;
}

bool SEPulmonaryFunctionTest::HasResidualVolume()
{
  return m_ResidualVolume==nullptr?false:m_ResidualVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetResidualVolume()
{
  if(m_ResidualVolume==nullptr)
    m_ResidualVolume = new SEScalarVolume();
  return *m_ResidualVolume;
}

bool SEPulmonaryFunctionTest::HasVitalCapacity()
{
  return m_VitalCapacity==nullptr?false:m_VitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetVitalCapacity()
{
  if(m_VitalCapacity==nullptr)
    m_VitalCapacity = new SEScalarVolume();
  return *m_VitalCapacity;
}

bool SEPulmonaryFunctionTest::HasLungVolumePlot()
{
  return m_LungVolumePlot==nullptr?false:m_LungVolumePlot->IsValid();
}
SEFunctionVolumeVsTime& SEPulmonaryFunctionTest::GetLungVolumePlot()
{
  if(m_LungVolumePlot==nullptr)
    m_LungVolumePlot = new SEFunctionVolumeVsTime();
  return *m_LungVolumePlot;
}



