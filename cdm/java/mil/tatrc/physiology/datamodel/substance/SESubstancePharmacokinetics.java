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

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import com.kitware.physiology.cdm.Substance.SubstanceData;

public class SESubstancePharmacokinetics
{
  protected SESubstancePhysicochemicals physicochemicals;  
  protected Map<String,SESubstanceTissuePharmacokinetics> TissueKinetics = new HashMap<String,SESubstanceTissuePharmacokinetics>();
    
  public SESubstancePharmacokinetics()
  {
    
  }
  
  public void reset()
  {
    if(this.physicochemicals!=null)
      this.physicochemicals.reset();
    
    if(this.TissueKinetics!=null)
      this.TissueKinetics.clear();
  }
  
  public boolean isValid()
  {
    if(hasTissueKinetics())
      return true;
    if(hasPhysicochemicals())       
      return true;
    return false;
  }
  
  public static void load(SubstanceData.PharmacokineticsData src, SESubstancePharmacokinetics dst)
  {
    dst.reset();
    if(src.hasPhysicochemicals())
      SESubstancePhysicochemicals.load(src.getPhysicochemicals(), dst.getPhysicochemicals());
    
    if(src.getTissueKineticsList()!=null)
    {      
      for(SubstanceData.TissuePharmacokineticsData kData : src.getTissueKineticsList())
      {
        SESubstanceTissuePharmacokinetics.load(kData,dst.getTissueKinetics(kData.getName()));
      }
    }
  }
  
  public static SubstanceData.PharmacokineticsData unload(SESubstancePharmacokinetics src)
  {
    if(!src.isValid())
      return null;
    SubstanceData.PharmacokineticsData.Builder dst = SubstanceData.PharmacokineticsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SESubstancePharmacokinetics src, SubstanceData.PharmacokineticsData.Builder dst)
  {
    if(src.hasPhysicochemicals())
      dst.setPhysicochemicals(SESubstancePhysicochemicals.unload(src.physicochemicals));
    
    if(src.hasTissueKinetics())
    {
      for(SESubstanceTissuePharmacokinetics fx : src.getTissueKinetics())
      {
        dst.addTissueKinetics(SESubstanceTissuePharmacokinetics.unload(fx));
      }
    }
  }
  
  public SESubstancePhysicochemicals getPhysicochemicals() 
  { 
    if(this.physicochemicals == null)
      this.physicochemicals = new SESubstancePhysicochemicals();
    return this.physicochemicals;
  }  
  public boolean hasPhysicochemicals() { return this.physicochemicals==null ? false : this.physicochemicals.isValid(); }
  
  
  public Collection<SESubstanceTissuePharmacokinetics> getTissueKinetics() 
  { 
    return this.TissueKinetics.values();
  }  
  public boolean hasTissueKinetics() {return !this.TissueKinetics.isEmpty();}
  public boolean hasTissueKinetics(String name)
  {
    return this.TissueKinetics.containsKey(name);
  }
  public SESubstanceTissuePharmacokinetics getTissueKinetics(String name)
  {
    
    SESubstanceTissuePharmacokinetics tk = this.TissueKinetics.get(name);
    if(tk==null)
    {
      tk = new SESubstanceTissuePharmacokinetics();
      tk.setName(name);
      this.TissueKinetics.put(name,tk);
    }    
    return tk;
  }
}
