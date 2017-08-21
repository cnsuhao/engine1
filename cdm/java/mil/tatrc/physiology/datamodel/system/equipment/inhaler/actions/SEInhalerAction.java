/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.inhaler.actions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.InhalerActions.AnyInhalerActionData;
import com.kitware.physiology.cdm.InhalerActions.InhalerActionData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public abstract class SEInhalerAction extends SEAction
{
  public SEInhalerAction()
  {
    
  }
  
  public void copy(SEInhalerAction other)
  {
    if (this == other)
      return;
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(InhalerActionData src, SEInhalerAction dst) 
  {
    SEAction.load(src.getAction(), dst);
  }
  protected static void unload(SEInhalerAction src, InhalerActionData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
  }
  
  public static SEInhalerAction ANY2CDM(AnyInhalerActionData c, SESubstanceManager subMgr) 
  {
    switch(c.getActionCase())
    {
    case CONFIGURATION:
    {
      SEInhalerConfiguration dst = new SEInhalerConfiguration();
      SEInhalerConfiguration.load(c.getConfiguration(), dst, subMgr);
      return dst;
    }
    case ACTION_NOT_SET:
      Log.warn("AnyInhalerActionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported Inhaler Action type "+c.getActionCase());
    return null;
  }
  public static AnyInhalerActionData CDM2ANY(SEInhalerAction c)
  {
    AnyInhalerActionData.Builder dst = AnyInhalerActionData.newBuilder();
    
    if(c instanceof SEInhalerConfiguration)
    {
      dst.setConfiguration(SEInhalerConfiguration.unload((SEInhalerConfiguration)c));
      return dst.build();
    }
    Log.error("Unsupported Inhaler Action type "+c);
    return dst.build();
  }
  
  public abstract String toString();
}
