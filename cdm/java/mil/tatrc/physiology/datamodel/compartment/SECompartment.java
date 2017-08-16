/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.compartment;

import com.kitware.physiology.cdm.Compartment.CompartmentData;

public abstract class SECompartment
{
  protected String name;
  
  public SECompartment()
  {
    
  }
  
  public void reset()
  {
    
  }
  
  public static void load(CompartmentData src, SECompartment dst)
  {
    dst.reset();
  }
  protected static void unload(SECompartment src, CompartmentData dst)
  {
    
  }
  
  public String getName()
  {
    return this.name;
  }
  public void setName(String n)
  {
    this.name = n;
  }
  public boolean hasName()
  {
    return this.name==null?false:!this.name.isEmpty();
  }
}
