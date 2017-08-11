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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.PatientAssessmentRequestData;
import com.kitware.physiology.cdm.PatientAssessments.PatientAssessmentData.eType;

public class SEPatientAssessmentRequest extends SEPatientAction
{
  protected eType type;
  
  public SEPatientAssessmentRequest()
  {
    type = null;
  }
  
  public void copy(SEPatientAssessmentRequest other)
  {
    if(this==other)
      return;
    super.copy(other);
    type = other.type;
  }
  
  public void reset()
  {
    super.reset();
    type = null;
  }
  
  public boolean isValid()
  {
    return hasType();
  }
  
  public static void load(PatientAssessmentRequestData src, SEPatientAssessmentRequest dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getType()!=eType.UNRECOGNIZED)
    	dst.type = src.getType();
  }
  
  public static PatientAssessmentRequestData unload(SEPatientAssessmentRequest src)
  {
    PatientAssessmentRequestData.Builder dst = PatientAssessmentRequestData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEPatientAssessmentRequest src, PatientAssessmentRequestData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasType())
      dst.setType(src.type);
  }
  
  public eType getType()
  {
    return type;
  }
  public void setType(eType type)
  {
    this.type = type;
  }
  public boolean hasType()
  {
    return type == null ? false : true;
  }
  
  public String toString() 
  {
    if (type != null)
      return "Patient Type"
          + "\n\tType: " + getType();
    else
      return "Type not specified properly";
  }
}
