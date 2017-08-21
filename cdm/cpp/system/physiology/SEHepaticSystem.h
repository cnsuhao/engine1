/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "system/SESystem.h"

class CDM_DECL SEHepaticSystem : public SESystem
{
public:

  SEHepaticSystem(Logger* logger);
  virtual ~SEHepaticSystem();

  virtual void Clear();// Deletes all members
  
  virtual const SEScalar* GetScalar(const std::string& name);

  static void Load(const cdm::HepaticSystemData& src, SEHepaticSystem& dst);
  static cdm::HepaticSystemData* Unload(const SEHepaticSystem& src);
protected:
  static void Serialize(const cdm::HepaticSystemData& src, SEHepaticSystem& dst);
  static void Serialize(const SEHepaticSystem& src, cdm::HepaticSystemData& dst);

public:

  
protected:

  
};