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

#define MAXN 1024

struct tp{int x,y;};

tp a[MAXN];
bool u[MAXN];
tp b[MAXN];

inline bool operator == (tp p1, tp p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

inline i64 sp(tp p1, tp p2)
{
	return (i64)p1.x * p2.x + (i64)p1.y * p2.y;
}

inline i64 vp(tp p1, tp p2)
{
	return (i64)p1.x * p2.y - (i64)p1.y * p2.x;
}

inline i64 vp(tp p, tp p1, tp p2)
{
	p1.x -= p.x;
	p1.y -= p.y;
	p2.x -= p.x;
	p2.y -= p.y;
	return (i64)p1.x * p2.y - (i64)p1.y * p2.x;
}

void strip(string &s)
{
	if (s.find('.') != string::npos)
	{
		while (s.sz && s[s.sz - 1] == '0') s = s.substr(0, s.sz - 1);
		if (s.sz && s[s.sz - 1] == '.' && s.substr(0, s.sz - 1).find('.') == string::npos) s = s.substr(0, s.sz - 1);
	}
	while (s.sz && s[0] == '0') s = s.substr(1);
	if (!s.sz || s[0] == '.') s = "0" + s;
}

int main(int argc, char **argv)
{
	registerTestlibCmd(argc, argv);

	memset(u, 0, sizeof(u));
	int n = inf.readInt();
	tp p0;
	p0.x = inf.readInt();
	p0.y = inf.readInt();
	forn(i, n)
	{
		a[i].x = inf.readInt() - p0.x;
		a[i].y = inf.readInt() - p0.y;
	}
	p0.x = 0;
	p0.y = 0;
	string ja = ans.readToken();
	string pa = ouf.readToken();
	if (pa.sz > 1000)
	{
		quitf(_pe, "too long string in output: '%s'", pa.c_str());
	}

	if (pa == "-1")
	{
		if (ja != pa)
		{
			quitf(_wa, "%s expected, %s found", ja.c_str(), pa.c_str());
		}
		else
		{
			quitf(_ok, "No solution");
		}
	}

	int k = ouf.readInt(1, n);
	forn(i, k)
	{
		int x = ouf.readInt(1, n);
		x--;
		if (u[x]) quitf(_wa, "Duplicate point %d", x+1);
		u[x] = true;
		b[i] = a[x];
	}
	forn(i, 3)
	{
		b[i+k] = b[i];
	}
	int cnt = 0;
	i64 s = 0;
	forn(i, k)
	{
		if (vp(b[i], b[i+1]) <= 0 || vp(b[i], b[i+1], b[i+2]) <= 0)
		{
			quitf(_wa, "Polygon is not convex or wrong order of vertices");
		}
		forn(j, n)
		{
			if (a[j] == b[i] || a[j] == b[i+1]) continue;
			if (vp(b[i], a[j]) >= 0 && vp(a[j], b[i+1]) >= 0 && vp(b[i], b[i+1], a[j]) >= 0)
			{
				quitf(_wa, "point inside polygon");
			}
		}
		cnt += (b[i].y <= 0 && b[i+1].y > 0);
		s += vp(b[i], b[i+1]);
	}
	if (cnt != 1)
	{
		quitf(_wa, "incorrect polygon");
	}

	ostringstream os("");
	os << s / 2 << "." << ((s % 2) ? "5" : "0");
	string ppa = os.str();
	string orig_pa = pa;
	strip(pa);
	strip(ppa);
	if (pa != ppa)
	{
		quitf(_wa, "area = %s, output = %s", ppa.c_str(), orig_pa.c_str());
	}

	if (ja == "-1")
	{
		quitf(_fail, "jury: No solution when solution exists");
	}

	i64 js;
	strip(ja);
	istringstream is(ja);
	char cc;
	is >> js;
	js *= 2;
	string ss;
	if (is >> cc >> ss)
	{
		if (ss.sz && ss[0] == '5') js++;
	}
	if (js > s)
	{
		quitf(_wa, "%s expected, %s found", ja.c_str(), orig_pa.c_str());
	}
	if (js < s)
	{
		quitf(_fail, "%s expected, %s found", ja.c_str(), orig_pa.c_str());
	}

	quitf(_ok, "All OK");

	return 0;
}
