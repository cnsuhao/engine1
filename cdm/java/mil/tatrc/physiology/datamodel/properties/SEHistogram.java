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

package mil.tatrc.physiology.datamodel.properties;

import com.kitware.physiology.cdm.Properties.HistogramData;

/**
 * @author abray
 */
public class SEHistogram extends SEFunction
{
  public SEHistogram()
  {
    super();
    invalidate();
  }
  
  public static void load(HistogramData src, SEHistogram dest)
  {
   SEFunction.load(src.getHistogram(), dest);
  }
  public static HistogramData unload(SEHistogram src)
  {
    if(!src.isValid())
      return null;
    HistogramData.Builder dst = HistogramData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEHistogram src, HistogramData.Builder dst)
  {
    SEFunction.unload(src,dst.getHistogramBuilder());
  }
  
  public boolean isValid()
  {
    if(this.dependent.length==0||this.independent.length==0)
      return false;
    if(this.dependent.length+1 != this.independent.length)
      return false;
    if(!isValidDependentUnit(this.dependentUnit))
      return false;
    if(!isValidIndependentUnit(this.independentUnit))
      return false;
    return true;
  }
}
