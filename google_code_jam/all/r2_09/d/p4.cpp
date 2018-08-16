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
#define EPS 10e-7


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


/*

   (x-xa)^2 + (y-ya)^2 = (r-ra)2
   (x-xb)^2 + (y-yb)^2 = (r-rb)2
2 - 1 
  	xxa-xxb+yya-yyb = (xa2+ya2-xb2-yb2-(r-ra)2+(r-rb)2)/2
	y(ya-yb)= ___ -x(xa-xb)
	y=A+B*x+ya

	x2-2xax+xa*xa+B*B*xx+2*A*B*x +A*A=(r-ra)2
 */


#define MAX_N 40




class Point;
class Point{
	public:
		Point(){};
		Point(long double _x, long double _y){x=_x, y=_y;}
		long double x, y, r;
};

int n;
Point pl[MAX_N];
vector<Point> cen;



void add_int(int u, int v, double r){
	long double A, B, a, b, c, d;
	long double xa, xb, ya, yb, ra, rb, x;

	xa=pl[u].x, ya=pl[u].y, xb=pl[v].x, yb=pl[v].y;
	ra=pl[u].r, rb=pl[v].r;

	if (ya-yb==0){
		x=(xa*xa+ya*ya-xb*xb-yb*yb-SQR(r-ra)+SQR(r-rb))/2/(xa-xb);
		d=SQR(r-ra)-SQR(x-xa);
		if (d > 0)
			cen.pb(Point(x, sqrt(d)+ya)), cen.pb(Point(x, -sqrt(d)+ya));
		
		if (d == 0)
			cen.pb(Point(x, 0));
		
		

	}else{


		A=(xa*xa+ya*ya-xb*xb-yb*yb-SQR(r-ra)+SQR(r-rb))/2/(ya-yb)-ya;
		B=-(xa-xb)/(ya-yb);
		a=1+B*B, b=-2*xa+2*A*B, c=xa*xa+A*A-SQR(r-ra);
		d=b*b-4*a*c;
		if (d < 0)
			return;

		if (d == 0){
			x=-b/2/a;
			cen.pb(Point(x, A+B*x+ya));
		}
		else{
			x=(-b-sqrt(d))/2/a;
			cen.pb(Point(x,  A+B*x+ya));

			x=(-b+sqrt(d))/2/a;
			cen.pb(Point(x,  A+B*x+ya));
		}
	}

}

int checkit2(Point p, Point q, long double r){
	int i;
	REP(i, n)
		if (sqrt(DIST(pl[i].x-p.x, pl[i].y-p.y)) > r-pl[i].r+EPS && sqrt(DIST(pl[i].x-q.x, pl[i].y-q.y)) > r-pl[i].r+EPS)
			return 0;
	return 1;
}
int checkit(long double r){
	int i, j, k;

	cen.clear();

	REP(i, n){
		cen.pb(Point(pl[i].x, pl[i].y));
		FOR(j, i+1, n-1)
			add_int(i, j, r);
	}
			

	REP(i, cen.size())
		FOR(j, i+1, cen.size()-1)
			if (checkit2(cen[i], cen[j], r))
				return 1;

	
	return 0;

	


}

long double solve(){

	long double H, L, M;


	if (n == 1)return pl[0].r;
	H=2000., L=0.;
	while(CMP(H, L) == 1){
		M=(H+L)/2;

		if (checkit(M) == 0)
			L=M;
		else
			H=M;
	}
	return H;


}



int main(){

	int i, j, T;
	cin >> T;
	REP(i, T){
		cin >> n;
		REP(j, n)
			cin >> pl[j].x >> pl[j].y >> pl[j].r;

		printf("Case #%d: %.8Lf\n", i+1, solve());


	}


	return EXIT_SUCCESS;
}

