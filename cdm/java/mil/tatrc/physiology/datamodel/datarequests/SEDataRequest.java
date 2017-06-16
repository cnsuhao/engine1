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

package mil.tatrc.physiology.datamodel.datarequests;

import java.io.Serializable;

import com.kitware.physiology.cdm.Scenario.DataRequestData;
import com.kitware.physiology.cdm.Scenario.DataRequestData.eCategory;
import com.kitware.physiology.cdm.Scenario.DecimalFormatData;

public class SEDataRequest implements Serializable
{
  protected String                  name;
  protected String                  unit;
  protected eCategory               category;
  protected String                  compartmentName;
  protected String                  substanceName;
  protected Integer                 precision;
  protected DecimalFormatData.eType format;
  
  public SEDataRequest() 
  {
    reset();
  }
  
  public void reset()
  {
    name            = "";
    unit            = null;
    category        = null;
    compartmentName = null;
    substanceName   = null;
    precision       = null;
    format          = null;
  }
  
  public static void load(DataRequestData src, SEDataRequest dst)
  {
    dst.reset();    
    dst.name = src.getName();
    dst.unit = src.getUnit();
    dst.category = src.getCategory();
    dst.compartmentName = src.getCompartmentName();
    dst.substanceName = src.getSubstanceName();
    if(src.hasDecimalFormat())
    {
      dst.format = src.getDecimalFormat().getType();      
      dst.precision = src.getDecimalFormat().getPrecision();
    }
  }
  public static DataRequestData unload(SEDataRequest src)
  {
    DataRequestData.Builder dst = DataRequestData.newBuilder();
    unload(src,dst);
    return dst.build();    
  }
  protected static void unload(SEDataRequest src, DataRequestData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    if(src.hasUnit())
      dst.setUnit(src.unit);
    if(src.hasCategory())
      dst.setCategory(src.category);
    if(src.hasCompartmentName())
      dst.setCompartmentName(src.compartmentName);
    if(src.hasSubstanceName())
      dst.setSubstanceName(src.substanceName);
    if(src.hasFormat())
      dst.getDecimalFormatBuilder().setType(src.format);
    if(src.hasPrecision())
      dst.getDecimalFormatBuilder().setPrecision(src.precision);    
  }
  
  public int hashCode()
  {
    int c = 17;
    if(name!=null)
    c = 31 * c + name.hashCode();
    if(unit!=null)
      c = 31 * c + unit.hashCode();
    if(category!=null)
      c = 31 * c + category.hashCode();
    if(compartmentName!=null)
      c = 31 * c + compartmentName.hashCode();
    if(substanceName!=null)
      c = 31 * c + substanceName.hashCode();
    if(precision!=null)
      c = 31 * c + (int)(precision ^ (precision >>> 32));
    if(format!=null)
      c = 31 * c + format.hashCode();    
    return c;
  }
  
  public String getName(){ return name; }
  public void setName(String name){ this.name = name; }
  public boolean hasName() { return name==null||name.isEmpty() ? false : true; }
  
  public String getUnit(){ return unit; }
  public void setUnit(String unit){ this.unit = unit; }
  public boolean hasUnit(){ return unit==null||unit.isEmpty() ? false : true; }
  
  public eCategory getCategory(){ return category; }
  public void setCategory(eCategory c){ this.category = c; }
  public boolean hasCategory(){ return category==null||category==eCategory.UNRECOGNIZED ? false : true; }
  
  public String getCompartmentName(){ return compartmentName; }
  public void setCompartmentName(String c){ this.compartmentName = c; }
  public boolean hasCompartmentName(){ return compartmentName==null||compartmentName.isEmpty() ? false : true; }
  
  public String getSubstanceName(){ return substanceName; }
  public void setSubstanceName(String s){ this.substanceName = s; }
  public boolean hasSubstanceName(){ return substanceName==null||substanceName.isEmpty() ? false : true; }
  
  public DecimalFormatData.eType getFormat(){ return format; }
  public void setFormat(DecimalFormatData.eType f){ this.format = f; }
  public boolean hasFormat(){ return format==null||format==DecimalFormatData.eType.UNRECOGNIZED ? false : true; }
  
  public Integer getPrecision(){ return precision; }
  public void setPrecision(Integer p){ this.precision = p; }
  public boolean hasPrecision(){ return precision==null ? false : true; }
  
}
