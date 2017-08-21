/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.exceptions;

public class InvalidUnitException extends RuntimeException
{
  private String badUnit;
  private String type;
  public InvalidUnitException(String unit, String type)
  {
    this.badUnit=unit;
    this.type=type;
  }
  
  public String toString()
  {
    return "InvalidUnitException: Unit '" + badUnit + "' is not compatible with " + type;
  }
}
