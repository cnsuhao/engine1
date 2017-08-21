/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;

import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.properties.*;

public class SESubstanceConcentration
{
  protected SEScalarMassPerVolume  concentration;
  protected SESubstance            substance;
  
  public SESubstanceConcentration(SESubstance s)
  {
    if(s==null)
      throw new RuntimeException("Must provide a valid substance");
    this.substance=s;
  }
  
  public void reset()
  {
    if(this.concentration!=null)
      this.concentration.invalidate();
  }
  
  public static void load(SubstanceData.ConcentrationData src, SESubstanceConcentration dst)
  {
    dst.reset();
    if(src.hasConcentration())
      SEScalarMassPerVolume.load(src.getConcentration(), dst.getConcentration());
  }
  public static SubstanceData.ConcentrationData unload(SESubstanceConcentration src)
  {
    SubstanceData.ConcentrationData.Builder dst = SubstanceData.ConcentrationData.newBuilder();
    SESubstanceConcentration.unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstanceConcentration src, SubstanceData.ConcentrationData.Builder dst)
  {
    dst.setName(src.substance.getName());
    if(src.hasConcentration())
      dst.setConcentration(SEScalarMassPerVolume.unload(src.concentration)); 
  }
  
  public SEScalarMassPerVolume getConcentration() 
  { 
    if(this.concentration==null)
      this.concentration=new SEScalarMassPerVolume();
    return this.concentration;
  }
  public boolean hasConcentration() {return this.concentration==null?false:this.concentration.isValid();}
  
  public boolean hasSubstance() { return substance != null; }
  public SESubstance getSubstance() 
  { 
    return this.substance;
  }
  
  public String toString()
  {
    if(!hasSubstance())
      return "";
    String str = "Concentration of "+this.substance.getName()+": "+(hasConcentration()?getConcentration():"None");      
    return str;
  }
}
