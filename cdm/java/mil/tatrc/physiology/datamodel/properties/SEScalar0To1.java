/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import mil.tatrc.physiology.utilities.Log;

import com.kitware.physiology.cdm.Properties.Scalar0To1Data;

/**
 * @author abray
 * 0To1 Scalar Class, will enforce that value is between 0 and 1 (inclusive)
 */

public class SEScalar0To1 extends SEScalar
{
  public SEScalar0To1()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalar0To1(double value)
  {
    this();
    this.setValue(value, "");
  }
  
  public static void load(Scalar0To1Data src, SEScalar0To1 dst)
  {
    SEScalar.load(src.getScalar0To1(),dst);
  }
  public static Scalar0To1Data unload(SEScalar0To1 src)
  {
    if(!src.isValid())
      return null;
    Scalar0To1Data.Builder dst = Scalar0To1Data.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalar0To1 src, Scalar0To1Data.Builder dst)
  {
    SEScalar.unload(src,dst.getScalar0To1Builder());
  }

  public boolean validUnit(String unit)
  {
    if(unit==null||unit.isEmpty()||unit.compareTo("unitless") == 0)
      return true;
    return false;
  }
  
  public void setValue(double d)
  {
    if(d>1)
    {
      d=1;
      Log.warn("Attempting to set 0-1 Scalar to greater than 1, bounding to 1");
    }
    else if(d<0)
    {
      d=0;
      Log.warn("Attempting to set 0-1 Scalar to less than 0, bounding to 0");
    }
    this.value = d;
  }
}
