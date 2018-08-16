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
using namespace __gnu_cxx;

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

#define ST first
#define ND second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const int INF=1000000;

const int MAX_N=510;

int store[2*MAX_N];
int cross[MAX_N][MAX_N];
int start[MAX_N], end[MAX_N];
vs sl;
int n;
int dp[2*MAX_N][2*MAX_N][MAX_N];
int sign[MAX_N];
vector<pii> bc[2*MAX_N];


void dfs(int u, int s){
	int i;
	if (sign[u] == s)return;
   	if (sign[u] == -s)
		throw 0;
	

	sign[u]=s;
	REP(i, n)
		if (i != u && cross[u][i])
			dfs(i, s*(-1));
}

vector<pii>& proc_bc(int a){
	int i, u;

	vector<pii>& e=bc[a];
	if (SZ(e) != 0)return e;

	memset(sign, 0, sizeof(sign));
	dfs(store[a], 1);

	FOR(i, a, 2*n-1){
		u=store[i];
		if (sign[u] == 0)continue;
		e.pb(make_pair(i, sign[u]+1+((i == end[u])?1:0)));
	}
	return e;
}

int proc(int a, int b, int hh){
	int i, j, st, nd;
	int bot, top, h, mask;
	int &res=dp[a][b][hh];
	vector<pii> e;


	if (hh < 0)return INF;
	if (res != -1)return res;
	if (a == b)return 0;


	e=proc_bc(a);
	res=INF;
	bot=top=0;

	assert(SZ(e) != 0);
	for(mask=0; mask <= 2; mask+=2){
		h=0;
		REP(i, SZ(e)+1){
			st=(i==0)?a:e[i-1].ST+1;
			nd=(i==SZ(e))?b:e[i].ST;

			h=max(h, proc(st, nd, hh-top)+bot);

			if (i != SZ(e)){
				switch((e[i].ND+mask)%4){
					case 0: bot++; break;
					case 1: bot--; break;
					case 2: top++; break;
					case 3: top--; break;
				}

			}
		}


		res=min(res, h);
	}


	return res;
}




int solve(){
	int i, j, k, m;


	memset(cross, 0, sizeof(cross));


	REP(i, 2*n)
		CLR(bc[i]);

	REP(i, n){
		FOR(j, i+1, n-1)
			if (end[i] > start[j] && end[i] < end[j])
				cross[i][j]=cross[j][i]=1;

	}

	memset(dp, -1, sizeof(dp));

	m=-1;
	REP(i, 2*n){
		try{
			k=proc(0, 2*n, i);
		}catch(int){
			return -1;
		}
		
		if (m == -1 || m > i+k)
			m=i+k;

	}

	return m;
}

int main(){
	int i, j, k, T, tx;
	string s;

	scanf("%d", &T);

	REP(tx, T){
		scanf("%d\n", &n);

		CLR(sl);
		memset(start, -1, sizeof(start));
		memset(end, -1, sizeof(end));
		REP(i, 2*n){
			cin >> s;

			REP(j, SZ(sl))
				if (s == sl[j])
					break;
			if (j == SZ(sl))
				sl.pb(s);
			store[i]=j;

			if (start[j] == -1)start[j]=i;
			else end[j]=i;

		}
		printf("Case #%d: %d\n", tx+1, solve());




	}


	return EXIT_SUCCESS;
}

