/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import java.util.ArrayList;
import java.util.Arrays;

import org.jfree.util.Log;

import com.google.protobuf.Internal.DoubleList;
import com.kitware.physiology.cdm.Properties.ArrayData;
import com.kitware.physiology.cdm.Properties.DoubleArrayData;
import com.kitware.physiology.cdm.Properties.DoubleArrayData.Builder;
import com.kitware.physiology.cdm.Properties.FunctionData;

import mil.tatrc.physiology.datamodel.SEEqualOptions;
import mil.tatrc.physiology.datamodel.exceptions.InvalidUnitException;
import mil.tatrc.physiology.utilities.DoubleUtils;
import mil.tatrc.physiology.utilities.StringUtils;
import mil.tatrc.physiology.utilities.UnitConverter;

/**
 * @author abray
 */
public class SEFunction
{
  protected double[] dependent;
  protected double[] independent;
  protected String   dependentUnit;
  protected String   independentUnit;

  public SEFunction()
  {
    super();
    invalidate();
  }

  public boolean set(SEFunction ary)
  {
    if(!ary.isValid())
      return false;
    this.dependentUnit = ary.dependentUnit;
    this.dependent = Arrays.copyOf(ary.dependent,ary.dependent.length);
    this.independentUnit = ary.independentUnit;
    this.independent = Arrays.copyOf(ary.independent,ary.independent.length);
    return true;
  }
  
  public int hashCode()
  {
    int code=1;
    if(!this.isValid())
      return 1;
    code += this.dependent.hashCode();
    code += this.independent.hashCode();
    code += this.dependentUnit.hashCode();
    code += this.independentUnit.hashCode();
    return code;
  }

  public static void load(FunctionData src, SEFunction dest)
  {
    if (src == null)
      return;
    dest.setDependent(SEArray.toArray(src.getDependent().getValueList()),src.getDependentUnit());
    dest.setIndependent(SEArray.toArray(src.getIndependent().getValueList()),src.getIndependentUnit());
    if(!dest.isValid())
      Log.error("Invalid function has been loaded");
  }
  public static FunctionData unload(SEFunction src)
  {
    if(!src.isValid())
      return null;
    FunctionData.Builder dst = FunctionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEFunction src, FunctionData.Builder dst)
  {
    dst.setDependentUnit(src.dependentUnit);
    SEArray.toData(dst.getDependentBuilder(),src.dependent);
    
    dst.setIndependentUnit(src.independentUnit);
    SEArray.toData(dst.getIndependentBuilder(),src.independent);
  }
  
  public boolean isValid()
  {
    if(this.dependent.length==0||this.independent.length==0)
      return false;
    if(this.dependent.length != this.independent.length)
      return false;
    if(!isValidDependentUnit(this.dependentUnit))
      return false;
    if(!isValidIndependentUnit(this.independentUnit))
      return false;
    return true;
  }
  
  public boolean isValidDependentUnit(String unit)
  {
    return true;
  }
  
  public boolean isValidIndependentUnit(String unit)
  {
    return true;
  }
  
  public void invalidate()
  {
    this.dependent = new double[0];
    this.independent = new double[0];
    this.dependentUnit="";
    this.independentUnit="";
  }

  public boolean equals(Object to)
  {
    if ((to == null) || !(to instanceof SEFunction))
    {
      return false;
    }

    return SEFunction.equals(this, (SEFunction) to, null);
  }

  public boolean equals(SEFunction to, SEEqualOptions options)
  {
    return SEFunction.equals(this, to, options);
  }

  public static boolean equals(SEFunction from, SEFunction to)
  {
    return SEFunction.equals(from, to, null);
  }
  
  public static boolean equals(SEFunction from, SEFunction to, SEEqualOptions options)
  {
    return equals(from, to, options, null);
  }

  public static boolean equals(SEFunction from, SEFunction to, SEEqualOptions options, String name)
  {
    if (from == to)
      return true;
    if (to == null && from != null && !from.isValid())
      return true;
    if (from == null && to != null && !to.isValid())
      return true;

    boolean forceReturn = true;
    if (options != null)
    {
      if (name == null)
        name = "SEFunction";
      options.pushTrack(name);
      forceReturn = options.returnOnFirstDiff;
    }

    if (from == null || to == null)
    {
      if (options != null)
      {
        options.track(name, from, to);
        options.trackToMap();
      }
      return false;
    }
    if (!from.isValid() && !to.isValid())
    {
      if(options != null)
        options.trackToMap();
      return true;
    }
    if((from.isValid()&&!to.isValid())||(!from.isValid()&&to.isValid()))
    {
      if(options!=null)
      {
        options.trackInvalid(name.toString(),from,to);
        options.trackToMap();
      }
     return false; 
    }

    boolean equals = true;
    if (!SEArray.equals(from.dependent, from.dependentUnit, to.dependent, to.dependentUnit, options, "Dependent"))
    {
      if (forceReturn)
      {
        if(options!=null)
          options.trackToMap();
        return false;
      }
      equals = false;
    }

    if (!SEArray.equals(from.independent, from.independentUnit, to.independent, to.independentUnit, options, "Independent"))
    {
      if (forceReturn)
      {
        if(options!=null)
          options.trackToMap();
        return false;
      }
      equals = false;
    }

    if (options != null)
      options.trackToMap();
    return equals;
  }
  
  public int length()
  {
    return this.independent.length;
  }
  
  public String getDependentUnit()
  {
    return this.dependentUnit;
  }
  
  public String getIndependentUnit()
  {
    return this.independentUnit;
  }

  public double[] getDependent()
  {
    return this.dependent;
  }
  
  public double[] getDependent(String unit)
  {
    if(!isValidDependentUnit(unit))
      throw new InvalidUnitException(unit, "Dependent");
    if(this.dependentUnit.equals(unit))
      return this.dependent;
    return UnitConverter.convert(dependent, dependentUnit, unit);
  }
  
  public String getDependentString()
  {
    return StringUtils.toString(this.dependent);
  }
  
  public String getDependentString(String unit)
  {
    if(!isValidDependentUnit(unit))
      throw new InvalidUnitException(unit, "Dependent");
    if(this.dependentUnit.equals(unit))
      return StringUtils.toString(this.dependent);
    double[]d=UnitConverter.convert(dependent, dependentUnit, unit);
    return StringUtils.toString(d);
  }
  
  public void setDependent(double[] data)
  {
    if(!isValidDependentUnit(""))
      throw new InvalidUnitException("no unit", "Dependent");
    this.dependent=data;
    this.dependentUnit="";
  }
  
  public void setDependent(double[] data, String unit)
  {
    if(!isValidDependentUnit(unit))
      throw new InvalidUnitException(unit, "Dependent");
    this.dependent=data;
    this.dependentUnit=unit;
  }

  public void setDependent(String data)
  {
    if(!isValidDependentUnit(""))
      throw new InvalidUnitException("no unit", "Dependent");
    this.dependent=StringUtils.toArray(data);
    this.dependentUnit="";
  }
  
  public void setDependent(String data, String unit)
  {
    if(!isValidDependentUnit(unit))
      throw new InvalidUnitException(unit, "Dependent");
    this.dependent=StringUtils.toArray(data);
    this.dependentUnit=unit;
  }
  
  public double[] getIndependent()
  {
    return this.independent;
  }
  
  public double[] getIndependent(String unit)
  {
    if(!isValidIndependentUnit(unit))
      throw new InvalidUnitException(unit, "Independent");
    if(this.independentUnit.equals(unit))
      return this.independent;
    return UnitConverter.convert(independent, independentUnit, unit);
  }
  
  public String getIndependentString()
  {
    return StringUtils.toString(this.independent);
  }
  
  public String getIndependentString(String unit)
  {
    if(!isValidIndependentUnit(unit))
      throw new InvalidUnitException(unit, "Independent");
    if(this.independentUnit.equals(unit))
      return StringUtils.toString(this.independent);
    double[]d=UnitConverter.convert(independent, independentUnit, unit);
    return StringUtils.toString(d);
  }
  
  public void setIndependent(double[] data)
  {
    if(!isValidIndependentUnit(""))
      throw new InvalidUnitException("no unit", "Ordiate");
    this.independent=data;
    this.independentUnit="";
  }
  
  public void setIndependent(double[] data, String unit)
  {
    if(!isValidIndependentUnit(unit))
      throw new InvalidUnitException(unit, "Ordiate");
    this.independent=data;
    this.independentUnit=unit;
  }
  
  public void setIndependent(String data)
  {
    if(!isValidIndependentUnit(""))
      throw new InvalidUnitException("no unit", "Independent");
    this.independent=StringUtils.toArray(data);
    this.independentUnit="";
  }
  
  public void setIndependent(String data, String unit)
  {
    if(!isValidIndependentUnit(unit))
      throw new InvalidUnitException(unit, "Independent");
    this.independent=StringUtils.toArray(data);
    this.independentUnit=unit;
  }
}
