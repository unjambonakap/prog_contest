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
//#include <ext/hash_map>


using namespace std;

#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;


#define MAX_N 1000000


class Point{
	public:
		Point(){}
		Point(int _x, int _y):x(_x), y(_y){}
		int x, y;
};



bool cmpx(const Point& a, const Point &b){
	if (a.x != b.x)
		return (a.x < b.x);
	return (a.y < b.y);
}
bool cmpy(const Point& a, const Point &b){
	if (a.y != b.y)
		return (a.y < b.y);
	return (a.x < b.x);
}




double solve(Point *pl, const vector<Point&> yl, int n){





	return 0.;
}
int main(){
	int i, j, T;
	int n;
	Point pl[MAX_N];
	
	scanf("%d", &T);

	REP(i, T){
		vector<Point&> ylist;
		scanf("%d", &n);
		REP(j, n){
			scanf("%d %d", &p[i].x, &p[i].y);
			ylist.pb(p[i]);
		}
		sort(ALL(ylist), cmpy);
		sort(pl, pl+n, cmpx);
		printf("Case #%d: %lf\n", i+1, solve(pl, ylist, n));

	}



	return EXIT_SUCCESS;
}




