/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.actions;

import com.kitware.physiology.cdm.Actions.AdvanceTimeData;

import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEAdvanceTime extends SEAction 
{
  protected SEScalarTime time;
  
  public SEAdvanceTime() 
  {
    time = null;
  }
  
  public void copy(SEAdvanceTime other)
  {
    if(this==other)
      return;
    super.copy(other);
  }
  
  public void reset() 
  {
    super.reset();
    if (hasTime())
      time.invalidate();
  }
  
  public boolean isValid()
  {
    return hasTime();
  }

  public static void load(AdvanceTimeData src, SEAdvanceTime dst) 
  {
    SEAction.load(src.getAction(), dst);
    if(src.hasTime())
      SEScalarTime.load(src.getTime(),dst.getTime());
  }
  public static AdvanceTimeData unload(SEAdvanceTime src)
  {
    AdvanceTimeData.Builder dst = AdvanceTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEAdvanceTime src, AdvanceTimeData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
    if (src.hasTime())
      dst.setTime(SEScalarTime.unload(src.time));
  }
  
  public boolean hasTime()
  {
    return time == null ? false : time.isValid();
  }
  public SEScalarTime getTime() 
  {
    if (time == null)
      time = new SEScalarTime();
    return time;
  }
  
  public String toString() 
  {
    return "Advance Time" 
        + "\n\tTime: " + getTime();
  }
}
