/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
ActionS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

package mil.tatrc.physiology.datamodel.system.environment.actions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.EnvironmentActions.EnvironmentActionData;
import com.kitware.physiology.cdm.EnvironmentActions.AnyEnvironmentActionData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public abstract class SEEnvironmentAction extends SEAction
{
  public SEEnvironmentAction()
  {
    
  }
  
  public void copy(SEEnvironmentAction other)
  {
    if (this == other)
      return;
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(EnvironmentActionData src, SEEnvironmentAction dst) 
  {
    SEAction.load(src.getAction(), dst);
  }
  protected static void unload(SEEnvironmentAction src, EnvironmentActionData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
  }
  
  public static SEEnvironmentAction ANY2CDM(AnyEnvironmentActionData c, SESubstanceManager subMgr) 
  {
    switch(c.getActionCase())
    {
    case CONFIGURATION:
    {
      SEEnvironmentConfiguration dst = new SEEnvironmentConfiguration();
      SEEnvironmentConfiguration.load(c.getConfiguration(), dst, subMgr);
      return dst;
    }
    case THERMALAPPLICATION:
    {
      SEThermalApplication dst = new SEThermalApplication();
      SEThermalApplication.load(c.getThermalApplication(), dst);
      return dst;
    }
    case ACTION_NOT_SET:
      Log.warn("AnyEnvironmentActionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported Environment Action type "+c.getActionCase());
    return null;
  }
  public static AnyEnvironmentActionData CDM2ANY(SEEnvironmentAction c)
  {
    AnyEnvironmentActionData.Builder dst = AnyEnvironmentActionData.newBuilder();
    
    if(c instanceof SEEnvironmentConfiguration)
    {
      dst.setConfiguration(SEEnvironmentConfiguration.unload((SEEnvironmentConfiguration)c));
      return dst.build();
    }
    if(c instanceof SEThermalApplication)
    {
      dst.setThermalApplication(SEThermalApplication.unload((SEThermalApplication)c));
      return dst.build();
    }
    Log.error("Unsupported Environment Action type "+c);
    return dst.build();
  }
  
  public abstract String toString();
}
