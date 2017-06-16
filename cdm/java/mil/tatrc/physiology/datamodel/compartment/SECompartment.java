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

import com.kitware.physiology.cdm.Compartment.CompartmentData;

public abstract class SECompartment
{
  protected String name;
  
  public SECompartment()
  {
    
  }
  
  public void reset()
  {
    
  }
  
  public static void load(CompartmentData src, SECompartment dst)
  {
    dst.reset();
  }
  protected static void unload(SECompartment src, CompartmentData dst)
  {
    
  }
  
  public String getName()
  {
    return this.name;
  }
  public void setName(String n)
  {
    this.name = n;
  }
  public boolean hasName()
  {
    return this.name==null?false:!this.name.isEmpty();
  }
}
