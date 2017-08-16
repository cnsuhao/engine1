/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.compartment;

import com.kitware.physiology.cdm.Compartment.ThermalCompartmentData;

import mil.tatrc.physiology.datamodel.properties.SEScalarEnergy;
import mil.tatrc.physiology.datamodel.properties.SEScalarPower;
import mil.tatrc.physiology.datamodel.properties.SEScalarTemperature;

public class SEThermalCompartment extends SECompartment
{
  protected SEScalarPower heatTransferRateIn;
  protected SEScalarPower heatTransferRateOut;
  protected SEScalarTemperature temperature;
  protected SEScalarEnergy heat;

  public SEThermalCompartment()
  {
    heatTransferRateIn = null;
    heatTransferRateOut = null;
    temperature = null;
    heat = null;
  }

  public void reset()
  {
    super.reset();
    if (heatTransferRateIn != null)
      heatTransferRateIn.invalidate();
    if (heatTransferRateOut != null)
      heatTransferRateOut.invalidate();
    if (temperature != null)
      temperature.invalidate();
    if (heat != null)
      heat.invalidate();
  }

  public static void load(ThermalCompartmentData src, SEThermalCompartment dst)
  {
    SECompartment.load(src.getCompartment(), dst);
    if (src.hasHeatTransferRateIn())
      SEScalarPower.load(src.getHeatTransferRateIn(),dst.getHeatTransferRateIn());
    if (src.hasHeatTransferRateOut())
      SEScalarPower.load(src.getHeatTransferRateOut(),dst.getHeatTransferRateOut());
    if (src.hasTemperature())
      SEScalarTemperature.load(src.getTemperature(),dst.getTemperature());
    if (src.hasHeat())
      SEScalarEnergy.load(src.getHeat(),dst.getHeat());
  }
  public static ThermalCompartmentData unload(SEThermalCompartment src)
  {
    ThermalCompartmentData.Builder dst = ThermalCompartmentData.newBuilder();
    unload(src,dst);
    return dst.build();    
  }
  protected static void unload(SEThermalCompartment src, ThermalCompartmentData.Builder dst)
  {
    SECompartment.unload(src,dst.getCompartment());
    if (src.hasHeatTransferRateIn())
      dst.setHeatTransferRateIn(SEScalarPower.unload(src.heatTransferRateIn));
    if (src.hasHeatTransferRateOut())
      dst.setHeatTransferRateOut(SEScalarPower.unload(src.heatTransferRateOut));
    if (src.hasTemperature())
      dst.setTemperature(SEScalarTemperature.unload(src.temperature));
    if (src.hasHeat())
      dst.setHeat(SEScalarEnergy.unload(src.heat));
  }

  public boolean hasHeatTransferRateIn()
  {
    return heatTransferRateIn == null ? false : heatTransferRateIn.isValid();
  }
  public SEScalarPower getHeatTransferRateIn()
  {
    if (heatTransferRateIn == null)
      heatTransferRateIn = new SEScalarPower();
    return heatTransferRateIn;
  }
  
  public boolean hasHeatTransferRateOut()
  {
    return heatTransferRateOut == null ? false : heatTransferRateOut.isValid();
  }
  public SEScalarPower getHeatTransferRateOut()
  {
    if (heatTransferRateOut == null)
      heatTransferRateOut = new SEScalarPower();
    return heatTransferRateOut;
  }

  public boolean hasTemperature()
  {
    return temperature == null ? false : temperature.isValid();
  }
  public SEScalarTemperature getTemperature()
  {
    if (temperature == null)
      temperature = new SEScalarTemperature();
    return temperature;
  }

  public boolean hasHeat()
  {
    return heat == null ? false : heat.isValid();
  }
  public SEScalarEnergy getHeat()
  {
    if (heat == null)
      heat = new SEScalarEnergy();
    return heat;
  }
}
