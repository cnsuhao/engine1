/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.compartment;

import java.util.*;

import com.kitware.physiology.cdm.Compartment.TissueCompartmentData;

import mil.tatrc.physiology.datamodel.properties.SEScalar;
import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarMassPerMass;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SETissueCompartment extends SECompartment
{
  protected SEScalarMassPerMass acidicPhospohlipidConcentration;  
  protected SEScalarVolume      matrixVolume;
  protected SEScalar0To1        neutralLipidsVolumeFraction;
  protected SEScalar0To1        neutralPhospholipidsVolumeFraction;  
  protected SEScalar            tissueToPlasmaAlbuminRatio;
  protected SEScalar            tissueToPlasmaAlphaAcidGlycoproteinRatio;
  protected SEScalar            tissueToPlasmaLipoproteinRatio;
  protected SEScalarMass        totalMass;
  
  public SETissueCompartment()
  {
    acidicPhospohlipidConcentration = null;
    matrixVolume = null;
    neutralLipidsVolumeFraction = null;
    neutralPhospholipidsVolumeFraction = null;    
    tissueToPlasmaAlbuminRatio = null;
    tissueToPlasmaAlphaAcidGlycoproteinRatio = null;
    tissueToPlasmaLipoproteinRatio = null;
    totalMass = null;
  }
  
  public void reset()
  {
    super.reset();
    if (acidicPhospohlipidConcentration != null)
      acidicPhospohlipidConcentration.invalidate();
    if (matrixVolume != null)
      matrixVolume.invalidate();
    if (neutralLipidsVolumeFraction != null)
      neutralLipidsVolumeFraction.invalidate();
    if (neutralPhospholipidsVolumeFraction != null)
      neutralPhospholipidsVolumeFraction.invalidate();
    if (tissueToPlasmaAlbuminRatio != null)
      tissueToPlasmaAlbuminRatio.invalidate();
    if (tissueToPlasmaAlphaAcidGlycoproteinRatio != null)
      tissueToPlasmaAlphaAcidGlycoproteinRatio.invalidate();
    if (tissueToPlasmaLipoproteinRatio != null)
      tissueToPlasmaLipoproteinRatio.invalidate();
    if (totalMass != null)
      totalMass.invalidate();
  }
  
  public static void load(TissueCompartmentData src, SETissueCompartment dst)
  {
    SECompartment.load(src.getCompartment(), dst);
    if(src.hasAcidicPhospohlipidConcentration())
      SEScalarMassPerMass.load(src.getAcidicPhospohlipidConcentration(),dst.getAcidicPhospohlipidConcentration());
    if(src.hasMatrixVolume())
      SEScalarVolume.load(src.getMatrixVolume(),dst.getMatrixVolume());
    if(src.hasNeutralLipidsVolumeFraction())
      SEScalar0To1.load(src.getNeutralLipidsVolumeFraction(),dst.getNeutralLipidsVolumeFraction());
    if(src.hasNeutralPhospholipidsVolumeFraction())
      SEScalar0To1.load(src.getNeutralPhospholipidsVolumeFraction(),dst.getNeutralPhospholipidsVolumeFraction());
    if(src.hasTissueToPlasmaAlbuminRatio())
      SEScalar.load(src.getTissueToPlasmaAlbuminRatio(),dst.getTissueToPlasmaAlbuminRatio());
    if(src.hasTissueToPlasmaAlphaAcidGlycoproteinRatio())
      SEScalar.load(src.getTissueToPlasmaAlphaAcidGlycoproteinRatio(),dst.getTissueToPlasmaAlphaAcidGlycoproteinRatio());
    if(src.hasTissueToPlasmaLipoproteinRatio())
      SEScalar.load(src.getTissueToPlasmaLipoproteinRatio(),dst.getTissueToPlasmaLipoproteinRatio());
    if(src.hasTotalMass())
      SEScalarMass.load(src.getTotalMass(),dst.getTotalMass());
  }
  public static TissueCompartmentData unload(SETissueCompartment src)
  {
    TissueCompartmentData.Builder dst = TissueCompartmentData.newBuilder();
    unload(src,dst);
    return dst.build();    
  }
  protected static void unload(SETissueCompartment src, TissueCompartmentData.Builder dst)
  {
    SECompartment.unload(src, dst.getCompartment());
    if(src.hasAcidicPhospohlipidConcentration())
      dst.setAcidicPhospohlipidConcentration(SEScalarMassPerMass.unload(src.acidicPhospohlipidConcentration));
    if(src.hasMatrixVolume())
      dst.setMatrixVolume(SEScalarVolume.unload(src.matrixVolume));
    if(src.hasNeutralLipidsVolumeFraction())
      dst.setNeutralLipidsVolumeFraction(SEScalar0To1.unload(src.neutralLipidsVolumeFraction));
    if(src.hasNeutralPhospholipidsVolumeFraction())
      dst.setNeutralPhospholipidsVolumeFraction(SEScalar0To1.unload(src.neutralPhospholipidsVolumeFraction));
    if(src.hasTissueToPlasmaAlbuminRatio())
      dst.setTissueToPlasmaAlbuminRatio(SEScalar.unload(src.tissueToPlasmaAlbuminRatio));
    if(src.hasTissueToPlasmaAlphaAcidGlycoproteinRatio())
      dst.setTissueToPlasmaAlphaAcidGlycoproteinRatio(SEScalar.unload(src.tissueToPlasmaAlphaAcidGlycoproteinRatio));
    if(src.hasTissueToPlasmaLipoproteinRatio())
      dst.setTissueToPlasmaLipoproteinRatio(SEScalar.unload(src.tissueToPlasmaLipoproteinRatio));
    if(src.hasTotalMass())
      dst.setTotalMass(SEScalarMass.unload(src.totalMass));
  }

  public SEScalarMassPerMass getAcidicPhospohlipidConcentration() 
  {
    if (acidicPhospohlipidConcentration == null)
      acidicPhospohlipidConcentration = new SEScalarMassPerMass();
    return acidicPhospohlipidConcentration;
  }
  public boolean hasAcidicPhospohlipidConcentration()
  {
    return acidicPhospohlipidConcentration == null ? false : acidicPhospohlipidConcentration.isValid();
  }

  public SEScalarVolume getMatrixVolume() 
  {
    if (matrixVolume == null)
      matrixVolume = new SEScalarVolume();
    return matrixVolume;
  }
  public boolean hasMatrixVolume()
  {
    return matrixVolume == null ? false : matrixVolume.isValid();
  }
  
  public SEScalar0To1 getNeutralLipidsVolumeFraction() 
  {
    if (neutralLipidsVolumeFraction == null)
      neutralLipidsVolumeFraction = new SEScalar0To1();
    return neutralLipidsVolumeFraction;
  }
  public boolean hasNeutralLipidsVolumeFraction()
  {
    return neutralLipidsVolumeFraction == null ? false : neutralLipidsVolumeFraction.isValid();
  }
  
  public SEScalar0To1 getNeutralPhospholipidsVolumeFraction() 
  {
    if (neutralPhospholipidsVolumeFraction == null)
      neutralPhospholipidsVolumeFraction = new SEScalar0To1();
    return neutralPhospholipidsVolumeFraction;
  }
  public boolean hasNeutralPhospholipidsVolumeFraction()
  {
    return neutralPhospholipidsVolumeFraction == null ? false : neutralPhospholipidsVolumeFraction.isValid();
  }
  
  public SEScalar getTissueToPlasmaAlbuminRatio() 
  {
    if (tissueToPlasmaAlbuminRatio == null)
      tissueToPlasmaAlbuminRatio = new SEScalar();
    return tissueToPlasmaAlbuminRatio;
  }
  public boolean hasTissueToPlasmaAlbuminRatio()
  {
    return tissueToPlasmaAlbuminRatio == null ? false : tissueToPlasmaAlbuminRatio.isValid();
  }
  
  public SEScalar getTissueToPlasmaAlphaAcidGlycoproteinRatio() 
  {
    if (tissueToPlasmaAlphaAcidGlycoproteinRatio == null)
      tissueToPlasmaAlphaAcidGlycoproteinRatio = new SEScalar();
    return tissueToPlasmaAlphaAcidGlycoproteinRatio;
  }
  public boolean hasTissueToPlasmaAlphaAcidGlycoproteinRatio()
  {
    return tissueToPlasmaAlphaAcidGlycoproteinRatio == null ? false : tissueToPlasmaAlphaAcidGlycoproteinRatio.isValid();
  }
  
  public SEScalar getTissueToPlasmaLipoproteinRatio() 
  {
    if (tissueToPlasmaLipoproteinRatio == null)
      tissueToPlasmaLipoproteinRatio = new SEScalar();
    return tissueToPlasmaLipoproteinRatio;
  }
  public boolean hasTissueToPlasmaLipoproteinRatio()
  {
    return tissueToPlasmaLipoproteinRatio == null ? false : tissueToPlasmaLipoproteinRatio.isValid();
  }
  
  public SEScalarMass getTotalMass() 
  {
    if (totalMass == null)
      totalMass = new SEScalarMass();
    return totalMass;
  }
  public boolean hasTotalMass()
  {
    return totalMass == null ? false : totalMass.isValid();
  }
}
