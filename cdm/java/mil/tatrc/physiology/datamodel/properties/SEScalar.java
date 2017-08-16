/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import java.lang.reflect.Method;
import java.math.BigDecimal;

import com.kitware.physiology.cdm.Properties.ScalarData;

import mil.tatrc.physiology.datamodel.SEEqualOptions;
import mil.tatrc.physiology.datamodel.exceptions.InvalidUnitException;
import mil.tatrc.physiology.utilities.DoubleUtils;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.UnitConverter;

/**
 * @author abray
 *
 */
public class SEScalar
{
  protected String             unit;
  protected double             value;
  protected int                precision=-1;
  
  public SEScalar()
  {
    super();
    invalidate();
  }
  
  public SEScalar(double val)
  {
    super();
    invalidate();
    unit="";
    value=val;
  }

  public boolean set(SEScalar s)
  {
    if (s == null || !s.isValid())
      return false;
    this.invalidate();
  
    this.unit = s.unit;
    this.value = s.value;
    this.precision = s.precision;
    
    return true;
  }

  public static void load(ScalarData src, SEScalar dest)
  {
    if (src == null)
      return;
    if(src.getUnit()!=null)
      dest.setValue(src.getValue(),src.getUnit());
    else
      dest.setValue(src.getValue());
  }
  public static ScalarData unload(SEScalar src)
  {
    if(!src.isValid())
      return null;
    ScalarData.Builder dst = ScalarData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEScalar src, ScalarData.Builder dst)
  {
    if(!src.unit.equals(""))
      dst.setUnit(src.unit);
    if(src.precision!=-1)
    {
      BigDecimal d = new BigDecimal(src.value);
      dst.setValue(Double.valueOf(d.setScale(3, BigDecimal.ROUND_CEILING).toString()));
    }
    else
      dst.setValue(src.value); 
  }

  public boolean equals(Object other)
  {
    if ((other == null) || !(SEScalar.class.isAssignableFrom(this.getClass())))
      return false;
  
    return SEScalar.equals(this, (SEScalar) other, null);
  }
  
  public static boolean equals(SEScalar from, SEScalar to)
  {
    return equals(from, to, null);
  }
  
  public static boolean equals(SEScalar from, SEScalar to, SEEqualOptions options)
  {
    return equals(from, to, options, null);
  }

  public static boolean equals(SEScalar from, SEScalar to, SEEqualOptions options, String name)
  {
    if (options != null)
    {
      if (name == null)
        name = "SEScalar";
      options.pushTrack(name);
    }
    boolean equals=true;
    if(!equals(from.value, from.unit, to.value, to.unit, options))
    {
      if (options != null)
        options.track(name, from.value, from.unit, to.value, to.unit);
      equals=false;
    }
    if(options != null)
      options.trackToMap();
    return equals;
  }
  
  public static boolean equals(double fValue, double tValue)
  {
    return equals(fValue, tValue, null);
  }
  // Tolerance is a percentage, not a decimal value
  public static boolean equals(double fValue, double tValue, DoubleUtils opts)
  {
    return equals(fValue,"",tValue,"", opts);
  }
  public static boolean equals(double fValue, String fUnit, double tValue, String tUnit)
  {
    return equals(fValue,fUnit,tValue,tUnit,null);
  }
  public static boolean equals(double fValue, String fUnit, double tValue, String tUnit, DoubleUtils options)
  {
    if (!DoubleUtils.equals(fValue, fUnit, tValue, tUnit, options))
      return false;
    return true;
  }
  public int hashCode()
  {
    int result = 1;

    long bits = Double.doubleToLongBits(this.value);
    result += this.unit.hashCode();
    result += (int)(bits^(bits >>> 32));

    return result;
  }
  
  /**
   * Set the amount of precision when converting to a string
   * @param p
   * @return
   */
  public void setPrecision(int p)
  {
    this.precision=p;
  }
  
  public int getPrecision()
  {
    return this.precision;
  }
  
  public void truncate(int mantissaLength)
  {
    this.value=DoubleUtils.truncate(this.value,mantissaLength);
  }
  
  public boolean isValid()
  {
    if(Double.isNaN(this.value))
      return false;
    if (!this.validUnit(this.unit))
      return false;
    return true;
  }

  public void invalidate()
  {
    this.unit="";
    this.value=Double.NaN;
    this.precision=-1;
  }

  public boolean validUnit(String unit)
  {
    return true;
  }

  public String getUnit()
  {
    return this.unit;
  }
  
  public double getValue()
  {
    if(Double.isNaN(this.value))
      Log.error("SEScalar Returning NaN from getValue()");
    return this.value;
  }

  public double getValue(String unit)
  {
    if(unit==null)
      return getValue();
    // Can't translate what we don't have
    if(Double.isNaN(this.value))
      return this.value;
    if (unit.equals(this.unit))
      return this.value;

    if (!validUnit(unit))
    {
      Log.error("Returning NaN");
      return Double.NaN;
    }
    return UnitConverter.convert(value, this.unit, unit);
  }

  public void setValue(double val)
  {
    if(this.validUnit(""))
    {
      this.unit = "";
      this.value = val;
    }
    else
    {
      this.unit = "";
      this.value = Double.NaN;
      Log.error("Unit not provided on derived scalar type "+this.getClass());
      throw new InvalidUnitException(unit,this.getClass().getName());
    }
  }
  
  public void setValue(double val, int precision)
  {
    this.precision=precision;
    this.setValue(val);
  }

  public void setValue(double val, String unit)
  {
    if (Double.isNaN(val) || validUnit(unit))
    {// Don't care what the unit is if we are NaN, it's probably not good anyway
      if(unit==null)// NaN check is from if you request an unsupported compartment, you don't get a unit back
        this.unit="";
      else
        this.unit = unit;
      this.value = val;
    }
    else 
    {
      this.unit="";
      this.value=Double.NaN;
      throw new InvalidUnitException(unit,this.getClass().getName());
    }
  }
  
  public void setValue(double val, String unit, int precision)
  {
    this.precision=precision;
    this.setValue(val,unit);
  }
  
  public String toString()
  {
    return this.value+this.unit;
  }
  
  public static String toString(ScalarData data)
  {
    return data.getValue()+data.getUnit();
  }
  
  public static SEScalar getScalar(Object object, String name)
  {    
    try
    {
      for(Method m : object.getClass().getMethods())
      {
        if(m.getName().startsWith("get") && m.getParameterCount()==0)
        {
          if(SEScalar.class.isAssignableFrom(m.getReturnType()))
          {
            if(m.getName().substring(3).equals(name))
              return (SEScalar)m.invoke(object);
          }
          else if(m.getReturnType().getSimpleName().startsWith("SE"))
          {
            SEScalar s = getScalar(m.invoke(object),name);
            if(s!=null)
              return s;
          }
        }
      }
    }
    catch (Exception ex)
    {
      
    }
    return null;
  }
}
