/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarLengthPerTimeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.LengthPerTimeUnit;

/**
 * @author abray
 * LengthPerTime Scalar Class, will enforce that units are proper to LengthPerTimes
 */

public class SEScalarLengthPerTime extends SEScalar
{
  public SEScalarLengthPerTime()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarLengthPerTime(double value, String unit)
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
  public SEScalarLengthPerTime(double value, LengthPerTimeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }

  public static void load(ScalarLengthPerTimeData src, SEScalarLengthPerTime dst)
  {
    SEScalar.load(src.getScalarLengthPerTime(),dst);
  }
  public static ScalarLengthPerTimeData unload(SEScalarLengthPerTime src)
  {
    if(!src.isValid())
      return null;
    ScalarLengthPerTimeData.Builder dst = ScalarLengthPerTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarLengthPerTime src, ScalarLengthPerTimeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarLengthPerTimeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, LengthPerTimeUnit unit)
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
  public double getValue(LengthPerTimeUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(LengthPerTimeUnit.validUnit(unit))
      return true;
    return false;
  }
}
