/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include <jni.h>
#include <iostream>
#include "PulsePhysiologyEngine.h"
#include "Controller/Engine.h"
#include "scenario/SEScenarioExec.h"
#include "utils/SEEventHandler.h"

#include <memory>

class PulseEngineJNI : public LoggerForward, public SEScenarioCustomExec, public SEEventHandler
{
public:
  PulseEngineJNI(const std::string& logFile);
  ~PulseEngineJNI();

  void Reset();

  void ForwardDebug(const std::string&  msg, const std::string&  origin);
  void ForwardInfo(const std::string&  msg, const std::string&  origin);
  void ForwardWarning(const std::string&  msg, const std::string&  origin);
  void ForwardError(const std::string&  msg, const std::string&  origin);
  void ForwardFatal(const std::string&  msg, const std::string&  origin);
  void CustomExec(double time_s, PhysiologyEngine* engine);
  void PushData(double time_s);

  void HandlePatientEvent(cdm::PatientData_eEvent type, bool active, const SEScalarTime* time = nullptr);
  void HandleAnesthesiaMachineEvent(cdm::AnesthesiaMachineData_eEvent type, bool active, const SEScalarTime* time = nullptr);

  JNIEnv*    jniEnv;
  jobject    jniObj;
  DataTrack* trk;
  PulseScenarioExec* exec;
  bool       firstUpdate;
  int        update_cnt;
  int        updateFrequency_cnt;
  std::unique_ptr<PulseEngine> eng;
  
  jmethodID jniDebugMethodID;
  jmethodID jniInfoMethodID;
  jmethodID jniWarnMethodID;
  jmethodID jniErrorMethodID;
  jmethodID jniFatalMethodID;
};
