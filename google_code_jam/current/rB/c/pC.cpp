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


const int MOD=100003;
const int MAX_N=502;
int tb[MAX_N][MAX_N];
int comb[MAX_N][MAX_N];

int proc_comb(int a, int b){
	if (comb[a][b]!=-1)return comb[a][b];
	return comb[a][b]=(proc_comb(a-1, b-1)+proc_comb(a, b-1))%MOD;
}

int dp(int n, int s){
	int i, j, k;
	ll temp;

	if (n==2 && s!=1)return 0;
	if (s==1 || s==n)return 1;
	if (n-1<s)return 0;
	if (tb[n][s]!=-1)return tb[n][s];
	int& a=tb[n][s];


	//n is the s-th elem => s is in the set => at which pos?

	a=0;
	FOR(i, 0, s-2){//s-1 elems to place => put i elem before s, s-i-2 after
		if (n-s-1<s-i-2)continue;
		temp=((ll)dp(s, i+1)*(ll)comb[s-i-2][n-s-1])%MOD;
		assert(dp(s, i+1)>=0);
		assert(temp>=0);
		a=(a+temp)%MOD;

	}
	return a;
}

int main(){
	int t, T, c, n;
	scanf("%d", &T);
	memset(tb, -1, sizeof(tb));
	int i, j, k;

	memset(comb, -1, sizeof(comb));

	REP(i, MAX_N+1)
		comb[0][i]=comb[i][i]=1;
	REP(i, MAX_N+1) REP(j, i) proc_comb(j, i);
	assert(comb[10][476]>=0);

	REP(t, T){
		c=0;
		scanf("%d", &n);
		FOR(i, 1, n-1)
			c=(c+dp(n, i))%MOD;
		

		


		printf("Case #%d: %d\n", t+1, c);



	}


	return EXIT_SUCCESS;
}

