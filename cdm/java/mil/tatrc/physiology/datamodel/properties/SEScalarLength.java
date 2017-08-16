/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarLengthData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.LengthUnit;

/**
 * @author abray
 * Length Scalar Class, will enforce that units are proper to Lengths
 */

public class SEScalarLength extends SEScalar
{
  public SEScalarLength()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarLength(double value, String unit)
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
  public SEScalarLength(double value, LengthUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarLengthData src, SEScalarLength dst)
  {
    SEScalar.load(src.getScalarLength(),dst);
  }
  public static ScalarLengthData unload(SEScalarLength src)
  {
    if(!src.isValid())
      return null;
    ScalarLengthData.Builder dst = ScalarLengthData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarLength src, ScalarLengthData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarLengthBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, LengthUnit unit)
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
  public double getValue(LengthUnit unit)
  {
    return this.getValue(unit.toString());
  }
  
  public boolean validUnit(String unit)
  {
    if(LengthUnit.validUnit(unit))
      return true;
    return false;
  }
}
