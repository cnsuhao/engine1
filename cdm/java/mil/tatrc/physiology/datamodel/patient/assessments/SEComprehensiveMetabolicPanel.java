/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/
package mil.tatrc.physiology.datamodel.patient.assessments;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.PatientAssessments.ComprehensiveMetabolicPanelData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.FileUtils;

public class SEComprehensiveMetabolicPanel extends SEPatientAssessment
{
  protected SEScalarMassPerVolume   albumin;
  protected SEScalarMassPerVolume   ALP;
  protected SEScalarMassPerVolume   ALT;
  protected SEScalarMassPerVolume   AST;
  protected SEScalarMassPerVolume   BUN;
  protected SEScalarMassPerVolume   calcium;
  protected SEScalarAmountPerVolume chloride;
  protected SEScalarAmountPerVolume CO2;  
  protected SEScalarMassPerVolume   creatinine;
  protected SEScalarMassPerVolume   glucose;
  protected SEScalarAmountPerVolume potassium;
  protected SEScalarAmountPerVolume sodium;
  protected SEScalarMassPerVolume   totalBilirubin;
  protected SEScalarMassPerVolume   totalProtein;
  
  public void clear()
  {
    super.clear();
    this.albumin = null;
    this.ALP = null;
    this.ALT = null;
    this.AST = null;
    this.BUN = null;
    this.calcium = null;
    this.chloride = null;
    this.CO2 = null;
    this.creatinine = null;
    this.glucose = null;
    this.potassium = null;
    this.sodium = null;
    this.totalBilirubin = null;
    this.totalProtein = null;
  }
  
  public void reset()
  {
    super.reset();
    if(this.albumin!=null)
      this.albumin.invalidate();
    if(this.ALP!=null)
      this.ALP.invalidate();
    if(this.ALT!=null)
      this.ALT.invalidate();
    if(this.AST!=null)
      this.AST.invalidate();
    if(this.BUN!=null)
      this.BUN.invalidate();
    if(this.calcium!=null)
      this.calcium.invalidate();
    if(this.chloride!=null)
      this.chloride.invalidate();
    if(this.CO2!=null)
      this.CO2.invalidate();
    if(this.creatinine!=null)
      this.creatinine.invalidate();
    if(this.glucose!=null)
      this.glucose.invalidate();
    if(this.potassium!=null)
      this.potassium.invalidate();
    if(this.sodium!=null)
      this.sodium.invalidate();
    if(this.totalBilirubin!=null)
      this.totalBilirubin.invalidate();
    if(this.totalProtein!=null)
      this.totalProtein.invalidate();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    ComprehensiveMetabolicPanelData.Builder builder = ComprehensiveMetabolicPanelData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEComprehensiveMetabolicPanel.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEComprehensiveMetabolicPanel.unload(this).toString());
  }
  
  public static void load(ComprehensiveMetabolicPanelData src, SEComprehensiveMetabolicPanel dst)
  {
    SEPatientAssessment.load(src.getPatientAssessment(), dst);
    if(src.hasAlbumin())
      SEScalarMassPerVolume.load(src.getAlbumin(),dst.getAlbumin());
    if(src.hasALP())
      SEScalarMassPerVolume.load(src.getALP(),dst.getALP());
    if(src.hasALT())
      SEScalarMassPerVolume.load(src.getALT(),dst.getALT());
    if(src.hasAST())
      SEScalarMassPerVolume.load(src.getAST(),dst.getAST());
    if(src.hasBUN())
      SEScalarMassPerVolume.load(src.getBUN(),dst.getBUN());
    if(src.hasCalcium())
      SEScalarMassPerVolume.load(src.getCalcium(),dst.getCalcium());
    if(src.hasChloride())
      SEScalarAmountPerVolume.load(src.getChloride(),dst.getChloride());
    if(src.hasCO2())
      SEScalarAmountPerVolume.load(src.getCO2(),dst.getCO2());
    if(src.hasCreatinine())
      SEScalarMassPerVolume.load(src.getCreatinine(),dst.getCreatinine());
    if(src.hasGlucose())
      SEScalarMassPerVolume.load(src.getGlucose(),dst.getGlucose());
    if(src.hasPotassium())
      SEScalarAmountPerVolume.load(src.getPotassium(),dst.getPotassium());
    if(src.hasSodium())
      SEScalarAmountPerVolume.load(src.getSodium(),dst.getSodium());
    if(src.hasTotalBilirubin())
      SEScalarMassPerVolume.load(src.getTotalBilirubin(),dst.getTotalBilirubin());
    if(src.hasTotalProtein())
      SEScalarMassPerVolume.load(src.getTotalProtein(),dst.getTotalProtein());
  }
  
  public static ComprehensiveMetabolicPanelData unload(SEComprehensiveMetabolicPanel src)
  {
    ComprehensiveMetabolicPanelData.Builder dst = ComprehensiveMetabolicPanelData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEComprehensiveMetabolicPanel src, ComprehensiveMetabolicPanelData.Builder dst)
  {
    SEPatientAssessment.unload(src, dst.getPatientAssessmentBuilder());
    if (src.hasAlbumin())
      dst.setAlbumin(SEScalarMassPerVolume.unload(src.getAlbumin()));
    if (src.hasALP())
      dst.setALP(SEScalarMassPerVolume.unload(src.getALP()));
    if (src.hasALT())
      dst.setALT(SEScalarMassPerVolume.unload(src.getALT()));
    if (src.hasAST())
      dst.setAST(SEScalarMassPerVolume.unload(src.getAST()));
    if (src.hasBUN())
      dst.setBUN(SEScalarMassPerVolume.unload(src.getBUN()));
    if (src.hasCalcium())
      dst.setCalcium(SEScalarMassPerVolume.unload(src.getCalcium()));
    if (src.hasChloride())
      dst.setChloride(SEScalarAmountPerVolume.unload(src.getChloride()));
    if (src.hasCO2())
      dst.setCO2(SEScalarAmountPerVolume.unload(src.getCO2()));
    if (src.hasCreatinine())
      dst.setCreatinine(SEScalarMassPerVolume.unload(src.getCreatinine()));
    if (src.hasGlucose())
      dst.setGlucose(SEScalarMassPerVolume.unload(src.getGlucose()));
    if (src.hasPotassium())
      dst.setPotassium(SEScalarAmountPerVolume.unload(src.getPotassium()));
    if (src.hasSodium())
      dst.setSodium(SEScalarAmountPerVolume.unload(src.getSodium()));
    if (src.hasTotalBilirubin())
      dst.setTotalBilirubin(SEScalarMassPerVolume.unload(src.getTotalBilirubin()));
    if (src.hasTotalProtein())
      dst.setTotalProtein(SEScalarMassPerVolume.unload(src.getTotalProtein()));
  }
  
  public boolean hasAlbumin()
  {
    return albumin == null ? false : albumin.isValid();
  }
  public SEScalarMassPerVolume getAlbumin()
  {
    if (albumin == null)
      albumin = new SEScalarMassPerVolume();
    return albumin;
  }
  
  public boolean hasALP()
  {
    return ALP == null ? false : ALP.isValid();
  }
  public SEScalarMassPerVolume getALP()
  {
    if (ALP == null)
      ALP = new SEScalarMassPerVolume();
    return ALP;
  }
  
  public boolean hasALT()
  {
    return ALT == null ? false : ALT.isValid();
  }
  public SEScalarMassPerVolume getALT()
  {
    if (ALT == null)
      ALT = new SEScalarMassPerVolume();
    return ALT;
  }
  
  public boolean hasAST()
  {
    return AST == null ? false : AST.isValid();
  }
  public SEScalarMassPerVolume getAST()
  {
    if (AST == null)
      AST = new SEScalarMassPerVolume();
    return AST;
  }
  
  public boolean hasBUN()
  {
    return BUN == null ? false : BUN.isValid();
  }
  public SEScalarMassPerVolume getBUN()
  {
    if (BUN == null)
      BUN = new SEScalarMassPerVolume();
    return BUN;
  }
  
  public boolean hasCalcium()
  {
    return calcium == null ? false : calcium.isValid();
  }
  public SEScalarMassPerVolume getCalcium()
  {
    if (calcium == null)
      calcium = new SEScalarMassPerVolume();
    return calcium;
  }
  
  public boolean hasChloride()
  {
    return chloride == null ? false : chloride.isValid();
  }
  public SEScalarAmountPerVolume getChloride()
  {
    if (chloride == null)
      chloride = new SEScalarAmountPerVolume();
    return chloride;
  }
  
  public boolean hasCO2()
  {
    return CO2 == null ? false : CO2.isValid();
  }
  public SEScalarAmountPerVolume getCO2()
  {
    if (CO2 == null)
      CO2 = new SEScalarAmountPerVolume();
    return CO2;
  }
  
  public boolean hasCreatinine()
  {
    return creatinine == null ? false : creatinine.isValid();
  }
  public SEScalarMassPerVolume getCreatinine()
  {
    if (creatinine == null)
      creatinine = new SEScalarMassPerVolume();
    return creatinine;
  }
  
  public boolean hasGlucose()
  {
    return glucose == null ? false : glucose.isValid();
  }
  public SEScalarMassPerVolume getGlucose()
  {
    if (glucose == null)
      glucose = new SEScalarMassPerVolume();
    return glucose;
  }
  
  public boolean hasPotassium()
  {
    return potassium == null ? false : potassium.isValid();
  }
  public SEScalarAmountPerVolume getPotassium()
  {
    if (potassium == null)
      potassium = new SEScalarAmountPerVolume();
    return potassium;
  }
  
  public boolean hasSodium()
  {
    return sodium == null ? false : sodium.isValid();
  }
  public SEScalarAmountPerVolume getSodium()
  {
    if (sodium == null)
      sodium = new SEScalarAmountPerVolume();
    return sodium;
  }
  
  public boolean hasTotalBilirubin()
  {
    return totalBilirubin == null ? false : totalBilirubin.isValid();
  }
  public SEScalarMassPerVolume getTotalBilirubin()
  {
    if (totalBilirubin == null)
      totalBilirubin = new SEScalarMassPerVolume();
    return totalBilirubin;
  }
  
  public boolean hasTotalProtein()
  {
    return totalProtein == null ? false : totalProtein.isValid();
  }
  public SEScalarMassPerVolume getTotalProtein()
  {
    if (totalProtein == null)
      totalProtein = new SEScalarMassPerVolume();
    return totalProtein;
  }

}
