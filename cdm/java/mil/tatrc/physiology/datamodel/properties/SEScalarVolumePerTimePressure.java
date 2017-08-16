/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarVolumePerTimePressureData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumePerTimePressureUnit;

/**
 * @author abray
 * VolumePerTimePerPressure Scalar Class, will enforce that units are proper to VolumePerTimePerPressures
 */

public class SEScalarVolumePerTimePressure extends SEScalar
{
  public SEScalarVolumePerTimePressure()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarVolumePerTimePressure(double value, String unit)
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
  public SEScalarVolumePerTimePressure(double value, VolumePerTimePressureUnit unit)
  {
    this();
    this.setValue(value,unit);
  }

  public static void load(ScalarVolumePerTimePressureData src, SEScalarVolumePerTimePressure dst)
  {
    SEScalar.load(src.getScalarVolumePerTimePressure(),dst);
  }
  public static ScalarVolumePerTimePressureData unload(SEScalarVolumePerTimePressure src)
  {
    if(!src.isValid())
      return null;
    ScalarVolumePerTimePressureData.Builder dst = ScalarVolumePerTimePressureData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarVolumePerTimePressure src, ScalarVolumePerTimePressureData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarVolumePerTimePressureBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, VolumePerTimePressureUnit unit)
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
  public double getValue(VolumePerTimePressureUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(VolumePerTimePressureUnit.validUnit(unit))
      return true;
    return false;
  }
}
