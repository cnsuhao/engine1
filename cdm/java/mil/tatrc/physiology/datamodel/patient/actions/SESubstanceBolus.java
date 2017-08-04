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

import com.kitware.physiology.cdm.PatientActions.SubstanceBolusData;
import com.kitware.physiology.cdm.PatientActions.SubstanceBolusData.eAdministrationRoute;

import mil.tatrc.physiology.datamodel.properties.SEScalarMassPerVolume;
import mil.tatrc.physiology.datamodel.properties.SEScalarVolume;
import mil.tatrc.physiology.datamodel.substance.SESubstance;

public class SESubstanceBolus extends SEPatientAction
{
  protected eAdministrationRoute adminRoute;
  protected SEScalarMassPerVolume concentration;
  protected SEScalarVolume dose;
  protected SESubstance substance;
  
  public SESubstanceBolus(SESubstance substance)
  {
    this.adminRoute = null;
    this.dose = null;
    this.concentration = null;
    this.substance = substance;
  }
  
  public void copy(SESubstanceBolus other)
  {
    if(this==other)
      return;
    super.copy(other);
    adminRoute = other.adminRoute;
    substance = other.substance;
    
    if (other.dose != null)
      getDose().set(other.getDose());
    else if (dose != null)
      dose.invalidate();
    
    if (other.concentration != null)
      getConcentration().set(other.getConcentration());
    else if (concentration != null)
      concentration.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    adminRoute = null;
    if (dose != null)
      dose.invalidate();
    if (concentration != null)
      concentration.invalidate();
  }
  
  public boolean isValid()
  {
    return hasAdminRoute() && hasDose() && hasConcentration() && hasSubstance();
  }
  
  public static void load(SubstanceBolusData src, SESubstanceBolus dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasDose())
      SEScalarVolume.load(src.getDose(),dst.getDose());
    if(src.hasConcentration())
      SEScalarMassPerVolume.load(src.getConcentration(),dst.getConcentration());
    if(src.getAdministrationRoute()!=eAdministrationRoute.UNRECOGNIZED)
    	dst.adminRoute = src.getAdministrationRoute();
  }
  
  public static SubstanceBolusData unload(SESubstanceBolus src)
  {
    SubstanceBolusData.Builder dst = SubstanceBolusData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SESubstanceBolus src, SubstanceBolusData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasDose())
      dst.setDose(SEScalarVolume.unload(src.dose));
    if (src.hasConcentration())
      dst.setConcentration(SEScalarMassPerVolume.unload(src.concentration));
    if (src.hasAdminRoute())
      dst.setAdministrationRoute(src.adminRoute);
    if (src.hasSubstance())
      dst.setSubstance(src.substance.getName());
  }

  public eAdministrationRoute getAdminRoute()
  {
    return adminRoute;
  }
  public void setAdminRoute(eAdministrationRoute adminRoute)
  {
    this.adminRoute = adminRoute;
  }
  public boolean hasAdminRoute()
  {
    return adminRoute == null ? false : true;
  }
  
  public boolean hasConcentration()
  {
    return concentration == null ? false : concentration.isValid();
  }
  public SEScalarMassPerVolume getConcentration()
  {
    if (concentration == null)
      concentration = new SEScalarMassPerVolume();
    return concentration;
  }
  
  public boolean hasDose()
  {
    return dose == null ? false : dose.isValid();
  }
  
  public SEScalarVolume getDose()
  {
    if (dose == null)
      dose = new SEScalarVolume();
    return dose;
  }
  
  public SESubstance getSubstance()
  {
    return substance;
  }
  public boolean hasSubstance() { return substance != null; }
  
  public String toString()
  {
    if (dose != null || concentration != null)
      return "Substance Bolus" 
          + "\n\tDose: " + getDose()
          + "\n\tConcentration: " + getConcentration()
          + "\n\tSubstance: " + getSubstance().getName() 
          + "\n\tAdministration Route: " + getAdminRoute();
    else
      return "Action not specified properly";
  }
}
