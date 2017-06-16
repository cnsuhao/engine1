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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsciousRespirationData.UseInhalerData;

import mil.tatrc.physiology.datamodel.properties.SEScalarMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SEUseInhaler extends SEConsciousRespirationCommand
{  
  public SEUseInhaler()
  {
  }
  
  public void copy(SEUseInhaler other)
  {
    if(this==other)
      return;
  }
  
  public SEUseInhaler getCopy()
  {
    SEUseInhaler command = new SEUseInhaler();
    command.copy(this);
    
    return command;
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public boolean isValid()
  {
    return true;
  }
  
  public static void load(UseInhalerData src, SEUseInhaler dst)
  {
    //SEConsciousRespirationCommand.load(src.getConsciousRespirationCommand(), dst);
  }
  
  public static UseInhalerData unload(SEUseInhaler src)
  {
    UseInhalerData.Builder dst = UseInhalerData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEUseInhaler src, UseInhalerData.Builder dst)
  {
    //SEConsciousRespirationCommand.unload(src, dst.getConsciousRespirationCommand());
  }
  
  public String toString()
  {
    return "Use Inhaler";
  }
}
