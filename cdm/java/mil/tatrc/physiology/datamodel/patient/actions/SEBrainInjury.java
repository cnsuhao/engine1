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

import com.kitware.physiology.cdm.PatientActions.BrainInjuryData;
import com.kitware.physiology.cdm.PatientActions.BrainInjuryData.eType;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEBrainInjury extends SEPatientAction
{
  protected SEScalar0To1        severity;
  protected eType type;
  
  public SEBrainInjury()
  {
    severity = null;
    type     = null;
  }
  
  public void reset()
  {
    super.reset();
    if (severity != null)
      severity.invalidate();
    this.type = null;
  }
  
  public void copy(SEBrainInjury other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.severity != null)
      getSeverity().set(other.getSeverity());
    else if (severity != null)
      severity.invalidate();
    this.type = other.type;
  }
  
  public boolean isValid()
  {
    return hasSeverity() && hasType();
  }
  
  public static void load(BrainInjuryData src, SEBrainInjury dst) 
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getType()!=eType.UNRECOGNIZED)
    	dst.setType(src.getType());
    if(src.hasSeverity())
      SEScalar0To1.load(src.getSeverity(),dst.getSeverity());
  }
  
  public static  BrainInjuryData unload(SEBrainInjury src)
  {
    BrainInjuryData.Builder dst = BrainInjuryData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEBrainInjury src, BrainInjuryData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if(src.hasType())
      dst.setType(src.type);
    if (src.hasSeverity())
      dst.setSeverity(SEScalar0To1.unload(src.severity));
  }
  
  public eType getType()
  {
    return type;
  }
  public void setType(eType t)
  {
    type = t;
  }
  public boolean hasType()
  {
    return type == null ? false : true;
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
      return "Brain Injury" 
          + "\n\tType: " + getType()
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
