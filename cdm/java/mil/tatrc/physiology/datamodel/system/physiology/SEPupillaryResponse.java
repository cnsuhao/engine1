/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.PupillaryResponseData;

import mil.tatrc.physiology.datamodel.properties.SEScalarNegative1To1;

public class SEPupillaryResponse
{
  protected SEScalarNegative1To1  reactivityModifier;
  protected SEScalarNegative1To1  shapeModifier;
  protected SEScalarNegative1To1  sizeModifier;
  
  public SEPupillaryResponse()
  {
    reactivityModifier = null;
    shapeModifier = null;
    sizeModifier = null;
  }

  public void reset()
  {
    if (reactivityModifier != null)
      reactivityModifier.invalidate();
    if (shapeModifier != null)
      shapeModifier.invalidate();
    if (sizeModifier != null)
      sizeModifier.invalidate();
  }

  public static void load(PupillaryResponseData src, SEPupillaryResponse dst)
  {
    dst.reset();
    if (src.hasReactivityModifier())
      SEScalarNegative1To1.load(src.getReactivityModifier(),dst.getReactivityModifier());
    if (src.hasShapeModifier())
      SEScalarNegative1To1.load(src.getShapeModifier(),dst.getShapeModifier());
    if (src.hasSizeModifier())
      SEScalarNegative1To1.load(src.getSizeModifier(),dst.getSizeModifier());    
  }

  public static PupillaryResponseData unload(SEPupillaryResponse src)
  {
    PupillaryResponseData.Builder dst = PupillaryResponseData.newBuilder();
    SEPupillaryResponse.unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEPupillaryResponse src, PupillaryResponseData.Builder dst)
  {
    if (src.reactivityModifier != null)
      dst.setReactivityModifier(SEScalarNegative1To1.unload(src.reactivityModifier));
    if (src.shapeModifier != null)
      dst.setShapeModifier(SEScalarNegative1To1.unload(src.shapeModifier));
    if (src.sizeModifier != null)
      dst.setSizeModifier(SEScalarNegative1To1.unload(src.sizeModifier));    
  }
  
  public SEScalarNegative1To1 getReactivityModifier()
  {
    if (reactivityModifier == null)
      reactivityModifier = new SEScalarNegative1To1();
    return reactivityModifier;
  }
  public boolean hasReactivityModifier()
  {
    return reactivityModifier == null ? false : reactivityModifier.isValid();
  }
  
  public SEScalarNegative1To1 getShapeModifier()
  {
    if (shapeModifier == null)
      shapeModifier = new SEScalarNegative1To1();
    return shapeModifier;
  }
  public boolean hasShapeModifier()
  {
    return shapeModifier == null ? false : shapeModifier.isValid();
  }
  
  public SEScalarNegative1To1 getSizeModifier()
  {
    if (sizeModifier == null)
      sizeModifier = new SEScalarNegative1To1();
    return sizeModifier;
  }
  public boolean hasSizeModifier()
  {
    return sizeModifier == null ? false : sizeModifier.isValid();
  }
}
