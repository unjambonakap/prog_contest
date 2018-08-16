package Andra;

import java.io.*;

public class C
{
	public static final long MOD = 1000000007;
	public static final int MAX = 500002;
	public static int n;
	public static int m;
	public static long x;
	public static long y;
	public static long z;
	public static long [] a = new long [MAX];
	public static long [] d = new long [MAX];
	public static long [] speed = new long [MAX];
	public static int [] p = new int [MAX];
	public static int [] index = new int [MAX];
	public static long sol;
	public static CumulativeTable ct = new CumulativeTable(MAX);
	
	public static void QuickSort (int l, int r)
	{
		int i, j, pivot;

		i = l;
		j = r;
		pivot = p [(i + j) / 2];
		do
		{
			while ((i <= r) && (speed [p [i]] < speed [pivot]))
				i++;
			while ((j >= l) && (speed [p [j]] > speed [pivot]))
				j--;
			if (i <= j)
			{
				int tmp = p [i];
				p [i] = p [j];
				p [j] = tmp;
				i++;
				j--;
			}
		}
		while (i < j);
		if (i < r)
			QuickSort (i, r);
		if (l < j)
			QuickSort (l, j);
	}

	public static void solve()
	{
		for (int i = 0; i < n; i++)
			p [i] = i;
		QuickSort(0, n - 1);
		index [p [0]] = 0;
		for (int i = 1; i < n; i++)
		{
			index [p [i]] = index [p [i - 1]];
			if (speed [p [i]] != speed [p [i - 1]])
				index [p [i]]++;
		}
		ct.reset();
		
		d [0] = 1;
		ct.add(index [0] + 1, d [0]);
		for (int i = 1; i < n; i++)
		{
			d [i] = (1 + ct.count (index [i])) % MOD;
			ct.add(index [i] + 1, d [i]);
		}
		
		sol = 0;
		for (int i = 0; i < n; i++)
			sol = (sol + d [i]) % MOD;
	}

	public static void main(String[] args) throws IOException 
	{
		BufferedReader in = new BufferedReader(new FileReader("./Andra/C-large.in"));
		BufferedWriter out = new BufferedWriter(new FileWriter("./Andra/C-large.out"));
		
		int numTest = Integer.parseInt(in.readLine());
		for (int testCase = 0; testCase < numTest; testCase++)
		{
			System.out.println(testCase);
			String [] tmp = in.readLine().split(" ");
			n = Integer.parseInt(tmp [0]);
			m = Integer.parseInt(tmp [1]);
			x = Long.parseLong(tmp [2]);
			y = Long.parseLong(tmp [3]);
			z = Long.parseLong(tmp [4]);
			for (int i = 0; i < m; i++)
				a [i] = Long.parseLong(in.readLine().trim());
			
			for (int i = 0; i < n; i++)
			{
				speed [i] = a [i % m];
				a [i % m] = (x * a [i % m] + y * (long)(i + 1)) % z;
			}
			solve ();
			
			out.write("Case #" + (testCase + 1) + ": " + sol);
			out.newLine();
		}
		in.close();
		out.close();
	}

}
