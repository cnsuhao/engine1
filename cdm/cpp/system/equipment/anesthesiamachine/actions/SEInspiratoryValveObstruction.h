/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEInspiratoryValveObstruction : public SEAnesthesiaMachineAction
{
public:

  SEInspiratoryValveObstruction();
  virtual ~SEInspiratoryValveObstruction();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst);
  static cdm::InspiratoryValveObstructionData* Unload(const SEInspiratoryValveObstruction& src);
protected:
  static void Serialize(const cdm::InspiratoryValveObstructionData& src, SEInspiratoryValveObstruction& dst);
  static void Serialize(const SEInspiratoryValveObstruction& src, cdm::InspiratoryValveObstructionData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  