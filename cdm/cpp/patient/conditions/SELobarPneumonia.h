/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/conditions/SEPatientCondition.h"
CDM_BIND_DECL(LobarPneumoniaData)

class CDM_DECL SELobarPneumonia : public SEPatientCondition
{
public:

  SELobarPneumonia();
  virtual ~SELobarPneumonia();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  static void Load(const cdm::LobarPneumoniaData& src, SELobarPneumonia& dst);
  static cdm::LobarPneumoniaData* Unload(const SELobarPneumonia& src);
protected:
  static void Serialize(const cdm::LobarPneumoniaData& src, SELobarPneumonia& dst);
  static void Serialize(const SELobarPneumonia& src, cdm::LobarPneumoniaData& dst);

public:
  virtual std::string GetName() const { return "LobarPneumonia"; }

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();  

  virtual bool HasLeftLungAffected() const;
  virtual SEScalar0To1& GetLeftLungAffected();

  virtual bool HasRightLungAffected() const;
  virtual SEScalar0To1& GetRightLungAffected();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
  SEScalar0To1*     m_LeftLungAffected;
  SEScalar0To1*     m_RightLungAffected;
};      
