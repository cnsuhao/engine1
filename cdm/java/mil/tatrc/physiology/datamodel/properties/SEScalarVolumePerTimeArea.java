/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarVolumePerTimeAreaData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.VolumePerTimeAreaUnit;

/**
 * @author abray
 * VolumePerTimePerArea Scalar Class, will enVolumePerTimePerArea that units are proper to VolumePerTimePerAreas
 */

public class SEScalarVolumePerTimeArea extends SEScalar
{
  public SEScalarVolumePerTimeArea()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarVolumePerTimeArea(double value, String unit)
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
  public SEScalarVolumePerTimeArea(double value, VolumePerTimeAreaUnit unit)
  {
    this();
    this.setValue(value,unit);
  }

  public static void load(ScalarVolumePerTimeAreaData src, SEScalarVolumePerTimeArea dst)
  {
    SEScalar.load(src.getScalarVolumePerTimeArea(),dst);
  }
  public static ScalarVolumePerTimeAreaData unload(SEScalarVolumePerTimeArea src)
  {
    if(!src.isValid())
      return null;
    ScalarVolumePerTimeAreaData.Builder dst = ScalarVolumePerTimeAreaData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarVolumePerTimeArea src, ScalarVolumePerTimeAreaData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarVolumePerTimeAreaBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, VolumePerTimeAreaUnit unit)
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
  public double getValue(VolumePerTimeAreaUnit unit)
  {
    return this.getValue(unit.toString());
  }

  public boolean validUnit(String unit)
  {
    if(VolumePerTimeAreaUnit.validUnit(unit))
      return true;
    return false;
  }
}
