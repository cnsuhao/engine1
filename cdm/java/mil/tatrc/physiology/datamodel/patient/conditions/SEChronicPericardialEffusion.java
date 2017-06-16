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

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ChronicPericardialEffusionData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SEChronicPericardialEffusion extends SEPatientCondition
{
  protected SEScalarVolume accumulatedVolume;
  
  public SEChronicPericardialEffusion()
  {
    accumulatedVolume = null;
  }
  
  public void reset()
  {
    super.reset();
    if (accumulatedVolume != null)
      accumulatedVolume.invalidate();
  }
  
  public void copy(SEChronicPericardialEffusion other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.accumulatedVolume != null)
      getAccumulatedVolume().set(other.getAccumulatedVolume());
    else if (accumulatedVolume != null)
      accumulatedVolume.invalidate();
  }
  
  public static void load(ChronicPericardialEffusionData src, SEChronicPericardialEffusion dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasAccumulatedVolume())
      SEScalarVolume.load(src.getAccumulatedVolume(),dst.getAccumulatedVolume());
  }
  
  public static ChronicPericardialEffusionData unload(SEChronicPericardialEffusion src) 
  {
    ChronicPericardialEffusionData.Builder dst = ChronicPericardialEffusionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicPericardialEffusion src, ChronicPericardialEffusionData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasAccumulatedVolume())
      dst.setAccumulatedVolume(SEScalarVolume.unload(src.accumulatedVolume));
  }
  
  public boolean hasAccumulatedVolume()
  {
    return accumulatedVolume == null ? false : accumulatedVolume.isValid();
  }
  public SEScalarVolume getAccumulatedVolume()
  {
    if (accumulatedVolume == null)
      accumulatedVolume = new SEScalarVolume();
    return accumulatedVolume;
  }
  
  public String toString()
  {
    return "Pericardial Effusion" 
        + "\n\tAccumulated Volume: " + getAccumulatedVolume();
  }

  
}
