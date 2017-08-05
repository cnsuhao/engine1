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

package mil.tatrc.physiology.datamodel.substance;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.google.protobuf.TextFormat.ParseException;

import mil.tatrc.physiology.utilities.Log;

public class SESubstanceManager 
{
	protected List<SESubstance>         substances     = new ArrayList<SESubstance>();  
	protected List<SESubstanceCompound> compounds      = new ArrayList<SESubstanceCompound>();

	public SESubstanceManager()
	{
		loadSubstanceDirectory();
	}

	public void reset()
	{

	}

	public void clear() 
	{
		reset();
		substances.clear();  
		compounds.clear();    
	}

	public List<SESubstance> getSubstances()
	{
		return Collections.unmodifiableList(substances);
	}

	public SESubstance getSubstance(String name) 
	{
		for (SESubstance s : substances)
		{
			if (name.equals(s.getName()))
				return s;
		}
		Log.error("Unknown Substance " + name);
		return null;
	}
	public void removeSubstance(String name)
	{
		for (SESubstance s : substances)
		{
			if (name.equals(s.getName()))
			{
				this.substances.remove(s);
				break;
			}      
		}
	}

	public void addSubstance(SESubstance substance)
	{
		if (substance == null)
			return;
		for (SESubstance s : substances)
		{
			if (substance==s)
				return;
		}
		substances.add(substance);
	}
	public void removeSubstance(SESubstance substance)
	{
		if (substance == null)
			return;
		for (SESubstance s : substances)
		{
			if (substance==s)
			{
				this.substances.remove(s);
				return;
			}
		}

	}

	public List<SESubstanceCompound> getCompounds()
	{
		return Collections.unmodifiableList(compounds);
	}

	public SESubstanceCompound getCompound(String name) 
	{
		for (SESubstanceCompound c : compounds)
		{
			if (name.equals(c.getName()))
				return c;
		}
		Log.error("Unknown Compound " + name);
		return null;
	}
	public void removeCompound(String name)
	{
		for (SESubstanceCompound c : compounds)
		{
			if (name.equals(c.getName()))
			{
				this.compounds.remove(c);
				break;
			}      
		}
	}

	public void addCompound(SESubstanceCompound compound)
	{
		if (compound == null)
			return;
		for (SESubstanceCompound c : compounds)
		{
			if (compound==c)
				return;
		}
		compounds.add(compound);
	}
	public void removeCompound(SESubstanceCompound compound)
	{
		if (compound == null)
			return;
		for (SESubstanceCompound c : compounds)
		{
			if (compound==c)
			{
				this.compounds.remove(c);
				return;
			}
		}
	}

	public void loadSubstanceDirectory()
	{
		clear();
		File sdir = new File("./substances").getAbsoluteFile();
		for(File sFile : sdir.listFiles())
		{
			if(sFile.getName().endsWith(".pba"))
			{
				//Log.info("Processing file "+sFile.getName());
				try
				{
					SESubstance s = new SESubstance();
					s.readFile(sFile.getAbsolutePath());
					addSubstance(s);
				}
				catch(ParseException ex)
				{
					Log.error("Unsupport file contents in "+sFile.getAbsolutePath());
				}      
			}
		}
		
		File cdir = new File("./substances/compounds/").getAbsoluteFile();
		File[] files = cdir.listFiles();
		if(files!=null)
		{
			for(File cFile : files)
			{
				try
				{
					SESubstanceCompound c = new SESubstanceCompound();
					c.readFile(cFile.getAbsolutePath(),this);
					addCompound(c);
				}
				catch(ParseException ex)
				{
					Log.error("Unsupport file contents in "+cFile.getAbsolutePath());
				}
			}
		}
	}

	public static void main(String[] args)
	{
		SESubstanceManager me = new SESubstanceManager();
		me.loadSubstanceDirectory();
		for(SESubstance s : me.getSubstances())
			System.out.println(s.getName());
		for(SESubstanceCompound c : me.getCompounds())
			System.out.println(c.getName());
	}
}
