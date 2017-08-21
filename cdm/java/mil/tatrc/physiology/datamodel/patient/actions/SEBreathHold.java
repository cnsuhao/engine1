/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsciousRespirationData.BreathHoldData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEBreathHold extends SEConsciousRespirationCommand
{
  protected SEScalarTime period;
  
  public SEBreathHold()
  {
    period = null;
  }
  
  public void copy(SEBreathHold other)
  {
    if(this==other)
      return;

    period = other.period;
  }
  
  public SEConsciousRespirationCommand getCopy()
  {
    SEConsciousRespirationCommand command = new SEBreathHold();
    command.copy(this);
    
    return command;
  }
  
  public void reset()
  {
    super.reset();

    if (period != null)
      period.invalidate();
  }
  
  public boolean isValid()
  {
    return hasPeriod();
  }
  
  public static void load(BreathHoldData src, SEBreathHold dst)
  {
    //SEConsciousRespirationCommand.load(src.getConsciousRespirationCommand(), dst);
    if(src.hasPeriod())
      SEScalarTime.load(src.getPeriod(),dst.getPeriod());    
  }
  
  public static BreathHoldData unload(SEBreathHold src)
  {
    BreathHoldData.Builder dst = BreathHoldData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEBreathHold src, BreathHoldData.Builder dst)
  {
    //SEConsciousRespirationCommand.unload(src,dst.getConsciousRespirationCommand());
    if (src.hasPeriod())
      dst.setPeriod(SEScalarTime.unload(src.period));
  }
  
  public boolean hasPeriod()
  {
    return period != null;
  }
  public SEScalarTime getPeriod()
  {
    if (period == null)
      period = new SEScalarTime();
    return period;
  }
  
  public String toString()
  {
    if (period != null)
    {
      return "Breath Hold"
          + "\n\tPeriod: " + getPeriod();
    }
    else
      return "Action not specified properly";
  }
}
