#define EJUDGE
#include "testlib.h"
#include <string>
#include <iostream>

using namespace std;

#define sz size()
#define forn(i, n) for(int i = 0; i < (int)(n); i++)
#define For(i, st, en) for(int i = (st); i <= (int)(en); i++)
#define Ford(i, st, en) for(int i = (st); i >= (int)(en); i--)

typedef long double ld;

const ld PI = 3.1415926535897932384626433832795L;

typedef long long i64;

#define MAXN 2048

int n, k, s, f;
bool a[MAXN][MAXN];
bool b[MAXN];
bool u[MAXN];

int main(int argc, char **argv)
{
	registerTestlibCmd(argc, argv);

	memset(b, 0, sizeof(b));
	memset(u, 0, sizeof(u));
	n = inf.readInt();
	k = inf.readInt();
	s = inf.readInt() - 1;
	f = inf.readInt() - 1;
	forn(i, k)
	{
		int x = inf.readInt();
		b[x - 1] = true;
	}
	forn(i, n)
	{
		string ss = inf.readToken();
		forn(j, n)
		{
			a[i][j] = ss[j] == '1';
		}
	}

	string ja = ans.readToken();
	string pa = ouf.readToken();
	if (pa == "NO")
	{
		if (ja != "NO")
		{
			quitf(_wa, "%s expected, %s found", ja.c_str(), pa.c_str());
		}
		quitf(_ok, "no solution");
	}
	else if (pa != "YES")
	{
		quitf(_pe, "YES/NO expected, %s found", pa.c_str());
	}
	
	int m = ouf.readInt(1, n * n);
	int last = -1;
	forn(i, m)
	{
		int x = ouf.readInt(1, n) - 1;
		if (i == 0 && x != s)
		{
			quitf(_wa, "Incorrect start: %d expected, %d found", s + 1, x + 1);
		}
		if (i == m - 1 && x != f)
		{
			quitf(_wa, "Incorrect finish: %d expected, %d found", f + 1, x + 1);
		}
		u[x] = true;
		if (i)
		{
			if (!a[last][x])
			{
				quitf(_wa, "no edge from %d to %d", last + 1, x + 1);
			}
		}

		last = x;
	}
	forn(i, n)
	{
		if (b[i] && !u[i])
		{
			quitf(_wa, "vertex %d not visited", i+1);
		}
	}

	if (ja == "NO")
	{
		quitf(_fail, "Jury: NO. Correct answer: YES");
	}

	quitf(_ok, "All OK");

	return 0;
}
