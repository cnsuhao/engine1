/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarOsmolarityData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.OsmolarityUnit;

/**
 * @author abray
 * Osmolarity Scalar Class, will enforce that units are proper to Osmolarity
 */

public class SEScalarOsmolarity extends SEScalar
{
  public SEScalarOsmolarity()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarOsmolarity(double value, String unit)
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
  public SEScalarOsmolarity(double value, OsmolarityUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarOsmolarityData src, SEScalarOsmolarity dst)
  {
    SEScalar.load(src.getScalarOsmolarity(),dst);
  }
  public static ScalarOsmolarityData unload(SEScalarOsmolarity src)
  {
    if(!src.isValid())
      return null;
    ScalarOsmolarityData.Builder dst = ScalarOsmolarityData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarOsmolarity src, ScalarOsmolarityData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarOsmolarityBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, OsmolarityUnit unit)
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
  public double getValue(OsmolarityUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(OsmolarityUnit.validUnit(unit))
      return true;
    return false;
  }
}
