/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarAmountPerMassData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.AmountPerMassUnit;

/**
 * @author abray
 * AmountPerMass Scalar Class, will enforce that units are proper to AmountPerMasss
 */

public class SEScalarAmountPerMass extends SEScalar
{
  public SEScalarAmountPerMass()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarAmountPerMass(double value, String unit)
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
  public SEScalarAmountPerMass(double value, AmountPerMassUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarAmountPerMassData src, SEScalarAmountPerMass dst)
  {
    SEScalar.load(src.getScalarAmountPerMass(),dst);
  }
  public static ScalarAmountPerMassData unload(SEScalarAmountPerMass src)
  {
    if(!src.isValid())
      return null;
    ScalarAmountPerMassData.Builder dst = ScalarAmountPerMassData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarAmountPerMass src, ScalarAmountPerMassData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarAmountPerMassBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, AmountPerMassUnit unit)
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
  public double getValue(AmountPerMassUnit unit)
  {
    return this.getValue(unit.toString());
  }
  
  public boolean validUnit(String unit)
  {
    if(AmountPerMassUnit.validUnit(unit))
      return true;
    return false;
  }
}
