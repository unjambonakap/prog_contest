import java.util.ArrayList;
import java.util.Scanner;


public class Main {

	
	public static void main(String[] args) {
		
		ArrayList<String> evaluations = new ArrayList<String>();
		Scanner sc = new Scanner(System.in);
		String input = sc.nextLine();
		while (!input.equals("0 0"))
		{
			evaluations.add(input);
			input = sc.nextLine();
		}
		for(String test : evaluations)
		{
			String[] arg = test.split(" ");
			if(arg.length==2)
			{
				eval(Integer.parseInt(arg[0]),Integer.parseInt(arg[1]));
			}
		}

	}
	
	static private void eval(int x, int y)
	{
		int nbEdge = nbEdge(x);
		int result = fact(nbEdge)/(fact(y)*fact(nbEdge-y));
		System.out.println(result+"");
	}
	
	static private int fact(int x)
	{
		int result=1;
		while (x!=0)
		{
			result*=x;
			x--;
		}
		return result;
	}
	
	static private int nbEdge(int nbNodes)
	{
		int result = 0;
		for(int i=1;i<nbNodes;i++)
		{
			result+=nbNodes-i;
		}
		return result;
	}

}
