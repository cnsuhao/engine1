/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.substance;

import java.util.*;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Patient.PatientData;
import com.kitware.physiology.cdm.Substance.SubstanceData;
import com.kitware.physiology.cdm.Substance.SubstanceData.eState;

import mil.tatrc.physiology.datamodel.patient.SEPatient;
import mil.tatrc.physiology.datamodel.properties.*;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.StringUtils;

public class SESubstance
{
  protected eState                           state;
  protected String                           name;
  protected SEScalarMassPerVolume            density;
  protected SEScalarMassPerAmount            molarMass;
  // Diffusion related-ish
  protected SEScalarMassPerAreaTime          maximumDiffusionFlux;
  protected SEScalar                         michaelisCoefficient;
  // Liquid related-ish
  protected SESubstanceAerosolization        aerosolization;
  protected SEScalarMassPerVolume            bloodConcentration;
  protected SEScalarMass                     massInBody;  
  protected SEScalarMass                     massInBlood;  
  protected SEScalarMass                     massInTissue;  
  protected SEScalarMassPerVolume            plasmaConcentration;
  protected SEScalarMass                     systemicMassCleared;
  protected SEScalarMassPerVolume            tissueConcentration;
  // Gas related-ish
  protected SEScalarVolumePerTime            alveolarTransfer;
  protected SEScalarVolumePerTimePressure    diffusingCapacity;
  protected SEScalar0To1                     endTidalFraction;
  protected SEScalarPressure                 endTidalPressure;
  protected SEScalar                         relativeDiffusionCoefficient;
  protected SEScalarInversePressure          solubilityCoefficient;
  
  protected SESubstanceClearance             clearance;
  protected SESubstancePharmacokinetics      pk;
  protected SESubstancePharmacodynamics      pd;
  
  public SESubstance()
  {
    
  }
  
  public void reset()
  {
    this.name=null;
    this.state=null;
    if(this.density!=null)
      this.density.invalidate();
    if(this.molarMass!=null)
      this.molarMass.invalidate();
    
    if(this.maximumDiffusionFlux!=null)
      this.maximumDiffusionFlux.invalidate();
    if(this.michaelisCoefficient!=null)
      this.michaelisCoefficient.invalidate();
    
    if(this.aerosolization!=null)
      this.aerosolization.reset();
    if(this.bloodConcentration!=null)
       this.bloodConcentration.invalidate();
    if(this.massInBody!=null)
      this.massInBody.invalidate();
    if(this.massInBlood!=null)
      this.massInBlood.invalidate();
    if(this.massInTissue!=null)
      this.massInTissue.invalidate();
    if(this.plasmaConcentration!=null)
      this.plasmaConcentration.invalidate();
    if(this.systemicMassCleared!=null)
      this.systemicMassCleared.invalidate();
    if(this.tissueConcentration!=null)
      this.tissueConcentration.invalidate();
    
    if(this.alveolarTransfer!=null)
      this.alveolarTransfer.invalidate();
    if(this.diffusingCapacity!=null)
      this.diffusingCapacity.invalidate();
    if(this.endTidalFraction!=null)
      this.endTidalFraction.invalidate();
    if(this.endTidalPressure!=null)
      this.endTidalPressure.invalidate();
    if(this.relativeDiffusionCoefficient!=null)
      this.relativeDiffusionCoefficient.invalidate();
    if(this.solubilityCoefficient!=null)
      this.solubilityCoefficient.invalidate();
    
    if(this.clearance!=null)
      this.clearance.reset();
    if(this.pk!=null)
      this.pk.reset();
    if(this.pd!=null)
      this.pd.reset();    
  }
  
  public void readFile(String fileName) throws ParseException
  {
    SubstanceData.Builder builder = SubstanceData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SESubstance.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SESubstance.unload(this).toString());
  }
  
  public static void load(SubstanceData src, SESubstance dst)
  {
    dst.reset();
    if(src.getName()!=null)
      dst.setName(src.getName());
    if(src.getState()!=eState.UNRECOGNIZED)
      dst.setState(src.getState());
    if(src.hasDensity())
      SEScalarMassPerVolume.load(src.getDensity(), dst.getDensity());    
    if(src.hasMolarMass())
      SEScalarMassPerAmount.load(src.getMolarMass(),dst.getMolarMass());
    
    if(src.hasMaximumDiffusionFlux())
      SEScalarMassPerAreaTime.load(src.getMaximumDiffusionFlux(),dst.getMaximumDiffusionFlux());
    if(src.hasMichaelisCoefficient())
      SEScalar.load(src.getMichaelisCoefficient(),dst.getMichaelisCoefficient());
        
    if(src.hasAerosolization())
      SESubstanceAerosolization.load(src.getAerosolization(),dst.getAerosolization());
    if(src.hasBloodConcentration())
      SEScalarMassPerVolume.load(src.getBloodConcentration(),dst.getBloodConcentration());
    if(src.hasMassInBody())
      SEScalarMass.load(src.getMassInBody(),dst.getMassInBody());
    if(src.hasMassInBlood())
      SEScalarMass.load(src.getMassInBlood(),dst.getMassInBlood());
    if(src.hasMassInTissue())
      SEScalarMass.load(src.getMassInTissue(),dst.getMassInTissue());
    if(src.hasPlasmaConcentration())
      SEScalarMassPerVolume.load(src.getPlasmaConcentration(),dst.getPlasmaConcentration());
    if(src.hasSystemicMassCleared())
      SEScalarMass.load(src.getSystemicMassCleared(),dst.getSystemicMassCleared());
    if(src.hasTissueConcentration())
      SEScalarMassPerVolume.load(src.getTissueConcentration(),dst.getTissueConcentration());
    
    if(src.hasAlveolarTransfer())
      SEScalarVolumePerTime.load(src.getAlveolarTransfer(),dst.getAlveolarTransfer());
    if(src.hasDiffusingCapacity())
      SEScalarVolumePerTimePressure.load(src.getDiffusingCapacity(),dst.getDiffusingCapacity());
    if(src.hasEndTidalFraction())
      SEScalar0To1.load(src.getEndTidalFraction(),dst.getEndTidalFraction());
    if(src.hasEndTidalPressure())
      SEScalarPressure.load(src.getEndTidalPressure(),dst.getEndTidalPressure());
    if(src.hasRelativeDiffusionCoefficient())
      SEScalar.load(src.getRelativeDiffusionCoefficient(),dst.getRelativeDiffusionCoefficient());
    if(src.hasSolubilityCoefficient())
      SEScalarInversePressure.load(src.getSolubilityCoefficient(),dst.getSolubilityCoefficient());

    if(src.hasClearance())
      SESubstanceClearance.load(src.getClearance(),dst.getClearance());
    if(src.hasPharmacokinetics())
      SESubstancePharmacokinetics.load(src.getPharmacokinetics(),dst.getPK());
    if(src.hasPharmacodynamics())
      SESubstancePharmacodynamics.load(src.getPharmacodynamics(),dst.getPD());
  }
  
  public static SubstanceData unload(SESubstance src)
  {
    SubstanceData.Builder to = SubstanceData.newBuilder();
    unload(src,to);
    return to.build();
  }
  protected static void unload(SESubstance src, SubstanceData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    if(src.hasState())
      dst.setState(src.state);
    if(src.hasDensity())
      dst.setDensity(SEScalarMassPerVolume.unload(src.density));    
    if(src.hasMolarMass())
      dst.setMolarMass(SEScalarMassPerAmount.unload(src.molarMass));
    
    if(src.hasMaximumDiffusionFlux())
      dst.setMaximumDiffusionFlux(SEScalarMassPerAreaTime.unload(src.maximumDiffusionFlux));
    if(src.hasMichaelisCoefficient())
      dst.setMichaelisCoefficient(SEScalar.unload(src.michaelisCoefficient));
         
    if(src.hasAerosolization())
      dst.setAerosolization(SESubstanceAerosolization.unload(src.aerosolization));
    if(src.hasBloodConcentration())
      dst.setBloodConcentration(SEScalarMassPerVolume.unload(src.bloodConcentration));
    if(src.hasMassInBody())
      dst.setMassInBody(SEScalarMass.unload(src.massInBody));
    if(src.hasMassInBlood())
      dst.setMassInBlood(SEScalarMass.unload(src.massInBlood));
    if(src.hasMassInTissue())
      dst.setMassInTissue(SEScalarMass.unload(src.massInTissue));
    if(src.hasPlasmaConcentration())
      dst.setPlasmaConcentration(SEScalarMassPerVolume.unload(src.plasmaConcentration));
    if(src.hasSystemicMassCleared())
      dst.setSystemicMassCleared(SEScalarMass.unload(src.systemicMassCleared));
    if(src.hasTissueConcentration())
      dst.setTissueConcentration(SEScalarMassPerVolume.unload(src.tissueConcentration));
     
    if(src.hasAlveolarTransfer())
      dst.setAlveolarTransfer(SEScalarVolumePerTime.unload(src.alveolarTransfer));
    if(src.hasDiffusingCapacity())
      dst.setDiffusingCapacity(SEScalarVolumePerTimePressure.unload(src.diffusingCapacity));
    if(src.hasEndTidalFraction())
      dst.setEndTidalFraction(SEScalar0To1.unload(src.endTidalFraction));
    if(src.hasEndTidalPressure())
      dst.setEndTidalPressure(SEScalarPressure.unload(src.endTidalPressure));
    if(src.hasRelativeDiffusionCoefficient())
      dst.setRelativeDiffusionCoefficient(SEScalar.unload(src.relativeDiffusionCoefficient));
    if(src.hasSolubilityCoefficient())
      dst.setSolubilityCoefficient(SEScalarInversePressure.unload(src.solubilityCoefficient));
    
    if(src.hasClearance())
      dst.setClearance(SESubstanceClearance.unload(src.clearance));
    if(src.hasPK())
      dst.setPharmacokinetics(SESubstancePharmacokinetics.unload(src.pk));
    if(src.hasPD())
      dst.setPharmacodynamics(SESubstancePharmacodynamics.unload(src.pd));        
  }
  
  public String  getName() { return this.name;}
  public void    setName(String name){this.name=name;}
  public boolean hasName(){return StringUtils.exists(this.name);}
  
  public eState  getState() { return this.state;}
  public void    setState(eState state){this.state=state;}
  public boolean hasState(){return this.state==null?false:state!=state.NullState;}
  
  public SEScalarMassPerVolume getDensity() 
  { 
    if(this.density==null)
      this.density=new SEScalarMassPerVolume();
    return this.density;
  }
  public boolean hasDensity() {return this.density==null?false:this.density.isValid();}
  
  public SEScalarMassPerAmount getMolarMass() 
  { 
    if(this.molarMass==null)
      this.molarMass=new SEScalarMassPerAmount();
    return this.molarMass;
  }
  public boolean hasMolarMass() {return this.molarMass==null?false:this.molarMass.isValid();}
  
  ////////////////
  // Diffusion-ish //
  ////////////////
  
  public SEScalarMassPerAreaTime getMaximumDiffusionFlux() 
  { 
    if(this.maximumDiffusionFlux==null)
      this.maximumDiffusionFlux=new SEScalarMassPerAreaTime();
    return this.maximumDiffusionFlux;
  }
  public boolean hasMaximumDiffusionFlux() {return this.maximumDiffusionFlux==null?false:this.maximumDiffusionFlux.isValid();}
  
  
  public SEScalar getMichaelisCoefficient() 
  { 
    if(this.michaelisCoefficient==null)
      this.michaelisCoefficient=new SEScalar();
    return this.michaelisCoefficient;
  }
  public boolean hasMichaelisCoefficient() {return this.michaelisCoefficient==null?false:this.michaelisCoefficient.isValid();}

  ////////////////
  // Liquid-ish //
  ////////////////
  
  public SESubstanceAerosolization getAerosolization()
  {
    if(this.aerosolization==null)
      this.aerosolization = new SESubstanceAerosolization();
    return this.aerosolization;
  }
  public boolean hasAerosolization() { return this.aerosolization!=null; }
  public void removeAerosolization() { this.aerosolization = null; }
    
  public SEScalarMassPerVolume getBloodConcentration() 
  { 
    if(this.bloodConcentration==null)
      this.bloodConcentration=new SEScalarMassPerVolume();
    return this.bloodConcentration;
  }
  public boolean hasBloodConcentration() {return this.bloodConcentration==null?false:this.bloodConcentration.isValid();}
  
  public SEScalarMass getMassInBody() 
  { 
    if(this.massInBody==null)
      this.massInBody=new SEScalarMass();
    return this.massInBody;
  }
  public boolean hasMassInBody() {return this.massInBody==null?false:this.massInBody.isValid();}
  
  public SEScalarMass getMassInBlood() 
  { 
    if(this.massInBlood==null)
      this.massInBlood=new SEScalarMass();
    return this.massInBlood;
  }
  public boolean hasMassInBlood() {return this.massInBlood==null?false:this.massInBlood.isValid();}
  
  public SEScalarMass getMassInTissue() 
  { 
    if(this.massInTissue==null)
      this.massInTissue=new SEScalarMass();
    return this.massInTissue;
  }
  public boolean hasMassInTissue() {return this.massInTissue==null?false:this.massInTissue.isValid();}
  
  public SEScalarMassPerVolume getPlasmaConcentration() 
  { 
    if(this.plasmaConcentration==null)
      this.plasmaConcentration=new SEScalarMassPerVolume();
    return this.plasmaConcentration;
  }
  public boolean hasPlasmaConcentration() {return this.plasmaConcentration==null?false:this.plasmaConcentration.isValid();}
  
  public SEScalarMass getSystemicMassCleared() 
  { 
    if(this.systemicMassCleared==null)
      this.systemicMassCleared=new SEScalarMass();
    return this.systemicMassCleared;
  }
  public boolean hasSystemicMassCleared() {return this.systemicMassCleared==null?false:this.systemicMassCleared.isValid();}

  public SEScalarMassPerVolume getTissueConcentration() 
  { 
    if(this.tissueConcentration==null)
      this.tissueConcentration=new SEScalarMassPerVolume();
    return this.tissueConcentration;
  }
  public boolean hasTissueConcentration() {return this.tissueConcentration==null?false:this.tissueConcentration.isValid();}
  
  /////////////
  // Gas-ish //
  /////////////
  
  public SEScalarVolumePerTime getAlveolarTransfer() 
  { 
    if(this.alveolarTransfer==null)
      this.alveolarTransfer=new SEScalarVolumePerTime();
    return this.alveolarTransfer;
  }
  public boolean hasAlveolarTransfer() {return this.alveolarTransfer==null?false:this.alveolarTransfer.isValid();}
  
  public SEScalarVolumePerTimePressure getDiffusingCapacity() 
  { 
    if(this.diffusingCapacity==null)
      this.diffusingCapacity=new SEScalarVolumePerTimePressure();
    return this.diffusingCapacity;
  }
  public boolean hasDiffusingCapacity() {return this.diffusingCapacity==null?false:this.diffusingCapacity.isValid();}
  
  public SEScalar0To1 getEndTidalFraction() 
  { 
    if(this.endTidalFraction==null)
      this.endTidalFraction=new SEScalar0To1();
    return this.endTidalFraction;
  }
  public boolean hasEndTidalFraction() {return this.endTidalFraction==null?false:this.endTidalFraction.isValid();}
  
  public SEScalarPressure getEndTidalPressure() 
  { 
    if(this.endTidalPressure==null)
      this.endTidalPressure=new SEScalarPressure();
    return this.endTidalPressure;
  }
  public boolean hasEndTidalPressure() {return this.endTidalPressure==null?false:this.endTidalPressure.isValid();}
  
  public SEScalarInversePressure getSolubilityCoefficient() 
  { 
    if(this.solubilityCoefficient==null)
      this.solubilityCoefficient=new SEScalarInversePressure();
    return this.solubilityCoefficient;
  }
  public boolean hasSolubilityCoefficient() {return this.solubilityCoefficient==null?false:this.solubilityCoefficient.isValid();}
  
  public SEScalar getRelativeDiffusionCoefficient() 
  { 
    if(this.relativeDiffusionCoefficient==null)
      this.relativeDiffusionCoefficient=new SEScalar();
    return this.relativeDiffusionCoefficient;
  }
  public boolean hasRelativeDiffusionCoefficient() {return this.relativeDiffusionCoefficient==null?false:this.relativeDiffusionCoefficient.isValid();}
  
  ///////////////
  // Clearance //
  ///////////////

  public SESubstanceClearance getClearance()
  {
    if(this.clearance==null)
      this.clearance = new SESubstanceClearance();
    return this.clearance;
  }
  public boolean hasClearance() { return this.clearance!=null; }
  public void removeClearance() { this.clearance = null; }

  ///////////
  // PK/PD //
  ///////////
  
  public SESubstancePharmacokinetics getPK()
  {
    if(this.pk==null)
      this.pk = new SESubstancePharmacokinetics();
    return this.pk;
  }
  public boolean hasPK() { return this.pk!=null?this.pk.isValid():false; }
  public void removePK() { this.pk = null; }
  
  public SESubstancePharmacodynamics getPD()
  {
    if(this.pd==null)
      this.pd = new SESubstancePharmacodynamics();
    return this.pd;
  }
  public boolean hasPD() { return this.pd!=null?this.pd.isValid():false; }
  public void removePD() { this.pd = null; }
  
  
  
}
