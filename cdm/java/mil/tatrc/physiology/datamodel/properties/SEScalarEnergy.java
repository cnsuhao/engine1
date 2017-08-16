/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarEnergyData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.EnergyUnit;

/**
 * @author abray
 * Energy Scalar Class, will enforce that units are proper to Energys
 */

public class SEScalarEnergy extends SEScalar
{
  public SEScalarEnergy()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarEnergy(double value, String unit)
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
  public SEScalarEnergy(double value, EnergyUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarEnergyData src, SEScalarEnergy dst)
  {
    SEScalar.load(src.getScalarEnergy(),dst);
  }
  public static ScalarEnergyData unload(SEScalarEnergy src)
  {
    if(!src.isValid())
      return null;
    ScalarEnergyData.Builder dst = ScalarEnergyData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarEnergy src, ScalarEnergyData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarEnergyBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, EnergyUnit unit)
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
  public double getValue(EnergyUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(EnergyUnit.validUnit(unit))
      return true;
    return false;
  }
}
