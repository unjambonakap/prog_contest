#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i < (b)) && (c); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define FORVC(i, a, b, c) for(i = (b) - 1; (i >= (a)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;

#define MAX_L 15
#define MAX_p 1000000

int d, l, ns;
vector<string> sl;

int doit(const char *s, const char *dest){
	const char *a;

	if (*s == '\0')
		return (*dest == '\0');
	if (*s != '('){
		if (*dest != *s)
			return 0;
		return doit(s+1, dest+1);
	}


	a=s;
	bool ok=false;
	while(*(++a) != ')')
		if (*a == *dest)
			ok=true;
	
	if (ok)
		return doit(a+1, dest+1)||doit(a,dest);
	return 0;


	


}
int solve(string s){
	int i, c;
	c=0;
	REP(i, d)
		if (doit(s.c_str(), sl[i].c_str()))
			c++;

	return c;



}


int main(){
	int i, j;
	string s;

	scanf("%d %d %d", &l, &d, &ns);
	REP(i, d){
		cin >> s;
		sl.pb(s);
	}
	REP(i, ns){
		cin >> s;
		printf("Case #%d: %d\n", i+1, solve(s));


	}
	return EXIT_SUCCESS;
}

