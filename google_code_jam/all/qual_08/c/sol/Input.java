package library;

import java.io.*;
import java.util.*;
public class Input
{
	BufferedReader reader;
	LinkedList<String> strings;
	public Input(String filename) throws IOException
	{
		reader=new BufferedReader(new FileReader(filename));
		strings=new LinkedList<String>();
	}
	public Input()
	{
		reader=new BufferedReader(new InputStreamReader(System.in));
		strings=new LinkedList<String>();
	}
	public void close() throws IOException
	{
		reader.close();
	}
	void check() throws IOException
	{
		while(strings.size()==0)
		{
			String s=reader.readLine();
			String[] ss=s.split(" ");
			for(int i=0;i<ss.length;i++)
			{
				strings.addLast(ss[i]);
			}
		}
		while(strings.getFirst().length()==0)
		{
			strings.removeFirst();
		}
	}
	public String readString() throws IOException
	{
		check();
		//System.out.println(strings.getFirst());
		return strings.removeFirst();
	}
	public int readInt() throws IOException
	{
		return Integer.parseInt(readString());
	}
	public double readDouble() throws IOException
	{
		return Double.parseDouble(readString());
	}
	public String readLine() throws IOException
	{
		check();
		String r="";
		while(strings.size()>0)
		{
			r+=(strings.removeFirst());
			if(strings.size()==0)
			{
				break;
			}
			r+=" ";
		}
		return r;
	}
}