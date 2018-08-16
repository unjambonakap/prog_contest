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

const double INF=1e20;

int dfs(int a, const vector<vi>& m, vi& ml, vi& mr, vi& visited){
	int i;
	if (visited[a])return 0;
	visited[a]=1;
	REP(i, SZ(m))
		if (m[a][i]==0)
			if (mr[i]==-1 || dfs(mr[i], m, ml, mr, visited)){ ml[a]=i, mr[i]=a;return 1; }
	return 0;
}



vi hungarian(vector<vi> m){
	int n, i, j, k;
	unsigned int ma, nm;
	n=SZ(m);

	vi ml(n, -1), mr(n, -1);
	nm=0;
	REP(i, n){
		ma=-1;
		REP(j, n)
			ma=min(ma, (unsigned int)m[i][j]);
		REP(j, n)
			m[i][j]-=ma;
	}
	REP(i, n){
		ma=-1;
		REP(j, n)
			ma=min(ma, (unsigned int)m[j][i]);
		REP(j, n)
			m[j][i]-=ma;
	}
	while(1){
		REP(i, n) if (ml[i]==-1){
			vi visited(n, 0);
			nm+=bool(dfs(i, m, ml, mr, visited));
		}
		REP(i, n){
			REP(j, n)
				printf("%d ", m[i][j]);
			printf("\n");
		}
		if (n == nm)break;//perfect matching
		vi sl(n, 0), sr(n, 0);
		REP(i, n){
			if (ml[i]==-1){
				sl[i]=1;
				REP(j, n)
					if (m[i][j]==0){
						sr[j]=1;
						if (mr[j]!=-1)
							sl[mr[j]]=1;
					}
			}
		}
		ma=-1;
		REP(i, n)
			REP(j, n)
				if (sl[i]==1 && sr[j]==0)
					ma=min(ma, (unsigned int)m[i][j]);
		//only maximum matching => relabel
		REP(i, n)
			REP(j, n){
				if (sl[i]==1 && sr[j]==0)m[i][j]-=ma;
				else if (sl[i]==0 && sr[j]==1)m[i][j]+=ma;
			}
	}
	return ml;
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
