/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarAmountPerVolumeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.AmountPerVolumeUnit;

/**
 * @author abray
 * AmountPerVolume Scalar Class, will enforce that units are proper to AmountPerVolumes
 */

public class SEScalarAmountPerVolume extends SEScalar
{
  public SEScalarAmountPerVolume()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarAmountPerVolume(double value, String unit)
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
  public SEScalarAmountPerVolume(double value, AmountPerVolumeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarAmountPerVolumeData src, SEScalarAmountPerVolume dst)
  {
    SEScalar.load(src.getScalarAmountPerVolume(),dst);
  }
  public static ScalarAmountPerVolumeData unload(SEScalarAmountPerVolume src)
  {
    if(!src.isValid())
      return null;
    ScalarAmountPerVolumeData.Builder dst = ScalarAmountPerVolumeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarAmountPerVolume src, ScalarAmountPerVolumeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarAmountPerVolumeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, AmountPerVolumeUnit unit)
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
  public double getValue(AmountPerVolumeUnit unit)
  {
    return this.getValue(unit.toString());
  }
  
  public boolean validUnit(String unit)
  {
    if(AmountPerVolumeUnit.validUnit(unit))
      return true;
    return false;
  }
}
