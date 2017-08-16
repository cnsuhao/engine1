/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarAreaData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.AreaUnit;

/**
 * @author abray
 * Area Scalar Class, will enforce that units are proper to Areas
 */

public class SEScalarArea extends SEScalar
{
  public SEScalarArea()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarArea(double value, String unit)
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
  public SEScalarArea(double value, AreaUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarAreaData src, SEScalarArea dst)
  {
    SEScalar.load(src.getScalarArea(),dst);
  }
  public static ScalarAreaData unload(SEScalarArea src)
  {
    if(!src.isValid())
      return null;
    ScalarAreaData.Builder dst = ScalarAreaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarArea src, ScalarAreaData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarAreaBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, AreaUnit unit)
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
  public double getValue(AreaUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(AreaUnit.validUnit(unit))
      return true;
    return false;
  }
}
