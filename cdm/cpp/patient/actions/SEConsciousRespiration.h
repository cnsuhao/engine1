/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"
CDM_BIND_DECL(ConsciousRespirationData)
class SEConsciousRespirationCommand;
class SEForcedExhale;
class SEForcedInhale;
class SEBreathHold;
class SEUseInhaler;

class CDM_DECL SEConsciousRespiration : public SEPatientAction
{
public:

  SEConsciousRespiration();
  virtual ~SEConsciousRespiration();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::ConsciousRespirationData& src, SEConsciousRespiration& dst);
  static cdm::ConsciousRespirationData* Unload(const SEConsciousRespiration& src);
protected:
  static void Serialize(const cdm::ConsciousRespirationData& src, SEConsciousRespiration& dst);
  static void Serialize(const SEConsciousRespiration& src, cdm::ConsciousRespirationData& dst);

public:
  // Get the active command
  virtual SEConsciousRespirationCommand* GetActiveCommand();
  /// When the active command has been processed, remove it
  virtual void RemoveActiveCommand();

  virtual SEForcedExhale& AddForcedExhale();
  virtual SEForcedInhale& AddForcedInhale();
  virtual SEBreathHold&   AddBreathHold();
  virtual SEUseInhaler&   AddUseInhaler();

  virtual void ToString(std::ostream &str) const;
protected:

  bool m_ClearCommands;
  std::vector<SEConsciousRespirationCommand*> m_Commands;
};  