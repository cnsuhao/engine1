/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarMassPerAreaTimeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerAreaTimeUnit;

/**
 * @author abray
 * MassPerAreaTime Scalar Class, will enforce that units are proper to MassPerAreaTimes
 */

public class SEScalarMassPerAreaTime extends SEScalar
{
  public SEScalarMassPerAreaTime()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarMassPerAreaTime(double value, String unit)
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
  public SEScalarMassPerAreaTime(double value, MassPerAreaTimeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarMassPerAreaTimeData src, SEScalarMassPerAreaTime dst)
  {
    SEScalar.load(src.getScalarMassPerAreaTime(),dst);
  }
  public static ScalarMassPerAreaTimeData unload(SEScalarMassPerAreaTime src)
  {
    if(!src.isValid())
      return null;
    ScalarMassPerAreaTimeData.Builder dst = ScalarMassPerAreaTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarMassPerAreaTime src, ScalarMassPerAreaTimeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarMassPerAreaTimeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, MassPerAreaTimeUnit unit)
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
  public double getValue(MassPerAreaTimeUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(MassPerAreaTimeUnit.validUnit(unit))
      return true;
    return false;
  }
}
