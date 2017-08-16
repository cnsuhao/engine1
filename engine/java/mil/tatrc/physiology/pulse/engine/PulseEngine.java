/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.pulse.engine;

import java.util.ArrayList;
import java.util.List;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.PatientAssessments.CompleteBloodCountData;
import com.kitware.physiology.cdm.PatientAssessments.ComprehensiveMetabolicPanelData;
import com.kitware.physiology.cdm.PatientAssessments.PatientAssessmentData;
import com.kitware.physiology.cdm.PatientAssessments.PulmonaryFunctionTestData;
import com.kitware.physiology.cdm.PatientAssessments.UrinalysisData;
import com.kitware.physiology.cdm.Scenario.ActionListData;
import com.kitware.physiology.cdm.Scenario.ConditionListData;
import com.kitware.physiology.pulse.EngineState.StateData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.conditions.SECondition;
import mil.tatrc.physiology.datamodel.datarequests.SEDataRequestManager;
import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.datamodel.patient.assessments.SECompleteBloodCount;
import mil.tatrc.physiology.datamodel.patient.assessments.SEComprehensiveMetabolicPanel;
import mil.tatrc.physiology.datamodel.patient.assessments.SEPatientAssessment;
import mil.tatrc.physiology.datamodel.patient.assessments.SEPulmonaryFunctionTest;
import mil.tatrc.physiology.datamodel.patient.assessments.SEUrinalysis;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.TimeUnit;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;

public class PulseEngine extends Pulse
{
  protected boolean deadEngine = false;
  
  public PulseEngine()
  {
    super();
  }
  
  public synchronized void reset()
  {
    super.reset();
    if(this.nativeObj!=0)
      this.nativeReset(this.nativeObj);
    this.deadEngine = false;
  }
  
  public synchronized boolean isDead()
  {
    return deadEngine;
  }

  // TODO Set a callback for patient events
  
  public synchronized boolean loadState(String logFile, String stateFile, SEDataRequestManager dataRequests)
  {    
    return loadStateContents(logFile, stateFile, -1.0, dataRequests);
  }  
  public synchronized boolean loadState(String logFile, String stateFile, SEScalarTime simTime, SEDataRequestManager dataRequests)
  {        
    return loadStateContents(logFile, stateFile, simTime.getValue(TimeUnit.s), dataRequests);
  }  
  protected synchronized boolean loadStateContents(String logFile, String stateFile, double simTime_s, SEDataRequestManager dataRequests)
  {
    this.reset();
    String dataRequestsStr = null;
    if(dataRequests !=null && !dataRequests.getRequestedData().isEmpty())
    	dataRequestsStr = SEDataRequestManager.unload(dataRequests).toString();
    if(dataRequestsStr == null)
    {
      Log.error("Invalid/No data requests provided");
      return false;
    }
    this.requestData(dataRequests);
    this.nativeObj = nativeAllocate(logFile);
    return nativeLoadState(this.nativeObj, stateFile, simTime_s, dataRequestsStr);
  }
  
  public synchronized StateData saveState(String stateFile) throws ParseException
  {
    String str = nativeSaveState(this.nativeObj, stateFile);
    StateData.Builder sd = StateData.newBuilder();
    TextFormat.getParser().merge(str, sd);
    return sd.build();
  }

  public synchronized boolean initializeEngine(String logFile, SEPatient patient, List<SECondition> conditions, SEDataRequestManager dataRequests)
  {    
    this.reset();
    String patientStr = SEPatient.unload(patient).toString();
    if(patientStr == null || patientStr.isEmpty())
    {
      Log.error("Invalid/No patient provided");
      return false;
    }
    String conditionsStr = null;
    if(conditions !=null && !conditions.isEmpty())
    {
      ConditionListData.Builder cData = ConditionListData.newBuilder();
      for(SECondition c : conditions)
      	cData.addAnyCondition(SECondition.CDM2ANY(c));
      conditionsStr = cData.toString();
    }
    String dataRequestsStr = null;
    if(dataRequests !=null && !dataRequests.getRequestedData().isEmpty())
    	dataRequestsStr = SEDataRequestManager.unload(dataRequests).toString();
    if(dataRequestsStr == null)
    {
      Log.error("Invalid/No data requests provided");
      return false;
    }
    this.requestData(dataRequests);
    this.nativeObj = nativeAllocate(logFile);
    this.deadEngine = !nativeInitializeEngine(this.nativeObj, patientStr, conditionsStr, dataRequestsStr);
    if(this.deadEngine)
      Log.error("Unable to initialize engine");
    return !this.deadEngine;
  }
  
  public synchronized boolean initializeEngine(String logFile, String patientFile, List<SECondition> conditions, SEDataRequestManager dataRequests)
  {    
    this.reset();
    String patientStr = FileUtils.readFile(patientFile);
    if(patientStr == null || patientStr.isEmpty())
    {
      Log.error("Invalid/No patient provided");
      return false;
    }
    String conditionsStr = null;
    if(conditions !=null && !conditions.isEmpty())
    {
      ConditionListData.Builder cData = ConditionListData.newBuilder();
      for(SECondition c : conditions)
      	cData.addAnyCondition(SECondition.CDM2ANY(c));
      conditionsStr = cData.toString();
    }
    String dataRequestsStr = null;
    if(dataRequests !=null && !dataRequests.getRequestedData().isEmpty())
    	dataRequestsStr = SEDataRequestManager.unload(dataRequests).toString();
    if(dataRequestsStr == null)
    {
      Log.error("Invalid/No data requests provided");
      return false;
    }
    this.requestData(dataRequests);
    this.nativeObj = nativeAllocate(logFile);
    this.deadEngine = !nativeInitializeEngine(this.nativeObj, patientStr, conditionsStr, dataRequestsStr);
    if(this.deadEngine)
      Log.error("Unable to initialize engine");
    return !this.deadEngine;
  }
  
  public synchronized boolean advanceTime()
  {
    if(this.deadEngine)
    {
      Log.error("Engine has died");
      return false;
    }
    if(!nativeAdvanceTimeStep(this.nativeObj))
      deadEngine=true;
    return !deadEngine;
  }
  
  public synchronized boolean advanceTime(SEScalarTime time)
  {
    if(this.deadEngine)
    {
      Log.error("Engine has died");
      return false;
    }
    if(!nativeAdvanceTime(this.nativeObj, time.getValue(TimeUnit.s)))
      deadEngine=true;
    return !deadEngine;
  }
  
  public synchronized boolean processAction(SEAction action)
  {
    List <SEAction> actions = new ArrayList<SEAction>(); 
    actions.add(action);
    return processActions(actions);
  }
  
  public synchronized boolean processActions(List<SEAction> actions)
  {
    if(this.deadEngine)
    {
      Log.error("Engine has died");
      return false;
    }
    if(actions !=null && !actions.isEmpty())
    {
      ActionListData.Builder aData = ActionListData.newBuilder();
      for(SEAction a : actions)
      	aData.addAnyAction(SEAction.CDM2ANY(a));
      String actionsStr = aData.toString();
      if(!nativeProcessActions(this.nativeObj,actionsStr))
        deadEngine=true;
      return !deadEngine;
    }
    return true;
  }
  
  public synchronized boolean getPatientAssessment(SEPatientAssessment assessment) throws ParseException
  {
    if(this.deadEngine)
    {
      Log.error("Engine has died");
      return false;
    }
    if(assessment instanceof SEPulmonaryFunctionTest)
    {
    	PulmonaryFunctionTestData.Builder b = PulmonaryFunctionTestData.newBuilder();
      String str = nativeGetAssessment(this.nativeObj, PatientAssessmentData.eType.PulmonaryFunctionTest.ordinal());
      TextFormat.getParser().merge(str, b);
      SEPulmonaryFunctionTest.load(b.build(),((SEPulmonaryFunctionTest)assessment));
      return true;
    }
    
    if(assessment instanceof SECompleteBloodCount)
    {
    	CompleteBloodCountData.Builder b = CompleteBloodCountData.newBuilder();
      String str = nativeGetAssessment(this.nativeObj, PatientAssessmentData.eType.CompleteBloodCount.ordinal());
      TextFormat.getParser().merge(str, b);
      SECompleteBloodCount.load(b.build(),((SECompleteBloodCount)assessment));
      return true;
    }
    
    if(assessment instanceof SEComprehensiveMetabolicPanel)
    {
    	ComprehensiveMetabolicPanelData.Builder b = ComprehensiveMetabolicPanelData.newBuilder();
      String str = nativeGetAssessment(this.nativeObj, PatientAssessmentData.eType.ComprehensiveMetabolicPanel.ordinal());
      TextFormat.getParser().merge(str, b);
      SEComprehensiveMetabolicPanel.load(b.build(),((SEComprehensiveMetabolicPanel)assessment));
      return true;
    }
    
    if(assessment instanceof SEUrinalysis)
    {
    	UrinalysisData.Builder b = UrinalysisData.newBuilder();
      String str = nativeGetAssessment(this.nativeObj, PatientAssessmentData.eType.Urinalysis.ordinal());
      TextFormat.getParser().merge(str, b);
      SEUrinalysis.load(b.build(),((SEUrinalysis)assessment));
      return true;
    }
    
    return false;
  }
  
  /**
   * Used for C++ communication for calculation outside of the java language
   * @return - success flag from calculate
   */
  protected native void nativeReset(long nativeObj);
  
  protected native boolean nativeInitializeEngine(long nativeObj, String patient, String conditions, String dataRequests);
  protected native boolean nativeLoadState(long nativeObj, String stateFile, double simTime_s, String dataRequests);// pass <0 as simTime to use the time in the file
  protected native String  nativeSaveState(long nativeObj, String stateFile);
  protected native boolean nativeAdvanceTimeStep(long nativeObj);
  protected native boolean nativeAdvanceTime(long nativeObj, double time_s);
  protected native boolean nativeProcessActions(long nativeObj, String actions);
  protected native String nativeGetAssessment(long nativeObj, int type);
}
