/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.patient.assessments;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.PatientAssessments.UrinalysisData;
import com.kitware.physiology.cdm.PatientAssessments.UrinalysisData.*;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.FileUtils;

public class SEUrinalysis extends SEPatientAssessment
{
  protected eUrineColor           color;
  protected eClarityIndicator     appearance;
  protected ePresenceIndicator    glucose;
  protected ePresenceIndicator    ketone;
  protected SEScalar              bilirubin;
  protected SEScalar              specificGravity;
  protected ePresenceIndicator    blood;
  protected SEScalar              pH;  
  protected ePresenceIndicator    protein;
  protected SEScalarMassPerVolume urobilinogen;
  protected ePresenceIndicator    nitrite;
  protected ePresenceIndicator    leukocyteEsterase;
  
  public void clear()
  {
    super.clear();
    this.color = null;
    this.appearance = null;
    this.urobilinogen = null;
    this.ketone = null;
    this.bilirubin = null;
    this.specificGravity = null;
    this.blood = null;
    this.pH = null;
    this.protein = null;
    this.urobilinogen = null;
    this.nitrite = null;
    this.leukocyteEsterase = null;
  }
  
  public void reset()
  {
    super.reset();
    this.color = null;
    this.appearance = null;
    this.urobilinogen = null;
    this.ketone = null;
    if(this.bilirubin!=null)
      this.bilirubin.invalidate();
    if(this.specificGravity!=null)
      this.specificGravity.invalidate();    
    this.blood = null;
    if(this.pH!=null)
      this.pH.invalidate();    
    this.protein = null;
    if(this.urobilinogen!=null)
      this.urobilinogen.invalidate();    
    this.nitrite = null;
    this.leukocyteEsterase = null;   
  }
  
  public void readFile(String fileName) throws ParseException
  {
    UrinalysisData.Builder builder = UrinalysisData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEUrinalysis.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEUrinalysis.unload(this).toString());
  }
  
  public static void load(UrinalysisData src, SEUrinalysis dst)
  {
    SEPatientAssessment.load(src.getPatientAssessment(), dst);
    if(src.getColor()!=eUrineColor.UNRECOGNIZED)
      dst.setColor(src.getColor());
    if(src.getAppearance()!=eClarityIndicator.UNRECOGNIZED)
      dst.setAppearance(src.getAppearance());
    if(src.getGlucose()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setGlucose(src.getGlucose());
    if(src.getKetone()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setKetone(src.getKetone());
    if(src.hasBilirubin())
      SEScalar.load(src.getBilirubin(),dst.getBilirubin());
    if(src.hasSpecificGravity())
      SEScalar.load(src.getSpecificGravity(),dst.getSpecificGravity());
    if(src.getBlood()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setBlood(src.getBlood());
    if(src.hasPH())
      SEScalar.load(src.getPH(),dst.getPH());
    if(src.getProtein()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setProtein(src.getProtein());
    if(src.hasUrobilinogen())
      SEScalarMassPerVolume.load(src.getUrobilinogen(),dst.getUrobilinogen());
    if(src.getNitrite()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setNitrite(src.getNitrite());
    if(src.getLeukocyteEsterase()!=ePresenceIndicator.UNRECOGNIZED)
      dst.setLeukocyteEsterase(src.getLeukocyteEsterase());
  }
  
  public static UrinalysisData unload(SEUrinalysis src)
  {
    UrinalysisData.Builder dst = UrinalysisData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEUrinalysis src, UrinalysisData.Builder dst)
  {
    SEPatientAssessment.unload(src, dst.getPatientAssessmentBuilder());
    if (src.hasColor())
      dst.setColor(src.color);
    if (src.hasAppearance())
      dst.setAppearance(src.appearance);
    if (src.hasGlucose())
      dst.setGlucose(src.glucose);
    if (src.hasKetone())
      dst.setKetone(src.ketone);
    if (src.hasBilirubin())
      dst.setBilirubin(SEScalar.unload(src.bilirubin));
    if (src.hasSpecificGravity())
      dst.setSpecificGravity(SEScalar.unload(src.specificGravity));
    if (src.hasBlood())
      dst.setBlood(src.blood);
    if (src.hasPH())
      dst.setPH(SEScalar.unload(src.pH));
    if (src.hasProtein())
      dst.setProtein(src.protein);
    if (src.hasUrobilinogen())
      dst.setUrobilinogen(SEScalarMassPerVolume.unload(src.urobilinogen));
    if (src.hasNitrite())
      dst.setNitrite(src.nitrite);
    if (src.hasLeukocyteEsterase())
      dst.setLeukocyteEsterase(src.leukocyteEsterase);
  }
  
  public eUrineColor  getColor() { return this.color;}
  public void    setColor(eUrineColor color){this.color=color;}
  public boolean hasColor(){return this.color==null?false:color!=eUrineColor.NullColor;}
  
  public eClarityIndicator  getAppearance() { return this.appearance;}
  public void    setAppearance(eClarityIndicator a){this.appearance=a;}
  public boolean hasAppearance(){return this.appearance==null?false:appearance!=eClarityIndicator.NullClarity;}
  
  public ePresenceIndicator  getGlucose() { return this.glucose;}
  public void    setGlucose(ePresenceIndicator g){this.glucose=g;}
  public boolean hasGlucose(){return this.glucose==null?false:glucose!=ePresenceIndicator.NullPresence;}
  
  public ePresenceIndicator  getKetone() { return this.ketone;}
  public void    setKetone(ePresenceIndicator k){this.ketone=k;}
  public boolean hasKetone(){return this.ketone==null?false:ketone!=ePresenceIndicator.NullPresence;}
  
  public boolean hasBilirubin()
  {
    return bilirubin == null ? false : bilirubin.isValid();
  }
  public SEScalar getBilirubin()
  {
    if (bilirubin == null)
      bilirubin = new SEScalar();
    return bilirubin;
  }
  
  public boolean hasSpecificGravity()
  {
    return specificGravity == null ? false : specificGravity.isValid();
  }
  public SEScalar getSpecificGravity()
  {
    if (specificGravity == null)
      specificGravity = new SEScalar();
    return specificGravity;
  }
  
  public ePresenceIndicator  getBlood() { return this.blood;}
  public void    setBlood(ePresenceIndicator b){this.blood=b;}
  public boolean hasBlood(){return this.blood==null?false:blood!=ePresenceIndicator.NullPresence;}
  
  public boolean hasPH()
  {
    return pH == null ? false : pH.isValid();
  }
  public SEScalar getPH()
  {
    if (pH == null)
      pH = new SEScalar();
    return pH;
  }
  
  public ePresenceIndicator  getProtein() { return this.protein;}
  public void    setProtein(ePresenceIndicator p){this.protein=p;}
  public boolean hasProtein(){return this.protein==null?false:protein!=ePresenceIndicator.NullPresence;}
 
  
  public boolean hasUrobilinogen()
  {
    return urobilinogen == null ? false : urobilinogen.isValid();
  }
  public SEScalarMassPerVolume getUrobilinogen()
  {
    if (urobilinogen == null)
      urobilinogen = new SEScalarMassPerVolume();
    return urobilinogen;
  }
  
  public ePresenceIndicator  getNitrite() { return this.nitrite;}
  public void    setNitrite(ePresenceIndicator n){this.nitrite=n;}
  public boolean hasNitrite(){return this.nitrite==null?false:nitrite!=ePresenceIndicator.NullPresence;}
  
  public ePresenceIndicator  getLeukocyteEsterase() { return this.leukocyteEsterase;}
  public void    setLeukocyteEsterase(ePresenceIndicator l){this.leukocyteEsterase=l;}
  public boolean hasLeukocyteEsterase(){return this.leukocyteEsterase==null?false:leukocyteEsterase!=ePresenceIndicator.NullPresence;}
}
