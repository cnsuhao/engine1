/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarHeatResistanceAreaData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.HeatResistanceAreaUnit;

/**
 * @author abray
 * HeatResistanceArea Scalar Class, will enforce that units are proper to HeatResistanceAreas
 */

public class SEScalarHeatResistanceArea extends SEScalar
{
  public SEScalarHeatResistanceArea()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarHeatResistanceArea(double value, String unit)
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
  public SEScalarHeatResistanceArea(double value, HeatResistanceAreaUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarHeatResistanceAreaData src, SEScalarHeatResistanceArea dst)
  {
    SEScalar.load(src.getScalarHeatResistanceArea(),dst);
  }
  public static ScalarHeatResistanceAreaData unload(SEScalarHeatResistanceArea src)
  {
    if(!src.isValid())
      return null;
    ScalarHeatResistanceAreaData.Builder dst = ScalarHeatResistanceAreaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarHeatResistanceArea src, ScalarHeatResistanceAreaData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarHeatResistanceAreaBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, HeatResistanceAreaUnit unit)
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
  public double getValue(HeatResistanceAreaUnit unit)
  {
    return this.getValue(unit.toString());
  }
  
  public boolean validUnit(String unit)
  {
    if(HeatResistanceAreaUnit.validUnit(unit))
      return true;
    return false;
  }
}
