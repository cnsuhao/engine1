/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.pulse.engine;

import mil.tatrc.physiology.datamodel.scenario.SEScenario;
import mil.tatrc.physiology.datamodel.utilities.SEEventHandler;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.LogListener;

/**
 * This is a class that will run a scenario through Pulse
 * and create it's results file. You could easily write your
 * own exec class that does what you want in between actions
 * but this may work for most of your needs.
 * @author abray
 */
public class PulseScenarioExec extends Pulse
{
  public void runScenario(String logFile, SEScenario scenario, String resultsFile, CDMUpdatedCallback callback)
  {    
    if(callback != null)
      callback.drMgr = scenario.getDataRequestManager();    
    runScenario(logFile,SEScenario.unload(scenario).toString(),resultsFile,callback);
  }
  
  public void runScenario(String logFile, String scenario, String resultsFile)
  {
    runScenario(logFile, scenario, resultsFile, null);
  }
  
  protected void runScenario(String logFile, String scenario, String resultsFile, CDMUpdatedCallback callback)
  {    
    double callbackFreq_s = 0;
    if(callback!=null)
    { 
      LogListener l = this.listener;
      SEEventHandler eh = this.eventHandler;
      reset();// Only create our CDM objects if we have a callback to fill data out (also save off listener and event handler)
      this.listener = l;
      this.eventHandler = eh;
      this.cdmCallback = callback;
      callbackFreq_s = callback.callbackFrequency_s;
      this.requestData(callback.drMgr);
    }
    this.nativeObj = nativeAllocate(logFile);
    nativeExecuteScenario(this.nativeObj, scenario, resultsFile, callbackFreq_s);
    nativeDelete(this.nativeObj);
    this.nativeObj=0;
    this.cdmCallback = null;
  }
  
  public void cancelScenario()
  {
    if(this.nativeObj!=0)
      nativeCancelScenario(this.nativeObj);
    Log.info("Cancelling execution");
  }
  
  protected native void nativeExecuteScenario(long nativeObj, String scenario, String resultsFile, double updateFreq_s);
  protected native void nativeCancelScenario(long nativeObj);
  
}
