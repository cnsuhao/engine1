/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarMassPerTimeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerTimeUnit;

/**
 * @author abray
 * MassPerTime Scalar Class, will enforce that units are proper to MassPerTimes
 */

public class SEScalarMassPerTime extends SEScalar
{
  public SEScalarMassPerTime()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarMassPerTime(double value, String unit)
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
  public SEScalarMassPerTime(double value, MassPerTimeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
 
  public static void load(ScalarMassPerTimeData src, SEScalarMassPerTime dst)
  {
    SEScalar.load(src.getScalarMassPerTime(),dst);
  }
  public static ScalarMassPerTimeData unload(SEScalarMassPerTime src)
  {
    if(!src.isValid())
      return null;
    ScalarMassPerTimeData.Builder dst = ScalarMassPerTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarMassPerTime src, ScalarMassPerTimeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarMassPerTimeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, MassPerTimeUnit unit)
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
  public double getValue(MassPerTimeUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(MassPerTimeUnit.validUnit(unit))
      return true;
    return false;
  }
}
