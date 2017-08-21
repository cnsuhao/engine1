/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
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
    case CONDITIONS:
    {
      SEChangeEnvironmentConditions dst = new SEChangeEnvironmentConditions();
      SEChangeEnvironmentConditions.load(c.getConditions(), dst, subMgr);
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
    
    if(c instanceof SEChangeEnvironmentConditions)
    {
      dst.setConditions(SEChangeEnvironmentConditions.unload((SEChangeEnvironmentConditions)c));
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
