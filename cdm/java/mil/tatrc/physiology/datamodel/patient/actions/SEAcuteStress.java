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

import com.kitware.physiology.cdm.PatientActions.AcuteStressData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEAcuteStress extends SEPatientAction
{
  protected SEScalar0To1 severity;
  
  public SEAcuteStress()
  {
    severity = null;
  }
  
  public void reset()
  {
    super.reset();
    if (severity != null)
      severity.invalidate();
  }
  
  public void copy(SEAcuteStress other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.severity != null)
      getSeverity().set(other.getSeverity());
    else if (severity != null)
      severity.invalidate();
  }
  
  public boolean isValid()
  {
    return hasSeverity();
  }
  
  public static void load(AcuteStressData src, SEAcuteStress dst) 
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasSeverity())
      SEScalar0To1.load(src.getSeverity(),dst.getSeverity());
  }
  
  public static AcuteStressData unload(SEAcuteStress src)
  {
    AcuteStressData.Builder dst = AcuteStressData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEAcuteStress src, AcuteStressData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasSeverity())
      dst.setSeverity(SEScalar0To1.unload(src.severity));
  }
  
  public boolean hasSeverity()
  {
    return severity == null ? false : severity.isValid();
  }
  public SEScalar0To1 getSeverity()
  {
    if (severity == null)
      severity = new SEScalar0To1();
    return severity;
  }

  public String toString()
  {
    if (severity != null)
      return "Acute Stress" 
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
