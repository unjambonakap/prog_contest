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

const int INF=INT_MAX;

struct Rect{int xa, ya, xb, yb;};

int n;
vector<Rect> tb;

bool connected(Rect a, Rect b){
	Rect in={max(a.xa, b.xa), max(a.ya, b.ya), min(a.xb, b.xb), min(a.yb, b.yb)};

	if (a.xa==b.xb+1 && a.ya==b.yb+1)return false;
	swap(a, b);
	if (a.xa==b.xb+1 && a.ya==b.yb+1)return false;
	if (in.xb-in.xa>=-1 && in.yb-in.ya>=-1)return true;
	return false;
}
int conn[1010];


int solve(){
	int c=0, nc;
	int x, y, d;
	int i;
	map<int, vector<Rect> > m;

	REP(i, n)
		m[conn[i]].pb(tb[i]);
	FE(it, m){
		x=0, y=0, d=INF;
		assert(SZ(it->ND)>0);
		FE(ita, it->ND){
			assert(ita->xa<=ita->xb && ita->ya<=ita->yb);
			x=max(x, ita->xb), y=max(y, ita->yb);
			d=min(d, ita->xa+ita->ya);
		}
		c=max(c, x+y-d+1);

	}
	return c;
}
int main(){
	int t, T;
	int i, j, k;
	Rect a;

	//printf("connected %d\n", connected({1, 1, 1,1}, {1, 2, 1, 2}));
	cin>>T;

	REP(t, T){
		memset(conn, -1, sizeof(conn));
		tb.clear();
		cin>>n;
		REP(j, n){
			scanf("%d %d %d %d", &a.xa, &a.ya, &a.xb, &a.yb);
			tb.pb(a);
		}


		REP(i, n){
			if (conn[i]!=-1)continue;
			stack<int> q;
			q.push(i);
			while(!q.empty()){
				j=q.top(), q.pop();
				conn[j]=i;
				REP(k, n){
					if (conn[k]!=-1)continue;
					if (connected(tb[j], tb[k]))q.push(k);
				}
			}

		}

			

		
		printf("Case #%d: %d\n", t+1, solve());


	}


	return EXIT_SUCCESS;
}

