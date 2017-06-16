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
import com.kitware.physiology.cdm.PatientAssessments.PulmonaryFunctionTestData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.FileUtils;

public class SEPulmonaryFunctionTest extends SEPatientAssessment
{
  protected SEScalarVolume         expiratoryReserveVolume;
  protected SEScalarVolume         forcedVitalCapacity;
  protected SEScalarVolume         forcedExpiratoryVolume;
  protected SEScalarVolumePerTime  forcedExpiratoryFlow;
  protected SEScalarVolume         functionalResidualCapacity;
  protected SEScalarVolume         inspiratoryCapacity;
  protected SEScalarVolume         inspiratoryReserveVolume;
  protected SEScalarVolume         maximumVoluntaryVentilation;  
  protected SEScalarVolumePerTime  peakExpiratoryFlow;
  protected SEScalarVolume         residualVolume;
  protected SEScalarVolume         slowVitalCapacity;
  protected SEScalarVolume         totalLungCapacity;
  protected SEScalarVolume         vitalCapacity;
  protected SEFunctionVolumeVsTime lungVolumePlot;
  
  public void clear()
  {
    super.clear();
    this.expiratoryReserveVolume = null;
    this.forcedVitalCapacity = null;
    this.forcedExpiratoryVolume = null;
    this.forcedExpiratoryFlow = null;
    this.functionalResidualCapacity = null;
    this.inspiratoryCapacity = null;
    this.inspiratoryReserveVolume = null;
    this.maximumVoluntaryVentilation = null;
    this.peakExpiratoryFlow = null;
    this.residualVolume = null;
    this.slowVitalCapacity = null;
    this.totalLungCapacity = null;
    this.vitalCapacity = null;
    this.lungVolumePlot = null;
  }
  
  public void reset()
  {
    super.reset();
    if(this.expiratoryReserveVolume!=null)
      this.expiratoryReserveVolume.invalidate();
    if(this.forcedVitalCapacity!=null)
      this.forcedVitalCapacity.invalidate();
    if(this.forcedExpiratoryVolume!=null)
      this.forcedExpiratoryVolume.invalidate();
    if(this.forcedExpiratoryFlow!=null)
      this.forcedExpiratoryFlow.invalidate();
    if(this.functionalResidualCapacity!=null)
      this.functionalResidualCapacity.invalidate();
    if(this.inspiratoryCapacity!=null)
      this.inspiratoryCapacity.invalidate();
    if(this.inspiratoryReserveVolume!=null)
      this.inspiratoryReserveVolume.invalidate();
    if(this.maximumVoluntaryVentilation!=null)
      this.maximumVoluntaryVentilation.invalidate();
    if(this.peakExpiratoryFlow!=null)
      this.peakExpiratoryFlow.invalidate();
    if(this.residualVolume!=null)
      this.residualVolume.invalidate();
    if(this.slowVitalCapacity!=null)
      this.slowVitalCapacity.invalidate();
    if(this.totalLungCapacity!=null)
      this.totalLungCapacity.invalidate();
    if(this.vitalCapacity!=null)
      this.vitalCapacity.invalidate();
    if(this.lungVolumePlot!=null)
      this.lungVolumePlot.invalidate();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    PulmonaryFunctionTestData.Builder builder = PulmonaryFunctionTestData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEPulmonaryFunctionTest.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEPulmonaryFunctionTest.unload(this).toString());
  }
  
  public static void load(PulmonaryFunctionTestData src, SEPulmonaryFunctionTest dst)
  {
    SEPatientAssessment.load(src.getPatientAssessment(), dst);
    if(src.hasExpiratoryReserveVolume())
      SEScalarVolume.load(src.getExpiratoryReserveVolume(),dst.getExpiratoryReserveVolume());
    if(src.hasForcedVitalCapacity())
      SEScalarVolume.load(src.getForcedVitalCapacity(),dst.getForcedVitalCapacity());
    if(src.hasForcedExpiratoryVolume())
      SEScalarVolume.load(src.getForcedExpiratoryVolume(),dst.getForcedExpiratoryVolume());
    if(src.hasForcedExpiratoryFlow())
      SEScalarVolumePerTime.load(src.getForcedExpiratoryFlow(),dst.getForcedExpiratoryFlow());
    if(src.hasFunctionalResidualCapacity())
      SEScalarVolume.load(src.getFunctionalResidualCapacity(),dst.getFunctionalResidualCapacity());
    if(src.hasInspiratoryCapacity())
      SEScalarVolume.load(src.getInspiratoryCapacity(),dst.getInspiratoryCapacity());
    if(src.hasInspiratoryReserveVolume())
      SEScalarVolume.load(src.getInspiratoryReserveVolume(),dst.getInspiratoryReserveVolume());
    if(src.hasMaximumVoluntaryVentilation())
      SEScalarVolume.load(src.getMaximumVoluntaryVentilation(),dst.getMaximumVoluntaryVentilation());
    if(src.hasPeakExpiratoryFlow())
      SEScalarVolumePerTime.load(src.getPeakExpiratoryFlow(),dst.getPeakExpiratoryFlow());
    if(src.hasResidualVolume())
      SEScalarVolume.load(src.getResidualVolume(),dst.getResidualVolume());
    if(src.hasSlowVitalCapacity())
      SEScalarVolume.load(src.getSlowVitalCapacity(),dst.getSlowVitalCapacity());
    if(src.hasTotalLungCapacity())
      SEScalarVolume.load(src.getTotalLungCapacity(),dst.getTotalLungCapacity());
    if(src.hasVitalCapacity())
      SEScalarVolume.load(src.getVitalCapacity(),dst.getVitalCapacity());
    if(src.hasLungVolumePlot())
      SEFunctionVolumeVsTime.load(src.getLungVolumePlot(),dst.getLungVolumePlot());
  }
  
  public static PulmonaryFunctionTestData unload(SEPulmonaryFunctionTest src)
  {
    PulmonaryFunctionTestData.Builder dst = PulmonaryFunctionTestData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEPulmonaryFunctionTest src, PulmonaryFunctionTestData.Builder dst)
  {
    SEPatientAssessment.unload(src, dst.getPatientAssessmentBuilder());
    if (src.hasExpiratoryReserveVolume())
      dst.setExpiratoryReserveVolume(SEScalarVolume.unload(src.getExpiratoryReserveVolume()));
    if (src.hasForcedVitalCapacity())
      dst.setForcedVitalCapacity(SEScalarVolume.unload(src.getForcedVitalCapacity()));
    if (src.hasForcedExpiratoryVolume())
      dst.setForcedExpiratoryVolume(SEScalarVolume.unload(src.getForcedExpiratoryVolume()));
    if (src.hasForcedExpiratoryFlow())
      dst.setForcedExpiratoryFlow(SEScalarVolumePerTime.unload(src.getForcedExpiratoryFlow()));
    if (src.hasFunctionalResidualCapacity())
      dst.setFunctionalResidualCapacity(SEScalarVolume.unload(src.getFunctionalResidualCapacity()));
    if (src.hasInspiratoryCapacity())
      dst.setInspiratoryCapacity(SEScalarVolume.unload(src.getInspiratoryCapacity()));
    if (src.hasInspiratoryReserveVolume())
      dst.setInspiratoryReserveVolume(SEScalarVolume.unload(src.getInspiratoryReserveVolume()));
    if (src.hasMaximumVoluntaryVentilation())
      dst.setMaximumVoluntaryVentilation(SEScalarVolume.unload(src.getMaximumVoluntaryVentilation()));
    if (src.hasPeakExpiratoryFlow())
      dst.setPeakExpiratoryFlow(SEScalarVolumePerTime.unload(src.getPeakExpiratoryFlow()));
    if (src.hasResidualVolume())
      dst.setResidualVolume(SEScalarVolume.unload(src.getResidualVolume()));
    if (src.hasSlowVitalCapacity())
      dst.setSlowVitalCapacity(SEScalarVolume.unload(src.getSlowVitalCapacity()));
    if (src.hasTotalLungCapacity())
      dst.setTotalLungCapacity(SEScalarVolume.unload(src.getTotalLungCapacity()));
    if (src.hasVitalCapacity())
      dst.setVitalCapacity(SEScalarVolume.unload(src.getVitalCapacity()));
    if (src.hasLungVolumePlot())
      dst.setLungVolumePlot(SEFunctionVolumeVsTime.unload(src.getLungVolumePlot()));
  }
  
  public boolean hasExpiratoryReserveVolume()
  {
    return expiratoryReserveVolume == null ? false : expiratoryReserveVolume.isValid();
  }
  public SEScalarVolume getExpiratoryReserveVolume()
  {
    if (expiratoryReserveVolume == null)
      expiratoryReserveVolume = new SEScalarVolume();
    return expiratoryReserveVolume;
  }
  
  public boolean hasForcedVitalCapacity()
  {
    return forcedVitalCapacity == null ? false : forcedVitalCapacity.isValid();
  }
  public SEScalarVolume getForcedVitalCapacity()
  {
    if (forcedVitalCapacity == null)
      forcedVitalCapacity = new SEScalarVolume();
    return forcedVitalCapacity;
  }
  
  public boolean hasForcedExpiratoryVolume()
  {
    return forcedExpiratoryVolume == null ? false : forcedExpiratoryVolume.isValid();
  }
  public SEScalarVolume getForcedExpiratoryVolume()
  {
    if (forcedExpiratoryVolume == null)
      forcedExpiratoryVolume = new SEScalarVolume();
    return forcedExpiratoryVolume;
  }
  
  public boolean hasForcedExpiratoryFlow()
  {
    return forcedExpiratoryFlow == null ? false : forcedExpiratoryFlow.isValid();
  }
  public SEScalarVolumePerTime getForcedExpiratoryFlow()
  {
    if (forcedExpiratoryFlow == null)
      forcedExpiratoryFlow = new SEScalarVolumePerTime();
    return forcedExpiratoryFlow;
  }
  
  public boolean hasFunctionalResidualCapacity()
  {
    return functionalResidualCapacity == null ? false : functionalResidualCapacity.isValid();
  }
  public SEScalarVolume getFunctionalResidualCapacity()
  {
    if (functionalResidualCapacity == null)
      functionalResidualCapacity = new SEScalarVolume();
    return functionalResidualCapacity;
  }
  
  public boolean hasInspiratoryCapacity()
  {
    return inspiratoryCapacity == null ? false : inspiratoryCapacity.isValid();
  }
  public SEScalarVolume getInspiratoryCapacity()
  {
    if (inspiratoryCapacity == null)
      inspiratoryCapacity = new SEScalarVolume();
    return inspiratoryCapacity;
  }
  
  public boolean hasInspiratoryReserveVolume()
  {
    return inspiratoryReserveVolume == null ? false : inspiratoryReserveVolume.isValid();
  }
  public SEScalarVolume getInspiratoryReserveVolume()
  {
    if (inspiratoryReserveVolume == null)
      inspiratoryReserveVolume = new SEScalarVolume();
    return inspiratoryReserveVolume;
  }
  
  public boolean hasMaximumVoluntaryVentilation()
  {
    return maximumVoluntaryVentilation == null ? false : maximumVoluntaryVentilation.isValid();
  }
  public SEScalarVolume getMaximumVoluntaryVentilation()
  {
    if (maximumVoluntaryVentilation == null)
      maximumVoluntaryVentilation = new SEScalarVolume();
    return maximumVoluntaryVentilation;
  }
  
  public boolean hasPeakExpiratoryFlow()
  {
    return peakExpiratoryFlow == null ? false : peakExpiratoryFlow.isValid();
  }
  public SEScalarVolumePerTime getPeakExpiratoryFlow()
  {
    if (peakExpiratoryFlow == null)
      peakExpiratoryFlow = new SEScalarVolumePerTime();
    return peakExpiratoryFlow;
  }
  
  public boolean hasResidualVolume()
  {
    return residualVolume == null ? false : residualVolume.isValid();
  }
  public SEScalarVolume getResidualVolume()
  {
    if (residualVolume == null)
      residualVolume = new SEScalarVolume();
    return residualVolume;
  }
  
  public boolean hasSlowVitalCapacity()
  {
    return slowVitalCapacity == null ? false : slowVitalCapacity.isValid();
  }
  public SEScalarVolume getSlowVitalCapacity()
  {
    if (slowVitalCapacity == null)
      slowVitalCapacity = new SEScalarVolume();
    return slowVitalCapacity;
  }
  
  public boolean hasTotalLungCapacity()
  {
    return totalLungCapacity == null ? false : totalLungCapacity.isValid();
  }
  public SEScalarVolume getTotalLungCapacity()
  {
    if (totalLungCapacity == null)
      totalLungCapacity = new SEScalarVolume();
    return totalLungCapacity;
  }
  
  public boolean hasVitalCapacity()
  {
    return vitalCapacity == null ? false : vitalCapacity.isValid();
  }
  public SEScalarVolume getVitalCapacity()
  {
    if (vitalCapacity == null)
      vitalCapacity = new SEScalarVolume();
    return vitalCapacity;
  }
  
  public boolean hasLungVolumePlot()
  {
    return lungVolumePlot == null ? false : lungVolumePlot.isValid();
  }
  public SEFunctionVolumeVsTime getLungVolumePlot()
  {
    if (lungVolumePlot == null)
      lungVolumePlot = new SEFunctionVolumeVsTime();
    return lungVolumePlot;
  }

}
