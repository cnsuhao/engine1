/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"
CDM_BIND_DECL(UrinateData)

class CDM_DECL SEUrinate : public SEPatientAction
{
public:

  SEUrinate();
  virtual ~SEUrinate();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  static void Load(const cdm::UrinateData& src, SEUrinate& dst);
  static cdm::UrinateData* Unload(const SEUrinate& src);
protected:
  static void Serialize(const cdm::UrinateData& src, SEUrinate& dst);
  static void Serialize(const SEUrinate& src, cdm::UrinateData& dst);

public:  
  
  virtual void ToString(std::ostream &str) const;

protected:
  
};      
