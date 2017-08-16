/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include "PulseEngineJNI.h"
#include "PulseScenario.h"
#include "Controller/ScenarioExec.h"
#include "scenario/SEDataRequest.h"
#include "scenario/SEAction.h"
#include "scenario/SECondition.h"

#include "patient/assessments/SEPulmonaryFunctionTest.h"
#include "patient/assessments/SECompleteBloodCount.h"
#include "patient/assessments/SEComprehensiveMetabolicPanel.h"
#include "patient/assessments/SEUrinalysis.h"

#include "bind/cdm/Patient.pb.h"
#include "bind/cdm/AnesthesiaMachine.pb.h"
#include <google/protobuf/text_format.h>

#include "EngineTest.h"

extern "C"
JNIEXPORT jlong JNICALL Java_mil_tatrc_physiology_pulse_testing_EngineUnitTestDriver_nativeAllocate(JNIEnv *env, jobject obj)
{
  PulseEngineTest *executor = new PulseEngineTest();
  return reinterpret_cast<jlong>(executor);
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_testing_EngineUnitTestDriver_nativeDelete(JNIEnv *env, jobject obj, jlong ptr)
{
  PulseEngineTest *executor = reinterpret_cast<PulseEngineTest*>(ptr);
  SAFE_DELETE(executor);
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_testing_EngineUnitTestDriver_nativeExecute(JNIEnv *env, jobject obj, jlong ptr, jstring test, jstring toDir)
{
  const char* testName = env->GetStringUTFChars(test, JNI_FALSE);
  const char* outputDir = env->GetStringUTFChars(toDir, JNI_FALSE);
  PulseEngineTest *executor = reinterpret_cast<PulseEngineTest*>(ptr);
  executor->RunTest(testName, outputDir);
  env->ReleaseStringUTFChars(test, testName);
  env->ReleaseStringUTFChars(toDir, outputDir);
}

extern "C"
JNIEXPORT jlong JNICALL Java_mil_tatrc_physiology_pulse_engine_Pulse_nativeAllocate(JNIEnv *env, jobject obj, jstring logFile)
{ 
  const char* logF = env->GetStringUTFChars(logFile, JNI_FALSE);
  PulseEngineJNI *engineJNI = new PulseEngineJNI(logF);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  env->ReleaseStringUTFChars(logFile, logF);
  return reinterpret_cast<jlong>(engineJNI);
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_engine_Pulse_nativeDelete(JNIEnv *env, jobject obj, jlong ptr)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  SAFE_DELETE(engineJNI);
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeReset(JNIEnv *env, jobject obj, jlong ptr)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr); 
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  engineJNI->Reset();
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseScenarioExec_nativeExecuteScenario(JNIEnv *env, jobject obj, jlong ptr, jstring scenario, jstring outputFile, double updateFreq_s)
{
  const char* sceStr = env->GetStringUTFChars(scenario, JNI_FALSE);
  const char* dataF = env->GetStringUTFChars(outputFile,JNI_FALSE);
  try
  {
    PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr); 
    engineJNI->updateFrequency_cnt = (int)(updateFreq_s /engineJNI->eng->GetTimeStep(TimeUnit::s));
    engineJNI->jniEnv = env;
    engineJNI->jniObj = obj;
    // Load up the pba and run the scenario
    PulseScenario sce(engineJNI->eng->GetSubstanceManager());
    if (!sce.Load(sceStr))
    {
      std::cerr << "The scenario string is bad " << std::endl;
    }
    else
    {
      engineJNI->exec = new PulseScenarioExec(*engineJNI->eng);
      engineJNI->exec->Execute(sce, dataF, updateFreq_s <= 0 ? nullptr : engineJNI);
    }
    SAFE_DELETE(engineJNI->exec);
  }
  catch (...)
  {
    std::cerr << "Unable to execute scenario " << std::endl;
  }
  env->ReleaseStringUTFChars(scenario, sceStr);
  env->ReleaseStringUTFChars(outputFile,dataF);
}

extern "C"
JNIEXPORT void JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseScenarioExec_nativeCancelScenario(JNIEnv *env, jobject obj, jlong ptr)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr); 
  //engineJNI->jniEnv = env; I am not doing this because the cancel comes in on another thread
  //engineJNI->jniObj = obj; and it has valid copies of the env and obj for its context
  if (engineJNI->exec != nullptr)
    engineJNI->exec->Cancel();// This will not do anything with JNI
}

extern "C"
JNIEXPORT jboolean JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeLoadState(JNIEnv *env, jobject obj, jlong ptr, jstring stateFilename, jdouble simTime_s, jstring dataRequests)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  

  // Load up the data requests
  if (dataRequests != nullptr)
  {
    const char* drmStr = env->GetStringUTFChars(dataRequests, JNI_FALSE);
    if (!engineJNI->eng->GetEngineTracker()->GetDataRequestManager().Load(drmStr, engineJNI->eng->GetSubstanceManager()))
    {
      env->ReleaseStringUTFChars(dataRequests, drmStr);
      std::cerr << "Unable to load datarequest string" << std::endl;
      return false;
    }
    env->ReleaseStringUTFChars(dataRequests, drmStr);
  }

  // Ok, crank 'er up!
  const char* pStateFilename = env->GetStringUTFChars(stateFilename, JNI_FALSE);
  jboolean bRet;
  SEScalarTime simTime;
  if (simTime_s >= 0)
  {
    simTime.SetValue(simTime_s, TimeUnit::s);
    bRet = engineJNI->eng->LoadStateFile(pStateFilename, &simTime);
  }
  else
  {
    std::cout << "Loading... " << std::endl;
    bRet = engineJNI->eng->LoadStateFile(pStateFilename);
  }  
  engineJNI->eng->SetEventHandler(engineJNI);

  env->ReleaseStringUTFChars(stateFilename, pStateFilename);
  return bRet;
}

extern "C"
JNIEXPORT jstring JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeSaveState(JNIEnv *env, jobject obj, jlong ptr, jstring stateFilename)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env; 
  engineJNI->jniObj = obj;
  const char* pStateFilename = env->GetStringUTFChars(stateFilename, JNI_FALSE);
  std::unique_ptr<google::protobuf::Message> data = engineJNI->eng->SaveState(pStateFilename);
  env->ReleaseStringUTFChars(stateFilename, pStateFilename);

  std::string content;
  google::protobuf::TextFormat::PrintToString(*data, &content);
  jstring state = env->NewStringUTF(content.c_str());
  return state;
}

extern "C"
JNIEXPORT jboolean JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeInitializeEngine(JNIEnv *env, jobject obj, jlong ptr, jstring patient, jstring conditions, jstring dataRequests)
{
  bool ret = false;
  
  
  const char* drStr = env->GetStringUTFChars(dataRequests, JNI_FALSE);
  try
  {
    PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
    engineJNI->jniEnv = env;
    engineJNI->jniObj = obj;

    // Load up the patient
    const char* pStr = env->GetStringUTFChars(patient, JNI_FALSE);
    SEPatient p(nullptr);
    if (!p.Load(pStr))
    {
      env->ReleaseStringUTFChars(patient, pStr);
      std::cerr << "Unable to load patient string" << std::endl;
      return false;
    }
    env->ReleaseStringUTFChars(patient, pStr);

    // Load up the conditions
    std::vector<const SECondition*> c;
    const char* cStr = nullptr;
    if (conditions != nullptr)
    {
      cStr = env->GetStringUTFChars(conditions, JNI_FALSE);
      cdm::ConditionListData cList;
      if (!google::protobuf::TextFormat::ParseFromString(cStr, &cList))
      {
        env->ReleaseStringUTFChars(conditions, cStr);
        return false;
      }
      env->ReleaseStringUTFChars(conditions, cStr);

      
      for (int i = 0; i < cList.anycondition_size(); i++)
      {
        c.push_back(SECondition::Load(cList.anycondition()[i], engineJNI->eng->GetSubstanceManager()));
      }
    }

    // Load up the data requests
    if (dataRequests != nullptr)
    {
      const char* drmStr = env->GetStringUTFChars(dataRequests, JNI_FALSE);
      if (!engineJNI->eng->GetEngineTracker()->GetDataRequestManager().Load(drmStr, engineJNI->eng->GetSubstanceManager()))
      {
        env->ReleaseStringUTFChars(dataRequests, drmStr);
        std::cerr << "Unable to load datarequest string" << std::endl;
        return false;
      }
      env->ReleaseStringUTFChars(dataRequests, drmStr);
    }

    // Ok, crank 'er up!
    ret = engineJNI->eng->InitializeEngine(p, &c);
    engineJNI->eng->SetEventHandler(engineJNI);
    DELETE_VECTOR(c);// Clean up the conditions, the engine makes copies of them
  }

  catch (std::exception& ex)
  {
    ret = false;
    std::cerr << "TODO Handle this Failure : " << ex.what() << std::endl;
  }
  
  return ret;
}

extern "C"
JNIEXPORT bool JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeAdvanceTimeStep(JNIEnv *env, jobject obj, jlong ptr)
{
  bool success = true;
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  try
  {
    engineJNI->eng->AdvanceModelTime();
  }
  catch (CommonDataModelException& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (std::exception& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (...)
  {
    success = false;
  }
  if (success)
  {
    double currentTime_s = engineJNI->eng->GetSimulationTime(TimeUnit::s);
    engineJNI->eng->GetEngineTracker()->TrackData(currentTime_s);
    engineJNI->PushData(currentTime_s);
  }
  return success;
}

extern "C"
JNIEXPORT bool JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeAdvanceTime(JNIEnv *env, jobject obj, jlong ptr, jdouble time_s)
{
  bool success = true;
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  try
  {
    engineJNI->eng->AdvanceModelTime(time_s, TimeUnit::s);
  }
  catch (CommonDataModelException& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (std::exception& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (...)
  {
    success = false;
  }
  if (success)
  {
    double currentTime_s = engineJNI->eng->GetSimulationTime(TimeUnit::s);
    engineJNI->eng->GetEngineTracker()->TrackData(currentTime_s);
    engineJNI->PushData(currentTime_s);
  }
  return success;
}

extern "C"
JNIEXPORT bool JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeProcessActions(JNIEnv *env, jobject obj, jlong ptr, jstring actions)
{
  bool success = true;
  if (actions == nullptr)
    return success;
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  const char* aStr = env->GetStringUTFChars(actions, JNI_FALSE);

  cdm::ActionListData aList;
  if (!google::protobuf::TextFormat::ParseFromString(aStr, &aList))
  {
    env->ReleaseStringUTFChars(actions, aStr);
    return false;
  }
  env->ReleaseStringUTFChars(actions, aStr);

  try
  {
    for (int i = 0; i < aList.anyaction_size(); i++)
    {
      SEAction* a = SEAction::Load(aList.anyaction()[i], engineJNI->eng->GetSubstanceManager());
      if (!engineJNI->eng->ProcessAction(*a))
        success = false;
      SAFE_DELETE(a);
    }
  }
  catch (CommonDataModelException& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (std::exception& ex)
  {
    success = false;
    engineJNI->GetLogger()->Error(ex.what());
  }
  catch (...)
  {
    success = false;
  }

  return success;
}

extern "C"
JNIEXPORT jstring JNICALL Java_mil_tatrc_physiology_pulse_engine_PulseEngine_nativeGetAssessment(JNIEnv *env, jobject obj, jlong ptr, jint type)
{
  PulseEngineJNI *engineJNI = reinterpret_cast<PulseEngineJNI*>(ptr);
  engineJNI->jniEnv = env;
  engineJNI->jniObj = obj;
  
  jstring assessment;

  std::string stream;
  switch (type)
  {
    case 0:// PFT
    {
      SEPulmonaryFunctionTest pft(engineJNI->eng->GetLogger());
      engineJNI->eng->GetPatientAssessment(pft);
      stream = pft.Save();
      break;
    }
    case 1: // CBC
    {
      SECompleteBloodCount cbc(engineJNI->eng->GetLogger());
      engineJNI->eng->GetPatientAssessment(cbc);
      stream = cbc.Save();
      break;
    }
    case 2: // CMP
    {
      SEComprehensiveMetabolicPanel cmp(engineJNI->eng->GetLogger());
      engineJNI->eng->GetPatientAssessment(cmp);
      stream = cmp.Save();
      break;
    }
    case 3: // U
    {
      SEUrinalysis u(engineJNI->eng->GetLogger());
      engineJNI->eng->GetPatientAssessment(u);
      stream = u.Save();
      break;
    }
    default:
      stream = "Unsupported assessment type";
  };

  assessment = env->NewStringUTF(stream.c_str());
  return assessment;
}

PulseEngineJNI::PulseEngineJNI(const std::string& logFile) : SEEventHandler(nullptr)
{// No logger needed for the event handler, at this point
  Reset(); 
  eng = std::unique_ptr<PulseEngine>((PulseEngine*)CreatePulseEngine(logFile).release());
  eng->GetLogger()->SetForward(this);
  eng->GetLogger()->LogToConsole(false);
  trk=&eng->GetEngineTracker()->GetDataTrack();
}

PulseEngineJNI::~PulseEngineJNI()
{
  Reset();
}

void PulseEngineJNI::Reset()
{
  exec = nullptr;
  firstUpdate = true;
  jniEnv=nullptr;
  jniObj=nullptr;
  jniDebugMethodID=nullptr;
  jniInfoMethodID=nullptr;
  jniWarnMethodID=nullptr;
  jniErrorMethodID=nullptr;
  jniFatalMethodID=nullptr;
  update_cnt = 0;
  updateFrequency_cnt = 45;// About every half second
}

void PulseEngineJNI::CustomExec(double time_s, PhysiologyEngine* engine)
{
  if (update_cnt++ > updateFrequency_cnt)
  {    
    PushData(time_s);
    update_cnt = 0;
  }
}
void PulseEngineJNI::PushData(double time_s)
{
  if (jniEnv != nullptr && jniObj != nullptr)
  {
    jmethodID m;
    std::vector<std::string>& headings = trk->GetHeadings();

    if (firstUpdate)
    {
      firstUpdate = false;
      jobjectArray sary = jniEnv->NewObjectArray(headings.size(), jniEnv->FindClass("java/lang/String"), jniEnv->NewStringUTF(""));
      for (unsigned int i = 0; i < headings.size(); i++)
        jniEnv->SetObjectArrayElement(sary, i, jniEnv->NewStringUTF(headings[i].c_str()));
      m = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "setCDMHeadings", "([Ljava/lang/String;)V");
      if (m == nullptr)
        std::cerr << "Can't find setCDMHeadings method in Java" << std::endl;
      jniEnv->CallVoidMethod(jniObj, m, sary);
    }

    // Gather up the requested data into an array and pass it over to java
    // The order is set in the header order
    jdoubleArray ary = jniEnv->NewDoubleArray(trk->GetProbes()->size());

    jboolean isCopy = JNI_FALSE;
    jdouble* reqData = jniEnv->GetDoubleArrayElements(ary, &isCopy);
    for (unsigned int i = 0; i < headings.size(); i++)
      reqData[i] = trk->GetProbe(headings[i]);
    if (isCopy == JNI_TRUE)
      jniEnv->ReleaseDoubleArrayElements(ary, reqData, JNI_COMMIT);

    m = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "updateCDM", "(D[D)V");
    if (m == nullptr)
      std::cerr << "Can't find updateCDM method in Java" << std::endl;
    jniEnv->CallVoidMethod(jniObj, m, time_s, ary);
  }
}

void PulseEngineJNI::ForwardDebug(const std::string&  msg, const std::string&  origin)
{
  if(jniEnv!=nullptr&&jniObj!=nullptr)
  {
    jstring m = jniEnv->NewStringUTF(msg.c_str());
    jstring o = jniEnv->NewStringUTF(origin.c_str());
    if(jniDebugMethodID==nullptr)
      jniDebugMethodID = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "LogDebug",   "(Ljava/lang/String;Ljava/lang/String;)V");
    jniEnv->CallVoidMethod(jniObj, jniDebugMethodID, m, o);
  }
}

void PulseEngineJNI::ForwardInfo(const std::string&  msg, const std::string&  origin)
{
  if(jniEnv!=nullptr&&jniObj!=nullptr)
  {
    jstring m = jniEnv->NewStringUTF(msg.c_str());
    jstring o = jniEnv->NewStringUTF(origin.c_str());
    if(jniInfoMethodID==nullptr)
      jniInfoMethodID  = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "LogInfo",    "(Ljava/lang/String;Ljava/lang/String;)V");  
    jniEnv->CallVoidMethod(jniObj, jniInfoMethodID, m, o);
  }
}

void PulseEngineJNI::ForwardWarning(const std::string&  msg, const std::string&  origin)
{
  if(jniEnv!=nullptr&&jniObj!=nullptr)
  {
    jstring m = jniEnv->NewStringUTF(msg.c_str());
    jstring o = jniEnv->NewStringUTF(origin.c_str());
    if(jniWarnMethodID==nullptr)
      jniWarnMethodID  = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "LogWarning", "(Ljava/lang/String;Ljava/lang/String;)V");  
    jniEnv->CallVoidMethod(jniObj, jniWarnMethodID, m, o);
  }
}

void PulseEngineJNI::ForwardError(const std::string&  msg, const std::string&  origin)
{
  if(jniEnv!=nullptr&&jniObj!=nullptr)
  {
    jstring m = jniEnv->NewStringUTF(msg.c_str());
    jstring o = jniEnv->NewStringUTF(origin.c_str());
    if(jniErrorMethodID==nullptr)
      jniErrorMethodID = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "LogError",   "(Ljava/lang/String;Ljava/lang/String;)V");
    jniEnv->CallVoidMethod(jniObj, jniErrorMethodID, m, o);
  }
}

void PulseEngineJNI::ForwardFatal(const std::string&  msg, const std::string&  origin)
{
  if(jniEnv!=nullptr&&jniObj!=nullptr)
  {
    jstring m = jniEnv->NewStringUTF(msg.c_str());
    jstring o = jniEnv->NewStringUTF(origin.c_str());
    if(jniFatalMethodID==nullptr)
      jniFatalMethodID = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "LogFatal",   "(Ljava/lang/String;Ljava/lang/String;)V");
    jniEnv->CallVoidMethod(jniObj, jniFatalMethodID, m, o);
  }
  std::string err;
  err.append(msg);
  err.append(" ");
  err.append(origin);
  throw PhysiologyEngineException(err);
}

void PulseEngineJNI::HandlePatientEvent(cdm::PatientData_eEvent type, bool active, const SEScalarTime* time)
{
  if (jniEnv != nullptr && jniObj != nullptr)
  {
    jmethodID m = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "handleEvent", "(IIZD)V");
    if (m == nullptr)
      std::cerr << "Can't find handleEvent method in Java" << std::endl;
    jniEnv->CallVoidMethod(jniObj, m, 0, type, active, time != nullptr ? time->GetValue(TimeUnit::s) : 0);
  }
}
void PulseEngineJNI::HandleAnesthesiaMachineEvent(cdm::AnesthesiaMachineData_eEvent type, bool active, const SEScalarTime* time)
{
  if (jniEnv != nullptr && jniObj != nullptr)
  {
    jmethodID m = jniEnv->GetMethodID(jniEnv->GetObjectClass(jniObj), "handleEvent", "(IIZD)V");
    if (m == nullptr)
      std::cerr << "Can't find handleEvent method in Java" << std::endl;
    jniEnv->CallVoidMethod(jniObj, m, 1, type, active, time != nullptr ? time->GetValue(TimeUnit::s) : 0);
  }
}
