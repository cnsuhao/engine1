/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEChestCompression : public SEPatientAction
{
public:

  SEChestCompression();
  virtual ~SEChestCompression();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

public:

  virtual void ToString(std::ostream &str) const = 0;
protected:
};