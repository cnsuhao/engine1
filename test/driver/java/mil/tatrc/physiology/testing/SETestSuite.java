package mil.tatrc.physiology.testing;

import java.util.*;
import com.kitware.physiology.cdm.TestReport.TestReportData.TestCaseData;
import com.kitware.physiology.cdm.TestReport.TestReportData.TestSuiteData;

import mil.tatrc.physiology.datamodel.SEEqualOptions;
import mil.tatrc.physiology.datamodel.properties.CommonUnits.TimeUnit;

public class SETestSuite 
{
	protected String           name;
	protected boolean          performed;
	protected List<String>     requirements = new ArrayList<String>();
	protected List<SETestCase> testCases = new ArrayList<SETestCase>();
	
	protected SETestCase       activeCase;
	
	protected SETestSuite()
	{

	}
	
	public void reset()
	{
		this.name=null;
		this.performed=false;
		this.requirements.clear();
		this.testCases.clear();
		activeCase = null;
	}
	
	public static void load(TestSuiteData src, SETestSuite dst)
  {
    dst.reset();
    dst.setName(src.getName());
    dst.setPerformed(src.getPerformed());
    for(String req : src.getRequirementList())
    	dst.requirements.add(req);
    for(TestCaseData tcd : src.getTestCaseList())
    {
    	SETestCase tc = dst.createTestCase();
    	SETestCase.load(tcd, tc);
    }
  }
	
	public static TestSuiteData unload(SETestSuite src)
  {
		TestSuiteData.Builder dst = TestSuiteData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SETestSuite src, TestSuiteData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    dst.setPerformed(src.performed);
    dst.setErrors(src.getNumErrors());
    dst.setTests(src.testCases.size());

    for(String req : src.requirements)
    	dst.getRequirementList().add(req);
    
    for(SETestCase tc : src.testCases)
    	dst.addTestCase(SETestCase.unload(tc));
  }
  
  public String  getName() { return this.name;}
  public void    setName(String name){this.name=name;}
  public boolean hasName(){return this.name==null?false:true;}
  
  public boolean getPerformed() { return this.performed;}
  public void    setPerformed(boolean b){this.performed=b;}
  
  public void AddRequirement(String f){requirements.add(f);}
  public List<String> getRequirements(){ return Collections.unmodifiableList(this.requirements); }
  
  public SETestCase createTestCase()
  {
  	SETestCase tc = new SETestCase();
  	this.testCases.add(tc);
  	return tc;
  }
  public List<SETestCase> getTestCases()
  {
  	return Collections.unmodifiableList(this.testCases);
  }
  public SEEqualOptions getCaseEqualOptions() 
	{
		if(activeCase==null)
			return null;
		return activeCase.getEqualOptions();
	}
  public SETestCase startCase(String name)
  {
  	activeCase = createTestCase();
  	activeCase.setName(name);
  	return activeCase;
  }
  public SETestCase getActiveCase()
  {
  	return activeCase;
  }
  public void endCase()
  {
  	
  }
  public int getNumErrors() 
  { 
  	int errs=0;
  	for(SETestCase tc : this.testCases)
  		if(!tc.failures.isEmpty())
  			errs++;
  	return errs;
  }
  public double getDuration(TimeUnit unit)
  {
  	double time=0;
  	for(SETestCase tc : this.testCases)
  		time += tc.getDuration().getValue(unit);
  	return time;
  }
}
