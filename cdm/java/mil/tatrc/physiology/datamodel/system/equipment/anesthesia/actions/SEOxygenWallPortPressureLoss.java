/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;

import com.kitware.physiology.cdm.AnesthesiaMachineActions.OxygenWallPortPressureLossData;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SEOxygenWallPortPressureLoss extends SEAnesthesiaMachineAction
{
  protected eSwitch state;
  
  public SEOxygenWallPortPressureLoss()
  {
    state = eSwitch.On;
  }
  
  public void reset()
  {
    super.reset();
    state = eSwitch.On;
  }
  
  public boolean isValid()
  {
    return true;
  }
  
  public static void load(OxygenWallPortPressureLossData src, SEOxygenWallPortPressureLoss dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if (src.getState()!=eSwitch.UNRECOGNIZED && src.getState()!=eSwitch.NullSwitch)
      dst.setState(src.getState());
  }
  public static OxygenWallPortPressureLossData unload(SEOxygenWallPortPressureLoss src)
  {
    OxygenWallPortPressureLossData.Builder dst = OxygenWallPortPressureLossData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEOxygenWallPortPressureLoss src, OxygenWallPortPressureLossData.Builder dst)
  {
    SEAnesthesiaMachineAction.unload(src, dst.getAnesthesiaMachineActionBuilder());
    dst.setState(src.state);
  }
  
  /*
   * State
   */
  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch s)
  {
  	this.state = (s==eSwitch.NullSwitch) ? eSwitch.Off : s;
  }
  
  public String toString()
  {
    return "Oxygen Wall Port Pressure Loss"
        + "\n\tState: " + getState();
  }
}
