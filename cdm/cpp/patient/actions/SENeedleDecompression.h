/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SENeedleDecompression : public SEPatientAction
{
public:

  SENeedleDecompression();
  virtual ~SENeedleDecompression();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;
  virtual void SetActive(bool b);

  static void Load(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst);
  static cdm::NeedleDecompressionData* Unload(const SENeedleDecompression& src);
protected:
  static void Serialize(const cdm::NeedleDecompressionData& src, SENeedleDecompression& dst);
  static void Serialize(const SENeedleDecompression& src, cdm::NeedleDecompressionData& dst);

public:

  virtual cdm::eSwitch GetState() const;
  virtual void SetState(cdm::eSwitch name);

  virtual cdm::eSide GetSide() const;
  virtual void SetSide(cdm::eSide LeftOrRight);
  virtual bool HasSide() const;
  virtual void InvalidateSide();
  
  virtual void ToString(std::ostream &str) const;

protected:
  cdm::eSide m_Side;
  cdm::eSwitch m_State;
};    