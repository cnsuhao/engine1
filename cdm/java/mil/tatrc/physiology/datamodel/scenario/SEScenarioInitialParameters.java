/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.scenario;

import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.Scenario.AnyConditionData;
import com.kitware.physiology.cdm.Scenario.ScenarioData;

import mil.tatrc.physiology.datamodel.conditions.SECondition;
import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public class SEScenarioInitialParameters 
{
  protected SEPatient                     patient;
  protected String                        patientFile;
  protected List<SECondition>             conditions;
  
  public SEScenarioInitialParameters()
  {
    this.patient = null;
    this.patientFile = "";
    this.conditions = new ArrayList<SECondition>();
  }
  
  public void reset() 
  {
    patient=null;
    patientFile = "";
    conditions.clear();
  }
  
  public static void load(ScenarioData.InitialParametersData src, SEScenarioInitialParameters dst, SESubstanceManager subMgr)
  {
    dst.reset();
    
    switch(src.getPatientTypeCase())
    {
    case PATIENT:
    {
      SEPatient p = new SEPatient();
      SEPatient.load(src.getPatient(),p);
      dst.setPatient(p);
      break;
    }
    case PATIENTFILE:
      dst.setPatientFile(src.getPatientFile());
    }
    
    for(AnyConditionData cData : src.getAnyConditionList())
      dst.conditions.add(SECondition.ANY2CDM(cData, subMgr));
  }
  
  public static ScenarioData.InitialParametersData unload(SEScenarioInitialParameters src)
  {
    ScenarioData.InitialParametersData.Builder dst = ScenarioData.InitialParametersData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScenarioInitialParameters src, ScenarioData.InitialParametersData.Builder dst)
  {
    if(src.hasPatient())
      dst.setPatient(SEPatient.unload(src.patient));
    if(src.hasPatientFile())
      dst.setPatientFile(src.patientFile);
    for(SECondition c : src.conditions)
      dst.addAnyCondition(SECondition.CDM2ANY(c));    
  }
  
  public boolean isValid()
  {
    if (!hasPatientFile()&&!hasPatient())
      return false;
   return true;
  }
  
  public SEPatient getPatient()
  {
    return patient;
  }
  public void setPatient(SEPatient patient)
  {
    this.patient = patient;
    this.patientFile = "";
  }
  public boolean hasPatient()
  {
    return patient==null ? false : true;
  }
  public void invalidatePatient()
  {
    patient = null;
  }

  public String getPatientFile()
  {
    return patientFile;
  }
  public void setPatientFile(String patientFile)
  {
    this.patient = null;
    this.patientFile = patientFile;
  }
  public boolean hasPatientFile()
  {
    return patientFile.isEmpty() ? false : true;
  }
  public void invalidatePatientFile()
  {
    patientFile = "";
  }
  
  public List<SECondition> getConditions() 
  {
    return conditions;
  }
}
