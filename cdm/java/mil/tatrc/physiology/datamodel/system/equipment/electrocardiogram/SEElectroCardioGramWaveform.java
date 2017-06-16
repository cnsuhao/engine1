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
package mil.tatrc.physiology.datamodel.system.equipment.electrocardiogram;

import com.kitware.physiology.cdm.ElectroCardioGram.ElectroCardioGramWaveformInterpolatorData;
import com.kitware.physiology.cdm.Physiology.eHeartRhythm;

import mil.tatrc.physiology.datamodel.properties.SEFunctionElectricPotentialVsTime;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;
import mil.tatrc.physiology.utilities.Log;

public class SEElectroCardioGramWaveform
{
  protected int                               lead;
  protected eHeartRhythm                      rhythm;
  protected SEFunctionElectricPotentialVsTime data;
  protected SEScalarTime                      timeStep;
  
  public SEElectroCardioGramWaveform()
  {
    reset();
  }
  
  public void reset()
  {
    lead = 0;
    rhythm = null;
    data = null;
    timeStep = null;
  }
  
  public static void load(ElectroCardioGramWaveformInterpolatorData.WaveformData src, SEElectroCardioGramWaveform dst)
  {
    dst.reset();
    if(src.getRhythm()!=eHeartRhythm.UNRECOGNIZED)
      dst.setRhythm(src.getRhythm());
    if(src.getLead()>0)
      dst.setLead(src.getLead());
    if(src.getLead()>12)
      throw new RuntimeException("ECG Lead cannot be greater than 12");
    if(src.hasData())
      SEFunctionElectricPotentialVsTime.load(src.getData(),dst.getData());
    if(src.hasTimeStep())
      SEScalarTime.load(src.getTimeStep(),dst.getTimeStep()); 
  }
  public static ElectroCardioGramWaveformInterpolatorData.WaveformData unload(SEElectroCardioGramWaveform src)
  {
    ElectroCardioGramWaveformInterpolatorData.WaveformData.Builder dst =  ElectroCardioGramWaveformInterpolatorData.WaveformData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEElectroCardioGramWaveform src, ElectroCardioGramWaveformInterpolatorData.WaveformData.Builder dst)
  {
    if(src.hasLead())
      dst.setLead(src.lead);
    if(src.hasRhythm())
      dst.setRhythm(src.rhythm);
    if(src.hasData())
      dst.setData(SEFunctionElectricPotentialVsTime.unload(src.data));
    if(src.hasTimeStep())
      dst.setTimeStep(SEScalarTime.unload(src.timeStep));
  }
  
  public int getLead()
  {
    return lead;
  }
  public void setLead(int l)
  {
    if(l>0 && l<=12)
      this.lead = l;
    Log.error("Lead must be between 1 and 12");
  }
  public boolean hasLead()
  {
    return lead != 0;
  }
  public void removeLead()
  {
    this.lead = 0;
  }
  
  public eHeartRhythm getRhythm()
  {
    return rhythm;
  }
  public void setRhythm(eHeartRhythm r)
  {
    this.rhythm = r;
  }
  public boolean hasRhythm()
  {
    return rhythm == null ? false : true;
  }
  
  public boolean hasData()
  {
    return data == null ? false : data.isValid();
  }
  public SEFunctionElectricPotentialVsTime getData()
  {
    if (data == null)
      data = new SEFunctionElectricPotentialVsTime();
    return data;
  }

  public boolean hasTimeStep()
  {
    return timeStep == null ? false : timeStep.isValid();
  }
  public SEScalarTime getTimeStep()
  {
    if (timeStep == null)
      timeStep = new SEScalarTime();
    return timeStep;
  }
}
