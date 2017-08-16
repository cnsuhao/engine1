/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.datamodel.patient.assessments;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.PatientAssessments.CompleteBloodCountData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.FileUtils;

public class SECompleteBloodCount extends SEPatientAssessment
{
  protected SEScalar0To1            hematocrit;
  protected SEScalarMassPerVolume   hemoglobin;
  protected SEScalarAmountPerVolume plateletCount;
  protected SEScalarMassPerAmount   meanCorpuscularHemoglobin;
  protected SEScalarMassPerVolume   meanCorpuscularHemoglobinConcentration;
  protected SEScalarVolume          meanCorpuscularVolume;
  protected SEScalarAmountPerVolume redBloodCellCount;
  protected SEScalarAmountPerVolume whiteBloodCellCount;
  
  public void clear()
  {
    super.clear();
    this.hematocrit = null;
    this.hemoglobin = null;
    this.plateletCount = null;
    this.meanCorpuscularHemoglobin = null;
    this.meanCorpuscularHemoglobinConcentration = null;
    this.meanCorpuscularVolume = null;
    this.redBloodCellCount = null;
    this.whiteBloodCellCount = null;
  }
  
  public void reset()
  {
    super.reset();
    if(this.hematocrit!=null)
      this.hematocrit.invalidate();
    if(this.hemoglobin!=null)
      this.hemoglobin.invalidate();
    if(this.plateletCount!=null)
      this.plateletCount.invalidate();
    if(this.meanCorpuscularHemoglobin!=null)
      this.meanCorpuscularHemoglobin.invalidate();
    if(this.meanCorpuscularHemoglobinConcentration!=null)
      this.meanCorpuscularHemoglobinConcentration.invalidate();
    if(this.meanCorpuscularVolume!=null)
      this.meanCorpuscularVolume.invalidate();
    if(this.redBloodCellCount!=null)
      this.redBloodCellCount.invalidate();
    if(this.whiteBloodCellCount!=null)
      this.whiteBloodCellCount.invalidate();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    CompleteBloodCountData.Builder builder = CompleteBloodCountData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SECompleteBloodCount.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SECompleteBloodCount.unload(this).toString());
  }
  
  public static void load(CompleteBloodCountData src, SECompleteBloodCount dst)
  {
    SEPatientAssessment.load(src.getPatientAssessment(), dst);
    if(src.hasHematocrit())
      SEScalar0To1.load(src.getHematocrit(),dst.getHematocrit());
    if(src.hasHemoglobin())
      SEScalarMassPerVolume.load(src.getHemoglobin(),dst.getHemoglobin());
    if(src.hasPlateletCount())
      SEScalarAmountPerVolume.load(src.getPlateletCount(),dst.getPlateletCount());
    if(src.hasMeanCorpuscularHemoglobin())
      SEScalarMassPerAmount.load(src.getMeanCorpuscularHemoglobin(),dst.getMeanCorpuscularHemoglobin());
    if(src.hasMeanCorpuscularHemoglobinConcentration())
      SEScalarMassPerVolume.load(src.getMeanCorpuscularHemoglobinConcentration(),dst.getMeanCorpuscularHemoglobinConcentration());
    if(src.hasMeanCorpuscularVolume())
      SEScalarVolume.load(src.getMeanCorpuscularVolume(),dst.getMeanCorpuscularVolume());
    if(src.hasRedBloodCellCount())
      SEScalarAmountPerVolume.load(src.getRedBloodCellCount(),dst.getRedBloodCellCount());
    if(src.hasWhiteBloodCellCount())
      SEScalarAmountPerVolume.load(src.getWhiteBloodCellCount(),dst.getWhiteBloodCellCount());
  }
  
  public static CompleteBloodCountData unload(SECompleteBloodCount src)
  {
    CompleteBloodCountData.Builder dst = CompleteBloodCountData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SECompleteBloodCount src, CompleteBloodCountData.Builder dst)
  {
    SEPatientAssessment.unload(src, dst.getPatientAssessmentBuilder());
    if (src.hasHematocrit())
      dst.setHematocrit(SEScalar0To1.unload(src.getHematocrit()));
    if (src.hasHemoglobin())
      dst.setHemoglobin(SEScalarMassPerVolume.unload(src.getHemoglobin()));
    if (src.hasPlateletCount())
      dst.setPlateletCount(SEScalarAmountPerVolume.unload(src.getPlateletCount()));
    if (src.hasMeanCorpuscularHemoglobin())
      dst.setMeanCorpuscularHemoglobin(SEScalarMassPerAmount.unload(src.getMeanCorpuscularHemoglobin()));
    if (src.hasMeanCorpuscularHemoglobinConcentration())
      dst.setMeanCorpuscularHemoglobinConcentration(SEScalarMassPerVolume.unload(src.getMeanCorpuscularHemoglobinConcentration()));
    if (src.hasMeanCorpuscularVolume())
      dst.setMeanCorpuscularVolume(SEScalarVolume.unload(src.getMeanCorpuscularVolume()));
    if (src.hasRedBloodCellCount())
      dst.setRedBloodCellCount(SEScalarAmountPerVolume.unload(src.getRedBloodCellCount()));
    if (src.hasWhiteBloodCellCount())
      dst.setWhiteBloodCellCount(SEScalarAmountPerVolume.unload(src.getWhiteBloodCellCount()));
  }
  
  public boolean hasHematocrit()
  {
    return hematocrit == null ? false : hematocrit.isValid();
  }
  public SEScalar0To1 getHematocrit()
  {
    if (hematocrit == null)
      hematocrit = new SEScalar0To1();
    return hematocrit;
  }
  
  public boolean hasHemoglobin()
  {
    return hemoglobin == null ? false : hemoglobin.isValid();
  }
  public SEScalarMassPerVolume getHemoglobin()
  {
    if (hemoglobin == null)
      hemoglobin = new SEScalarMassPerVolume();
    return hemoglobin;
  }
  
  public boolean hasPlateletCount()
  {
    return plateletCount == null ? false : plateletCount.isValid();
  }
  public SEScalarAmountPerVolume getPlateletCount()
  {
    if (plateletCount == null)
      plateletCount = new SEScalarAmountPerVolume();
    return plateletCount;
  }
  
  public boolean hasMeanCorpuscularHemoglobin()
  {
    return meanCorpuscularHemoglobin == null ? false : meanCorpuscularHemoglobin.isValid();
  }
  public SEScalarMassPerAmount getMeanCorpuscularHemoglobin()
  {
    if (meanCorpuscularHemoglobin == null)
      meanCorpuscularHemoglobin = new SEScalarMassPerAmount();
    return meanCorpuscularHemoglobin;
  }
  
  public boolean hasMeanCorpuscularHemoglobinConcentration()
  {
    return meanCorpuscularHemoglobinConcentration == null ? false : meanCorpuscularHemoglobinConcentration.isValid();
  }
  public SEScalarMassPerVolume getMeanCorpuscularHemoglobinConcentration()
  {
    if (meanCorpuscularHemoglobinConcentration == null)
      meanCorpuscularHemoglobinConcentration = new SEScalarMassPerVolume();
    return meanCorpuscularHemoglobinConcentration;
  }
  
  public boolean hasMeanCorpuscularVolume()
  {
    return meanCorpuscularVolume == null ? false : meanCorpuscularVolume.isValid();
  }
  public SEScalarVolume getMeanCorpuscularVolume()
  {
    if (meanCorpuscularVolume == null)
      meanCorpuscularVolume = new SEScalarVolume();
    return meanCorpuscularVolume;
  }
  
  public boolean hasRedBloodCellCount()
  {
    return redBloodCellCount == null ? false : redBloodCellCount.isValid();
  }
  public SEScalarAmountPerVolume getRedBloodCellCount()
  {
    if (redBloodCellCount == null)
      redBloodCellCount = new SEScalarAmountPerVolume();
    return redBloodCellCount;
  }
  
  public boolean hasWhiteBloodCellCount()
  {
    return whiteBloodCellCount == null ? false : whiteBloodCellCount.isValid();
  }
  public SEScalarAmountPerVolume getWhiteBloodCellCount()
  {
    if (whiteBloodCellCount == null)
      whiteBloodCellCount = new SEScalarAmountPerVolume();
    return whiteBloodCellCount;
  }

}
