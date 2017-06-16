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

package mil.tatrc.physiology.datamodel.patient.conditions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.PatientConditions.AnyPatientConditionData;
import com.kitware.physiology.cdm.PatientConditions.PatientConditionData;

import mil.tatrc.physiology.datamodel.conditions.SECondition;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public abstract class SEPatientCondition extends SECondition
{
  public SEPatientCondition()
  {
    
  }
  
  public void copy(SEPatientCondition other)
  {
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(PatientConditionData src, SEPatientCondition dst)
  {
    SECondition.load(src.getCondition(), dst);
  }
  
  protected static void unload(SEPatientCondition src, PatientConditionData.Builder dst)
  {
    SECondition.unload(src,dst.getConditionBuilder());
  }
  
  public abstract String toString();

  public static SEPatientCondition ANY2CDM(AnyPatientConditionData c, SESubstanceManager subMgr) 
  {
    switch(c.getConditionCase())
    {
    case CHRONICANEMIA:
    {
      SEChronicAnemia newC = new SEChronicAnemia();
      SEChronicAnemia.load(c.getChronicAnemia(), newC);
      return newC;
    }
    case CHRONICOBSTRUCTIVEPULMONARYDISEASE:
    {
      SEChronicObstructivePulmonaryDisease newC = new SEChronicObstructivePulmonaryDisease();
      SEChronicObstructivePulmonaryDisease.load(c.getChronicObstructivePulmonaryDisease(), newC);
      return newC;
    }
    case CHRONICPERICARDIALEFFUSION:
    {
      SEChronicPericardialEffusion newC = new SEChronicPericardialEffusion();
      SEChronicPericardialEffusion.load(c.getChronicPericardialEffusion(), newC);
      return newC;
    }
    case CHRONICRENALSTENOSIS:
    {
      SEChronicRenalStenosis newC = new SEChronicRenalStenosis();
      SEChronicRenalStenosis.load(c.getChronicRenalStenosis(), newC);
      return newC;
    }
    case CHRONICVENTRICULARSYSTOLICDYSFUNCTION:
    {
      SEChronicVentricularSystolicDysfunction newC = new SEChronicVentricularSystolicDysfunction();
      SEChronicVentricularSystolicDysfunction.load(c.getChronicVentricularSystolicDysfunction(), newC);
      return newC;
    }
    case CONSUMEMEAL:
    {
      SEConsumeMeal newC = new SEConsumeMeal();
      SEConsumeMeal.load(c.getConsumeMeal(), newC);
      return newC;      
    }
    case IMPAIREDALVEOLAREXCHANGE:
    {
      SEImpairedAlveolarExchange newC = new SEImpairedAlveolarExchange();
      SEImpairedAlveolarExchange.load(c.getImpairedAlveolarExchange(), newC);
      return newC;      
    }
    case LOBARPNEUMONIA:
    {
      SELobarPneumonia newC = new SELobarPneumonia();
      SELobarPneumonia.load(c.getLobarPneumonia(), newC);
      return newC;
    }
    case CONDITION_NOT_SET:
      Log.warn("AnyPatientConditionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported Patient condition type "+c.getConditionCase());
    return null;
  }
  public static AnyPatientConditionData CDM2ANY(SEPatientCondition c)
  {
    AnyPatientConditionData.Builder dst = AnyPatientConditionData.newBuilder();
    if(c instanceof SEChronicAnemia)
    {
      dst.setChronicAnemia(SEChronicAnemia.unload((SEChronicAnemia)c));    
      return dst.build();
    }
    if(c instanceof SEChronicObstructivePulmonaryDisease)
    {
      dst.setChronicObstructivePulmonaryDisease(SEChronicObstructivePulmonaryDisease.unload((SEChronicObstructivePulmonaryDisease)c));    
      return dst.build();
    }
    if(c instanceof SEChronicPericardialEffusion)
    {
      dst.setChronicPericardialEffusion(SEChronicPericardialEffusion.unload((SEChronicPericardialEffusion)c));    
      return dst.build();
    }
    if(c instanceof SEChronicRenalStenosis)
    {
      dst.setChronicRenalStenosis(SEChronicRenalStenosis.unload((SEChronicRenalStenosis)c));    
      return dst.build();
    }
    if(c instanceof SEChronicVentricularSystolicDysfunction)
    {
      dst.setChronicVentricularSystolicDysfunction(SEChronicVentricularSystolicDysfunction.unload((SEChronicVentricularSystolicDysfunction)c));    
      return dst.build();
    }
    if(c instanceof SEConsumeMeal)
    {
      dst.setConsumeMeal(SEConsumeMeal.unload((SEConsumeMeal)c));    
      return dst.build();
    }
    if(c instanceof SEImpairedAlveolarExchange)
    {
      dst.setImpairedAlveolarExchange(SEImpairedAlveolarExchange.unload((SEImpairedAlveolarExchange)c));    
      return dst.build();
    }
    if(c instanceof SELobarPneumonia)
    {
      dst.setLobarPneumonia(SELobarPneumonia.unload((SELobarPneumonia)c));    
      return dst.build();
    }
    Log.error("Unsupported Patient condition type "+c);
    return dst.build();
  }
}
