/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;


import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.properties.*;

public class SESubstanceFractionAmount
{
  protected SEScalar0To1  amount;
  protected SESubstance   substance;
  
  public SESubstanceFractionAmount(SESubstance s)
  {
    if(s==null)
      throw new RuntimeException("Must provide a valid substance");
    this.substance=s;
  }
  
  public void reset()
  {
    if(this.amount!=null)
      this.amount.invalidate();
  }
  
  public void copy(SESubstanceFractionAmount from)
  {
    this.substance=from.substance;
    if(from.hasAmount())
      this.getAmount().set(from.getAmount());
  }
  
  public static void load(SubstanceData.FractionAmountData src, SESubstanceFractionAmount dst)
  {
    dst.reset();
    if(src.hasAmount())
      SEScalar0To1.load(src.getAmount(), dst.getAmount());
  }
  public static SubstanceData.FractionAmountData unload(SESubstanceFractionAmount src)
  {
    SubstanceData.FractionAmountData.Builder dst = SubstanceData.FractionAmountData.newBuilder();
    SESubstanceFractionAmount.unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstanceFractionAmount src, SubstanceData.FractionAmountData.Builder dst)
  {
    dst.setName(src.substance.getName());
    if(src.hasAmount())
      dst.setAmount(SEScalar0To1.unload(src.amount)); 
  }
  
  public SEScalar0To1 getAmount() 
  { 
    if(this.amount==null)
      this.amount=new SEScalar0To1();
    return this.amount;
  }
  public boolean hasAmount() {return this.amount==null?false:this.amount.isValid();}
  
  public boolean hasSubstance() { return substance != null; }
  public SESubstance getSubstance() 
  { 
    return this.substance;
  }
  
  public String toString()
  {
    if(!hasSubstance())
      return "";
    String str = "Amount of "+this.substance.getName()+": "+(hasAmount()?getAmount():"None");      
    return str;
  }
}
