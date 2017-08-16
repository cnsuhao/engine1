/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarVolumePerTimePressureAreaData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumePerTimePressureAreaUnit;

/**
 * @author abray
 * VolumePerTimePerArea Scalar Class, will enVolumePerTimePerArea that units are proper to VolumePerTimePerAreas
 */

public class SEScalarVolumePerTimePressureArea extends SEScalar
{
  public SEScalarVolumePerTimePressureArea()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarVolumePerTimePressureArea(double value, String unit)
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
  public SEScalarVolumePerTimePressureArea(double value, VolumePerTimePressureAreaUnit unit)
  {
    this();
    this.setValue(value,unit);
  }

  public static void load(ScalarVolumePerTimePressureAreaData src, SEScalarVolumePerTimePressureArea dst)
  {
    SEScalar.load(src.getScalarVolumePerTimePressureArea(),dst);
  }
  public static ScalarVolumePerTimePressureAreaData unload(SEScalarVolumePerTimePressureArea src)
  {
    if(!src.isValid())
      return null;
    ScalarVolumePerTimePressureAreaData.Builder dst = ScalarVolumePerTimePressureAreaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarVolumePerTimePressureArea src, ScalarVolumePerTimePressureAreaData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarVolumePerTimePressureAreaBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, VolumePerTimePressureAreaUnit unit)
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
  public double getValue(VolumePerTimePressureAreaUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(VolumePerTimePressureAreaUnit.validUnit(unit))
      return true;
    return false;
  }
}
