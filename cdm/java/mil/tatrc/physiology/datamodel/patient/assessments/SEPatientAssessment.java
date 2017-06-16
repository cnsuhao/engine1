/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

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
