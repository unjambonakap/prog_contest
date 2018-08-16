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

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}

const double INF=1e20;


const int MAX_R=10, MAX_P=26;
const int MOD=10007;
const int MAX_STATE=200000;

int r, c;
int mmap[MAX_R][MAX_R];
vi restate[MAX_STATE];
map<vi, int> state;
int ns;
int store[MAX_STATE][MAX_R][MAX_R];

int F[MAX_STATE], G[MAX_STATE];


void dfs(vi h){
	if (SZ(h) == MAX_R){
		state[h]=ns;
		restate[ns++]=h;

	}else{
		int i;
		FORV(i, (SZ(h) == 0)?MAX_R:h.back(), 0){
			h.pb(i);
			dfs(h);
			h.pop_back();
		}
	}


}

int solve(){
	int i, j, k, l, S;
	vi h;
	memset(F, 0, sizeof(F));
	memset(store, -1, sizeof(store));

	REP(i, MAX_R)
		h.pb(0);


	F[state[h]]=1;

	for(l=0; l < MAX_P; l++){
		for(j=0; j < c; j++){
			memset(G, 0, sizeof(G));
			for(i=0; i < ns; i++){
				if (F[i] == 0)continue;

				G[i]+=F[i];
				if (G[i] > MOD)
					G[i]-=MOD;
				h=restate[i];
				int oh=h[j];
				for(k=h[j]; k<((j == 0)?r:h[j-1]); k++){
					if (mmap[j][k] >= 0 && mmap[j][k] != l)break;
					S=store[i][j][k];
					if (S == -1){
						h[j]=k+1;
						S=store[i][j][k]=state[h];
					}
					G[S]+=G[i];
					if (G[S] >= MOD)
						G[S]-=MOD;
				}
				h[j]=oh;
			}
			memcpy(F, G, sizeof(F));
		}
	}
	h.clear();
	REP(i, MAX_R)
		h.pb((i < c)?r:0);

	return F[state[h]];






}

int main(){
	int i, j, k, T;
	char ca;

	ns=0;
	vi h;
	dfs(h);
	scanf("%d", &T);

	REP(i, T){
		scanf("%d %d\n", &r, &c);

		REP(j, r){
			REP(k, c){
				scanf("%c", &ca);
				if (ca == '.')
					mmap[k][j]=-1;
				else
					mmap[k][j]=ca-'a';

			}
			scanf("\n");
		}

		printf("Case #%d: %d\n", i+1, solve());

	}


	return EXIT_SUCCESS;
}

