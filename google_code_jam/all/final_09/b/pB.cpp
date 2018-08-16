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

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}

const double INF=1e20;

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

Point getMid(Point &a, Point &b){return Point((a.x+b.x)/2, (a.y+b.y)/2);}

double getPerim(Point &a, Point &b, Point &c){ return dist(a.x, a.y, b.x, b.y)+dist(a.x, a.y, c.x, c.y)+dist(b.x, b.y, c.x, c.y);}



double solve(Point *pl, vector<Point> &yl){
	int i, j, k, l, u, n;
	double midx;
	double ml, mr, m;
	vector<Point> ylr, ylf;

	n=yl.size();
	if (n < 3)return INF;

	midx=((double)(pl[n/2].x+pl[n/2+1].x)/2);
	ylf.reserve(n/2+1), ylr.reserve(n/2+1);
	
	FE(it, yl){
		if ((double)it->x < midx || ((double)it->x == midx && it->y <= pl[n/2].y))
			ylf.pb(*it);
		else
			ylr.pb(*it);
	}
	assert(ylf.size() == n/2+1);
	ml=solve(pl, ylf), mr=solve(pl+n/2+1, ylr);
	m=std::min(ml, mr);	
	deque<Point*> box;


	assert(n == yl.size());
	for(i=0;i<n;i++){
		if (fabs(yl[i].x-midx) >= m/2)continue;
		box.pb(&yl[i]);

		while((double)box.front()->y <= (double)yl[i].y-m/2)
		   	box.pop_front();
		
		assert(SZ(box) < 30);
		assert(box.front()->x >= 0 && box.front()->y >= 0);
		
		
		if (SZ(box) < 3)continue;

		REP(j, SZ(box))
			FOR(k, j+1, SZ(box)-1)
				FOR(l, k+1, SZ(box)-1){
					m=std::min(m, getPerim(*box[j], *box[k], *box[l]));
				}
				

		assert(m!=0);
				



	}
	return m;

}


int main(){
	int i, j, T;
	int n;
	Point pl[MAX_N];
	
	scanf("%d", &T);

	REP(i, T){
		vector<Point> ylist;
		scanf("%d", &n);
		REP(j, n){
			scanf("%d %d", &pl[j].x, &pl[j].y);
			ylist.pb(pl[j]);
		}
		sort(ALL(ylist), cmpy);
		sort(pl, pl+n, cmpx);

		printf("Case #%d: %.15lf\n", i+1, solve(pl, ylist));

	}



	return EXIT_SUCCESS;
}




