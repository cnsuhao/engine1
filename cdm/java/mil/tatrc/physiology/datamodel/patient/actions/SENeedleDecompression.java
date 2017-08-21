/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.NeedleDecompressionData;
import com.kitware.physiology.cdm.Properties.eSide;
import com.kitware.physiology.cdm.Properties.eSwitch;

public class SENeedleDecompression extends SEPatientAction
{
  protected eSwitch state;
  protected eSide side;
  
  public SENeedleDecompression()
  {
    state = eSwitch.Off;
    side = null;
  }
  
  public void copy(SENeedleDecompression other)
  {
    if(this==other)
      return;
    super.copy(other);
    state = other.state;
    side = other.side;
  }
  
  public void reset()
  {
    super.reset();
    state = eSwitch.Off;
    side = null;
  }
  
  public boolean isValid()
  {
    return hasSide();
  }
  
  public static void load(NeedleDecompressionData src, SENeedleDecompression dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.getState()!=eSwitch.UNRECOGNIZED && src.getState()!=eSwitch.NullSwitch)
    	dst.state = src.getState();
    if(src.getSide()!=eSide.UNRECOGNIZED)
    	dst.side = src.getSide();
  }
  
  public static NeedleDecompressionData unload(SENeedleDecompression src)
  {
    NeedleDecompressionData.Builder dst = NeedleDecompressionData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SENeedleDecompression src, NeedleDecompressionData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    dst.setState(src.state);
    if (src.hasSide())
      dst.setSide(src.side);
  }
  
  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch s)
  {
  	this.state = (s==eSwitch.NullSwitch) ? eSwitch.Off : s;
  }
  
  public eSide getSide()
  {
    return side;
  }
  
  public void setSide(eSide rightOrLeft)
  {
    side = rightOrLeft;
  }
  
  public boolean hasSide()
  {
    return side == null ? false : true;
  }
  
  public String toString()
  {
    return "Needle Decompression"
        + "\n\tState: " + getState()
        + "\n\tSide: " + getSide();
  }
}
