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

import com.kitware.physiology.cdm.PatientConditions.ChronicAnemiaData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEChronicAnemia extends SEPatientCondition
{
  protected SEScalar0To1 reductionFactor;
  
  public SEChronicAnemia()
  {
    reductionFactor = null;
  }
  
  public void reset()
  {
    super.reset();
    if (reductionFactor != null)
      reductionFactor.invalidate();
  }
  
  public void copy(SEChronicAnemia other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.reductionFactor != null)
      getReductionFactor().set(other.getReductionFactor());
    else if (reductionFactor != null)
      reductionFactor.invalidate();
  }
  
  public static void load(ChronicAnemiaData src, SEChronicAnemia dst) 
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasReductionFactor())
      SEScalar0To1.load(src.getReductionFactor(),dst.getReductionFactor());
  }
  
  public static ChronicAnemiaData unload(SEChronicAnemia src) 
  {
    ChronicAnemiaData.Builder dst = ChronicAnemiaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChronicAnemia src, ChronicAnemiaData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasReductionFactor())
      dst.setReductionFactor(SEScalar0To1.unload(src.reductionFactor));
  }
  
  public boolean hasReductionFactor()
  {
    return reductionFactor == null ? false : reductionFactor.isValid();
  }
  public SEScalar0To1 getReductionFactor()
  {
    if (reductionFactor == null)
      reductionFactor = new SEScalar0To1();
    return reductionFactor;
  }
  
  public String toString()
  {
    return "Chronic Anemia" 
        + "\n\tReduction Factor: " + getReductionFactor();
  }

  
}
