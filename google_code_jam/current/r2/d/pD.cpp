#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

double intersect(int xa, int ya, int xb, int yb, long double ra, long double rb){
	long double A, B, a, b, c, d;
	double x;

	if (ya-yb==0){ 
		x=(xa*xa+ya*ya-xb*xb-yb*yb-SQR(ra)+SQR(rb))/2/(xa-xb); 
		d=SQR(ra)-SQR(x-xa); 
		if (d > 0) 
			cen.pb(Point(x, sqrt(d)+ya)), cen.pb(Point(x, -sqrt(d)+ya)); 

		if (d == 0) 
			cen.pb(Point(x, 0)); 



	}else{ 


		A=(xa*xa+ya*ya-xb*xb-yb*yb-SQR(ra)+SQR(rb))/2/(ya-yb)-ya; 
		B=-(xa-xb)/(ya-yb); 
		a=1+B*B, b=-2*xa+2*A*B, c=xa*xa+A*A-SQR(ra); 
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

int main(){
	int _t, _T;
	int i, j, k;

	scanf("%d", &_T);
	REP(_t, _T){


		printf("Case #%d: ", _t+1);
	}



	return EXIT_SUCCESS;
}

