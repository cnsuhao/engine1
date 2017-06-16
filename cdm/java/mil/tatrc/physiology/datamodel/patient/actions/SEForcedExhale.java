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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ConsciousRespirationData.ForcedExhaleData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SEForcedExhale extends SEConsciousRespirationCommand
{
  protected SEScalar0To1 expiratoryReserveVolumeFraction;
  protected SEScalarTime period;
  
  public SEForcedExhale()
  {
    expiratoryReserveVolumeFraction = null;
    period = null;
  }
  
  public void copy(SEForcedExhale other)
  {
    if(this==other)
      return;
    
    expiratoryReserveVolumeFraction = other.expiratoryReserveVolumeFraction;
    period = other.period;
  }
  
  public SEConsciousRespirationCommand getCopy()
  {
    SEConsciousRespirationCommand command = new SEForcedExhale();
    command.copy(this);
    
    return command;
  }
  
  public void reset()
  {
    super.reset();
    
    if (expiratoryReserveVolumeFraction != null)
      expiratoryReserveVolumeFraction.invalidate();
    if (period != null)
      period.invalidate();
  }
  
  public boolean isValid()
  {
    return hasExpiratoryReserveVolumeFraction() && hasPeriod();
  }
  
  public static void load(ForcedExhaleData src, SEForcedExhale dst)
  {
    //SEConsciousRespirationCommand.load(src.getConsciousRespirationCommand(), dst);
    if(src.hasExpiratoryReserveVolumeFraction())
      SEScalar0To1.load(src.getExpiratoryReserveVolumeFraction(),dst.getExpiratoryReserveVolumeFraction());
    if(src.hasPeriod())
      SEScalarTime.load(src.getPeriod(),dst.getPeriod());
  }
  
  public static ForcedExhaleData unload(SEForcedExhale src)
  {
    ForcedExhaleData.Builder dst = ForcedExhaleData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEForcedExhale src, ForcedExhaleData.Builder dst)
  {
    //SEConsciousRespirationCommand.unload(src,dst.getConsciousRespirationCommand());
    if (src.hasExpiratoryReserveVolumeFraction())
      dst.setExpiratoryReserveVolumeFraction(SEScalar0To1.unload(src.expiratoryReserveVolumeFraction));
    if (src.hasPeriod())
      dst.setPeriod(SEScalarTime.unload(src.period));
  }
  
  public boolean hasExpiratoryReserveVolumeFraction()
  {
    return expiratoryReserveVolumeFraction != null;
  }
  public SEScalar0To1 getExpiratoryReserveVolumeFraction()
  {
    if (expiratoryReserveVolumeFraction == null)
      expiratoryReserveVolumeFraction = new SEScalar0To1();
    return expiratoryReserveVolumeFraction;
  }
  
  public boolean hasPeriod()
  {
    return period != null;
  }
  public SEScalarTime getPeriod()
  {
    if (period == null)
      period = new SEScalarTime();
    return period;
  }
  
  public String toString()
  {
    if (expiratoryReserveVolumeFraction != null &&
      period != null)
      return "Forced Exhale" 
          + "\n\tExpiratory Reserve Volume Fraction: " + getExpiratoryReserveVolumeFraction()
          + "\n\tPeriod: " + getPeriod();
    else
      return "Action not specified properly";
  }
}
