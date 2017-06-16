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

package mil.tatrc.physiology.datamodel.substance;

import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.StringUtils;

public class SESubstanceAerosolization
{
  protected SEScalarNegative1To1         bronchioleModifier;
  protected SEScalar0To1                 inflammationCoefficient;
  protected SEHistogramFractionVsLength  particulateSizeDistribution;
  
  public SESubstanceAerosolization()
  {
    
  }
  
  public void reset()
  {
    if(this.bronchioleModifier!=null)
      this.bronchioleModifier.invalidate();
    if(this.inflammationCoefficient!=null)
      this.inflammationCoefficient.invalidate();
    if(this.particulateSizeDistribution!=null)
      this.particulateSizeDistribution.invalidate();
  }
  
  public boolean isValid()
  {
    if(!hasInflammationCoefficient() || !hasParticulateSizeDistribution() || !hasBronchioleModifier())
      return false;
    return true;
  }
  
  public static void load(SubstanceData.AerosolizationData src, SESubstanceAerosolization dst)
  {
    dst.reset();

    if(src.hasBronchioleModifier())
      SEScalarNegative1To1.load(src.getBronchioleModifier(),dst.getBronchioleModifier());
    if(src.hasInflammationCoefficient())
      SEScalar0To1.load(src.getInflammationCoefficient(),dst.getInflammationCoefficient());
    if(src.hasParticulateSizeDistribution())
      SEHistogramFractionVsLength.load(src.getParticulateSizeDistribution(),dst.getParticulateSizeDistribution());
  }
  public static SubstanceData.AerosolizationData unload(SESubstanceAerosolization src)
  {
    if(!src.isValid())
      return null;
    SubstanceData.AerosolizationData.Builder dst = SubstanceData.AerosolizationData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SESubstanceAerosolization src, SubstanceData.AerosolizationData.Builder dst)
  {
    if(src.hasBronchioleModifier())
      dst.setBronchioleModifier(SEScalarNegative1To1.unload(src.getBronchioleModifier()));
    if(src.hasInflammationCoefficient())
      dst.setInflammationCoefficient(SEScalar0To1.unload(src.getInflammationCoefficient()));
    if(src.hasParticulateSizeDistribution())
      dst.setParticulateSizeDistribution(SEHistogramFractionVsLength.unload(src.getParticulateSizeDistribution()));
  }
  
  public SEScalarNegative1To1 getBronchioleModifier() 
  { 
    if(this.bronchioleModifier==null)
      this.bronchioleModifier=new SEScalarNegative1To1();
    return this.bronchioleModifier;
  }
  public boolean hasBronchioleModifier() {return this.bronchioleModifier==null?false:this.bronchioleModifier.isValid();}

  public SEScalar0To1 getInflammationCoefficient() 
  { 
    if(this.inflammationCoefficient==null)
      this.inflammationCoefficient=new SEScalar0To1();
    return this.inflammationCoefficient;
  }
  public boolean hasInflammationCoefficient() {return this.inflammationCoefficient==null?false:this.inflammationCoefficient.isValid();}

  
  public SEHistogramFractionVsLength getParticulateSizeDistribution() 
  { 
    if(this.particulateSizeDistribution==null)
      this.particulateSizeDistribution=new SEHistogramFractionVsLength();
    return this.particulateSizeDistribution;
  }
  public boolean hasParticulateSizeDistribution() {return this.particulateSizeDistribution==null?false:this.particulateSizeDistribution.isValid();}

}
