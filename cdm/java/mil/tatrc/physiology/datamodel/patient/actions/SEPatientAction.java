/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

import org.jfree.util.Log;

import com.kitware.physiology.cdm.PatientActions.AnyPatientActionData;
import com.kitware.physiology.cdm.PatientActions.PatientActionData;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceCompound;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions.SEOxygenWallPortPressureLoss;

public abstract class SEPatientAction extends SEAction
{
  public SEPatientAction()
  {
    
  }
  
  public void copy(SEPatientAction other)
  {
    super.copy(other);
  }
  
  public void reset()
  {
    super.reset();
  }
  
  public static void load(PatientActionData src, SEPatientAction dst) 
  {
    SEAction.load(src.getAction(), dst);
  }
  protected static void unload(SEPatientAction src, PatientActionData.Builder dst)
  {
    SEAction.unload(src, dst.getActionBuilder());
  }
  
  public static SEPatientAction ANY2CDM(AnyPatientActionData c, SESubstanceManager subMgr) 
  {
    switch(c.getActionCase())
    {
    case ASSESSMENT:
    {
      SEPatientAssessmentRequest dst = new SEPatientAssessmentRequest();
      SEPatientAssessmentRequest.load(c.getAssessment(), dst);
      return dst;
    }
    case ACUTESTRESS:
    {
      SEAcuteStress dst = new SEAcuteStress();
      SEAcuteStress.load(c.getAcuteStress(), dst);
      return dst;
    }
    case AIRWAYOBSTRUCTION:
    {
      SEAirwayObstruction dst = new SEAirwayObstruction();
      SEAirwayObstruction.load(c.getAirwayObstruction(), dst);
      return dst;
    }
    case APNEA:
    {
      SEApnea dst = new SEApnea();
      SEApnea.load(c.getApnea(), dst);
      return dst;
    }
    case ASTHMAATTACK:
    {
      SEAsthmaAttack dst = new SEAsthmaAttack();
      SEAsthmaAttack.load(c.getAsthmaAttack(), dst);
      return dst;
    }
    case BRAININJURY:
    {
      SEBrainInjury dst = new SEBrainInjury();
      SEBrainInjury.load(c.getBrainInjury(), dst);
      return dst;
    }
    case BRONCHOCONSTRICTION:
    {
      SEBronchoconstriction dst = new SEBronchoconstriction();
      SEBronchoconstriction.load(c.getBronchoconstriction(), dst);
      return dst;
    }
    case CARDIACARREST:
    {
      SECardiacArrest dst = new SECardiacArrest();
      SECardiacArrest.load(c.getCardiacArrest(), dst);
      return dst;
    }
    case CHESTCOMPRESSIONFORCE:
    {
      SEChestCompressionForce dst = new SEChestCompressionForce();
      SEChestCompressionForce.load(c.getChestCompressionForce(), dst);
      return dst;
    }
    case CHESTCOMPRESSIONFORCESCALE:
    {
      SEChestCompressionForceScale dst = new SEChestCompressionForceScale();
      SEChestCompressionForceScale.load(c.getChestCompressionForceScale(), dst);
      return dst;
    }
    case CHESTOCCLUSIVEDRESSING:
    {
      SEChestOcclusiveDressing dst = new SEChestOcclusiveDressing();
      SEChestOcclusiveDressing.load(c.getChestOcclusiveDressing(), dst);
      return dst;
    }
    case CONSCIOUSRESPIRATION:
    {
      SEConsciousRespiration dst = new SEConsciousRespiration();
      SEConsciousRespiration.load(c.getConsciousRespiration(), dst);
      return dst;
    }
    case CONSUMENUTRIENTS:
    {
      SEConsumeNutrients dst = new SEConsumeNutrients();
      SEConsumeNutrients.load(c.getConsumeNutrients(), dst);;
      return dst;
    }
    case EXERCISE:
    {
      SEExercise dst = new SEExercise();
      SEExercise.load(c.getExercise(), dst);
      return dst;
    }
    case HEMORRHAGE:
    {
      SEHemorrhage dst = new SEHemorrhage();
      SEHemorrhage.load(c.getHemorrhage(), dst);
      return dst;
    }
    case INTUBATION:
    {
      SEIntubation dst = new SEIntubation();
      SEIntubation.load(c.getIntubation(), dst);
      return dst;
    }
    case MECHANICALVENTILATION:
    {
      SEMechanicalVentilation dst = new SEMechanicalVentilation();
      SEMechanicalVentilation.load(c.getMechanicalVentilation(), dst, subMgr);
      return dst;
    }
    case NEEDLEDECOMPRESSION:
    {
      SENeedleDecompression dst = new SENeedleDecompression();
      SENeedleDecompression.load(c.getNeedleDecompression(), dst);
      return dst;
    }
    case PERICARDIALEFFUSION:
    {
      SEPericardialEffusion dst = new SEPericardialEffusion();
      SEPericardialEffusion.load(c.getPericardialEffusion(), dst);
      return dst;
    }
    case TENSIONPNEUMOTHORAX:
    {
      SETensionPneumothorax dst = new SETensionPneumothorax();
      SETensionPneumothorax.load(c.getTensionPneumothorax(), dst);
      return dst;
    }
    case SUBSTANCEBOLUS:
    {
      SESubstance sub = subMgr.getSubstance(c.getSubstanceBolus().getSubstance());
      SESubstanceBolus dst = new SESubstanceBolus(sub);
      SESubstanceBolus.load(c.getSubstanceBolus(), dst);
      return dst;
    }
    case SUBSTANCECOMPOUNDINFUSION:
    {
      SESubstanceCompound cmpd = subMgr.getCompound(c.getSubstanceCompoundInfusion().getSubstanceCompound());
      SESubstanceCompoundInfusion dst = new SESubstanceCompoundInfusion(cmpd);
      SESubstanceCompoundInfusion.load(c.getSubstanceCompoundInfusion(), dst);
      return dst;
    }
    case SUBSTANCEINFUSION:
    {
      SESubstance sub = subMgr.getSubstance(c.getSubstanceInfusion().getSubstance());
      SESubstanceInfusion dst = new SESubstanceInfusion(sub);
      SESubstanceInfusion.load(c.getSubstanceInfusion(), dst);
      return dst;
    }
    case URINATE:
    {
      SEUrinate dst = new SEUrinate();
      SEUrinate.load(c.getUrinate(), dst);
      return dst;
    }
    case ACTION_NOT_SET:
      Log.warn("AnyPatientActionData was empty...was that intended?");
      return null;
    }
    Log.error("Unsupported Patient Action type "+c.getActionCase());
    return null;
  }
  public static AnyPatientActionData CDM2ANY(SEPatientAction c)
  {
    AnyPatientActionData.Builder dst = AnyPatientActionData.newBuilder();
    if(c instanceof SEPatientAssessmentRequest)
    {
      dst.setAssessment(SEPatientAssessmentRequest.unload((SEPatientAssessmentRequest)c));
      return dst.build();
    }
    if(c instanceof SEAcuteStress)
    {
      dst.setAcuteStress(SEAcuteStress.unload((SEAcuteStress)c));
      return dst.build();
    }
    if(c instanceof SEAirwayObstruction)
    {
      dst.setAirwayObstruction(SEAirwayObstruction.unload((SEAirwayObstruction)c));
      return dst.build();
    }
    if(c instanceof SEApnea)
    {
      dst.setApnea(SEApnea.unload((SEApnea)c));
      return dst.build();
    }
    if(c instanceof SEAsthmaAttack)
    {
      dst.setAsthmaAttack(SEAsthmaAttack.unload((SEAsthmaAttack)c));
      return dst.build();
    }
    if(c instanceof SEBrainInjury)
    {
      dst.setBrainInjury(SEBrainInjury.unload((SEBrainInjury)c));
      return dst.build();
    }
    if(c instanceof SEBronchoconstriction)
    {
      dst.setBronchoconstriction(SEBronchoconstriction.unload((SEBronchoconstriction)c));
      return dst.build();
    }
    if(c instanceof SECardiacArrest)
    {
      dst.setCardiacArrest(SECardiacArrest.unload((SECardiacArrest)c));
      return dst.build();
    }
    if(c instanceof SEChestCompressionForce)
    {
      dst.setChestCompressionForce(SEChestCompressionForce.unload((SEChestCompressionForce)c));
      return dst.build();
    }
    if(c instanceof SEChestCompressionForceScale)
    {
      dst.setChestCompressionForceScale(SEChestCompressionForceScale.unload((SEChestCompressionForceScale)c));
      return dst.build();
    }
    if(c instanceof SEChestOcclusiveDressing)
    {
      dst.setChestOcclusiveDressing(SEChestOcclusiveDressing.unload((SEChestOcclusiveDressing)c));
      return dst.build();
    }
    if(c instanceof SEConsciousRespiration)
    {
      dst.setConsciousRespiration(SEConsciousRespiration.unload((SEConsciousRespiration)c));
      return dst.build();
    }
    if(c instanceof SEConsumeNutrients)
    {
      dst.setConsumeNutrients(SEConsumeNutrients.unload((SEConsumeNutrients)c));
      return dst.build();
    }
    if(c instanceof SEExercise)
    {
      dst.setExercise(SEExercise.unload((SEExercise)c));
      return dst.build();
    }
    if(c instanceof SEHemorrhage)
    {
      dst.setHemorrhage(SEHemorrhage.unload((SEHemorrhage)c));
      return dst.build();
    }
    if(c instanceof SEIntubation)
    {
      dst.setIntubation(SEIntubation.unload((SEIntubation)c));
      return dst.build();
    }
    if(c instanceof SEMechanicalVentilation)
    {
      dst.setMechanicalVentilation(SEMechanicalVentilation.unload((SEMechanicalVentilation)c));
      return dst.build();
    }
    if(c instanceof SENeedleDecompression)
    {
      dst.setNeedleDecompression(SENeedleDecompression.unload((SENeedleDecompression)c));
      return dst.build();
    }
    if(c instanceof SEPericardialEffusion)
    {
      dst.setPericardialEffusion(SEPericardialEffusion.unload((SEPericardialEffusion)c));
      return dst.build();
    }
    if(c instanceof SETensionPneumothorax)
    {
      dst.setTensionPneumothorax(SETensionPneumothorax.unload((SETensionPneumothorax)c));
      return dst.build();
    }
    if(c instanceof SESubstanceBolus)
    {
      dst.setSubstanceBolus(SESubstanceBolus.unload((SESubstanceBolus)c));
      return dst.build();
    }
    if(c instanceof SESubstanceCompoundInfusion)
    {
      dst.setSubstanceCompoundInfusion(SESubstanceCompoundInfusion.unload((SESubstanceCompoundInfusion)c));
      return dst.build();
    }
    if(c instanceof SESubstanceInfusion)
    {
      dst.setSubstanceInfusion(SESubstanceInfusion.unload((SESubstanceInfusion)c));
      return dst.build();
    }
    if(c instanceof SEUrinate)
    {
      dst.setUrinate(SEUrinate.unload((SEUrinate)c));
      return dst.build();
    }
    Log.error("Unsupported Patient Action type "+c);
    return dst.build();
  }
  
  public abstract String toString();
}
