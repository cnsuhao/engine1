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

import com.kitware.physiology.cdm.Properties.ScalarOsmolalityData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.OsmolalityUnit;

/**
 * @author abray
 * Osmolality Scalar Class, will enforce that units are proper to Osmolality
 */

public class SEScalarOsmolality extends SEScalar
{
  public SEScalarOsmolality()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarOsmolality(double value, String unit)
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
  public SEScalarOsmolality(double value, OsmolalityUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarOsmolalityData src, SEScalarOsmolality dst)
  {
    SEScalar.load(src.getScalarOsmolality(),dst);
  }
  public static ScalarOsmolalityData unload(SEScalarOsmolality src)
  {
    if(!src.isValid())
      return null;
    ScalarOsmolalityData.Builder dst = ScalarOsmolalityData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarOsmolality src, ScalarOsmolalityData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarOsmolalityBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, OsmolalityUnit unit)
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
  public double getValue(OsmolalityUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(OsmolalityUnit.validUnit(unit))
      return true;
    return false;
  }
}
