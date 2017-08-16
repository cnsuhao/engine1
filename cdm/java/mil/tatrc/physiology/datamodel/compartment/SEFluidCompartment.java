/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.compartment;

import com.kitware.physiology.cdm.Compartment.FluidCompartmentData;

import mil.tatrc.physiology.datamodel.properties.SEScalarPressure;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolumePerTime;

public abstract class SEFluidCompartment extends SECompartment
{
  protected SEScalarVolumePerTime inFlow;
  protected SEScalarVolumePerTime outFlow;
  protected SEScalarPressure      pressure;  
  protected SEScalarVolume        volume;
  
  public SEFluidCompartment()
  {
    super();
    
  }
  
  public void reset()
  {
    super.reset();
    if (pressure != null)
      pressure.invalidate();
    if (inFlow != null)
      inFlow.invalidate();
    if (outFlow != null)
      outFlow.invalidate();
    if (volume != null)
      volume.invalidate();
  }
  
  public static void load(FluidCompartmentData src, SEFluidCompartment dst)
  {
    SECompartment.load(src.getCompartment(),dst);
    if (src.hasPressure()) 
       SEScalarPressure.load(src.getPressure(),dst.getPressure()); 
    if (src.hasInFlow()) 
      SEScalarVolumePerTime.load(src.getInFlow(),dst.getInFlow()); 
    if (src.hasOutFlow()) 
      SEScalarVolumePerTime.load(src.getOutFlow(),dst.getOutFlow()); 
    if (src.hasVolume()) 
      SEScalarVolume.load(src.getVolume(),dst.getVolume()); 
  }
  protected static void unload(SEFluidCompartment src, FluidCompartmentData.Builder dst)
  {
    SECompartment.unload(src,dst.getCompartment());
    if (src.hasPressure())
      dst.setPressure(SEScalarPressure.unload(src.pressure));
    if (src.hasInFlow())
      dst.setInFlow(SEScalarVolumePerTime.unload(src.inFlow));
    if (src.hasOutFlow())
      dst.setOutFlow(SEScalarVolumePerTime.unload(src.outFlow));
    if (src.hasVolume())
      dst.setVolume(SEScalarVolume.unload(src.volume));
  }
  
  public SEScalarVolumePerTime getInFlow() 
  {
    if (inFlow == null)
      inFlow = new SEScalarVolumePerTime();
    return inFlow;
  }
  public boolean hasInFlow()
  {
    return inFlow == null ? false : inFlow.isValid();
  }
  
  public SEScalarVolumePerTime getOutFlow() 
  {
    if (outFlow == null)
      outFlow = new SEScalarVolumePerTime();
    return outFlow;
  }
  public boolean hasOutFlow()
  {
    return outFlow == null ? false : outFlow.isValid();
  }
  
  public SEScalarPressure getPressure() 
  {
    if (pressure == null)
      pressure = new SEScalarPressure();
    return pressure;
  }
  public boolean hasPressure()
  {
    return pressure == null ? false : pressure.isValid();
  }
  
  public SEScalarVolume getVolume() 
  {
    if (volume == null)
      volume = new SEScalarVolume();
    return volume;
  }
  public boolean hasVolume()
  {
    return volume == null ? false : volume.isValid();
  }
}
