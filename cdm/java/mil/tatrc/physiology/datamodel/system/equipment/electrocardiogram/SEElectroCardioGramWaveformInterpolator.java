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

import java.util.*;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.ElectroCardioGram.ElectroCardioGramWaveformInterpolatorData;
import com.kitware.physiology.cdm.Physiology.eHeartRhythm;

import mil.tatrc.physiology.utilities.FileUtils;

public class SEElectroCardioGramWaveformInterpolator
{
  Map<Integer,Map<eHeartRhythm,SEElectroCardioGramWaveform>> waveforms = new HashMap<Integer, Map<eHeartRhythm,SEElectroCardioGramWaveform>>();
 
  public SEElectroCardioGramWaveformInterpolator()
  {
    reset();
  }
  
  public void reset()
  {
    waveforms.clear();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    ElectroCardioGramWaveformInterpolatorData.Builder builder = ElectroCardioGramWaveformInterpolatorData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEElectroCardioGramWaveformInterpolator.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEElectroCardioGramWaveformInterpolator.unload(this).toString());
  }
  
  public static void load(ElectroCardioGramWaveformInterpolatorData src, SEElectroCardioGramWaveformInterpolator dst)
  {
    dst.reset();
    for(ElectroCardioGramWaveformInterpolatorData.WaveformData wData : src.getWaveformList())
    {
      SEElectroCardioGramWaveform w = new SEElectroCardioGramWaveform();
      SEElectroCardioGramWaveform.load(wData,w);
      Map<eHeartRhythm, SEElectroCardioGramWaveform> leads = dst.waveforms.get(w.getLead());
      if(leads == null)
      {
        leads = new HashMap<eHeartRhythm, SEElectroCardioGramWaveform>();
        dst.waveforms.put(w.getLead(), leads);
      }
      leads.put(w.getRhythm(), w);
    }
  }
  public static ElectroCardioGramWaveformInterpolatorData unload(SEElectroCardioGramWaveformInterpolator src)
  {
    ElectroCardioGramWaveformInterpolatorData.Builder dst =  ElectroCardioGramWaveformInterpolatorData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEElectroCardioGramWaveformInterpolator src, ElectroCardioGramWaveformInterpolatorData.Builder dst)
  {
    for(Map<eHeartRhythm, SEElectroCardioGramWaveform> leads : src.waveforms.values())
    {     
      for(SEElectroCardioGramWaveform w : leads.values())
        dst.addWaveform(SEElectroCardioGramWaveform.unload(w));
    }
  }
  
  public SEElectroCardioGramWaveform getWaveform(int lead, eHeartRhythm rhythm)
  {
    Map<eHeartRhythm, SEElectroCardioGramWaveform> leads = this.waveforms.get(lead);
    if(leads == null)
    {
      leads = new HashMap<eHeartRhythm, SEElectroCardioGramWaveform>();
      this.waveforms.put(lead, leads);
    }
    if(!leads.containsKey(rhythm))
    {
      leads.put(rhythm, new SEElectroCardioGramWaveform());
    }
    return leads.get(rhythm);
  }
}
