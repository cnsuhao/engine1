/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/
package mil.tatrc.physiology.pulse.engine;

import mil.tatrc.physiology.datamodel.datarequests.SEDataRequestManager;

public abstract class CDMUpdatedCallback
{
  protected double callbackFrequency_s;
  protected SEDataRequestManager drMgr;
  public CDMUpdatedCallback(double updateFrequency_s)
  {
    this.drMgr = null;
    callbackFrequency_s = updateFrequency_s;
  }
  public void setDataRequests(SEDataRequestManager drMgr)
  {
    this.drMgr = drMgr;
  }
  
  public abstract void update(double time_s);
}
