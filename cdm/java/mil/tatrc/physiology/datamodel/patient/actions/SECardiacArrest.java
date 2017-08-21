/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.CardiacArrestData;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SECardiacArrest extends SEPatientAction
{
  protected eSwitch state;
  
  public SECardiacArrest()
  {
    state = eSwitch.Off;
  }
  
  public void copy(SECardiacArrest other)
  {
    if(this==other)
      return;
    super.copy(other);
    state = other.state;
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
  
  public static void load(CardiacArrestData src, SECardiacArrest dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getState()!=eSwitch.UNRECOGNIZED && src.getState()!=eSwitch.NullSwitch)
    	dst.state = src.getState();
  }
  
  public static CardiacArrestData unload(SECardiacArrest src)
  {
    CardiacArrestData.Builder dst = CardiacArrestData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SECardiacArrest src, CardiacArrestData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    dst.setState(src.state);
  }
  
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
    return "Cardiac Arrest"
        + "\n\tState: " + getState();
  }
}
