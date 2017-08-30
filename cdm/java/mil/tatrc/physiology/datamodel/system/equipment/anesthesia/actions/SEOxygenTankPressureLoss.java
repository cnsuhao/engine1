/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;

import com.kitware.physiology.cdm.AnesthesiaMachineActions.OxygenTankPressureLossData;
import com.kitware.physiology.cdm.Enums.eSwitch;

public class SEOxygenTankPressureLoss extends SEAnesthesiaMachineAction
{
  protected eSwitch state;

  public SEOxygenTankPressureLoss()
  {
    state = eSwitch.Off;
  }

  public void reset()
  {
    super.reset();
    state = eSwitch.Off;
  }

  public boolean isValid()
  {
    return true;
  }

  public static void load(OxygenTankPressureLossData src, SEOxygenTankPressureLoss dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if (src.getState()!=eSwitch.UNRECOGNIZED && src.getState()!=eSwitch.NullSwitch)
      dst.setState(src.getState());
  }
  public static OxygenTankPressureLossData unload(SEOxygenTankPressureLoss src)
  {
    OxygenTankPressureLossData.Builder dst = OxygenTankPressureLossData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEOxygenTankPressureLoss src, OxygenTankPressureLossData.Builder dst)
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
    return "Oxygen Tank Pressure Loss"
        + "\n\tState: " + getState();
  }
}
