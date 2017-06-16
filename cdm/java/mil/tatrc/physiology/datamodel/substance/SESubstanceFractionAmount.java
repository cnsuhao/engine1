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
