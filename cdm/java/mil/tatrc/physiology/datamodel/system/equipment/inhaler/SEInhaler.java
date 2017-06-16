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

package mil.tatrc.physiology.datamodel.system.equipment.inhaler;

import com.kitware.physiology.cdm.Inhaler.InhalerData;
import com.kitware.physiology.cdm.Properties.eSwitch;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEInhaler implements SESystem
{
  protected eSwitch        state;
  protected SEScalarMass   meteredDose;
  protected SEScalar0To1   nozzleLoss;
  protected SEScalarVolume spacerVolume;
  protected SESubstance    substance;

  public SEInhaler()
  {
    clear();
  }
  
  public void clear()
  {
    state = null;
    meteredDose = null;
    nozzleLoss = null;
    spacerVolume = null;
    substance = null;
  }

  public void reset()
  {
    state = null;
    if (meteredDose != null)
      meteredDose.invalidate();
    if (nozzleLoss != null)
      nozzleLoss.invalidate();
    if (spacerVolume != null)
      spacerVolume.invalidate();
    substance = null;
  }

  public void copy(SEInhaler from)
  {
    reset();

    setState(from.getState());
    meteredDose = from.getMeteredDose();
    nozzleLoss = from.getNozzleLoss();
    spacerVolume = from.getSpacerVolume();
    substance = from.substance;
  }

  public static void load(InhalerData src, SEInhaler dst, SESubstanceManager subMgr)
  {
    if (src.getState()!=eSwitch.UNRECOGNIZED)
      dst.setState(src.getState());
    if (src.hasMeteredDose())
      SEScalarMass.load(src.getMeteredDose(),dst.getMeteredDose());
    if (src.hasNozzleLoss())
      SEScalar0To1.load(src.getNozzleLoss(),dst.getNozzleLoss());
    if (src.hasSpacerVolume())
      SEScalarVolume.load(src.getSpacerVolume(),dst.getSpacerVolume());
    if (src.getSubstance() != null)
      dst.setSubstance(subMgr.getSubstance(src.getSubstance()));
  }
  public static InhalerData unload(SEInhaler src)
  {
    InhalerData.Builder dst = InhalerData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEInhaler src, InhalerData.Builder dst)
  {
    if (src.hasState())
      dst.setState(src.state);
    if (src.hasMeteredDose())
      dst.setMeteredDose(SEScalarMass.unload(src.meteredDose));
    if (src.hasNozzleLoss())
      dst.setNozzleLoss(SEScalar0To1.unload(src.nozzleLoss));
    if (src.hasSpacerVolume())
      dst.setSpacerVolume(SEScalarVolume.unload(src.spacerVolume));
    if (src.hasSubstance())
      dst.setSubstance(src.substance.getName());
  }

  public eSwitch getState()
  {
    return state;
  }
  public void setState(eSwitch state)
  {
    this.state = state;
  }
  public boolean hasState()
  {
    return state == null ? false : true;
  }

  public boolean hasMeteredDose()
  {
    return meteredDose == null ? false : meteredDose.isValid();
  }
  public SEScalarMass getMeteredDose()
  {
    if (meteredDose == null)
      meteredDose = new SEScalarMass();
    return meteredDose;
  }

  public boolean hasNozzleLoss()
  {
    return nozzleLoss == null ? false : nozzleLoss.isValid();
  }
  public SEScalar0To1 getNozzleLoss()
  {
    if (nozzleLoss == null)
      nozzleLoss = new SEScalar0To1();
    return nozzleLoss;
  }

  public boolean hasSpacerVolume()
  {
    return spacerVolume == null ? false : spacerVolume.isValid();
  }
  public SEScalarVolume getSpacerVolume()
  {
    if (spacerVolume == null)
      spacerVolume = new SEScalarVolume();
    return spacerVolume;
  }

  public SESubstance getSubstance()
  {
    return substance;
  }
  public void setSubstance(SESubstance s)
  {
    this.substance = s;
  }
  public boolean hasSubstance() 
  {
    return substance == null ? false : true;
  }
  
  public String toString()
  {
    String str = "Inhaler:";
    str += "\n\tMetered Dose: "; str += this.hasMeteredDose()?this.getMeteredDose():"Not Supplied";
    str += "\n\tNozzle Loss: "; str += this.hasNozzleLoss()?this.getNozzleLoss():"Not Supplied";
    str += "\n\tSpacer Volume: "; str += this.hasSpacerVolume()?this.getSpacerVolume():"Not Supplied";    
    str += "\n\tSubstance: "; str += this.hasSubstance()?this.getSubstance().getName():"Not Supplied";
    return str;
  }
}