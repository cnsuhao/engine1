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

package mil.tatrc.physiology.datamodel.patient.actions;

import com.kitware.physiology.cdm.PatientActions.ChestCompressionForceData;

import mil.tatrc.physiology.datamodel.properties.SEScalarForce;

public class SEChestCompressionForce extends SEPatientAction
{
  protected SEScalarForce force;
  
  public SEChestCompressionForce()
  {
    force = null;
  }
  
  public SEChestCompressionForce(SEChestCompressionForce other)
  {
    this();
    copy(other);
  }
  
  public void copy(SEChestCompressionForce other)
  {
    if (other.force != null)
      getForce().set(other.force);
    else if (force != null)
      force.invalidate();
  }
  
  public void reset()
  {
    super.reset();
    if (force != null)
      force.invalidate();
  }
  
  public boolean isValid()
  {
    return hasForce();
  }
  
  public static void load(ChestCompressionForceData src, SEChestCompressionForce dst)
  {
    SEPatientAction.load(src.getPatientAction(), dst);
    if(src.hasForce())
      SEScalarForce.load(src.getForce(),dst.getForce());
  }
  
  public static ChestCompressionForceData unload(SEChestCompressionForce src)
  {
    ChestCompressionForceData.Builder dst = ChestCompressionForceData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  
  protected static void unload(SEChestCompressionForce src, ChestCompressionForceData.Builder dst)
  {
    SEPatientAction.unload(src,dst.getPatientActionBuilder());
    if (src.hasForce())
      dst.setForce(SEScalarForce.unload(src.force));
  }
  
  public boolean hasForce()
  {
    return force == null ? false : force.isValid();
  }
  public SEScalarForce getForce()
  {
    if (force == null)
      force = new SEScalarForce();
    return force;
  }
  
  public String toString()
  {
    if (force != null)
      return "Chest Compression" 
          + "\n\tForce: " + getForce();
    else
      return "Action not specified properly";
  }
}