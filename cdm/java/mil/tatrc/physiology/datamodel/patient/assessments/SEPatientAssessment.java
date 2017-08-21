/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.assessments;

import org.jfree.util.Log;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.PatientAssessments.PatientAssessmentData;
import com.kitware.physiology.cdm.PatientAssessments.PulmonaryFunctionTestData;

import mil.tatrc.physiology.utilities.FileUtils;

public abstract class SEPatientAssessment
{
  public SEPatientAssessment()
  {
    
  }
  
  public void clear()
  {
    
  }
  
  public void reset()
  {
    
  }
  
  public static void load(PatientAssessmentData src, SEPatientAssessment dst) 
  {
    dst.reset();
  }
  protected static void unload(SEPatientAssessment src, PatientAssessmentData.Builder dst)
  {

  }
  
  public static SEPatientAssessment readAssessment(String fileName) throws ParseException
  {
    try
    {
      SECompleteBloodCount cbc = new SECompleteBloodCount();
      cbc.readFile(fileName);
      return cbc;
    }
    catch(ParseException ex){}
    
    try
    {
      SEComprehensiveMetabolicPanel cmp = new SEComprehensiveMetabolicPanel();
      cmp.readFile(fileName);
      return cmp;
    }
    catch(ParseException ex){}
    
    try
    {
      SEPulmonaryFunctionTest pft = new SEPulmonaryFunctionTest();
      pft.readFile(fileName);
      return pft;
    }
    catch(ParseException ex){}
    
    SEUrinalysis u = new SEUrinalysis();
    u.readFile(fileName);
    return u;
  }
  public static boolean writeAssement(String fileName, SEPatientAssessment ass)
  {
    if(ass instanceof SECompleteBloodCount)
      return FileUtils.writeFile(fileName, SECompleteBloodCount.unload((SECompleteBloodCount)ass).toString());
    if(ass instanceof SEComprehensiveMetabolicPanel)
      return FileUtils.writeFile(fileName, SEComprehensiveMetabolicPanel.unload((SEComprehensiveMetabolicPanel)ass).toString());
    if(ass instanceof SEPulmonaryFunctionTest)
      return FileUtils.writeFile(fileName, SEPulmonaryFunctionTest.unload((SEPulmonaryFunctionTest)ass).toString());
    if(ass instanceof SEUrinalysis)
      return FileUtils.writeFile(fileName, SEUrinalysis.unload((SEUrinalysis)ass).toString());
    Log.error("No write support for assesment of class "+ass.getClass().getName());
    return false;
  }
}
