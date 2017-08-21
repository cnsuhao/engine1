/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;


import org.jfree.util.Log;

import com.kitware.physiology.cdm.AnesthesiaMachineActions.AnesthesiaMachineActionData;
import com.kitware.physiology.cdm.AnesthesiaMachineActions.AnyAnesthesiaMachineActionData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.environment.actions.SEThermalApplication;

public abstract class SEAnesthesiaMachineAction extends SEAction
{
  public SEAnesthesiaMachineAction()
  {
    
  }
  
  public void copy(SEAnesthesiaMachineAction other)
  {
    if (this == other)
      return;
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(AnesthesiaMachineActionData src, SEAnesthesiaMachineAction dst) 
  {
    SEAction.load(src.getAction(), dst);
  }
  protected static void unload(SEAnesthesiaMachineAction src, AnesthesiaMachineActionData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
  }
  
  public static SEAnesthesiaMachineAction ANY2CDM(AnyAnesthesiaMachineActionData c, SESubstanceManager subMgr) 
  {
    switch(c.getActionCase())
    {
    case CONFIGURATION:
    {
      SEAnesthesiaMachineConfiguration dst = new SEAnesthesiaMachineConfiguration();
      SEAnesthesiaMachineConfiguration.load(c.getConfiguration(), dst, subMgr);
      return dst;
    }
    case EXPIRATORYVALVELEAK:
    {
      SEExpiratoryValveLeak dst = new SEExpiratoryValveLeak();
      SEExpiratoryValveLeak.load(c.getExpiratoryValveLeak(), dst);
      return dst;
    }
    case EXPIRATORYVALVEOBSTRUCTION:
    {
      SEExpiratoryValveObstruction dst = new SEExpiratoryValveObstruction();
      SEExpiratoryValveObstruction.load(c.getExpiratoryValveObstruction(), dst);
      return dst;
    }
    case INSPIRATORYVALVELEAK:
    {
      SEInspiratoryValveLeak dst = new SEInspiratoryValveLeak();
      SEInspiratoryValveLeak.load(c.getInspiratoryValveLeak(), dst);
      return dst;
    }
    case INSPIRATORYVALVEOBSTRUCTION:
    {
      SEInspiratoryValveObstruction dst = new SEInspiratoryValveObstruction();
      SEInspiratoryValveObstruction.load(c.getInspiratoryValveObstruction(), dst);
      return dst;
    }
    case MASKLEAK:
    {
      SEMaskLeak dst = new SEMaskLeak();
      SEMaskLeak.load(c.getMaskLeak(), dst);
      return dst;
    }
    case SODALIMEFAILURE:
    {
      SESodaLimeFailure dst = new SESodaLimeFailure();
      SESodaLimeFailure.load(c.getSodaLimeFailure(), dst);
      return dst;
    }
    case TUBECUFFLEAK:
    {
      SETubeCuffLeak dst = new SETubeCuffLeak();
      SETubeCuffLeak.load(c.getTubeCuffLeak(), dst);
      return dst;
    }
    case VAPORIZERFAILURE:
    {
      SEVaporizerFailure dst = new SEVaporizerFailure();
      SEVaporizerFailure.load(c.getVaporizerFailure(), dst);
      return dst;
    }
    case VENTILATORPRESSURELOSS:
    {
      SEVentilatorPressureLoss dst = new SEVentilatorPressureLoss();
      SEVentilatorPressureLoss.load(c.getVentilatorPressureLoss(), dst);
      return dst;
    }
    case YPIECEDISCONNECT:
    {
      SEYPieceDisconnect dst = new SEYPieceDisconnect();
      SEYPieceDisconnect.load(c.getYPieceDisconnect(), dst);
      return dst;
    }
    case OXYGENTANKPRESSURELOSS:
    {
      SEOxygenTankPressureLoss dst = new SEOxygenTankPressureLoss();
      SEOxygenTankPressureLoss.load(c.getOxygenTankPressureLoss(), dst);
      return dst;
    }
    case OXYGENWALLPORTPRESSURELOSS:
    {
      SEOxygenWallPortPressureLoss dst = new SEOxygenWallPortPressureLoss();
      SEOxygenWallPortPressureLoss.load(c.getOxygenWallPortPressureLoss(), dst);
      return dst;
    }
    case ACTION_NOT_SET:
      Log.warn("AnyAnesthesiaMachineActionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported AnesthesiaMachine Action type "+c.getActionCase());
    return null;
  }
  public static AnyAnesthesiaMachineActionData CDM2ANY(SEAnesthesiaMachineAction c)
  {
    AnyAnesthesiaMachineActionData.Builder dst = AnyAnesthesiaMachineActionData.newBuilder();
    if(c instanceof SEAnesthesiaMachineConfiguration)
    {
      dst.setConfiguration(SEAnesthesiaMachineConfiguration.unload((SEAnesthesiaMachineConfiguration)c));
      return dst.build();
    }
    if(c instanceof SEExpiratoryValveLeak)
    {
      dst.setExpiratoryValveLeak(SEExpiratoryValveLeak.unload((SEExpiratoryValveLeak)c));
      return dst.build();
    }
    if(c instanceof SEExpiratoryValveObstruction)
    {
      dst.setExpiratoryValveObstruction(SEExpiratoryValveObstruction.unload((SEExpiratoryValveObstruction)c));
      return dst.build();
    }
    if(c instanceof SEInspiratoryValveLeak)
    {
      dst.setInspiratoryValveLeak(SEInspiratoryValveLeak.unload((SEInspiratoryValveLeak)c));
      return dst.build();
    }
    if(c instanceof SEInspiratoryValveObstruction)
    {
      dst.setInspiratoryValveObstruction(SEInspiratoryValveObstruction.unload((SEInspiratoryValveObstruction)c));
      return dst.build();
    }
    if(c instanceof SEMaskLeak)
    {
      dst.setMaskLeak(SEMaskLeak.unload((SEMaskLeak)c));
      return dst.build();
    }
    if(c instanceof SESodaLimeFailure)
    {
      dst.setSodaLimeFailure(SESodaLimeFailure.unload((SESodaLimeFailure)c));
      return dst.build();
    }
    if(c instanceof SETubeCuffLeak)
    {
      dst.setTubeCuffLeak(SETubeCuffLeak.unload((SETubeCuffLeak)c));
      return dst.build();
    }
    if(c instanceof SEVaporizerFailure)
    {
      dst.setVaporizerFailure(SEVaporizerFailure.unload((SEVaporizerFailure)c));
      return dst.build();
    }
    if(c instanceof SEVentilatorPressureLoss)
    {
      dst.setVentilatorPressureLoss(SEVentilatorPressureLoss.unload((SEVentilatorPressureLoss)c));
      return dst.build();
    }
    if(c instanceof SEYPieceDisconnect)
    {
      dst.setYPieceDisconnect(SEYPieceDisconnect.unload((SEYPieceDisconnect)c));
      return dst.build();
    }
    if(c instanceof SEOxygenTankPressureLoss)
    {
      dst.setOxygenTankPressureLoss(SEOxygenTankPressureLoss.unload((SEOxygenTankPressureLoss)c));
      return dst.build();
    }
    if(c instanceof SEOxygenWallPortPressureLoss)
    {
      dst.setOxygenWallPortPressureLoss(SEOxygenWallPortPressureLoss.unload((SEOxygenWallPortPressureLoss)c));
      return dst.build();
    }
    Log.error("Unsupported AnesthesiaMachine Action type "+c);
    return dst.build();
  }
  
  public abstract String toString();
}
