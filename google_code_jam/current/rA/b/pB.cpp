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
#define MP make_pair

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


int D, I, M, L;
const int MAX_L=100, MAX_P=256;
int tb[MAX_L];
int dp[MAX_L][MAX_P+1];


int doit(int lp, int id){
	int &ref=dp[id][lp];
	int i, j, k;
	int tp;

	if (ref!=-1)return ref;
	if (id==L)return 0;

	
	ref=D+doit(lp, id+1);//deletion

	REP(i, MAX_P){
		if (lp==256 || abs(lp-i)<=M){
			ref=min(ref, I+doit(i, id));//insertion
		   	ref=min(ref, abs(i-tb[id])+doit(i, id+1));//modify
		}
	}


	return ref;
}

int solve(){
	int i, j, k;
	memset(dp, -1, sizeof(dp));

	return doit(256, 0);
}

int main(){
	int X, t;
	int i, j;

	scanf("%d", &X);

	REP(t, X){
		scanf("%d %d %d %d\n", &D, &I, &M, &L);
		REP(i, L)
			scanf("%d", tb+i);

		//printf("%d %d %d %d\n", D, I, M, L);
		//REP(i, L)
		//	printf("%d ", tb[i]);

		assert(solve()>=0);
		printf("Case #%d: %d\n", t+1, solve());
	}


	return EXIT_SUCCESS;
}


