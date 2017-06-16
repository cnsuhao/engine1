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

package mil.tatrc.physiology.datamodel.system.environment.conditions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.EnvironmentConditions.AnyEnvironmentConditionData;
import com.kitware.physiology.cdm.EnvironmentConditions.EnvironmentConditionData;
import com.kitware.physiology.cdm.Scenario.AnyConditionData;

import mil.tatrc.physiology.datamodel.conditions.SECondition;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public abstract class SEEnvironmentCondition extends SECondition
{
  public SEEnvironmentCondition()
  {
    
  }
  
  public void copy(SEEnvironmentCondition other)
  {
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(EnvironmentConditionData src, SEEnvironmentCondition dst) 
  {
    SECondition.load(src.getCondition(), dst);
  }
  protected static void unload(SEEnvironmentCondition src, EnvironmentConditionData.Builder dst)
  {
    SECondition.unload(src, dst.getConditionBuilder());
  }
  
  public abstract String toString();

  public static SEEnvironmentCondition ANY2CDM(AnyEnvironmentConditionData c, SESubstanceManager subMgr) 
  {
    switch(c.getConditionCase())
    {
    case INITIALENVIRONMENTCONFIGURATION:
      SEInitialEnvironmentConfiguration newC = new SEInitialEnvironmentConfiguration();
      SEInitialEnvironmentConfiguration.load(c.getInitialEnvironmentConfiguration(), newC, subMgr);
      return newC;
    case CONDITION_NOT_SET:
      Log.warn("AnyEnvironmentConditionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported Environment condition type "+c.getConditionCase());
    return null;
  }
  public static AnyEnvironmentConditionData CDM2ANY(SEEnvironmentCondition c)
  {
    AnyEnvironmentConditionData.Builder dst = AnyEnvironmentConditionData.newBuilder();
    if(c instanceof SEInitialEnvironmentConfiguration)
    {
      dst.setInitialEnvironmentConfiguration(SEInitialEnvironmentConfiguration.unload((SEInitialEnvironmentConfiguration)c));    
      return dst.build();
    }
    Log.error("Unsupported Environment condition type "+c);
    return dst.build();
  }
}
