/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
PROTO_PUSH
#include "bind/cdm/PatientNutrition.pb.h"
PROTO_POP

class CDM_DECL SENutrition : public Loggable
{
public:

  SENutrition(Logger* logger);
  virtual ~SENutrition();

  virtual void Clear();

 static void Load(const cdm::NutritionData& src, SENutrition& dst);
  static cdm::NutritionData* Unload(const SENutrition& src);
protected:
  static void Serialize(const cdm::NutritionData& src, SENutrition& dst);
  static void Serialize(const SENutrition& src, cdm::NutritionData& dst);

public:
  const SEScalar* GetScalar(const std::string& name);
  
  bool LoadFile(const std::string& nutritionFile);

  void Increment(const SENutrition& from);
  
  virtual bool HasCarbohydrate() const;
  virtual SEScalarMass& GetCarbohydrate();
  virtual double GetCarbohydrate(const MassUnit& unit) const;

  virtual bool HasCarbohydrateDigestionRate() const;
  virtual SEScalarMassPerTime& GetCarbohydrateDigestionRate();
  virtual double GetCarbohydrateDigestionRate(const MassPerTimeUnit& unit) const;
  
  virtual bool HasFat() const;
  virtual SEScalarMass& GetFat();
  virtual double GetFat(const MassUnit& unit) const;

  virtual bool HasFatDigestionRate() const;
  virtual SEScalarMassPerTime& GetFatDigestionRate();
  virtual double GetFatDigestionRate(const MassPerTimeUnit& unit) const;
  
  virtual bool HasProtein() const;
  virtual SEScalarMass& GetProtein();
  virtual double GetProtein(const MassUnit& unit) const;

  virtual bool HasProteinDigestionRate() const;
  virtual SEScalarMassPerTime& GetProteinDigestionRate();
  virtual double GetProteinDigestionRate(const MassPerTimeUnit& unit) const;
  
  virtual bool HasSodium() const;
  virtual SEScalarMass& GetSodium();
  virtual double GetSodium(const MassUnit& unit) const;

  virtual bool HasCalcium() const;
  virtual SEScalarMass& GetCalcium();
  virtual double GetCalcium(const MassUnit& unit) const;
  
  virtual bool HasWater() const;
  virtual SEScalarVolume& GetWater();
  virtual double GetWater(const VolumeUnit& unit) const;

  virtual double GetWeight(const MassUnit& unit) const;

  virtual void ToString(std::ostream &str) const;
  
protected:

  SEScalarMass*          m_Carbohydrate;
  SEScalarMassPerTime*   m_CarbohydrateDigestionRate;
  SEScalarMass*          m_Fat;
  SEScalarMassPerTime*   m_FatDigestionRate;
  SEScalarMass*          m_Protein;
  SEScalarMassPerTime*   m_ProteinDigestionRate;
  SEScalarMass*          m_Calcium;
  SEScalarMass*          m_Sodium;
  SEScalarVolume*        m_Water;
};

inline std::ostream& operator<< (std::ostream& out, const SENutrition& n)
{
  n.ToString(out);
  return out;
}