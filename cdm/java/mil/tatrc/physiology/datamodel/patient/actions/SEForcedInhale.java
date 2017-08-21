/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsciousRespirationData.ForcedInhaleData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEForcedInhale extends SEConsciousRespirationCommand
{
  protected SEScalar0To1 inspiratoryCapacityFraction;
  protected SEScalarTime period;
  
  public SEForcedInhale()
  {
    inspiratoryCapacityFraction = null;
    period = null;
  }
  
  public void copy(SEForcedInhale other)
  {
    if(this==other)
      return;
    
    inspiratoryCapacityFraction = other.inspiratoryCapacityFraction;
    period = other.period;
  }
  
  public SEConsciousRespirationCommand getCopy()
  {
    SEConsciousRespirationCommand command = new SEForcedInhale();
    command.copy(this);
    
    return command;
  }
  
  public void reset()
  {
    super.reset();
    if (inspiratoryCapacityFraction != null)
      inspiratoryCapacityFraction.invalidate();
    if (period != null)
      period.invalidate();
  }
  
  public boolean isValid()
  {
    return hasInspiratoryCapacityFraction() && hasPeriod();
  }
  
  public static void load(ForcedInhaleData src, SEForcedInhale dst)
  {
    //SEConsciousRespirationCommand.load(src.getConsciousRespirationCommand(), dst);
    if(src.hasInspiratoryCapacityFraction())
      SEScalar0To1.load(src.getInspiratoryCapacityFraction(),dst.getInspiratoryCapacityFraction());
    if(src.hasPeriod())
      SEScalarTime.load(src.getPeriod(),dst.getPeriod());
  }
  
  public static ForcedInhaleData unload(SEForcedInhale src)
  {
    ForcedInhaleData.Builder dst = ForcedInhaleData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEForcedInhale src, ForcedInhaleData.Builder dst)
  {
    //SEConsciousRespirationCommand.unload(src,dst.getConsciousRespirationCommand());    
    if (src.hasInspiratoryCapacityFraction())
      dst.setInspiratoryCapacityFraction(SEScalar0To1.unload(src.inspiratoryCapacityFraction));
    if (src.hasPeriod())
      dst.setPeriod(SEScalarTime.unload(src.period));
  }
  
  public boolean hasInspiratoryCapacityFraction()
  {
    return inspiratoryCapacityFraction != null;
  }
  public SEScalar0To1 getInspiratoryCapacityFraction()
  {
    if (inspiratoryCapacityFraction == null)
      inspiratoryCapacityFraction = new SEScalar0To1();
    return inspiratoryCapacityFraction;
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
    if (inspiratoryCapacityFraction != null &&
      period != null)
    {
      return "Forced Inhale" 
          + "\n\tInspiratory Capacity Fraction: " + getInspiratoryCapacityFraction()
          + "\n\tPeriod: " + getPeriod();
    }
    else
      return "Action not specified properly";
  }
}
