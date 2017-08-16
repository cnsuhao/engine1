/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.conditions;

import com.kitware.physiology.cdm.PatientConditions.ImpairedAlveolarExchangeData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarArea;

public class SEImpairedAlveolarExchange extends SEPatientCondition
{
  protected SEScalarArea impairedSurfaceArea;
  protected SEScalar0To1 impairedFraction;
  
  public SEImpairedAlveolarExchange()
  {
    impairedSurfaceArea = null;
    impairedFraction = null;
  }
  
  public void copy(SEImpairedAlveolarExchange other)
  {
    if(this==other)
      return;
    super.copy(other);
    if (other.impairedSurfaceArea != null)
      getImpairedSurfaceArea().set(other.getImpairedSurfaceArea());
    else if (impairedSurfaceArea != null)
      impairedSurfaceArea.invalidate();
    if (other.impairedFraction != null)
      getImpairedFraction().set(other.getImpairedFraction());
    else if (impairedFraction != null)
      impairedFraction.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (impairedSurfaceArea != null)
      impairedSurfaceArea.invalidate();
    if (impairedFraction != null)
      impairedFraction.invalidate();
  }
  
  public boolean isValid()
  {
    return hasImpairedSurfaceArea() || hasImpairedFraction();
  }
  
  public static void load(ImpairedAlveolarExchangeData src, SEImpairedAlveolarExchange dst)
  {
    SEPatientCondition.load(src.getPatientCondition(), dst);
    if(src.hasImpairedSurfaceArea())
      SEScalarArea.load(src.getImpairedSurfaceArea(),dst.getImpairedSurfaceArea());
    if(src.hasImpairedFraction())
      SEScalar0To1.load(src.getImpairedFraction(),dst.getImpairedFraction());
  }
  
  public static ImpairedAlveolarExchangeData unload(SEImpairedAlveolarExchange src)
  {
    ImpairedAlveolarExchangeData.Builder dst = ImpairedAlveolarExchangeData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEImpairedAlveolarExchange src, ImpairedAlveolarExchangeData.Builder dst)
  {
    SEPatientCondition.unload(src, dst.getPatientConditionBuilder());
    if (src.hasImpairedSurfaceArea())
      dst.setImpairedSurfaceArea(SEScalarArea.unload(src.impairedSurfaceArea));
    if (src.hasImpairedFraction())
      dst.setImpairedFraction(SEScalar0To1.unload(src.impairedFraction));
  }
  
  public boolean hasImpairedSurfaceArea()
  {
    return impairedSurfaceArea == null ? false : impairedSurfaceArea.isValid();
  }
  public SEScalarArea getImpairedSurfaceArea()
  {
    if (impairedSurfaceArea == null)
      impairedSurfaceArea = new SEScalarArea();
    return impairedSurfaceArea;
  }
  
  public boolean hasImpairedFraction()
  {
    return impairedFraction == null ? false : impairedFraction.isValid();
  }
  public SEScalar0To1 getImpairedFraction()
  {
    if (impairedFraction == null)
      impairedFraction = new SEScalar0To1();
    return impairedFraction;
  }
  
  public String toString()
  {
    if (impairedFraction != null)
      return "ImpairedAlveolarExchange" 
          + "\n\tImpairedFraction: " + getImpairedFraction();
    else if (impairedSurfaceArea != null)
      return "ImpairedAlveolarExchange" 
          + "\n\tImpairedSurfaceArea: " + getImpairedSurfaceArea();
    else
      return "Action not specified properly";
  }
}
