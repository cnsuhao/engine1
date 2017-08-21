/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#include <mutex>
#include <thread>

#include "CommonDataModel.h"
#include "PulsePhysiologyEngine.h"
// This class will run Pulse in it's own thread and accept changes to hemorrage and iv flow as the engine is running

// Forward declare what we will use in our thread
class SEHemorrhage;
class SESubstanceCompoundInfusion;
class PhysiologyEngine;


class PulseThread
{
public:
  PulseThread(const std::string& logfile);
  virtual ~PulseThread();

  void SetHemorrhageFlow_mL_Per_min(double rate);
  void SetIVFluidsFlow_mL_Per_min(double rate);

  void Status();

  Logger* GetLogger() { return m_pe->GetLogger(); }

protected:
  void AdvanceTime();

  std::thread m_thread;
  std::mutex  m_mutex;
  bool m_runThread;

  std::unique_ptr<PhysiologyEngine> m_pe;

  SEHemorrhage*                     m_hemorrhage;
  SESubstanceCompoundInfusion*      m_infusion;
};