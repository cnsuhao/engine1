/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
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
