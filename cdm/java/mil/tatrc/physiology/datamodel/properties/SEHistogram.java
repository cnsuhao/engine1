/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.HistogramData;

/**
 * @author abray
 */
public class SEHistogram extends SEFunction
{
  public SEHistogram()
  {
    super();
    invalidate();
  }
  
  public static void load(HistogramData src, SEHistogram dest)
  {
   SEFunction.load(src.getHistogram(), dest);
  }
  public static HistogramData unload(SEHistogram src)
  {
    if(!src.isValid())
      return null;
    HistogramData.Builder dst = HistogramData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEHistogram src, HistogramData.Builder dst)
  {
    SEFunction.unload(src,dst.getHistogramBuilder());
  }
  
  public boolean isValid()
  {
    if(this.dependent.length==0||this.independent.length==0)
      return false;
    if(this.dependent.length+1 != this.independent.length)
      return false;
    if(!isValidDependentUnit(this.dependentUnit))
      return false;
    if(!isValidIndependentUnit(this.independentUnit))
      return false;
    return true;
  }
}
