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

import com.kitware.physiology.cdm.PatientActions.UrinateData;

public class SEUrinate extends SEPatientAction
{
  public SEUrinate()
  {

  }
  
  public void copy(SEUrinate other)
  {
    if(this==other)
      return;
    super.copy(other);    
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public boolean isValid()
  {
    return true;
  }
  
  public static void load(UrinateData src, SEUrinate dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
  }
  
  public static UrinateData unload(SEUrinate src) 
  {
    UrinateData.Builder dst = UrinateData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEUrinate src, UrinateData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
  }
  
  
  public String toString() 
  {
      return "Urinate";
  }
}
