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

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia;

import com.kitware.physiology.cdm.AnesthesiaMachine.AnesthesiaMachineData;

import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;

public class SEAnesthesiaMachineOxygenBottle
{
  protected SEScalarVolume volume;

  public SEAnesthesiaMachineOxygenBottle()
  {
    volume = null;
  }

  public void reset()
  {
    if (volume != null)
      volume.invalidate();
  }

  public void copy(SEAnesthesiaMachineOxygenBottle from)
  {
    reset();
    if(from.hasVolume())
      this.getVolume().set(from.getVolume());
  }

  public static void load(AnesthesiaMachineData.OxygenBottleData src, SEAnesthesiaMachineOxygenBottle dst)
  {
    if (src.hasVolume())
      SEScalarVolume.load(src.getVolume(),dst.getVolume());        
  }
  public static AnesthesiaMachineData.OxygenBottleData unload(SEAnesthesiaMachineOxygenBottle src)
  {
    AnesthesiaMachineData.OxygenBottleData.Builder dst
      = AnesthesiaMachineData.OxygenBottleData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEAnesthesiaMachineOxygenBottle src, AnesthesiaMachineData.OxygenBottleData.Builder dst)
  {
    if (src.hasVolume())
      dst.setVolume(SEScalarVolume.unload(src.volume));
  }

  public boolean hasVolume()
  {
    return volume == null ? false : volume.isValid();
  }

  public SEScalarVolume getVolume()
  {
    if (volume == null)
      volume = new SEScalarVolume();        
    return volume;
  }

  public String toString()
  {
    return "Anesthesia Machine Oxygen Bottle"
        + "\n\tVolume: " + getVolume();
  }
}