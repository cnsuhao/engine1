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

import com.kitware.physiology.cdm.PatientActions.PericardialEffusionData;

import mil.tatrc.physiology.datamodel.properties.SEScalarVolumePerTime;

public class SEPericardialEffusion extends SEPatientAction
{
  protected SEScalarVolumePerTime effusionRate;
  
  public SEPericardialEffusion()
  {
    effusionRate=null;
  }
  
  public void copy(SEPericardialEffusion other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.effusionRate != null)
      getEffusionRate().set(other.getEffusionRate());
    else if (effusionRate != null)
      effusionRate.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (effusionRate != null)
      effusionRate.invalidate();
  }
  
  public boolean isValid()
  {
    return hasEffusionRate();
  }
  
  public static void load(PericardialEffusionData src, SEPericardialEffusion dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasEffusionRate())
      SEScalarVolumePerTime.load(src.getEffusionRate(),dst.getEffusionRate());
  }
  
  public static PericardialEffusionData unload(SEPericardialEffusion src) 
  {
    PericardialEffusionData.Builder dst = PericardialEffusionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEPericardialEffusion src, PericardialEffusionData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasEffusionRate())
      dst.setEffusionRate(SEScalarVolumePerTime.unload(src.effusionRate));
  }
  
  public boolean hasEffusionRate()
  {
    return effusionRate == null ? false : effusionRate.isValid();
  }
  public SEScalarVolumePerTime getEffusionRate()
  {
    if (effusionRate == null)
      effusionRate = new SEScalarVolumePerTime();
    return effusionRate;
  }
  
  public String toString() 
  {
    if (effusionRate != null)
      return "Pericardial Effusion" 
          + "\n\tEffusion Rate: " + getEffusionRate(); 
    else
      return "Action not properly specified";
  }
}
