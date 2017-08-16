/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarVolumePerTimeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumePerTimeUnit;

/**
 * @author abray
 * VolumePerTime Scalar Class, will enforce that units are proper to VolumePerTimes
 */

public class SEScalarVolumePerTime extends SEScalar
{
  public SEScalarVolumePerTime()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarVolumePerTime(double value, String unit)
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
  public SEScalarVolumePerTime(double value, VolumePerTimeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }

  public static void load(ScalarVolumePerTimeData src, SEScalarVolumePerTime dst)
  {
    SEScalar.load(src.getScalarVolumePerTime(),dst);
  }
  public static ScalarVolumePerTimeData unload(SEScalarVolumePerTime src)
  {
    if(!src.isValid())
      return null;
    ScalarVolumePerTimeData.Builder dst = ScalarVolumePerTimeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarVolumePerTime src, ScalarVolumePerTimeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarVolumePerTimeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, VolumePerTimeUnit unit)
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
  public double getValue(VolumePerTimeUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(VolumePerTimeUnit.validUnit(unit))
      return true;
    return false;
  }
}
