/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.compartment;

import java.util.HashMap;
import java.util.Map;

import com.kitware.physiology.cdm.Compartment.eCompartmentType;

public class SECompartmentManager
{
  protected Map<String,SEGasCompartment>        gas=new HashMap<String,SEGasCompartment>();
  protected Map<String,SELiquidCompartment>     liquid=new HashMap<String,SELiquidCompartment>();
  protected Map<String,SEThermalCompartment>    thermal=new HashMap<String,SEThermalCompartment>();
  protected Map<String,SETissueCompartment>     tissue=new HashMap<String,SETissueCompartment>();
  
  public SECompartmentManager()
  {
    
  }
  
  public void clear()
  {
    gas.clear();
    liquid.clear();
    thermal.clear();
    tissue.clear();
  }
  
  public SECompartment GetCompartment(String name, eCompartmentType type)
  {
    switch(type)
    {
      case Gas:
        return GetGasCompartment(name);
      case Liquid:
        return GetLiquidCompartment(name);
      case Thermal:
        return GetThermalCompartment(name);
      case Tissue:
        return GetTissueCompartment(name);     
    }
    return null;
  }
  
  public boolean HasGasCompartment(String name)
  {
    return gas.containsKey(name);
  }
  public SEGasCompartment GetGasCompartment(String name)
  {
    SEGasCompartment cmpt = gas.get(name);
    if(cmpt==null)
    {
      cmpt = new SEGasCompartment();
      cmpt.setName(name);
      gas.put(name, cmpt);
    }
    return cmpt;
  }
  
  public boolean HasLiquidCompartment(String name)
  {
    return liquid.containsKey(name);
  }
  public SELiquidCompartment GetLiquidCompartment(String name)
  {
    SELiquidCompartment cmpt = liquid.get(name);
    if(cmpt==null)
    {
      cmpt = new SELiquidCompartment();
      cmpt.setName(name);
      liquid.put(name, cmpt);
    }
    return cmpt;
  }

  

  public boolean HasThermalCompartment(String name)
  {
    return thermal.containsKey(name);
  }
  public SEThermalCompartment GetThermalCompartment(String name)
  {
    SEThermalCompartment cmpt = thermal.get(name);
    if(cmpt==null)
    {
      cmpt = new SEThermalCompartment();
      cmpt.setName(name);
      thermal.put(name, cmpt);
    }
    return cmpt;
  }

  public boolean HasTissueCompartment(String name)
  {
    return tissue.containsKey(name);
  }
  public SETissueCompartment GetTissueCompartment(String name)
  {
    SETissueCompartment cmpt = tissue.get(name);
    if(cmpt==null)
    {
      cmpt = new SETissueCompartment();
      cmpt.setName(name);
      tissue.put(name, cmpt);
    }
    return cmpt;
  }
}
