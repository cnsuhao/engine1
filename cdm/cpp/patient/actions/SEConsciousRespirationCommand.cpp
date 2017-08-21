/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "stdafx.h"
#include "patient/actions/SEConsciousRespirationCommand.h"

SEConsciousRespirationCommand::SEConsciousRespirationCommand()
{
  m_Comment = "";
}

SEConsciousRespirationCommand::~SEConsciousRespirationCommand()
{
  Clear();
}

void SEConsciousRespirationCommand::Clear()
{
  m_Comment = "";
}

bool SEConsciousRespirationCommand::IsValid() const
{
  return true;
}

bool SEConsciousRespirationCommand::IsActive() const
{
  return true;
}

std::string SEConsciousRespirationCommand::GetComment() const
{
  return m_Comment;
}
void SEConsciousRespirationCommand::SetComment(const std::string& comment)
{
  m_Comment = comment;
}
bool SEConsciousRespirationCommand::HasComment() const
{
  return m_Comment.empty() ? false : true;
}
void SEConsciousRespirationCommand::InvalidateComment()
{
  m_Comment = "";
}


