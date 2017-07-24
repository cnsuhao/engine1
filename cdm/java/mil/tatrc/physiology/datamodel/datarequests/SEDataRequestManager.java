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
package mil.tatrc.physiology.datamodel.datarequests;

import java.util.ArrayList;
import java.util.List;

import com.kitware.physiology.cdm.Scenario.*;

public class SEDataRequestManager
{
  protected String                        resultsFilename;
  // TODO Decimal Formatting Data
  protected List<SEDataRequest>           dataRequests = new ArrayList<SEDataRequest>();  
  protected double                        samplesPerSecond;
  
  public SEDataRequestManager()
  {
    reset();
  }
  
  public void reset() 
  {
    this.resultsFilename = "";
    this.samplesPerSecond = 0;
    dataRequests.clear();
  }
  
  public static void load(DataRequestManagerData src, SEDataRequestManager dst)
  {
    dst.reset();
    dst.setResultsFilename(src.getResultsFilename());
    if(src.getSamplesPerSecond()>0)
      dst.setSamplesPerSecond(src.getSamplesPerSecond());
    for (DataRequestData drData : src.getDataRequestList())
    {
      SEDataRequest dr = new SEDataRequest();
      SEDataRequest.load(drData,dr);
      dst.dataRequests.add(dr);
    }
  }
  
  public static DataRequestManagerData unload(SEDataRequestManager src)
  {
    DataRequestManagerData.Builder dst = DataRequestManagerData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEDataRequestManager src, DataRequestManagerData.Builder dst)
  {
    if(src.hasResultsFilename())
      dst.setResultsFilename(src.resultsFilename);
    if(src.samplesPerSecond>0)
      dst.setSamplesPerSecond(src.samplesPerSecond);
    for(SEDataRequest dr : src.dataRequests)
      dst.addDataRequest(SEDataRequest.unload(dr));
  }
  
  public boolean hasResultsFilename(){ return this.resultsFilename!=null&&!this.resultsFilename.isEmpty(); }
  public void setResultsFilename(String f) { this.resultsFilename = f; }
  public String getResultsFilename(){ return this.resultsFilename; }
  
  public void setSamplesPerSecond(double d){ this.samplesPerSecond=d; }
  public double getSamplesPerSecond(){ return this.samplesPerSecond; }
  
  public List<SEDataRequest> getRequestedData(){ return dataRequests; }
  
}
