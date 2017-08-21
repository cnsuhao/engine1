/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEExpiratoryValveObstruction : public SEAnesthesiaMachineAction
{
public:

  SEExpiratoryValveObstruction();
  virtual ~SEExpiratoryValveObstruction();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ExpiratoryValveObstructionData& src, SEExpiratoryValveObstruction& dst);
  static cdm::ExpiratoryValveObstructionData* Unload(const SEExpiratoryValveObstruction& src);
protected:
  static void Serialize(const cdm::ExpiratoryValveObstructionData& src, SEExpiratoryValveObstruction& dst);
  static void Serialize(const SEExpiratoryValveObstruction& src, cdm::ExpiratoryValveObstructionData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  