/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SECardiacArrest : public SEPatientAction
{
public:

  SECardiacArrest();
  virtual ~SECardiacArrest();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::CardiacArrestData& src, SECardiacArrest& dst);
  static cdm::CardiacArrestData* Unload(const SECardiacArrest& src);
protected:
  static void Serialize(const cdm::CardiacArrestData& src, SECardiacArrest& dst);
  static void Serialize(const SECardiacArrest& src, cdm::CardiacArrestData& dst);

public:

  virtual cdm::eSwitch GetState() const { return m_State; }
  virtual void SetState(cdm::eSwitch s) { m_State = (s == cdm::eSwitch::NullSwitch) ? cdm::eSwitch::Off : s; }

  virtual void ToString(std::ostream &str) const;

protected:
  cdm::eSwitch m_State;

};