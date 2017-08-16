/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/assessments/SEPatientAssessment.h"
#include "compartment/fluid/SEFluidCompartment.h"
#include "compartment/fluid/SEFluidCompartmentLink.h"
#include "patient/assessments/SEUrinalysisMicroscopic.h"
class SEPatient;
class SERenalSystem;
class SEAnatomy;

class CDM_DECL SEUrinalysis : public SEPatientAssessment
{
public:

  SEUrinalysis(Logger* logger);
  virtual ~SEUrinalysis();

  virtual void Clear();

  virtual std::string Save() const;
  virtual void SaveFile(const std::string& filename) const;

  static void Load(const cdm::UrinalysisData& src, SEUrinalysis& dst);
  static cdm::UrinalysisData* Unload(const SEUrinalysis& src);
protected:
  static void Serialize(const cdm::UrinalysisData& src, SEUrinalysis& dst);
  static void Serialize(const SEUrinalysis& src, cdm::UrinalysisData& dst);

public:

  virtual bool HasColorResult() const;
  virtual cdm::UrinalysisData_eUrineColor GetColorResult() const;
  virtual void SetColorResult(cdm::UrinalysisData_eUrineColor color);
  virtual void InvalidateColorResult();

  virtual bool HasAppearanceResult() const;
  virtual cdm::UrinalysisData_eClarityIndicator GetAppearanceResult() const;
  virtual void SetAppearanceResult(cdm::UrinalysisData_eClarityIndicator c);
  virtual void InvalidateAppearanceResult();

  virtual bool HasGlucoseResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetGlucoseResult() const;
  virtual void SetGlucoseResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateGlucoseResult();

  virtual bool HasKetoneResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetKetoneResult() const;
  virtual void SetKetoneResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateKetoneResult();
  
  virtual bool HasBilirubinResult() const;
  virtual SEScalar& GetBilirubinResult();
  virtual double GetBilirubinResult() const;

  virtual bool HasSpecificGravityResult() const;
  virtual SEScalar& GetSpecificGravityResult();
  virtual double GetSpecificGravityResult() const;

  virtual bool HasBloodResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetBloodResult() const;
  virtual void SetBloodResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateBloodResult();

  virtual bool HasPHResult() const;
  virtual SEScalar& GetPHResult();
  virtual double GetPHResult() const;

  virtual bool HasProteinResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetProteinResult() const;
  virtual void SetProteinResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateProteinResult();

  virtual bool HasUrobilinogenResult() const;
  virtual SEScalarMassPerVolume& GetUrobilinogenResult();
  virtual double GetUrobilinogenResult(const MassPerVolumeUnit& unit) const;

  virtual bool HasNitriteResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetNitriteResult() const;
  virtual void SetNitriteResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateNitriteResult();

  virtual bool HasLeukocyteEsteraseResult() const;
  virtual cdm::UrinalysisData_ePresenceIndicator GetLeukocyteEsteraseResult() const;
  virtual void SetLeukocyteEsteraseResult(cdm::UrinalysisData_ePresenceIndicator p);
  virtual void InvalidateLeukocyteEsteraseResult();

  virtual bool HasMicroscopicResult() const;
  virtual SEUrinalysisMicroscopic& GetMicroscopicResult();
  virtual const SEUrinalysisMicroscopic* GetMicroscopicResult() const;
  virtual void RemoveMicroscopicResult();
  
protected:

  cdm::UrinalysisData_eUrineColor        m_Color;
  cdm::UrinalysisData_eClarityIndicator  m_Appearance;
  cdm::UrinalysisData_ePresenceIndicator m_Glucose;
  cdm::UrinalysisData_ePresenceIndicator m_Ketone;
  SEScalar*                              m_Bilirubin;
  SEScalar*                              m_SpecificGravity;
  cdm::UrinalysisData_ePresenceIndicator m_Blood;
  SEScalar*                              m_pH;
  cdm::UrinalysisData_ePresenceIndicator m_Protein;
  SEScalarMassPerVolume*                 m_Urobilinogen;
  cdm::UrinalysisData_ePresenceIndicator m_Nitrite;
  cdm::UrinalysisData_ePresenceIndicator m_LeukocyteEsterase;

  SEUrinalysisMicroscopic*               m_Microscopic;
};  