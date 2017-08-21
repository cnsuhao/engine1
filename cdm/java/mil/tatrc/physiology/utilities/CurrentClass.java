/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

/**
 * 
 */
package mil.tatrc.physiology.utilities;

import java.util.Set;

/**
 * @author abray
 *
 */
public class CurrentClass extends SecurityManager 
{
  protected String getClassName() 
  {
    return getClassContext()[2].getName();
  }
  
  protected String getClassName(Set<String> ignoreMe) 
  {
    int i=-1;
    boolean skip;
    Class[] classes = getClassContext();
    for(Class clazz : classes)
    {
      i++;
      if(clazz.getName().indexOf("CurrentClass")>=0)
        continue;
      skip=false;
      for(String ignore : ignoreMe)
      {
        if(clazz.getName().indexOf(ignore)>=0)
        {
          skip=true;
          break;
        }
      }
      if(skip)continue;
      return clazz.getName()+"::"+Thread.currentThread().getStackTrace()[i+1].getLineNumber();
    }
    return "?CurrentClass?";
  }
  
  protected String getClassNameTrimmed(Set<String> ignoreMe)
  {
    int i=-1;
    boolean skip;
    Class[] classes = getClassContext();
    for(Class clazz : classes)
    {
      i++;
      if(clazz.getName().indexOf("CurrentClass")>=0)
        continue;
      skip=false;
      for(String ignore : ignoreMe)
      {
        if(clazz.getName().indexOf(ignore)>=0)
        {
          skip=true;
          break;
        }
      }
      if(skip)continue;
      String n = clazz.getName()+"::"+Thread.currentThread().getStackTrace()[i+1].getLineNumber();
      return n.substring(n.lastIndexOf(".")+1);
    }
    return "?CurrentClass?";
  }
  
  protected static CurrentClass cc=new CurrentClass();
  
  public static String getName()
  {
    return cc.getClassName();
  }
  
  public static String getName(Set<String>ignoreMe)
  {
    return cc.getClassName(ignoreMe);
  }
  
  public static String getTrimmedName(Set<String> ignoreMe)
  {
    return cc.getClassNameTrimmed(ignoreMe);
  }
}
