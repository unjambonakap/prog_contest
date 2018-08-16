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

const int INF=1000000;

const int MAX_S=110;
int m[MAX_S][MAX_S];
int added[3*MAX_S][3*MAX_S];
int k;
int vx[]={1, -1, 1, -1};
int vy[]={1, 1, -1, -1};

bool isSym(int x, int y){
	int a, b, i, j, nx, ny, l;
	REP(i, 2*k+1)
		REP(j, 2*k+1){
			//printf("try %d %d\n", i, j);
			if ((a=m[i][j])==-1)continue;
			REP(l, 4){
				nx=x+(x-i)*vx[l], ny=y+(y-j)*vy[l];
				//printf("sym %d %d\n", nx, ny);
				if (nx>=0 && nx<2*k+1 && ny>=0 && ny<2*k+1 && (b=m[nx][ny])!=-1 && b!=a)return false;
			}
		}
	return true;
}

int costSym(int x, int y){
	int nk=0;
	nk=max(nk, y+abs(x-k+1));
	nk=max(nk, 2*k-2-y+abs(x-k+1));
	nk=max(nk, x+abs(y-k+1));
	nk=max(nk, 2*k-2-x+abs(y-k+1));
	++nk;
	return nk*(nk+1)-nk-(k*(k+1)-k);

}

int solve(){
	int i, j, c;

	c=INF;
	REP(i, 2*k+1)
		REP(j, 2*k+1)
			if (isSym(i, j))
				c=min(c, costSym(i, j));
	return c;
		
}

int main(){
	int i, j;
	int t, T;
	int x;

	scanf("%d", &T);
	REP(t, T){
		memset(m, -1, sizeof(m));
		scanf("%d", &k);

		REP(i, k)
			REP(j, i+1)
				scanf("%d", &m[k-i-1+2*j][i]);
		REP(i, k-1)
			REP(j, k-i-1)
				scanf("%d", &m[i+1+2*j][k+i]);

	//	REP(i, 2*k){
	//		REP(j, 2*k)
	//			printf("%d", m[j][i]);
	//		printf("\n");
	//	}


		


		printf("Case #%d: %d\n", t+1, solve());
	}


	return EXIT_SUCCESS;
}

