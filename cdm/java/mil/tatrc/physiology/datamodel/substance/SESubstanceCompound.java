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

import java.util.ArrayList;
import java.util.List;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Patient.PatientData;
import com.kitware.physiology.cdm.Substance.SubstanceData;
import com.kitware.physiology.cdm.Substance.SubstanceData.ConcentrationData;

import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.StringUtils;

public class SESubstanceCompound
{
  protected String                         name;
  protected List<SESubstanceConcentration> components;
  
  public SESubstanceCompound()
  {
    
  }
  
  public void reset()
  {
    this.name=null;
    
    if(this.components!=null)
      this.components.clear();
  }
  
  public void readFile(String fileName, SESubstanceManager mgr) throws ParseException
  {
    SubstanceData.CompoundData.Builder builder = SubstanceData.CompoundData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SESubstanceCompound.load(builder.build(), this, mgr);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SESubstanceCompound.unload(this).toString());
  }
  
  public static void load(SubstanceData.CompoundData src, SESubstanceCompound dst, SESubstanceManager mgr)
  {
    dst.reset();
    if(src.getName()!=null)
      dst.setName(src.getName());

    if(src.getComponentList()!=null)
    {      
      for(ConcentrationData cData : src.getComponentList())
      {
        SESubstanceConcentration.load(cData,dst.createComponent(mgr.getSubstance(cData.getName())));
      }
    }
  } 
  public static SubstanceData.CompoundData unload(SESubstanceCompound src)
  {
    SubstanceData.CompoundData.Builder dst = SubstanceData.CompoundData.newBuilder();
    SESubstanceCompound.unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstanceCompound src, SubstanceData.CompoundData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    
    if(src.hasComponents())
    {
      for(SESubstanceConcentration c : src.getComponents())
        dst.addComponent(SESubstanceConcentration.unload(c));
    }
  }
  
  public String  getName() { return this.name;}
  public void    setName(String name){this.name=name;}
  public boolean hasName(){return StringUtils.exists(this.name);}
  
  public SESubstanceConcentration createComponent(SESubstance s) 
  { 
    return getComponent(s);
  }  
  public List<SESubstanceConcentration> getComponents() 
  { 
    if(this.components==null)
      this.components=new ArrayList<SESubstanceConcentration>();
    return this.components;
  }  
  public boolean hasComponents() {return this.components==null?false:this.components.size()>0;}
  public boolean hasComponent(SESubstance s) 
  {
    if(this.components==null)
      return false;
    for(SESubstanceConcentration c : this.components)
    {
      if(c.getSubstance()==s)
        return true;
    }
    return false;
  }
  public SESubstanceConcentration getComponent(SESubstance s) 
  {    
    for(SESubstanceConcentration c : getComponents())
    {
      if(c.getSubstance()==s)
        return c;
    }
    SESubstanceConcentration c=new SESubstanceConcentration(s);
    this.getComponents().add(c);
    return c;
  }
}
