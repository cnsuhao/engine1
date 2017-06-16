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
