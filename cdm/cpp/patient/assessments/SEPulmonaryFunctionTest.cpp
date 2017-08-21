/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/assessments/SEPulmonaryFunctionTest.h"
#include "patient/SEPatient.h"
#include "system/physiology/SERespiratorySystem.h"
#include "properties/SEScalarFrequency.h"
#include "properties/SEScalarTime.h"
#include "properties/SEScalarVolume.h"
#include "properties/SEScalarVolumePerTime.h"
#include "properties/SEFunctionVolumeVsTime.h"
#include <google/protobuf/text_format.h>

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

std::string SEPulmonaryFunctionTest::Save() const
{
  std::string content;
  cdm::PulmonaryFunctionTestData* src = SEPulmonaryFunctionTest::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  return content;
}
void SEPulmonaryFunctionTest::SaveFile(const std::string& filename) const
{
  std::string content;
  cdm::PulmonaryFunctionTestData* src = SEPulmonaryFunctionTest::Unload(*this);
  google::protobuf::TextFormat::PrintToString(*src, &content);
  std::ofstream ascii_ostream(filename, std::ios::out | std::ios::trunc);
  ascii_ostream << content;
  ascii_ostream.flush();
  ascii_ostream.close();
  delete src;
}

void SEPulmonaryFunctionTest::Load(const cdm::PulmonaryFunctionTestData& src, SEPulmonaryFunctionTest& dst)
{
  SEPulmonaryFunctionTest::Serialize(src, dst);
}
void SEPulmonaryFunctionTest::Serialize(const cdm::PulmonaryFunctionTestData& src, SEPulmonaryFunctionTest& dst)
{
  SEPatientAssessment::Serialize(src.patientassessment(), dst);
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
  SEPatientAssessment::Serialize(src, *dst.mutable_patientassessment());
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

bool SEPulmonaryFunctionTest::HasExpiratoryReserveVolume() const
{
  return m_ExpiratoryReserveVolume==nullptr?false:m_ExpiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetExpiratoryReserveVolume()
{
  if(m_ExpiratoryReserveVolume==nullptr)
    m_ExpiratoryReserveVolume = new SEScalarVolume();
  return *m_ExpiratoryReserveVolume;
}
double SEPulmonaryFunctionTest::GetExpiratoryReserveVolume(const VolumeUnit& unit) const
{
  if (!HasExpiratoryReserveVolume())
    return SEScalar::dNaN();
  return m_ExpiratoryReserveVolume->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasForcedVitalCapacity() const
{
  return m_ForcedVitalCapacity==nullptr?false:m_ForcedVitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetForcedVitalCapacity()
{
  if(m_ForcedVitalCapacity==nullptr)
    m_ForcedVitalCapacity = new SEScalarVolume();
  return *m_ForcedVitalCapacity;
}
double SEPulmonaryFunctionTest::GetForcedVitalCapacity(const VolumeUnit& unit) const
{
  if (!HasForcedVitalCapacity())
    return SEScalar::dNaN();
  return m_ForcedVitalCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasForcedExpiratoryVolume() const
{
  return m_ForcedExpiratoryVolume==nullptr?false:m_ForcedExpiratoryVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetForcedExpiratoryVolume()
{
  if(m_ForcedExpiratoryVolume==nullptr)
    m_ForcedExpiratoryVolume = new SEScalarVolume();
  return *m_ForcedExpiratoryVolume;
}
double SEPulmonaryFunctionTest::GetForcedExpiratoryVolume(const VolumeUnit& unit) const
{
  if (!HasForcedExpiratoryVolume())
    return SEScalar::dNaN();
  return m_ForcedExpiratoryVolume->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasForcedExpiratoryFlow() const
{
  return m_ForcedExpiratoryFlow==nullptr?false:m_ForcedExpiratoryFlow->IsValid();
}
SEScalarVolumePerTime& SEPulmonaryFunctionTest::GetForcedExpiratoryFlow()
{
  if(m_ForcedExpiratoryFlow==nullptr)
    m_ForcedExpiratoryFlow = new SEScalarVolumePerTime();
  return *m_ForcedExpiratoryFlow;
}
double SEPulmonaryFunctionTest::GetForcedExpiratoryFlow(const VolumePerTimeUnit& unit) const
{
  if (!HasForcedExpiratoryFlow())
    return SEScalar::dNaN();
  return m_ForcedExpiratoryFlow->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasInspiratoryCapacity() const
{
  return m_InspiratoryCapacity==nullptr?false:m_InspiratoryCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetInspiratoryCapacity()
{
  if(m_InspiratoryCapacity==nullptr)
    m_InspiratoryCapacity = new SEScalarVolume();
  return *m_InspiratoryCapacity;
}
double SEPulmonaryFunctionTest::GetInspiratoryCapacity(const VolumeUnit& unit) const
{
  if (!HasInspiratoryCapacity())
    return SEScalar::dNaN();
  return m_InspiratoryCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasInspiratoryReserveVolume() const
{
  return m_InspiratoryReserveVolume==nullptr?false:m_InspiratoryReserveVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetInspiratoryReserveVolume()
{
  if(m_InspiratoryReserveVolume==nullptr)
    m_InspiratoryReserveVolume = new SEScalarVolume();
  return *m_InspiratoryReserveVolume;
}
double SEPulmonaryFunctionTest::GetInspiratoryReserveVolume(const VolumeUnit& unit) const
{
  if (!HasInspiratoryReserveVolume())
    return SEScalar::dNaN();
  return m_InspiratoryReserveVolume->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasPeakExpiratoryFlow() const
{
  return m_PeakExpiratoryFlow==nullptr?false:m_PeakExpiratoryFlow->IsValid();
}
SEScalarVolumePerTime& SEPulmonaryFunctionTest::GetPeakExpiratoryFlow()
{
  if(m_PeakExpiratoryFlow==nullptr)
    m_PeakExpiratoryFlow = new SEScalarVolumePerTime();
  return *m_PeakExpiratoryFlow;
}
double SEPulmonaryFunctionTest::GetPeakExpiratoryFlow(const VolumePerTimeUnit& unit) const
{
  if (!HasPeakExpiratoryFlow())
    return SEScalar::dNaN();
  return m_PeakExpiratoryFlow->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasMaximumVoluntaryVentilation() const
{
  return m_MaximumVoluntaryVentilation==nullptr?false:m_MaximumVoluntaryVentilation->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetMaximumVoluntaryVentilation()
{
  if(m_MaximumVoluntaryVentilation==nullptr)
    m_MaximumVoluntaryVentilation = new SEScalarVolume();
  return *m_MaximumVoluntaryVentilation;
}
double SEPulmonaryFunctionTest::GetMaximumVoluntaryVentilation(const VolumeUnit& unit) const
{
  if (!HasMaximumVoluntaryVentilation())
    return SEScalar::dNaN();
  return m_MaximumVoluntaryVentilation->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasSlowVitalCapacity() const
{
  return m_SlowVitalCapacity==nullptr?false:m_SlowVitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetSlowVitalCapacity()
{
  if(m_SlowVitalCapacity==nullptr)
    m_SlowVitalCapacity = new SEScalarVolume();
  return *m_SlowVitalCapacity;
}
double SEPulmonaryFunctionTest::GetSlowVitalCapacity(const VolumeUnit& unit) const
{
  if (!HasSlowVitalCapacity())
    return SEScalar::dNaN();
  return m_SlowVitalCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasTotalLungCapacity() const
{
  return m_TotalLungCapacity==nullptr?false:m_TotalLungCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetTotalLungCapacity()
{
  if(m_TotalLungCapacity==nullptr)
    m_TotalLungCapacity = new SEScalarVolume();
  return *m_TotalLungCapacity;
}
double SEPulmonaryFunctionTest::GetTotalLungCapacity(const VolumeUnit& unit) const
{
  if (!HasTotalLungCapacity())
    return SEScalar::dNaN();
  return m_TotalLungCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasFunctionalResidualCapacity() const
{
  return m_FunctionalResidualCapacity==nullptr?false:m_FunctionalResidualCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetFunctionalResidualCapacity()
{
  if(m_FunctionalResidualCapacity==nullptr)
    m_FunctionalResidualCapacity = new SEScalarVolume();
  return *m_FunctionalResidualCapacity;
}
double SEPulmonaryFunctionTest::GetFunctionalResidualCapacity(const VolumeUnit& unit) const
{
  if (!HasFunctionalResidualCapacity())
    return SEScalar::dNaN();
  return m_FunctionalResidualCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasResidualVolume() const
{
  return m_ResidualVolume==nullptr?false:m_ResidualVolume->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetResidualVolume()
{
  if(m_ResidualVolume==nullptr)
    m_ResidualVolume = new SEScalarVolume();
  return *m_ResidualVolume;
}
double SEPulmonaryFunctionTest::GetResidualVolume(const VolumeUnit& unit) const
{
  if (!HasResidualVolume())
    return SEScalar::dNaN();
  return m_ResidualVolume->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasVitalCapacity() const
{
  return m_VitalCapacity==nullptr?false:m_VitalCapacity->IsValid();
}
SEScalarVolume& SEPulmonaryFunctionTest::GetVitalCapacity()
{
  if(m_VitalCapacity==nullptr)
    m_VitalCapacity = new SEScalarVolume();
  return *m_VitalCapacity;
}
double SEPulmonaryFunctionTest::GetVitalCapacity(const VolumeUnit& unit) const
{
  if (!HasVitalCapacity())
    return SEScalar::dNaN();
  return m_VitalCapacity->GetValue(unit);
}

bool SEPulmonaryFunctionTest::HasLungVolumePlot() const
{
  return m_LungVolumePlot==nullptr?false:m_LungVolumePlot->IsValid();
}
SEFunctionVolumeVsTime& SEPulmonaryFunctionTest::GetLungVolumePlot()
{
  if(m_LungVolumePlot==nullptr)
    m_LungVolumePlot = new SEFunctionVolumeVsTime();
  return *m_LungVolumePlot;
}
const SEFunctionVolumeVsTime* SEPulmonaryFunctionTest::GetLungVolumePlot() const
{
  if (!HasLungVolumePlot())
    return nullptr;
  return m_LungVolumePlot;
}



