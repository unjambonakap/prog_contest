import java.util.ArrayList;
import java.util.Scanner;


public class Main {

	public static void main(String[] args) {

		ArrayList<String> evaluations = new ArrayList<String>();
		Scanner sc = new Scanner(System.in);
		String input = sc.nextLine();
		while (!input.equals("0 0 0 0 0 0 0"))
		{
            System.out.println(input);
			evaluations.add(input);
			input = sc.nextLine();
		}
		for(String test : evaluations)
		{
			String[] arg = test.split(" ");
			if(arg.length==7)
			{
				eval(Integer.parseInt(arg[0]),Integer.parseInt(arg[1]),Integer.parseInt(arg[2]),Integer.parseInt(arg[3]),Integer.parseInt(arg[4]),Integer.parseInt(arg[5]),Integer.parseInt(arg[6]));
			}
		}

	}

	static private void eval(int k, int x1, int x2, int y1, int y2, int t1, int t2)
	{
		int x1init = x1;
		int x2init = x2;
		int kinit = k;
		int cpt = 0;
		x1++;
		x2++;
		if(x1>t1)
			x1=1;
		if(x2>t2)
			x2=1;
		while (k!=0)
		{
			if(x1==x1init && x2==x2init && k==kinit)
			{
				System.out.println("-1");
				return;
			}
			
			if(x1==y1 && x2==y2)
				k--;

			x1++;
			x2++;
			if(x1>t1)
				x1=1;
			if(x2>t2)
				x2=1;
			cpt++;

		}
		System.out.println(cpt+"");
	}

}
