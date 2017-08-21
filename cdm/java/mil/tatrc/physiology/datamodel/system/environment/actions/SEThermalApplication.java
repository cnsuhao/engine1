/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.environment.actions;

import com.kitware.physiology.cdm.EnvironmentActions.ThermalApplicationData;

import mil.tatrc.physiology.datamodel.system.environment.*;

public class SEThermalApplication extends SEEnvironmentAction
{
  protected SEActiveConditioning activeHeating;
  protected SEActiveConditioning activeCooling;
  protected SEAppliedTemperature appliedTemperature;
  protected Boolean              appendToPrevious;
  
  public SEThermalApplication() 
  {
    appendToPrevious = null;
    activeHeating=null;   
    activeCooling=null;
    appliedTemperature=null;
  }
  
  public void copy(SEThermalApplication other)
  {
    if(this==other)
      return;
    super.copy(other);
    appendToPrevious = other.appendToPrevious;
    if (other.activeHeating != null)
      getActiveHeating().copy(other.getActiveHeating());
    else if (activeHeating != null)
      activeHeating.reset();
    if (other.activeCooling != null)
      getActiveCooling().copy(other.getActiveCooling());
    else if (activeCooling != null)
      activeCooling.reset();
    if (other.appliedTemperature != null)
      getAppliedTemperature().copy(other.getAppliedTemperature());
    else if (appliedTemperature != null)
      appliedTemperature.reset();
  }
  
  public void reset()
  {
    super.reset();
    appendToPrevious = null;
    if (activeHeating != null)
      activeHeating.reset();
    if (activeCooling != null)
      activeCooling.reset();
    if (appliedTemperature != null)
      appliedTemperature.reset();
  }
  
  public boolean isValid()
  {
    return hasActiveCooling() || hasActiveHeating() || hasAppliedTemperature();
  }

  public static void load(ThermalApplicationData src, SEThermalApplication dst)
  {
    SEEnvironmentAction.load(src.getEnvironmentAction(), dst);
    if(src.getAppendToPrevious())
      dst.appendToPrevious = src.getAppendToPrevious();
    if(src.hasActiveHeating())
      SEActiveConditioning.load(src.getActiveHeating(),dst.getActiveHeating());
    if(src.hasActiveCooling())
      SEActiveConditioning.load(src.getActiveCooling(),dst.getActiveCooling());
    if(src.hasAppliedTemperature())
      SEAppliedTemperature.load(src.getAppliedTemperature(),dst.getAppliedTemperature());
  }
  public static ThermalApplicationData unload(SEThermalApplication src)
  {
    ThermalApplicationData.Builder dst = ThermalApplicationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEThermalApplication src, ThermalApplicationData.Builder dst)
  {
    SEEnvironmentAction.unload(src, dst.getEnvironmentActionBuilder());
    if(src.appendToPrevious!=null)
      dst.setAppendToPrevious(src.appendToPrevious);
    if (src.hasActiveHeating())
      dst.setActiveHeating(SEActiveConditioning.unload(src.activeHeating));
    if (src.hasActiveCooling())
      dst.setActiveCooling(SEActiveConditioning.unload(src.activeCooling));
    if (src.hasAppliedTemperature())
      dst.setAppliedTemperature(SEAppliedTemperature.unload(src.appliedTemperature));
  }
  
  public boolean hasAppendToPrevious() { return this.appendToPrevious!=null;}
  public boolean appendToPrevious() { return appendToPrevious; }
  
  public boolean hasActiveHeating()
  {
    return activeHeating != null;
  }
  public SEActiveConditioning getActiveHeating()
  {
    if (activeHeating == null)
      activeHeating = new SEActiveConditioning();
    return activeHeating;
  }
  
  public boolean hasActiveCooling()
  {
    return activeCooling != null;
  }
  public SEActiveConditioning getActiveCooling()
  {
    if (activeCooling == null)
      activeCooling = new SEActiveConditioning();
    return activeCooling;
  }
  
  public boolean hasAppliedTemperature()
  {
    return appliedTemperature != null;
  }
  public SEAppliedTemperature getAppliedTemperature()
  {
    if (appliedTemperature == null)
      appliedTemperature = new SEAppliedTemperature();
    return appliedTemperature;
  }
  
  public String toString() 
  {
      return "Thermal Application:" 
          + (this.hasActiveHeating()?this.getActiveHeating().toString():"No Heating")
          + (this.hasActiveCooling()?this.getActiveCooling().toString():"No Cooling")
          + (this.hasAppliedTemperature()?this.getAppliedTemperature().toString():"No Applied Temperature");
  }
}
