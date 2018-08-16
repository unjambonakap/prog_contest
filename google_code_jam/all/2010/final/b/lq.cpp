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
const int MAX_P=16;



int used[MAX_P];

bool dfs_ham(const vector<vi> &g, int p, int s, int st){
	if (s==SZ(g))return p==st;
	FE(it, g[p]){
		if (used[*it])continue;
		used[*it]=1;
		if (dfs_ham(g, *it, s+1, st))return true;

		used[*it]=0;
	}
	return false;
}

int main(){
	int n, na;
	int t, tn;
	int i, j, k;
	int rmap[MAX_P];
	cin>>tn;
	REP(t, tn){

		cin>>n;
		vector<vi> edges(n);
		vi deg(n, 0);
		REP(i, 3)
			edges[i].pb((i+1)%3), edges[i].pb((i+2)%3), deg[i]=2;
		REP(i, n-3){
			cin>>j>>k;
			--j, --k;
			edges[i+3].pb(j), edges[i+3].pb(k);
			edges[j].pb(i+3), edges[k].pb(i+3);
		}

		int m=-1;
		REP(i, two(n)){

			vector<vi> ng(na=count_bit(i));
			k=0;
			memset(rmap, -1, sizeof(rmap));

			REP(j, n){
				if (i&two(j)){
					rmap[j]=k++;
					assert(k<=na);
					FE(it, edges[j])
						if (rmap[*it]!=-1 && i&two(*it))ng[k-1].pb(rmap[*it]), ng[rmap[*it]].pb(k-1);
					
				}

			}
			memset(used, 0, sizeof(used));
			if (dfs_ham(ng, 0, 0, 0))
				m=max(m, na);




		}
		assert(m>=3);

		printf("Case #%d: %d\n", t+1, m);



	}



	return EXIT_SUCCESS;
}

