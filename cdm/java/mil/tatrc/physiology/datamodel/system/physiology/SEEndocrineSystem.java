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

package mil.tatrc.physiology.datamodel.system.physiology;

import com.kitware.physiology.cdm.Physiology.EndocrineSystemData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEEndocrineSystem extends SEPhysiologySystem implements SESystem
{
  protected SEScalarAmountPerTime insulinSynthesisRate;

  public SEEndocrineSystem()
  {
    insulinSynthesisRate = null;
  }

  public void reset()
  {    
    if (insulinSynthesisRate != null)
      insulinSynthesisRate.invalidate();
  }

  public static void load(EndocrineSystemData src, SEEndocrineSystem dst)
  {    
    if (src.hasInsulinSynthesisRate())
      SEScalarAmountPerTime.load(src.getInsulinSynthesisRate(),dst.getInsulinSynthesisRate());
  }

  public static EndocrineSystemData unload(SEEndocrineSystem src)
  {
    EndocrineSystemData.Builder dst = EndocrineSystemData.newBuilder();
    unload(src,dst);
    return dst.build();
  }

  protected static void unload(SEEndocrineSystem src, EndocrineSystemData.Builder dst)
  {    
    if (src.hasInsulinSynthesisRate())
      dst.setInsulinSynthesisRate(SEScalarAmountPerTime.unload(src.getInsulinSynthesisRate()));
  }

  public boolean hasInsulinSynthesisRate()
  {
    return insulinSynthesisRate == null ? false : insulinSynthesisRate.isValid();
  }
  public SEScalarAmountPerTime getInsulinSynthesisRate()
  {
    if (insulinSynthesisRate == null)
      insulinSynthesisRate = new SEScalarAmountPerTime();
    return insulinSynthesisRate;
  }
}
