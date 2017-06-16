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

package mil.tatrc.physiology.datamodel.scenario;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import com.google.protobuf.TextFormat;
import com.google.protobuf.TextFormat.ParseException;
import com.kitware.physiology.cdm.Scenario.AnyActionData;
import com.kitware.physiology.cdm.Scenario.ScenarioData;
import com.kitware.physiology.cdm.Scenario.DataRequestData.eCategory;

import mil.tatrc.physiology.datamodel.actions.SEAction;
import mil.tatrc.physiology.datamodel.actions.SEAdvanceTime;
import mil.tatrc.physiology.datamodel.datarequests.*;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.TimeUnit;
import mil.tatrc.physiology.datamodel.substance.SESubstanceManager;
import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.SimpleEquals;

public class SEScenario 
{
  public static void main(String[] args)
  {
    SESubstanceManager mgr = new SESubstanceManager();
    mgr.loadSubstanceDirectory();
    
    {
    SEScenario s = new SEScenario(mgr);
    s.setName("Test");
    s.setDescription("Description");
    s.getInitialParameters().setPatientFile("StandardMale.pba");
    SEDataRequest dr = new SEDataRequest();
    dr.setCategory(eCategory.Physiology);
    dr.setName("Weight");
    dr.setUnit("kg");
    dr.setPrecision(1);
    s.getDataRequestManager().getRequestedData().add(dr);
    SEAdvanceTime adv = new SEAdvanceTime();
    adv.getTime().setValue(320,TimeUnit.s);
    s.getActions().add(adv);
    System.out.println(SEScenario.unload(s).toString());
    }
    
    boolean onlyCheckSchema=true;
    
    String searchDir;
    if(args.length==0)
      searchDir="./verification/Scenarios";
    else
      searchDir=args[0];
    List<String> files=FileUtils.findFiles(searchDir, ".pba", true);
    for(String file : files)
    {
      Log.info("Testing scenario file "+file);
      SEScenario sce1 = new SEScenario(mgr);
      try{
        sce1.readFile(file);
      }catch(ParseException ex){Log.error("Unable to read file "+file,ex);}
      
      // Let's make sure we don't have the same data request more than once
      Set<Integer> hashes = new HashSet<Integer>();
      for(SEDataRequest dr : sce1.getDataRequestManager().getRequestedData())
      {
        int hash = dr.hashCode();        
        if(!hashes.contains(hash))
          hashes.add(hash);
        else
          Log.error("Duplicate Data Request");
      }
      
      if(!onlyCheckSchema)
      {
        ScenarioData sce1Data = SEScenario.unload(sce1);
        SEScenario sce2 = new SEScenario(mgr);
        SEScenario.load(sce1Data, sce2);
        ScenarioData sce2Data = SEScenario.unload(sce2);

        int numActions;

        numActions = sce1Data.getAnyActionList().size();
        if(numActions != sce2Data.getAnyActionList().size())
          Log.error("We have a xsd actions problem with : "+file);      
        for(int i=0; i<numActions; i++)
        {
          AnyActionData action1 = sce1Data.getAnyAction(i);
          AnyActionData action2 = sce2Data.getAnyAction(i);

          //Log.info("Comparing "+action1.getClass().getSimpleName());
          if(!SimpleEquals.Equals(action1, action2))
          {
            Log.error("We have an actions problem with : "+file);
            Log.error("Scenario 1 action is : "+action1);
            Log.error("Scenario 2 action is : "+action2);          
          }
        }

        // Now let's compare SEActions
        numActions = sce1.actions.size();
        if(numActions != sce2.actions.size())
          Log.error("We have an actions problem with : "+file);

        for(int i=0; i<numActions; i++)
        {
          String action1 = sce1.actions.get(i).toString();
          String action2 = sce2.actions.get(i).toString();

          if(!action1.equals(action2))
          {
            Log.error("We have an actions problem with : "+file);
            Log.error("Scenario 1 action is : "+action1);
            Log.error("Scenario 2 action is : "+action2);          
          }
        }
      }
    }
  }
  
  protected String                        name;
  protected String                        description;
  protected SEScenarioInitialParameters   params;
  protected SEScenarioAutoSerialization   autoSerialize;
  protected String                        engineStateFile;
  protected SEDataRequestManager          drMgr = new SEDataRequestManager();
  protected List<SEAction>                actions = new ArrayList<SEAction>();
  
  protected SESubstanceManager            subMgr;
  
  public SEScenario(SESubstanceManager subMgr)
  {
    this.subMgr = subMgr; 
    reset();
  }
  
  public void reset() 
  {
    this.name          = "";
    this.description   = "";
    this.params        = null;
    this.autoSerialize = null;
    this.engineStateFile   = null;
    this.actions.clear();    
    this.drMgr.reset();
  }
  
  public void readFile(String fileName) throws ParseException
  {
    ScenarioData.Builder builder = ScenarioData.newBuilder();
    TextFormat.getParser().merge(FileUtils.readFile(fileName), builder);
    SEScenario.load(builder.build(), this);
  }
  public void writeFile(String fileName)
  {
    FileUtils.writeFile(fileName, SEScenario.unload(this).toString());
  }
  
  public static void load(ScenarioData src, SEScenario dst)
  {
    dst.reset();
    
    dst.name = src.getName();
    dst.description = src.getDescription();
    
    switch(src.getStartTypeCase())
    {
    case ENGINESTATEFILE:
      dst.engineStateFile = src.getEngineStateFile();
      break;
    case INITIALPARAMETERS:
      SEScenarioInitialParameters.load(src.getInitialParameters(),dst.getInitialParameters(),dst.subMgr);
    }
    
    if(src.hasAutoSerialization())
      SEScenarioAutoSerialization.load(src.getAutoSerialization(), dst.getAutoSerialization());
    
    if(src.hasDataRequestManager())
      SEDataRequestManager.load(src.getDataRequestManager(), dst.getDataRequestManager());
   
    for(AnyActionData aData : src.getAnyActionList())
      dst.actions.add(SEAction.ANY2CDM(aData,dst.subMgr)); 
  }
  
  public static ScenarioData unload(SEScenario src)
  {
    ScenarioData.Builder dst = ScenarioData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEScenario src, ScenarioData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    
    if(src.hasDescription())
      dst.setDescription(src.description);
    
    if(src.hasInitialParameters())
      dst.setInitialParameters(SEScenarioInitialParameters.unload(src.params));
    else if(src.hasEngineState())
      dst.setEngineStateFile(src.engineStateFile);
    
    if(src.hasAutoSerialization())
      dst.setAutoSerialization(SEScenarioAutoSerialization.unload(src.autoSerialize));
    
    if(!src.drMgr.getRequestedData().isEmpty())
      dst.setDataRequestManager(SEDataRequestManager.unload(src.drMgr));
    
    for(SEAction a : src.actions)
      dst.addAnyAction(SEAction.CDM2ANY(a));
  }
  
  public boolean isValid()
  {
    if (actions.size() == 0)
      return false;
    if(!hasInitialParameters() && !hasEngineState())
      return false;
    return true;
  }

  public String getName()
  {
    return name;
  }
  public void setName(String name)
  {
    this.name = name;
  }
  public boolean hasName()
  {
    return name.isEmpty() ? false : true;
  }
  public void invalidateName()
  {
    name = "";
  }
  
  public String getDescription()
  {
    return description;
  }
  public void setDescription(String description)
  {
    this.description = description;
  }
  public boolean hasDescription()
  {
    return description.isEmpty() ? false : true;
  }
  public void invalidateDescription()
  {
    description = "";
  }
  
  public boolean hasEngineState()
  {
    if(hasInitialParameters())
      return false;
    return this.engineStateFile != null && !this.engineStateFile.isEmpty();
  }
  public void setEngineState(String stateFile)
  {
    invalidateInitialParameters();
    this.engineStateFile = stateFile;
  }
  public String getEngineState(){ return this.engineStateFile; }
  public void invalidateEngineState()
  {
    this.engineStateFile = null;
  }
  
  public boolean hasInitialParameters()
  {
    return params!=null && params.isValid();
  }
  public SEScenarioInitialParameters getInitialParameters()
  {
    if(this.params==null)
      this.params=new SEScenarioInitialParameters();
    return this.params;
  }
  public void invalidateInitialParameters()
  {
    this.params = null;
  }
  
  public boolean hasAutoSerialization()
  {
    return autoSerialize!=null && autoSerialize.isValid();
  }
  public SEScenarioAutoSerialization getAutoSerialization()
  {
    if(this.autoSerialize==null)
      this.autoSerialize=new SEScenarioAutoSerialization();
    return this.autoSerialize;
  }
  public void invalidateAutoSerialization()
  {
    this.autoSerialize = null;
  }

  public List<SEAction> getActions() 
  {
    return actions;
  }

  public SEDataRequestManager getDataRequestManager() 
  {
    return this.drMgr;
  }
  
  public SESubstanceManager getSubstanceManager()
  {
    return this.subMgr;
  }
}
