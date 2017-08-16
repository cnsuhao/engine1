/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ChestOcclusiveDressingData;
import com.kitware.physiology.cdm.Properties.eSide;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SEChestOcclusiveDressing extends SEPatientAction
{
  protected eSide side;
  protected eSwitch state;
  
  public SEChestOcclusiveDressing()
  {
    side = null;
    state = null;
  }
  
  public void copy(SEChestOcclusiveDressing other)
  {
    if(this==other)
      return;
    super.copy(other);
    this.state = other.state;
    this.side = other.side;
  }
  
  public void reset()
  {
    super.reset();
    state = null;
    side = null;
  }
  
  public boolean isValid()
  {
    return hasSide() && hasState();
  }
  
  public static void load(ChestOcclusiveDressingData src, SEChestOcclusiveDressing dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getState()!=eSwitch.UNRECOGNIZED)
    	dst.state = src.getState();
    if(src.getSide()!=eSide.UNRECOGNIZED)
    	dst.side = src.getSide();
  }
  
  public static ChestOcclusiveDressingData unload(SEChestOcclusiveDressing src)
  {
    ChestOcclusiveDressingData.Builder dst = ChestOcclusiveDressingData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChestOcclusiveDressing src, ChestOcclusiveDressingData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasState())
      dst.setState(src.state);
    if (src.hasSide())
      dst.setSide(src.side);
  }
  
  public eSide getSide()
  {
    return side;
  }
  public void setSide(eSide leftOrRight)
  {
    side = leftOrRight;
  }
  public boolean hasSide()
  {
    return side == null ? false : true;
  }
  
  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch onOrOff)
  {
    state = onOrOff;
  }
  public boolean hasState()
  {
    return state == null ? false : true;
  }
  
  public String toString()
  {
    if (side != null)
      return "Chest Occlusive Dressing" 
          + "\n\tState: " + getState()
          + "\n\tSide: " + getSide();
    else
      return "Action not properly specified";
  }
}
