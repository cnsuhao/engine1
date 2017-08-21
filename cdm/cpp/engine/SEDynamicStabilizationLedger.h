/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
#include "engine/SEDynamicStabilizationEngineConvergence.h"

// Book keeping class that tracks all the properties and if their convergent state
class CDM_DECL SEDynamicStabilizationLedger : public Loggable
{
public:
  SEDynamicStabilizationLedger(double timeStep_s, const SEDynamicStabilizationEngineConvergence& convergence);
  virtual ~SEDynamicStabilizationLedger() {};

  virtual void TestConvergence();
  virtual bool HasConverged() { return m_converged; }
  virtual bool HasConvergedOptional() { return m_convergedOptional; }
  virtual bool HasExceededTime() { return m_exceededTime; }

protected:

  bool   m_converged;
  bool   m_convergedOptional;
  bool   m_exceededTime;
  bool   m_hasOptionalProperties;
  double m_dT_s;
  double m_totTime_s;// Total time we have been converging
  double m_covTime_s;// Convergence Window Length
  double m_minTime_s;// Minimum amount of time to run before testing
  double m_maxTime_s;// Maximum amount of time to run before we quit
  double m_passTime_s;
  double m_optsPassTime_s;

  const std::vector<SEDynamicStabilizationPropertyConvergence*>& m_properties;
};