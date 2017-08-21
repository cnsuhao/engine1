/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#pragma  warning(push)
#pragma warning(disable:4512) // assignment operator could not be generated
#pragma warning(disable:4290) // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
#include "log4cpp/Category.hh"
#pragma  warning(pop)

class Logger;
class SEScalarTime;
class CDM_DECL Loggable
{
public:
  static const std::string empty;

  Loggable();
  Loggable(Logger* log);
  virtual ~Loggable();

  virtual Logger* GetLogger() const;

  virtual void Debug(const std::string&  msg, const std::string&  origin = empty) const;
  virtual void Debug(std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Debug(std::ostream &msg, const std::string&  origin = empty) const;

  virtual void Info(const std::string&  msg, const std::string&  origin = empty) const;
  virtual void Info(std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Info(const std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Info(std::ostream &msg, const std::string&  origin = empty) const;

  virtual void Warning(const std::string&  msg, const std::string&  origin = empty) const;
  virtual void Warning(std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Warning(std::ostream &msg, const std::string&  origin = empty) const;

  virtual void Error(const std::string&  msg, const std::string&  origin = empty) const;
  virtual void Error(std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Error(std::ostream &msg, const std::string&  origin = empty) const;

  virtual void Fatal(const std::string&  msg, const std::string&  origin = empty) const;
  virtual void Fatal(std::stringstream &msg, const std::string&  origin = empty) const;
  virtual void Fatal(std::ostream &msg, const std::string&  origin = empty) const;

protected:
  Logger* m_Logger;
};

#pragma warning(push)
#pragma warning(disable:4100)
class CDM_DECL LoggerForward
{
public:
  virtual void ForwardDebug(const std::string&  msg, const std::string&  origin){};
  virtual void ForwardInfo(const std::string&  msg, const std::string&  origin){};
  virtual void ForwardWarning(const std::string&  msg, const std::string&  origin){};
  virtual void ForwardError(const std::string&  msg, const std::string&  origin){};
  virtual void ForwardFatal(const std::string&  msg, const std::string&  origin){};
};

#pragma warning(pop)

class CDM_DECL Logger
{
  friend Loggable;
public:
  Logger(const std::string&  logFilename = Loggable::empty);
  virtual ~Logger();

  void LogToConsole(bool b);

  void ResetLogFile(const std::string&  logFilename = Loggable::empty);

  void SetLogLevel(log4cpp::Priority::Value priority);
  log4cpp::Priority::Value GetLogLevel();

  virtual void SetLogTime(const SEScalarTime* time);

  virtual void SetForward(LoggerForward* forward);
  virtual bool HasForward();

  virtual void Debug(const std::string&  msg, const std::string&  origin = Loggable::empty);
  virtual void Debug(std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Debug(std::ostream &msg, const std::string&  origin = Loggable::empty);

  virtual void Info(const std::string&  msg, const std::string&  origin = Loggable::empty);
  virtual void Info(std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Info(const std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Info(std::ostream &msg, const std::string&  origin = Loggable::empty);

  virtual void Warning(const std::string&  msg, const std::string&  origin = Loggable::empty);
  virtual void Warning(std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Warning(std::ostream &msg, const std::string&  origin = Loggable::empty);

  virtual void Error(const std::string&  msg, const std::string&  origin = Loggable::empty);
  virtual void Error(std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Error(std::ostream &msg, const std::string&  origin = Loggable::empty);

  virtual void Fatal(const std::string&  msg, const std::string&  origin = Loggable::empty);
  virtual void Fatal(std::stringstream &msg, const std::string&  origin = Loggable::empty);
  virtual void Fatal(std::ostream &msg, const std::string&  origin = Loggable::empty);

protected:

  virtual std::string FormatLogMessage(const std::string&  origin, const std::string&  msg);

  LoggerForward*      m_Forward;
  log4cpp::Category*  m_Log;
  log4cpp::Appender*  m_FileAppender;
  log4cpp::Appender*  m_ConsoleAppender;
  const SEScalarTime* m_time;
  std::stringstream   m_ss;
};

