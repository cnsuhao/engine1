/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarNegative1To1Data;

import mil.tatrc.physiology.utilities.Log;

/**
 * @author abray
 * 0To1 Scalar Class, will enforce that value is between 0 and 1 (inclusive)
 */

public class SEScalarNegative1To1 extends SEScalar
{
  public SEScalarNegative1To1()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarNegative1To1(double value)
  {
    this();
    this.setValue(value, "");
  }
  
  public static void load(ScalarNegative1To1Data src, SEScalarNegative1To1 dst)
  {
    SEScalar.load(src.getScalarNegative1To1(),dst);
  }
  public static ScalarNegative1To1Data unload(SEScalarNegative1To1 src)
  {
    if(!src.isValid())
      return null;
    ScalarNegative1To1Data.Builder dst = ScalarNegative1To1Data.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarNegative1To1 src, ScalarNegative1To1Data.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarNegative1To1Builder());
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
      Log.warn("Attempting to set [-1,1] Scalar to greater than 1, bounding to 1");
    }
    else if(d<-1)
    {
      d=-1;
      Log.warn("Attempting to set [-1,1] Scalar to less than -1, bounding to -1");
    }
    this.value = d;
  }
}
