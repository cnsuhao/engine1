package mil.tatrc.physiology.testing;

import java.util.*;

import com.kitware.physiology.cdm.TestReport.TestReportData.TestCaseData;

import mil.tatrc.physiology.datamodel.SEEqualOptions;
import mil.tatrc.physiology.datamodel.properties.SEScalarTime;

public class SETestCase 
{
	protected String         name;
	protected SEScalarTime   duration;
	protected List<String>   failures = new ArrayList<String>();

  protected SEEqualOptions eqOpts;
	
	protected SETestCase()
	{
		eqOpts = new SEEqualOptions();
		eqOpts.trackError(true);
		eqOpts.trackDifferences(true);
	}
	
	public void reset()
	{
		this.name=null;
		if(this.duration!=null)
			this.duration.invalidate();
		this.failures.clear();
	}
	
	public static void load(TestCaseData src, SETestCase dst)
  {
    dst.reset();
    dst.setName(src.getName());
    for(String failure : src.getFailureList())
    	dst.failures.add(failure);
  }
	
	public static TestCaseData unload(SETestCase src)
  {
		TestCaseData.Builder dst = TestCaseData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SETestCase src, TestCaseData.Builder dst)
  {
    if(src.hasName())
      dst.setName(src.name);
    if(src.hasDuration())
    	dst.setDuration(SEScalarTime.unload(src.duration));
    for(String failure : src.failures)
    	dst.getFailureList().add(failure);
  }
  
  public String  getName() { return this.name;}
  public void    setName(String name){this.name=name;}
  public boolean hasName(){return this.name==null?false:true;}
  
  public SEScalarTime getDuration() 
  { 
    if(this.duration==null)
      this.duration=new SEScalarTime();
    return this.duration;
  }
  public boolean      hasDuration() {return this.duration==null?false:this.duration.isValid();}
	
  public boolean hasFailures(){return failures.size()>1;}
  public void AddFailure(String f){failures.add(f);}
  public List<String> getFailures(){ return Collections.unmodifiableList(this.failures); }
  
  SEEqualOptions getEqualOptions(){return eqOpts;}
}
