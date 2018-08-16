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
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const int INF=1e9;

vi hungarian(vector<vi> m){
	int n=SZ(m);
	int i, j, k, nm;
	vi lr(n, 0), lf(n);
	vi mr(n, -1), mf(n, -1);

	REP(i, n)
		lf[i]=*max_element(ALL(m[i]));
	while(1){
		vi ns, nt(n, 0);
		vi parent(n, -1);
		REP(j, n)if (mf[j]==-1)break;
		if (j == n)break;
		ns.pb(j);
		while(1){
			REP(j, SZ(ns))
				if (mf[ns[j]] != -1)assert(lf[ns[j]]+lr[mf[ns[j]]]==m[ns[j]][mf[ns[j]]]);
			REP(j, SZ(ns)){
				assert(SZ(ns)<=n);
				REP(k, n) 
					if (!nt[k] && m[ns[j]][k]==lf[ns[j]]+lr[k])break;
				if (k!=n)break;
			}
			if (j==SZ(ns)){//update labels
				nm=INF;
				REP(j, SZ(ns))
					REP(k, n)
						if (!nt[k]) nm=min(nm, lf[ns[j]]+lr[k]-m[ns[j]][k]);

				assert(nm > 0);
				REP(j, SZ(ns)){
				   	lf[ns[j]]-=nm;
					assert(lf[ns[j]]>=0);
				}
				REP(k, n) 
					if (nt[k]) lr[k]+=nm;
				continue;
			}
			j=ns[j];
			if (mr[k]==-1){
				
				while(j != ns[0]){
					int oldk=mf[j];
					assert(parent[j]!=-1);
					assert(parent[j]!=j);
					mr[k]=j, mf[j]=k;
					j=parent[j], k=oldk;
				}
				mr[k]=j, mf[j]=k;
				break;
			}else{
				assert(k<n);
				assert(nt[k]==0);
				ns.pb(mr[k]), nt[k]=1;
				assert(mr[k]!=j);
				parent[mr[k]]=j;
			}
		}
	}
	return mf;

}

int main(){
	int i, j, n, c;

	scanf("%d", &n);

	vector<vi> m(n, vi(n));
	REP(i, n)
		REP(j, n)
		scanf("%d", &m[i][j]);


	vi s=hungarian(m);
	c=0;
	REP(i, n)
		c+=m[i][s[i]];

	printf("%d\n", c);





	return EXIT_SUCCESS;
}

