/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.patient.actions;

public abstract class SEConsciousRespirationCommand
{
  protected String comment;
  
  public SEConsciousRespirationCommand()
  {
  }
  
  public void copy(SEConsciousRespirationCommand other)
  {
    if(this==other)
      return;
    
    comment = other.comment;
  }
  
  public abstract SEConsciousRespirationCommand getCopy();
  
  public void reset()
  {
    comment = "";
  }
  /*
  public static void load(ConsciousRespirationCommandData in)
  {
    comment = in.getComment();
  }
  protected void unload(ConsciousRespirationCommandData data)
  {
    if (hasComment())
      data.setComment(comment);
  }
  */
  public boolean hasComment()
  {
    return comment != null && !comment.isEmpty();
  }
  public String getComment()
  {
    return comment;
  }
  public void setComment(String s)
  {
    comment = s;
  }
  
  public abstract boolean isValid();
  public abstract String toString();
}
