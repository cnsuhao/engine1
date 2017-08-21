/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once
class SECondition;
class SEEngineTrack;
class PhysiologyEngine;
class SEEngineConfiguration;
PROTO_PUSH
#include "bind/cdm/Properties.pb.h"
PROTO_POP

class CDM_DECL SEEngineStabilization : public Loggable
{
public:
  SEEngineStabilization(Logger* logger);
  virtual ~SEEngineStabilization();

  virtual void Clear();

  virtual bool LoadFile(const std::string& file) = 0;

  virtual bool StabilizeRestingState(PhysiologyEngine& engine)=0;
  virtual bool StabilizeFeedbackState(PhysiologyEngine& engine) = 0;
  virtual bool StabilizeConditions(PhysiologyEngine& engine, const std::vector<const SECondition*>& conditions)=0;
  
  virtual void LogProgress(bool b);

  virtual void CancelStabilization();

  virtual void TrackStabilization(cdm::eSwitch state);
  virtual bool IsTrackingStabilization();

  virtual bool HasStabilizationDuration();
  virtual SEScalarTime& GetStabilizationDuration();

protected:

  bool m_Cancelled;
  bool m_LogProgress;
  cdm::eSwitch m_TrackingStabilization;
  double m_currentTime_s;
  std::stringstream m_ss;

  SEScalarTime* m_StabilizationDuration;
};
