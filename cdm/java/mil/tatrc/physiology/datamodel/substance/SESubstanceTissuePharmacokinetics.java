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
