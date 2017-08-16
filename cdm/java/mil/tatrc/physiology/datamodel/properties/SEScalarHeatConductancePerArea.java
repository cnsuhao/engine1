/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarHeatConductancePerAreaData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.HeatConductancePerAreaUnit;

/**
 * @author abray
 * HeatConductancePerArea Scalar Class, will enforce that units are proper to HeatConductancePerAreas
 */

public class SEScalarHeatConductancePerArea extends SEScalar
{
  public SEScalarHeatConductancePerArea()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarHeatConductancePerArea(double value, String unit)
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
  public SEScalarHeatConductancePerArea(double value, HeatConductancePerAreaUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarHeatConductancePerAreaData src, SEScalarHeatConductancePerArea dst)
  {
    SEScalar.load(src.getScalarHeatConductancePerArea(),dst);
  }
  public static ScalarHeatConductancePerAreaData unload(SEScalarHeatConductancePerArea src)
  {
    if(!src.isValid())
      return null;
    ScalarHeatConductancePerAreaData.Builder dst = ScalarHeatConductancePerAreaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarHeatConductancePerArea src, ScalarHeatConductancePerAreaData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarHeatConductancePerAreaBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, HeatConductancePerAreaUnit unit)
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
  public double getValue(HeatConductancePerAreaUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(HeatConductancePerAreaUnit.validUnit(unit))
      return true;
    return false;
  }
}
