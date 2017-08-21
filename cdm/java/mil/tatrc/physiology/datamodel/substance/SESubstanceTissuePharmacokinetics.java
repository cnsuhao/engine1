/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;

import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.properties.*;

public class SESubstanceTissuePharmacokinetics 
{
  protected String        name;
  protected SEScalar      partitionCoefficient;
  
  public SESubstanceTissuePharmacokinetics()
  {
    
  }
  
  public void reset()
  {
    this.name=null;
    if(this.partitionCoefficient!=null)
      this.partitionCoefficient.invalidate();  
  }
  
  public static void load(SubstanceData.TissuePharmacokineticsData src, SESubstanceTissuePharmacokinetics dst)
  {
    if(src.getName()!=null)
      dst.setName(src.getName());
    if(src.hasPartitionCoefficient())
      SEScalar.load(src.getPartitionCoefficient(),dst.getPartitionCoefficient());    
  }
  
  public static SubstanceData.TissuePharmacokineticsData unload(SESubstanceTissuePharmacokinetics src)
  {
    SubstanceData.TissuePharmacokineticsData.Builder dst = SubstanceData.TissuePharmacokineticsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SESubstanceTissuePharmacokinetics src, SubstanceData.TissuePharmacokineticsData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);    
    if(src.hasPartitionCoefficient())
      dst.setPartitionCoefficient(SEScalar.unload(src.partitionCoefficient));    
  }
  
  public String  getName() { return this.name;}
  public void    setName(String name){this.name=name;}
  public boolean hasName(){return this.name==null?false:!this.name.isEmpty();}
  
  public SEScalar getPartitionCoefficient() 
  { 
    if(this.partitionCoefficient==null)
      this.partitionCoefficient=new SEScalar();
    return this.partitionCoefficient;
  }
  public boolean      hasPartitionCoefficient() {return this.partitionCoefficient==null?false:this.partitionCoefficient.isValid();}
}
