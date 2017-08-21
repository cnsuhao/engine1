/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SETensionPneumothorax : public SEPatientAction
{
public:

  SETensionPneumothorax();
  virtual ~SETensionPneumothorax();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::TensionPneumothoraxData& src, SETensionPneumothorax& dst);
  static cdm::TensionPneumothoraxData* Unload(const SETensionPneumothorax& src);
protected:
  static void Serialize(const cdm::TensionPneumothoraxData& src, SETensionPneumothorax& dst);
  static void Serialize(const SETensionPneumothorax& src, cdm::TensionPneumothoraxData& dst);

public:

  virtual cdm::eGate GetType() const;
  virtual void SetType(cdm::eGate name);
  virtual bool HasType() const;
  virtual void InvalidateType();
  
  virtual cdm::eSide GetSide() const;
  virtual void SetSide(cdm::eSide name);
  virtual bool HasSide() const;
  virtual void InvalidateSide();

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:
  cdm::eGate    m_Type;
  cdm::eSide    m_Side;
  SEScalar0To1* m_Severity;
  
};    