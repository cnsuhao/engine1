/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include "substance/SESubstanceManager.h"
#include "system/equipment/inhaler/SEInhaler.h"
#include "system/equipment/inhaler/actions/SEInhalerConfiguration.h"

class CDM_DECL SEInhalerActionCollection : public Loggable
{
  friend class SEActionManager;
protected:
  SEInhalerActionCollection(SESubstanceManager&);
public:
  ~SEInhalerActionCollection();

  // STATE ACTION
  bool HasConfiguration() const;
  SEInhalerConfiguration* GetConfiguration() const;
  void RemoveConfiguration();
  
protected:
  void Clear();
  static void Serialize(const SEInhalerActionCollection& src, cdm::ActionListData& dst);
  bool ProcessAction(const SEInhalerAction& action, cdm::AnyInhalerActionData& any);

  SEInhalerConfiguration*   m_Configuration;
  // General
  SESubstanceManager& m_Substances;
};
