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

package mil.tatrc.physiology.datamodel.conditions;

import java.io.Serializable;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.Actions.ActionData;
import com.kitware.physiology.cdm.Conditions.ConditionData;
import com.kitware.physiology.cdm.EnvironmentConditions.AnyEnvironmentConditionData;
import com.kitware.physiology.cdm.Scenario.AnyConditionData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.patient.conditions.SEPatientCondition;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceCompound;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.conditions.SEEnvironmentCondition;
import mil.tatrc.physiology.datamodel.system.environment.conditions.SEInitialEnvironmentConfiguration;
import mil.tatrc.physiology.utilities.Log;

public abstract class SECondition implements Serializable
{
  protected String comment;
  
  public SECondition() 
  {
    comment = null;
  }
  
  public void copy(SECondition other) 
  {
    reset();
    comment = other.comment;
  }
  
  public void reset() 
  {
    this.comment = null;
  }
  
  public static void load(ConditionData src, SECondition dst) 
  {
    dst.reset();
    if(!src.getComment().isEmpty())
      dst.setComment(src.getComment());
  }
  protected static void unload(SECondition src, ConditionData.Builder dst)
  {
    if (src.hasComment())
      dst.setComment(src.comment);
  }
  
  public boolean hasComment()
  {
    return this.comment != null && !this.comment.isEmpty();
  }  
  public String getComment()
  {
    return this.comment;
  }
  public void setComment(String comment)
  {
    this.comment = comment;
  }
  public void invalidateComment()
  {
    this.comment = null;
  }
  
  public static SECondition ANY2CDM(AnyConditionData any, SESubstanceManager subMgr)
  {
    switch(any.getConditionCase())
    {
      case PATIENTCONDITION:
        return SEPatientCondition.ANY2CDM(any.getPatientCondition(), subMgr);
      case ENVIRONMENTCONDITION:
        return SEEnvironmentCondition.ANY2CDM(any.getEnvironmentCondition(), subMgr);
      case CONDITION_NOT_SET:
        Log.warn("AnyConditionData is empty...was that intended?");
        return null;
      default:
        Log.error("Unsupported AnyConditionData Type "+any.getConditionCase());
    }
    return null;
  }
  
  public static AnyConditionData CDM2ANY(SECondition c)
  {
    AnyConditionData.Builder dst = AnyConditionData.newBuilder();
    if(c instanceof SEEnvironmentCondition)
    {
      dst.setEnvironmentCondition(SEEnvironmentCondition.CDM2ANY((SEEnvironmentCondition)c));
      return dst.build();
    }
    if(c instanceof SEPatientCondition)
    {
      dst.setPatientCondition(SEPatientCondition.CDM2ANY((SEPatientCondition)c));
      return dst.build();
    }
    Log.error("Unsupported AnyConditionData Type "+c.toString());
    return dst.build();
  }

  public abstract String toString();
}
