package mil.tatrc.physiology.datamodel.doxygen;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;

public class Proto2Doxygen 
{
	static class Property
	{
		public String name;
		public String type;
		public String comment;		
	}
	static class Message
	{
		public String         name;
		public String         comment;
		public List<Message>  children   = new ArrayList<Message>();
		public List<Property> properties = new ArrayList<Property>();
	}

	public static void main(String[] args) 
	{
		Log.setFileName("Proto2Doxygen.log");
		try
		{
			if(args.length!=2)
			{
				Log.info("Command arguments are : <Directory of files to process> <Directory to place processed files>");
				return;
			}
			File srcDir = new File(args[0]);
			if(!srcDir.isDirectory())
			{
				Log.info("Cannot find Source Directory : "+args[0]);
				return;
			}
			File sDir = new File(args[0]);
			File dDir = new File(args[1]);
			dDir.mkdir();
			
			List<String> found = FileUtils.findFiles(sDir.getAbsolutePath(), "proto", true);      
			for (String fName : found)
			{        
				if(new File(fName).isDirectory())
					continue;// Not making this recursive at this point
				processFile(fName, sDir, dDir);
			}      
		}
		catch (Exception ex)
		{
			Log.error("Unable to create single validation table file.",ex);
		}
	}

	protected static void processFile(String fName, File sDir, File dDir) throws IOException
	{
		String line;
		int start,end;
		String comment = "";
		Message message = null;
		Message child   = null;
		List<Message> messages = new ArrayList<Message>();
		List<Message> hierarchy = new ArrayList<Message>();
		boolean looking4comment = false;
		Log.info("Processing file : "+fName);
		FileReader in = new FileReader(fName);
		BufferedReader inFile = new BufferedReader(in);
		while ((line = inFile.readLine()) != null)
		{
			line = line.trim();
			if(line.isEmpty() || line.indexOf(" import ")>-1)
				continue;
			
			start = line.indexOf("{");
			if(start > -1 && message!=null)
			{
				hierarchy.add(message);
				continue;
			}
			start = line.indexOf("}");
			if(start > -1 && message!=null)
			{
				hierarchy.remove(message);
				if(hierarchy.isEmpty())
					message = null;
				else
					message = hierarchy.get(hierarchy.size()-1);
				continue;
			}
			
			if(looking4comment)
			{
				end = line.indexOf("*/"); 
				if(end >-1)
				{
					comment = line.substring(0, end);
					looking4comment = false;
				}
				else
				{
					comment += line;
					continue;
				}
			}
			
			if(line.indexOf("/**<<")==-1)
			{// Look for a comment if we know its not a reverse comment (property comment)
				start = line.indexOf("/*");
				if(start > -1)
				{  
					comment = "";
					end = line.indexOf("*/"); 
					if(end > -1)
						comment = line.substring(start, end+2);
					else
					{
						looking4comment = true;
						comment += line;
					}
					continue;
				}
			}
			
			if(line.startsWith("enum "))
				start = 0;
			if(line.startsWith("message "))
				start = 0;
			if(start > -1)
			{
				String hierarchy_name = "";
				for(Message m : hierarchy)
					hierarchy_name = m.name +"_";
				if(message==null)
				{
					message = new Message();
				}
				else
				{
					child = new Message();
					message.children.add(child);
					message = child; 	    		
				}
				messages.add(message);
				message.name = hierarchy_name+line.trim().split("\\s+")[1];
				message.comment = cleanComment(comment);
				comment = "";
				continue;
			}
			
			if(message!=null)
			{
				start = line.indexOf("/**<<");
				if(start > -1)
				{
					end = line.indexOf("*/");
					comment = line.substring(start+5,end).trim();
					line = line.substring(0,start).trim();
				}
				start = line.indexOf("=");
				if(start > -1)
					line = line.substring(0,start).trim();
				String [] properties = line.trim().split("\\s+");
				if(properties.length == 1)
				{
					Property p = new Property();
					p.comment = cleanComment(comment);
					p.type = "";// Should be an enum
					p.name = properties[0];
					message.properties.add(p);
					continue;
				}
				if(properties.length == 2)
				{
					Property p = new Property();
					p.comment = cleanComment(comment);
					p.type = properties[0];
					p.name = properties[1];
					message.properties.add(p);
					continue;
				}
				if(properties.length == 3)
				{
					Property p = new Property();
					p.comment = cleanComment(comment);
					p.type = properties[1];
					p.name = properties[2];
					message.properties.add(p);
					continue;
				}
			}
		}
		inFile.close();

		String[] path = fName.split("[\\\\/]");
		String proto_file = path[path.length-1];
		String new_file_name = proto_file.substring(0, proto_file.lastIndexOf('.'));
		new_file_name = dDir.getAbsolutePath()+"/"+new_file_name+".ixx";
		File dstFile = new File(new_file_name);
		if(dstFile.exists())
			dstFile.delete();
			
	  PrintWriter writer=new PrintWriter(new_file_name, "UTF-8");
		for(Message m : messages)
		{
			writer.println("/**");
			writer.println(" * @defgroup "+m.name+" "+m.name);
			if(!m.comment.isEmpty())
				writer.println(" * "+m.comment);
			writer.println(" * @{");
			for(Property p : m.properties)
			{
				writer.println(" * @defgroup "+m.name+"_"+p.name+" "+p.name);
				if(!p.comment.isEmpty())
					writer.println(" * "+p.comment);
			}
			writer.println(" * @}");
			writer.println(" */");
			writer.println();
		}
		writer.close();
	}
	
	protected static String cleanComment(String str)
	{
		str = str.replace("/**", "");
		str = str.replace("/*", "");
		str = str.replace("*/", "");
		return str.trim();
	}
}



