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
#define EPS 10e-12


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
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

#define MAX_N 500

long double xm, ym, zm;
long double vxm, vym, vzm;
int x[MAX_N], y[MAX_N], z[MAX_N];
int vx[MAX_N], vy[MAX_N], vz[MAX_N];
int n;
long double tm, dm;



void solve(){
	int i, j;

	xm=ym=zm=vxm=vym=vzm=0;
	REP(i, n)
		xm+=x[i], ym+=y[i], zm+=z[i], vxm+=vx[i], vym+=vy[i], vzm+=vz[i];

	xm/=n, ym/=n, zm/=n, vxm/=n, vym/=n, vzm/=n;
	long double a, b, c;
	a=vxm*vxm+vym*vym+vzm*vzm;
	b=2*vxm*xm+2*vym*ym+2*vzm*zm;
	c=xm*xm+ym*ym+zm*zm;
	if (a == 0){
		if (b == 0)
			tm=0;
		else
			tm=-c/b;
	   
	}else{
		long double d=b*b-4*a*c;
		assert(d <=10e-7);
		tm=-b/2./a;
	}

	tm=MAX(tm, 2*EPS);
	dm=a*tm*tm+b*tm+c;
	dm=MAX(dm, 2*EPS);
	dm=sqrt(dm);
	


		



}



int main(){
	int i, j, k, T;
	cin >> T;

	REP(i, T){
		cin >> n;

		REP(j, n)
			scanf("%d %d %d %d %d %d", x+j, y+j, z+j, vx+j, vy+j, vz+j);
		solve();
		printf("Case #%d: %Lf %Lf\n", i+1, dm, tm);


	}


	return EXIT_SUCCESS;
}

