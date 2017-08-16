/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarFlowElastanceData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.FlowElastanceUnit;

/**
 * @author abray
 * FlowElastance Scalar Class, will enforce that units are proper to FlowElastances
 */

public class SEScalarFlowElastance extends SEScalar
{
  public SEScalarFlowElastance()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarFlowElastance(double value, String unit)
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
  public SEScalarFlowElastance(double value, FlowElastanceUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarFlowElastanceData src, SEScalarFlowElastance dst)
  {
    SEScalar.load(src.getScalarFlowElastance(),dst);
  }
  public static ScalarFlowElastanceData unload(SEScalarFlowElastance src)
  {
    if(!src.isValid())
      return null;
    ScalarFlowElastanceData.Builder dst = ScalarFlowElastanceData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarFlowElastance src, ScalarFlowElastanceData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarFlowElastanceBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, FlowElastanceUnit unit)
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
  public double getValue(FlowElastanceUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(FlowElastanceUnit.validUnit(unit))
      return true;
    return false;
  }
}
