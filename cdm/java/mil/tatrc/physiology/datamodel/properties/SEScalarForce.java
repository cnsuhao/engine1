/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarForceData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.ForceUnit;

/**
 * @author abray
 * Force Scalar Class, will enforce that units are proper to Forces
 */

public class SEScalarForce extends SEScalar
{
  public SEScalarForce()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarForce(double value, String unit)
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
  public SEScalarForce(double value, ForceUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarForceData src, SEScalarForce dst)
  {
    SEScalar.load(src.getScalarForce(),dst);
  }
  public static ScalarForceData unload(SEScalarForce src)
  {
    if(!src.isValid())
      return null;
    ScalarForceData.Builder dst = ScalarForceData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarForce src, ScalarForceData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarForceBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, ForceUnit unit)
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
  public double getValue(ForceUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(ForceUnit.validUnit(unit))
      return true;
    return false;
  }
}
