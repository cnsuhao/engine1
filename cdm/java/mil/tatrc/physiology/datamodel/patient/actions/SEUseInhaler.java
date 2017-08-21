/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsciousRespirationData.UseInhalerData;

import mil.tatrc.physiology.datamodel.properties.SEScalarMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SEUseInhaler extends SEConsciousRespirationCommand
{  
  public SEUseInhaler()
  {
  }
  
  public void copy(SEUseInhaler other)
  {
    if(this==other)
      return;
  }
  
  public SEUseInhaler getCopy()
  {
    SEUseInhaler command = new SEUseInhaler();
    command.copy(this);
    
    return command;
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public boolean isValid()
  {
    return true;
  }
  
  public static void load(UseInhalerData src, SEUseInhaler dst)
  {
    //SEConsciousRespirationCommand.load(src.getConsciousRespirationCommand(), dst);
  }
  
  public static UseInhalerData unload(SEUseInhaler src)
  {
    UseInhalerData.Builder dst = UseInhalerData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEUseInhaler src, UseInhalerData.Builder dst)
  {
    //SEConsciousRespirationCommand.unload(src, dst.getConsciousRespirationCommand());
  }
  
  public String toString()
  {
    return "Use Inhaler";
  }
}
