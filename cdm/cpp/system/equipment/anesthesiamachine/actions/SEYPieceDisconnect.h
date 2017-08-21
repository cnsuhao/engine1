/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
#pragma once
#include "system/equipment/anesthesiamachine/actions/SEAnesthesiaMachineAction.h"

class CDM_DECL SEYPieceDisconnect : public SEAnesthesiaMachineAction
{
public:

  SEYPieceDisconnect();
  virtual ~SEYPieceDisconnect();

  virtual void Clear();

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::YPieceDisconnectData& src, SEYPieceDisconnect& dst);
  static cdm::YPieceDisconnectData* Unload(const SEYPieceDisconnect& src);
protected:
  static void Serialize(const cdm::YPieceDisconnectData& src, SEYPieceDisconnect& dst);
  static void Serialize(const SEYPieceDisconnect& src, cdm::YPieceDisconnectData& dst);

public:

  virtual bool HasSeverity() const;
  virtual SEScalar0To1& GetSeverity();

  virtual void ToString(std::ostream &str) const;

protected:

  SEScalar0To1*     m_Severity;
};  