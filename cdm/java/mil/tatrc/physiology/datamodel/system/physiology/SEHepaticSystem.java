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

package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.HepaticSystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEHepaticSystem extends SEPhysiologySystem implements SESystem
{
  public SEHepaticSystem()
  {
    
  }

  public void reset()
  {    
    
  }

  public static void load(HepaticSystemData src, SEHepaticSystem dst)
  {        
    
  }
  public static HepaticSystemData unload(SEHepaticSystem src)
  {
    HepaticSystemData.Builder dst = HepaticSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEHepaticSystem src, HepaticSystemData.Builder dst)
  {    
    
  }

  
}
