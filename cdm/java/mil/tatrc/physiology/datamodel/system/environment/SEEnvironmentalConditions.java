/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.environment;

import java.util.*;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Environment.EnvironmentData;
import com.kitware.physiology.cdm.Environment.EnvironmentData.eSurroundingType;
import com.kitware.physiology.cdm.Substance.SubstanceData;

import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;

import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.datamodel.substance.SESubstance;
import mil.tatrc.physiology.datamodel.substance.SESubstanceCompound;
import mil.tatrc.physiology.datamodel.substance.SESubstanceConcentration;
import mil.tatrc.physiology.datamodel.substance.SESubstanceFractionAmount;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;

public class SEEnvironmentalConditions
{
  protected eSurroundingType                surroundingType;
  protected SEScalarMassPerVolume           airDensity;
  protected SEScalarLengthPerTime           airVelocity;
  protected SEScalarTemperature             ambientTemperature;
  protected SEScalarPressure                atmosphericPressure;
  protected SEScalarHeatResistanceArea      clothingResistance;
  protected SEScalar0To1                    emissivity;
  protected SEScalarTemperature             meanRadiantTemperature;
  protected SEScalar0To1                    relativeHumidity;
  protected SEScalarTemperature             respirationAmbientTemperature;

  protected List<SESubstanceFractionAmount> ambientGases;
  protected List<SESubstanceConcentration>  ambientAerosols;
  
  
  public SEEnvironmentalConditions()
  {
    this.surroundingType=null;

    this.airDensity=null;
    this.airVelocity=null;
    this.ambientTemperature=null;
    this.atmosphericPressure=null;
    this.clothingResistance=null;
    this.emissivity=null;
    this.meanRadiantTemperature=null;
    this.relativeHumidity=null;
    this.respirationAmbientTemperature=null;

    this.ambientGases=new ArrayList<SESubstanceFractionAmount>();
    this.ambientAerosols=new ArrayList<SESubstanceConcentration>();

  }
  
  public void reset()
  {
    surroundingType = null;
    if (airDensity != null)
      airDensity.invalidate();
    if (airVelocity != null)
      airVelocity.invalidate();
    if (ambientTemperature != null)
      ambientTemperature.invalidate();
    if (atmosphericPressure != null)
      atmosphericPressure.invalidate();
    if (clothingResistance != null)
      clothingResistance.invalidate();
    if (emissivity != null)
      emissivity.invalidate();
    if (meanRadiantTemperature != null)
      meanRadiantTemperature.invalidate();
    if (relativeHumidity != null)
      relativeHumidity.invalidate();
    if (respirationAmbientTemperature != null)
      respirationAmbientTemperature.invalidate();
    
    this.ambientGases.clear();
    this.ambientAerosols.clear();
  }
  
  public void copy(SEEnvironmentalConditions from)
  {
    this.reset();
    if(from.surroundingType != eSurroundingType.NullSurrounding)
      this.setSurroundingType(from.surroundingType);
    if(from.hasAirDensity())
      this.getAirDensity().set(from.getAirDensity());
    if(from.hasAirVelocity())
      this.getAirVelocity().set(from.getAirVelocity());
    if(from.hasAmbientTemperature())
      this.getAmbientTemperature().set(from.getAmbientTemperature());
    if(from.hasAtmosphericPressure())
      this.getAtmosphericPressure().set(from.getAtmosphericPressure());
    if(from.hasClothingResistance())
      this.getClothingResistance().set(from.getClothingResistance());
    if(from.hasEmissivity())
      this.getEmissivity().set(from.getEmissivity());
    if(from.hasMeanRadiantTemperature())
      this.getMeanRadiantTemperature().set(from.getMeanRadiantTemperature());
    if(from.hasRelativeHumidity())
      this.getRelativeHumidity().set(from.getRelativeHumidity());
    if(from.hasRespirationAmbientTemperature())
      this.getRespirationAmbientTemperature().set(from.getRespirationAmbientTemperature());
    
    if(from.ambientGases!=null)
    {
      SESubstanceFractionAmount mine;
      for(SESubstanceFractionAmount sf : from.ambientGases)
      {
        mine=this.createAmbientGas(sf.getSubstance());
        if(sf.hasAmount())
          mine.getAmount().set(sf.getAmount());
      }
    }    
    
    if(from.ambientAerosols!=null)
    {
      SESubstanceConcentration mine;
      for(SESubstanceConcentration sc : from.ambientAerosols)
      {
        mine=this.createAmbientAerosol(sc.getSubstance());
        if(sc.hasConcentration())
          mine.getConcentration().set(sc.getConcentration());
      }
    }    
  }
  
  public void readFile(String fileName, SESubstanceManager mgr) throws ParseException
  {
    EnvironmentData.ConditionsData.Builder builder = EnvironmentData.ConditionsData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEEnvironmentalConditions.load(builder.build(), this, mgr);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEEnvironmentalConditions.unload(this).toString());
  }
  
  public static void load(EnvironmentData.ConditionsData src, SEEnvironmentalConditions dst, SESubstanceManager substances)
  {
    dst.reset();
    if (src.getSurroundingType() != eSurroundingType.UNRECOGNIZED)
      dst.setSurroundingType(src.getSurroundingType());
    if (src.hasAirDensity())
      SEScalarMassPerVolume.load(src.getAirDensity(),dst.getAirDensity());
    if (src.hasAirVelocity())
      SEScalarLengthPerTime.load(src.getAirVelocity(),dst.getAirVelocity());
    if (src.hasAmbientTemperature())
      SEScalarTemperature.load(src.getAmbientTemperature(),dst.getAmbientTemperature());
    if (src.hasAtmosphericPressure())
      SEScalarPressure.load(src.getAtmosphericPressure(),dst.getAtmosphericPressure());
    if (src.hasClothingResistance())
      SEScalarHeatResistanceArea.load(src.getClothingResistance(),dst.getClothingResistance());
    if (src.hasEmissivity())
      SEScalar0To1.load(src.getEmissivity(),dst.getEmissivity());
    if (src.hasMeanRadiantTemperature())
      SEScalarTemperature.load(src.getMeanRadiantTemperature(),dst.getMeanRadiantTemperature());
    if (src.hasRelativeHumidity())
      SEScalar0To1.load(src.getRelativeHumidity(),dst.getRelativeHumidity());
    if (src.hasRespirationAmbientTemperature())
      SEScalarTemperature.load(src.getRespirationAmbientTemperature(),dst.getRespirationAmbientTemperature());
    
    SESubstance sub;
    if(src.getAmbientGasList()!=null)
    {
      for(SubstanceData.FractionAmountData subData : src.getAmbientGasList())
      {
        sub = substances.getSubstance(subData.getName());
        if(sub == null)
        {
          Log.error("Substance does not exist for ambient gas : "+subData.getName());
          continue;
        }
        if(sub.getState() != SubstanceData.eState.Gas)
        {
          Log.error("Environment Ambient Gas must be a gas, "+subData.getName()+" is not a gas...");
          continue;
        }
        SEScalar0To1.load(subData.getAmount(),dst.createAmbientGas(sub).getAmount());
      }
    }
    
    if(src.getAmbientAerosolList()!=null)
    {
      for(SubstanceData.ConcentrationData subData : src.getAmbientAerosolList())
      {
        sub = substances.getSubstance(subData.getName());
        if(sub == null)
        {
          Log.error("Substance does not exist for ambient aerosol : "+subData.getName());
          continue;
        }
        if(sub.getState() != SubstanceData.eState.Solid && sub.getState() != SubstanceData.eState.Liquid)
        {
          Log.error("Environment Ambient Aerosol must be a liquid or a gas, "+subData.getName()+" is neither...");
          continue;
        }
        SEScalarMassPerVolume.load(subData.getConcentration(),dst.createAmbientAerosol(sub).getConcentration());
      }
    }
  }
  public static EnvironmentData.ConditionsData unload(SEEnvironmentalConditions src)
  {
    EnvironmentData.ConditionsData.Builder dst = EnvironmentData.ConditionsData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEEnvironmentalConditions src, EnvironmentData.ConditionsData.Builder dst)
  {
  	if(src.hasSurroundingType())
  		dst.setSurroundingType(src.surroundingType);
    if (src.hasAirDensity())
      dst.setAirDensity(SEScalarMassPerVolume.unload(src.airDensity));
    if (src.hasAirVelocity())
      dst.setAirVelocity(SEScalarLengthPerTime.unload(src.airVelocity));
    if (src.hasAmbientTemperature())
      dst.setAmbientTemperature(SEScalarTemperature.unload(src.ambientTemperature));
    if (src.hasAtmosphericPressure())
      dst.setAtmosphericPressure(SEScalarPressure.unload(src.atmosphericPressure));    
    if (src.hasClothingResistance())
      dst.setClothingResistance(SEScalarHeatResistanceArea.unload(src.clothingResistance));
    if (src.hasEmissivity())
      dst.setEmissivity(SEScalar0To1.unload(src.emissivity));  
    if (src.hasMeanRadiantTemperature())
      dst.setMeanRadiantTemperature(SEScalarTemperature.unload(src.meanRadiantTemperature));
    if (src.hasRelativeHumidity())
      dst.setRelativeHumidity(SEScalar0To1.unload(src.relativeHumidity));
    if (src.hasRespirationAmbientTemperature())
      dst.setRespirationAmbientTemperature(SEScalarTemperature.unload(src.respirationAmbientTemperature));    
    
    for(SESubstanceFractionAmount ambSub : src.ambientGases)
      dst.addAmbientGas(SESubstanceFractionAmount.unload(ambSub));
    
    for(SESubstanceConcentration ambSub : src.ambientAerosols)
      dst.addAmbientAerosol(SESubstanceConcentration.unload(ambSub));
  }
  
  public boolean hasSurroundingType()
  {
    return surroundingType != null;
  }
  public eSurroundingType getSurroundingType()
  {
    return surroundingType;
  }
  public void setSurroundingType(eSurroundingType st)
  {
    this.surroundingType = (st==eSurroundingType.UNRECOGNIZED) ? null : st;
  }
  public SEScalarMassPerVolume getAirDensity()
  {
    if (airDensity == null)
      airDensity = new SEScalarMassPerVolume();
    return airDensity;
  }
  public boolean hasAirDensity()
  {
    return airDensity == null ? false : airDensity.isValid();
  }
  
  public SEScalarLengthPerTime getAirVelocity()
  {
    if (airVelocity == null)
      airVelocity = new SEScalarLengthPerTime();
    return airVelocity;
  }
  public boolean hasAirVelocity()
  {
    return airVelocity == null ? false : airVelocity.isValid();
  }
  
  public SEScalarTemperature getAmbientTemperature()
  {
    if (ambientTemperature == null)
      ambientTemperature = new SEScalarTemperature();
    return ambientTemperature;
  }
  public boolean hasAmbientTemperature()
  {
    return ambientTemperature == null ? false : ambientTemperature.isValid();
  }

  public SEScalarPressure getAtmosphericPressure()
  {
    if (atmosphericPressure == null)
      atmosphericPressure = new SEScalarPressure();
    return atmosphericPressure;
  }
  public boolean hasAtmosphericPressure()
  {
    return atmosphericPressure == null ? false : atmosphericPressure.isValid();
  }
  
  public SEScalarHeatResistanceArea getClothingResistance()
  {
    if (clothingResistance == null)
      clothingResistance = new SEScalarHeatResistanceArea();
    return clothingResistance;
  }
  public boolean hasClothingResistance()
  {
    return clothingResistance == null ? false : clothingResistance.isValid();
  }
  
  public SEScalar0To1 getEmissivity()
  {
      if (emissivity == null)
        emissivity = new SEScalar0To1();
      return emissivity;
  }
  public boolean hasEmissivity()
  {
      return emissivity == null ? false : emissivity.isValid();
  }
  
  public SEScalarTemperature getMeanRadiantTemperature()
  {
    if (meanRadiantTemperature == null)
      meanRadiantTemperature = new SEScalarTemperature();
    return meanRadiantTemperature;
  }
  public boolean hasMeanRadiantTemperature()
  {
    return meanRadiantTemperature == null ? false : meanRadiantTemperature.isValid();
  }
  
  public SEScalar0To1 getRelativeHumidity()
  {
    if (relativeHumidity == null)
      relativeHumidity = new SEScalar0To1();
    return relativeHumidity;
  }
  public boolean hasRelativeHumidity()
  {
    return relativeHumidity == null ? false : relativeHumidity.isValid();
  }
  
  public SEScalarTemperature getRespirationAmbientTemperature()
  {
    if (respirationAmbientTemperature == null)
      respirationAmbientTemperature = new SEScalarTemperature();
    return respirationAmbientTemperature;
  }
  public boolean hasRespirationAmbientTemperature()
  {
    return respirationAmbientTemperature == null ? false : respirationAmbientTemperature.isValid();
  }
  
  public SESubstanceFractionAmount createAmbientGas(SESubstance substance)
  {
    return getAmbientGas(substance);
  }
  public SESubstanceFractionAmount getAmbientGas(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.ambientGases)
    {
      if(sf.getSubstance().getName().equals(substance.getName()))
      {        
        return sf;
      }
    }    
    SESubstanceFractionAmount sf = new SESubstanceFractionAmount(substance);    
    this.ambientGases.add(sf);
    return sf;
  }
  public boolean hasAmbientGas()
  {
    return !this.ambientGases.isEmpty();
  }
  public boolean hasAmbientGas(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.ambientGases)
    {
      if(sf.getSubstance()==substance)
      {        
        return true;
      }
    }
    return false;
  }
  public List<SESubstanceFractionAmount> getAmbientGas()
  {
    return this.ambientGases;
  }
  public void removeAmbientGas(SESubstance substance)
  {
    for(SESubstanceFractionAmount sf : this.ambientGases)
    {
      if(sf.getSubstance()==substance)
      {
        this.ambientGases.remove(sf);
        return;
      }
    }  
  }

  
  public SESubstanceConcentration createAmbientAerosol(SESubstance substance)
  {
    return getAmbientAerosol(substance);
  }
  public SESubstanceConcentration getAmbientAerosol(SESubstance substance)
  {
    for(SESubstanceConcentration sc : this.ambientAerosols)
    {
      if(sc.getSubstance().getName().equals(substance.getName()))
      {        
        return sc;
      }
    }    
    SESubstanceConcentration sc = new SESubstanceConcentration(substance);    
    this.ambientAerosols.add(sc);
    return sc;
  }
  public boolean hasAmbientAerosol()
  {
    return !this.ambientAerosols.isEmpty();
  }
  public boolean hasAmbientAerosol(SESubstance substance)
  {
    for(SESubstanceConcentration sc : this.ambientAerosols)
    {
      if(sc.getSubstance()==substance)
      {        
        return true;
      }
    }
    return false;
  }
  public List<SESubstanceConcentration> getAmbientAerosol()
  {
    return Collections.unmodifiableList(this.ambientAerosols);
  }
  public void removeAmbientAerosol(SESubstance substance)
  {
    for(SESubstanceConcentration sc : this.ambientAerosols)
    {
      if(sc.getSubstance()==substance)
      {
        this.ambientAerosols.remove(sc);
        return;
      }
    }  
  }
  
  
  public void trim()
  {
    SESubstanceConcentration sc;
    Iterator<SESubstanceConcentration> icon = this.ambientAerosols.iterator();
    while(icon.hasNext())
    {
      sc=icon.next();
      if(sc.getConcentration().getValue()==0)
        icon.remove();
    }    
    
    SESubstanceFractionAmount sf;
    Iterator<SESubstanceFractionAmount> ifrac = this.ambientGases.iterator();
    while(ifrac.hasNext())
    {
      sf=ifrac.next();
      if(sf.getAmount().getValue()==0)
        ifrac.remove();
    }    
  }
  
  public String toString()
  {
      String str = "Envriomental Conditions:" 
          + "\n\tSurroundingType: " + getSurroundingType()
          + "\n\tAirDensity: " + (hasAirDensity()?getAirDensity():"None")
          + "\n\tAirVelocity: " + (hasAirVelocity()?getAirVelocity():"None")
          + "\n\tAmbientTemperature: " + (hasAmbientTemperature()?getAmbientTemperature():"None")
          + "\n\tAtmosphericPressure: " + (hasAtmosphericPressure()?getAtmosphericPressure():"None")
          + "\n\tClothingResistance: " + (hasClothingResistance()?getClothingResistance():"None")
          + "\n\tEmissivity: " + (hasEmissivity()?getEmissivity():"None")
          + "\n\tMeanRadiantTemperature: " + (hasMeanRadiantTemperature()?getMeanRadiantTemperature():"None")
          + "\n\tRelativeHumidity: " + (hasRelativeHumidity()?getRelativeHumidity():"None")
          + "\n\tRespirationAmbientTemperature: " + (hasRespirationAmbientTemperature()?getRespirationAmbientTemperature():"None");
      for(SESubstanceFractionAmount sf : this.ambientGases)
        str += "\n\t"+sf.toString();
      for(SESubstanceConcentration sc : this.ambientAerosols)
      str += "\n\t"+sc.toString();
      
      return str;
  }
  
  
}