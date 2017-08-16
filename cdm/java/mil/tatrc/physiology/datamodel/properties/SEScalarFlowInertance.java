/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarFlowInertanceData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.FlowInertanceUnit;

/**
 * @author abray
 * FlowInertance Scalar Class, will enforce that units are proper to FlowInertances
 */

public class SEScalarFlowInertance extends SEScalar
{
  public SEScalarFlowInertance()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarFlowInertance(double value, String unit)
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
  public SEScalarFlowInertance(double value, FlowInertanceUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarFlowInertanceData src, SEScalarFlowInertance dst)
  {
    SEScalar.load(src.getScalarFlowInertance(),dst);
  }
  public static ScalarFlowInertanceData unload(SEScalarFlowInertance src)
  {
    if(!src.isValid())
      return null;
    ScalarFlowInertanceData.Builder dst = ScalarFlowInertanceData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarFlowInertance src, ScalarFlowInertanceData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarFlowInertanceBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, FlowInertanceUnit unit)
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
  public double getValue(FlowInertanceUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(FlowInertanceUnit.validUnit(unit))
      return true;
    return false;
  }
}
