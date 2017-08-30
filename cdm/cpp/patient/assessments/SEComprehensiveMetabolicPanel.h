/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/assessments/SEPatientAssessment.h"
CDM_BIND_DECL(ComprehensiveMetabolicPanelData)
class SEBloodChemistrySystem;

class CDM_DECL SEComprehensiveMetabolicPanel : public SEPatientAssessment
{
public:

  SEComprehensiveMetabolicPanel(Logger* logger);
  virtual ~SEComprehensiveMetabolicPanel();

  virtual void Clear(); //clear memory

  virtual std::string Save() const;
  virtual void SaveFile(const std::string& filename) const;

  static void Load(const cdm::ComprehensiveMetabolicPanelData& src, SEComprehensiveMetabolicPanel& dst);
  static cdm::ComprehensiveMetabolicPanelData* Unload(const SEComprehensiveMetabolicPanel& src);
protected:
  static void Serialize(const cdm::ComprehensiveMetabolicPanelData& src, SEComprehensiveMetabolicPanel& dst);
  static void Serialize(const SEComprehensiveMetabolicPanel& src, cdm::ComprehensiveMetabolicPanelData& dst);

public:
  bool HasAlbumin() const;
  SEScalarMassPerVolume& GetAlbumin();
  virtual double GetAlbumin(const MassPerVolumeUnit& unit) const;

  bool HasALP() const;
  SEScalarMassPerVolume& GetALP();
  virtual double GetALP(const MassPerVolumeUnit& unit) const;

  bool HasALT() const;
  SEScalarMassPerVolume& GetALT();
  virtual double GetALT(const MassPerVolumeUnit& unit) const;

  bool HasAST() const;
  SEScalarMassPerVolume& GetAST();
  virtual double GetAST(const MassPerVolumeUnit& unit) const;

  bool HasBUN() const;
  SEScalarMassPerVolume& GetBUN();
  virtual double GetBUN(const MassPerVolumeUnit& unit) const;

  bool HasCalcium() const;
  SEScalarMassPerVolume& GetCalcium();
  virtual double GetCalcium(const MassPerVolumeUnit& unit) const;

  bool HasChloride() const;
  SEScalarAmountPerVolume& GetChloride();
  virtual double GetChloride(const AmountPerVolumeUnit& unit) const;

  bool HasCO2() const;
  SEScalarAmountPerVolume& GetCO2();
  virtual double GetCO2(const AmountPerVolumeUnit& unit) const;

  bool HasCreatinine() const;
  SEScalarMassPerVolume& GetCreatinine();
  virtual double GetCreatinine(const MassPerVolumeUnit& unit) const;

  bool HasGlucose() const;
  SEScalarMassPerVolume& GetGlucose();
  virtual double GetGlucose(const MassPerVolumeUnit& unit) const;

  bool HasPotassium() const;
  SEScalarAmountPerVolume& GetPotassium();
  virtual double GetPotassium(const AmountPerVolumeUnit& unit) const;

  bool HasSodium() const;
  SEScalarAmountPerVolume& GetSodium();
  virtual double GetSodium(const AmountPerVolumeUnit& unit) const;

  bool HasTotalBilirubin() const;
  SEScalarMassPerVolume& GetTotalBilirubin();
  virtual double GetTotalBilirubin(const MassPerVolumeUnit& unit) const;

  bool HasTotalProtein() const;
  SEScalarMassPerVolume& GetTotalProtein();
  virtual double GetTotalProtein(const MassPerVolumeUnit& unit) const;

protected:

  SEScalarMassPerVolume*    m_Albumin;
  SEScalarMassPerVolume*    m_ALP;
  SEScalarMassPerVolume*    m_ALT;
  SEScalarMassPerVolume*    m_AST;
  SEScalarMassPerVolume*    m_BUN;
  SEScalarMassPerVolume*    m_Calcium;
  SEScalarAmountPerVolume*  m_Chloride;
  SEScalarAmountPerVolume*  m_CO2;
  SEScalarMassPerVolume*    m_Creatinine;
  SEScalarMassPerVolume*    m_Glucose;
  SEScalarAmountPerVolume*  m_Potassium;
  SEScalarAmountPerVolume*  m_Sodium;
  SEScalarMassPerVolume*    m_TotalBilirubin;
  SEScalarMassPerVolume*    m_TotalProtein;

};  