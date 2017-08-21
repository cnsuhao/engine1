/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "patient/actions/SEPatientAction.h"

class CDM_DECL SEConsciousRespirationCommand
{
public:

  SEConsciousRespirationCommand();
  virtual ~SEConsciousRespirationCommand();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;
  virtual bool IsActive() const;

  virtual std::string GetComment() const;
  virtual void SetComment(const std::string& comment);
  virtual bool HasComment() const;
  virtual void InvalidateComment();

  virtual void ToString(std::ostream &str) const = 0;

protected:

  std::string                               m_Comment;
};  

inline std::ostream& operator<< (std::ostream& out, const SEConsciousRespirationCommand& c)
{
  c.ToString(out);
  return out;
}