/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarPressurePerVolumeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.PressurePerVolumeUnit;

/**
 * @author abray
 * Pressure Scalar Class, will enforce that units are proper to Pressures
 */

public class SEScalarPressurePerVolume extends SEScalar
{
  public SEScalarPressurePerVolume()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarPressurePerVolume(double value, String unit)
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
  public SEScalarPressurePerVolume(double value, PressurePerVolumeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarPressurePerVolumeData src, SEScalarPressurePerVolume dst)
  {
    SEScalar.load(src.getScalarPressurePerVolume(),dst);
  }
  public static ScalarPressurePerVolumeData unload(SEScalarPressurePerVolume src)
  {
    if(!src.isValid())
      return null;
    ScalarPressurePerVolumeData.Builder dst = ScalarPressurePerVolumeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarPressurePerVolume src, ScalarPressurePerVolumeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarPressurePerVolumeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, PressurePerVolumeUnit unit)
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
  public double getValue(PressurePerVolumeUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(PressurePerVolumeUnit.validUnit(unit))
      return true;
    return false;
  }
}
