/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

package mil.tatrc.physiology.datamodel.compartment;


import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.Compartment.LiquidCompartmentData;
import com.kitware.physiology.cdm.SubstanceQuantity.LiquidSubstanceQuantityData;

import mil.tatrc.physiology.datamodel.properties.SEScalar;
import mil.tatrc.physiology.datamodel.properties.SEScalarTemperature;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.substance.quantity.SELiquidSubstanceQuantity;

public class SELiquidCompartment extends SEFluidCompartment
{
  protected SEScalar                        pH;
  protected List<SELiquidSubstanceQuantity> substanceQuantities;
  
  public SELiquidCompartment()
  {
    this.substanceQuantities=new ArrayList<SELiquidSubstanceQuantity>();
  }
  
  public void reset()
  {
    super.reset();
    pH=null;
    for (SELiquidSubstanceQuantity sq : this.substanceQuantities)
      sq.reset();
  }
  
  public static void load(LiquidCompartmentData src, SELiquidCompartment dst, SESubstanceManager subMgr)
  {
    SEFluidCompartment.load(src.getFluidCompartment(), dst);
    if(src.hasPH())
      SEScalar.load(src.getPH(), dst.getPH());
    for(LiquidSubstanceQuantityData subQData : src.getSubstanceQuantityList())
    {
      SELiquidSubstanceQuantity subQ = dst.getSubstanceQuantity(subMgr.getSubstance(subQData.getSubstanceQuantity().getSubstance()));
      SELiquidSubstanceQuantity.load(subQData, subQ);
    }
  }
  public static LiquidCompartmentData unload(SELiquidCompartment src)
  {
    LiquidCompartmentData.Builder dst = LiquidCompartmentData.newBuilder();
    unload(src,dst);
    return dst.build();    
  }
  protected static void unload(SELiquidCompartment src, LiquidCompartmentData.Builder dst)
  {
    SEFluidCompartment.unload(src,dst.getFluidCompartmentBuilder());
    if(src.hasPH())
      dst.setPH(SEScalar.unload(src.getPH()));
    for(SELiquidSubstanceQuantity subQ : src.getSubstanceQuantities())
      dst.addSubstanceQuantity(SELiquidSubstanceQuantity.unload(subQ));
  }
  
  public boolean hasPH()
  {
    return pH == null ? false : pH.isValid();
  }
  public SEScalar getPH()
  {
    if (pH == null)
      pH = new SEScalar();
    return pH;
  }
  
  public boolean hasSubstanceQuantities()
  {
    return substanceQuantities.size() > 0 ? true : false;
  }
  public boolean hasSubstanceQuantity(SESubstance substance)
  {
    for (SELiquidSubstanceQuantity csq : substanceQuantities)
    {
      if (csq.getSubstance() == substance)
        return true;
    }
    return false;
  }
  public SELiquidSubstanceQuantity getSubstanceQuantity(SESubstance substance)
  {
    for (SELiquidSubstanceQuantity csq : substanceQuantities)
    {
      if (substance == csq.getSubstance())
        return csq;
    }
    SELiquidSubstanceQuantity csq = new SELiquidSubstanceQuantity(substance);
    substanceQuantities.add(csq);
    return csq;
  }
  public List<SELiquidSubstanceQuantity> getSubstanceQuantities()
  {
    return substanceQuantities;
  }
  public void removeSubstanceQuantity(SESubstance substance)
  {
    for (SELiquidSubstanceQuantity csq : substanceQuantities)
    {
      if (csq.getSubstance() == substance)
      {
        substanceQuantities.remove(csq);
        return;
      }
    }
  }
  public void removeSubstanceQuantity(String substanceName)
  {
    for (SELiquidSubstanceQuantity csq : substanceQuantities)
    {
      if (csq.getSubstance().getName().equals(substanceName))
      {
        substanceQuantities.remove(csq);
        return;
      }
    }
  }
}
