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

package mil.tatrc.physiology.datamodel.system.environment;

import com.kitware.physiology.cdm.Environment.EnvironmentData;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.SESystem;

public class SEEnvironment implements SESystem
{

  protected SEScalarPower                   convectiveHeatLoss;
  protected SEScalarHeatConductancePerArea  convectiveHeatTranferCoefficient;
  protected SEScalarPower                   evaporativeHeatLoss;
  protected SEScalarHeatConductancePerArea  evaporativeHeatTranferCoefficient;
  protected SEScalarPower                   radiativeHeatLoss;
  protected SEScalarHeatConductancePerArea  radiativeHeatTranferCoefficient;
  protected SEScalarPower                   respirationHeatLoss;
  protected SEScalarPower                   skinHeatLoss;
  
  protected SEEnvironmentalConditions       conditions;
  protected SEActiveConditioning            activeHeating;
  protected SEActiveConditioning            activeCooling;
  protected SEAppliedTemperature            appliedTemperature;
  
  public SEEnvironment()
  {    
    this.convectiveHeatLoss=null;
    this.convectiveHeatTranferCoefficient=null;
    this.evaporativeHeatLoss=null;
    this.evaporativeHeatTranferCoefficient=null;
    this.radiativeHeatLoss=null;
    this.radiativeHeatTranferCoefficient=null;
    this.respirationHeatLoss=null;
    this.skinHeatLoss=null;
    
    this.conditions=null;
    activeHeating=null;  
    activeCooling=null;
    appliedTemperature=null;
  }
  
  public void reset()
  {    
    if (convectiveHeatLoss != null)
      convectiveHeatLoss.invalidate();
    if (convectiveHeatTranferCoefficient != null)
      convectiveHeatTranferCoefficient.invalidate();
    if (evaporativeHeatLoss != null)
      evaporativeHeatLoss.invalidate();
    if (evaporativeHeatTranferCoefficient != null)
      evaporativeHeatTranferCoefficient.invalidate();
    if (radiativeHeatLoss != null)
      radiativeHeatLoss.invalidate();
    if (radiativeHeatTranferCoefficient != null)
      radiativeHeatTranferCoefficient.invalidate();
    if (respirationHeatLoss != null)
      respirationHeatLoss.invalidate();
    if (skinHeatLoss != null)
      skinHeatLoss.invalidate();
    if (conditions != null)
      conditions.reset();
    if (activeHeating != null)
      activeHeating.reset();
    if (activeCooling != null)
      activeCooling.reset();
    if (appliedTemperature != null)
      appliedTemperature.reset();
  }
  
  public static void load(EnvironmentData src, SEEnvironment dst, SESubstanceManager subMgr)
  {    
    dst.reset();
    if (src.hasConvectiveHeatLoss())
      SEScalarPower.load(src.getConvectiveHeatLoss(),dst.getConvectiveHeatLoss());
    if (src.hasConvectiveHeatTranferCoefficient())
      SEScalarHeatConductancePerArea.load(src.getConvectiveHeatTranferCoefficient(),dst.getConvectiveHeatTranferCoefficient());
    if (src.hasEvaporativeHeatLoss())
      SEScalarPower.load(src.getEvaporativeHeatLoss(),dst.getEvaporativeHeatLoss());
    if (src.hasEvaporativeHeatTranferCoefficient())
      SEScalarHeatConductancePerArea.load(src.getEvaporativeHeatTranferCoefficient(),dst.getEvaporativeHeatTranferCoefficient());
    if (src.hasRadiativeHeatLoss())
      SEScalarPower.load(src.getRadiativeHeatLoss(),dst.getRadiativeHeatLoss());
    if (src.hasRadiativeHeatTranferCoefficient())
      SEScalarHeatConductancePerArea.load(src.getRadiativeHeatTranferCoefficient(),dst.getRadiativeHeatTranferCoefficient());
    if (src.hasRespirationHeatLoss())
      SEScalarPower.load(src.getRespirationHeatLoss(),dst.getRespirationHeatLoss());
    if (src.hasSkinHeatLoss())
      SEScalarPower.load(src.getSkinHeatLoss(),dst.getSkinHeatLoss());  
    
    if (src.hasConditions())
      SEEnvironmentalConditions.load(src.getConditions(),dst.getConditions(),subMgr); 
    if (src.hasActiveHeating())
      SEActiveConditioning.load(src.getActiveHeating(),dst.getActiveHeating());
    if (src.hasActiveCooling())
      SEActiveConditioning.load(src.getActiveCooling(),dst.getActiveCooling());
    if (src.hasAppliedTemperature())
      SEAppliedTemperature.load(src.getAppliedTemperature(),dst.getAppliedTemperature());
  }
  public static EnvironmentData unload(SEEnvironment src)
  {
    EnvironmentData.Builder dst = EnvironmentData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEEnvironment src, EnvironmentData.Builder dst)
  {    
    if (src.hasConvectiveHeatLoss())
        dst.setConvectiveHeatLoss(SEScalarPower.unload(src.convectiveHeatLoss));
    if (src.hasConvectiveHeatTranferCoefficient())
      dst.setConvectiveHeatTranferCoefficient(SEScalarHeatConductancePerArea.unload(src.convectiveHeatTranferCoefficient));
    if (src.hasEvaporativeHeatLoss())
      dst.setEvaporativeHeatLoss(SEScalarPower.unload(src.evaporativeHeatLoss));
    if (src.hasEvaporativeHeatTranferCoefficient())
      dst.setEvaporativeHeatTranferCoefficient(SEScalarHeatConductancePerArea.unload(src.evaporativeHeatTranferCoefficient));
    if (src.hasRadiativeHeatLoss())
      dst.setRadiativeHeatLoss(SEScalarPower.unload(src.radiativeHeatLoss));
    if (src.hasRadiativeHeatTranferCoefficient())
      dst.setRadiativeHeatTranferCoefficient(SEScalarHeatConductancePerArea.unload(src.radiativeHeatTranferCoefficient));
    if (src.hasRespirationHeatLoss())
      dst.setRespirationHeatLoss(SEScalarPower.unload(src.respirationHeatLoss));
    if (src.hasSkinHeatLoss())
      dst.setSkinHeatLoss(SEScalarPower.unload(src.skinHeatLoss));
    
    if (src.hasConditions())
      dst.setConditions(SEEnvironmentalConditions.unload(src.conditions));
    if (src.hasActiveHeating())
      dst.setActiveHeating(SEActiveConditioning.unload(src.activeHeating));
    if (src.hasActiveCooling())
      dst.setActiveCooling(SEActiveConditioning.unload(src.activeCooling));
    if (src.hasAppliedTemperature())
      dst.setAppliedTemperature(SEAppliedTemperature.unload(src.appliedTemperature));
  }

  public SEScalarPower getConvectiveHeatLoss()
  {
    if (convectiveHeatLoss == null)
      convectiveHeatLoss = new SEScalarPower();
    return convectiveHeatLoss;
  }
  public boolean hasConvectiveHeatLoss()
  {
    return convectiveHeatLoss == null ? false : convectiveHeatLoss.isValid();
  }
  
  public SEScalarHeatConductancePerArea getConvectiveHeatTranferCoefficient()
  {
    if (convectiveHeatTranferCoefficient == null)
      convectiveHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
    return convectiveHeatTranferCoefficient;
  }
  public boolean hasConvectiveHeatTranferCoefficient()
  {
    return convectiveHeatTranferCoefficient == null ? false : convectiveHeatTranferCoefficient.isValid();
  }
  
  public SEScalarPower getEvaporativeHeatLoss()
  {
    if (evaporativeHeatLoss == null)
      evaporativeHeatLoss = new SEScalarPower();
    return evaporativeHeatLoss;
  }
  public boolean hasEvaporativeHeatLoss()
  {
    return evaporativeHeatLoss == null ? false : evaporativeHeatLoss.isValid();
  }
  
  public SEScalarHeatConductancePerArea getEvaporativeHeatTranferCoefficient()
  {
    if (evaporativeHeatTranferCoefficient == null)
      evaporativeHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
    return evaporativeHeatTranferCoefficient;
  }
  public boolean hasEvaporativeHeatTranferCoefficient()
  {
    return evaporativeHeatTranferCoefficient == null ? false : evaporativeHeatTranferCoefficient.isValid();
  }
  
  public SEScalarPower getRadiativeHeatLoss()
  {
    if (radiativeHeatLoss == null)
      radiativeHeatLoss = new SEScalarPower();
    return radiativeHeatLoss;
  }
  public boolean hasRadiativeHeatLoss()
  {
    return radiativeHeatLoss == null ? false : radiativeHeatLoss.isValid();
  }
  
  public SEScalarHeatConductancePerArea getRadiativeHeatTranferCoefficient()
  {
    if (radiativeHeatTranferCoefficient == null)
      radiativeHeatTranferCoefficient = new SEScalarHeatConductancePerArea();
    return radiativeHeatTranferCoefficient;
  }
  public boolean hasRadiativeHeatTranferCoefficient()
  {
    return radiativeHeatTranferCoefficient == null ? false : radiativeHeatTranferCoefficient.isValid();
  }
  
  public SEScalarPower getRespirationHeatLoss()
  {
    if (respirationHeatLoss == null)
      respirationHeatLoss = new SEScalarPower();
    return respirationHeatLoss;
  }
  public boolean hasRespirationHeatLoss()
  {
    return respirationHeatLoss == null ? false : respirationHeatLoss.isValid();
  }
  
  public SEScalarPower getSkinHeatLoss()
  {
    if (skinHeatLoss == null)
      skinHeatLoss = new SEScalarPower();
    return skinHeatLoss;
  }
  public boolean hasSkinHeatLoss()
  {
    return skinHeatLoss == null ? false : skinHeatLoss.isValid();
  }
  
  public SEEnvironmentalConditions getConditions()
  {
    if (conditions == null)
      conditions = new SEEnvironmentalConditions();
    return conditions;
  }
  public boolean hasConditions()
  {
    return conditions != null;
  }
  
  public boolean hasActiveHeating()
  {
    return activeHeating != null;
  }
  public SEActiveConditioning getActiveHeating()
  {
    if (activeHeating == null)
      activeHeating = new SEActiveConditioning();
    return activeHeating;
  }
  
  public boolean hasActiveCooling()
  {
    return activeCooling != null;
  }
  public SEActiveConditioning getActiveCooling()
  {
    if (activeCooling == null)
      activeCooling = new SEActiveConditioning();
    return activeCooling;
  }
  
  public boolean hasAppliedTemperature()
  {
    return appliedTemperature != null;
  }
  public SEAppliedTemperature getAppliedTemperature()
  {
    if (appliedTemperature == null)
      appliedTemperature = new SEAppliedTemperature();
    return appliedTemperature;
  }
}