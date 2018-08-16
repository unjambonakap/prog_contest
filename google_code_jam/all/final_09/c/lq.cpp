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


const int MAX_R=4, MAX_P=26;
const int MOD=10007;

int r, c;
int mmap[MAX_R][MAX_R];
int dp[MAX_R][MAX_R][MAX_P*MAX_P*MAX_P*MAX_P];

int get_d(int d, int p){ return (int(d/pow(MAX_P, p)))%MAX_P; }
int set_d(int d, int p, int nd){ return d+(nd-get_d(d, p))*pow(MAX_P, p); }

int solve(int x, int y, int d){
	if (x == c)x=0, y++;
	if (y == r)return 1;

	int& v=dp[x][y][d];
	if (v != -1)return v;

	v=0;

	int i, nd;
	FOR(i, (mmap[x][y] == -1)?0:mmap[x][y], ((mmap[x][y] == -1)?MAX_P-1:mmap[x][y])){
		if (y > 0 && i < get_d(d, x))continue;
		if (x > 0 && i < get_d(d, x-1))continue;
		nd=set_d(d, x, i);
		v+=solve(x+1, y, nd);
	}
	
	v%=MOD;
	return v;
}


int main(){
	int i, j, k, T;
	char ca;
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d\n", &r, &c);
		memset(dp, -1, sizeof(dp));
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
		printf("Case #%d: %d\n", i+1, solve(0, 0, 0));
	}


	return EXIT_SUCCESS;
}

