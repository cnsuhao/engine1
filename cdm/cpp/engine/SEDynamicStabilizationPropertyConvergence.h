/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "engine/SEEngineTracker.h"

class CDM_DECL SEDynamicStabilizationPropertyConvergence : public Loggable
{
  friend class SEDynamicStabilizationEngineConvergence;
protected:
  SEDynamicStabilizationPropertyConvergence(SEDataRequest& dr, Logger* logger);
public:
  virtual ~SEDynamicStabilizationPropertyConvergence();

  bool Test(double time_s);

  double GetPercentError()        const { return m_Error; }
  double GetLastPercentError()    const { return m_LastError; }
  double GetLastErrorTime_s()     const { return m_LastErrorTime_s; }
  double GetCurrentTarget()       const { return m_Target; }
  SEDataRequest& GetDataRequest() const { return m_DataRequest; }
  bool IsOptional()               const { return m_Optional; }
  void SetOptional(bool b)              { m_Optional = b; }

  void TrackScalar(const SEScalar& s)   { m_DataRequestScalar.SetScalar(&s, m_DataRequest); }
  SEDataRequestScalar& GetDataRequestScalar() { return m_DataRequestScalar; }
protected:

  SEDataRequest&       m_DataRequest;
  SEDataRequestScalar  m_DataRequestScalar;

  bool                 m_Optional;
  double               m_Target;
  double               m_Error;
  double               m_LastError;
  double               m_LastErrorTime_s;
  std::stringstream    m_ss;
};