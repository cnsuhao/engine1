/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarMassPerMassData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerMassUnit;

/**
 * @author abray
 * MassPerMass Scalar Class, will enforce that units are proper to MassPerMasss
 */

public class SEScalarMassPerMass extends SEScalar
{
  public SEScalarMassPerMass()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarMassPerMass(double value, String unit)
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
  public SEScalarMassPerMass(double value, MassPerMassUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarMassPerMassData src, SEScalarMassPerMass dst)
  {
    SEScalar.load(src.getScalarMassPerMass(),dst);
  }
  public static ScalarMassPerMassData unload(SEScalarMassPerMass src)
  {
    if(!src.isValid())
      return null;
    ScalarMassPerMassData.Builder dst = ScalarMassPerMassData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarMassPerMass src, ScalarMassPerMassData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarMassPerMassBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, MassPerMassUnit unit)
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
  public double getValue(MassPerMassUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(MassPerMassUnit.validUnit(unit))
      return true;
    return false;
  }
}
