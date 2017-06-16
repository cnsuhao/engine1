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

import com.kitware.physiology.cdm.Properties.ScalarMassPerAmountData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerAmountUnit;

/**
 * @author abray
 * MassPerAmount Scalar Class, will enforce that units are proper to MassPerAmountes
 */

public class SEScalarMassPerAmount extends SEScalar
{
  public SEScalarMassPerAmount()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarMassPerAmount(double value, String unit)
  {
    this();
    this.setValue(value, unit);
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public SEScalarMassPerAmount(double value, MassPerAmountUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarMassPerAmountData src, SEScalarMassPerAmount dst)
  {
    SEScalar.load(src.getScalarMassPerAmount(),dst);
  }
  public static ScalarMassPerAmountData unload(SEScalarMassPerAmount src)
  {
    if(!src.isValid())
      return null;
    ScalarMassPerAmountData.Builder dst = ScalarMassPerAmountData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarMassPerAmount src, ScalarMassPerAmountData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarMassPerAmountBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, MassPerAmountUnit unit)
  {
    this.setValue(value,unit.toString());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public double getValue(MassPerAmountUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(MassPerAmountUnit.validUnit(unit))
      return true;
    return false;
  }
}
