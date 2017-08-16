/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.ScalarMassPerVolumeData;

import mil.tatrc.physiology.datamodel.properties.CommonUnits.MassPerVolumeUnit;

/**
 * @author abray
 * MassPerVolume Scalar Class, will enforce that units are proper to MassPerVolumes
 */

public class SEScalarMassPerVolume extends SEScalar
{
  public SEScalarMassPerVolume()
  {
    super();
  }
  
  /**
   * @param value
   * @param unit - specific any valid standard unit abbreviation
   * http://www.bipm.org/en/si/ for this quantity type
   */
  public SEScalarMassPerVolume(double value, String unit)
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
  public SEScalarMassPerVolume(double value, MassPerVolumeUnit unit)
  {
    this();
    this.setValue(value,unit);
  }
  
  public static void load(ScalarMassPerVolumeData src, SEScalarMassPerVolume dst)
  {
    SEScalar.load(src.getScalarMassPerVolume(),dst);
  }
  public static ScalarMassPerVolumeData unload(SEScalarMassPerVolume src)
  {
    if(!src.isValid())
      return null;
    ScalarMassPerVolumeData.Builder dst = ScalarMassPerVolumeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalarMassPerVolume src, ScalarMassPerVolumeData.Builder dst)
  {
    SEScalar.unload(src,dst.getScalarMassPerVolumeBuilder());
  }
  
  /**
   * @param value
   * @param unit - enumeration of commonly used units for this type
   * Units are not limited to this set.
   * You can use the other method convention:(double,string)
   * and specify any valid standard unit abbreviation sting for this type
   * Unit Abbreviation Standards: http://www.bipm.org/en/si/
   */
  public void setValue(double value, MassPerVolumeUnit unit)
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
  public double getValue(MassPerVolumeUnit unit)
  {
    return this.getValue(unit.toString());
  }
  
  public boolean validUnit(String unit)
  {
    if(MassPerVolumeUnit.validUnit(unit))
      return true;
    return false;
  }
}
