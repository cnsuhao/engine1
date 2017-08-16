/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

class CDM_DECL SEProperty
{
protected:

public:

  SEProperty();
  virtual ~SEProperty();

  virtual void Clear(); //clear memory

  virtual void Invalidate()=0;
  virtual bool IsValid() const=0;

};