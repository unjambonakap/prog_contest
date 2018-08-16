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
const int MAX_C=3;
const int MAX_K=21;


int K, c;
int dp[61][31][31][21];

bool checkit(int a, int b, int c, int d){
	if (a<0||b<0||c<0||d<0)return false;
	return dp[a][b][c][d];
}

int solvea(){
	int i, j, k, l;
	memset(dp, 0, sizeof(dp));

	int s=INT_MAX;
	REP(k, K+1){
		REP(i, 2*K+1)
			REP(j, K+1){
				if (k==0)dp[i][j][0][k]=1;
				else dp[i][j][0][k]=(checkit(i-2, j, 0, k-1)||checkit(i, j-1, 0, k-1))&&checkit(i-1, j, 0, k-1);
				if (k==K && dp[i][j][0][k])s=min(s, i+j);
			}
	}
	return s;
}


int solveb(){
	memset(dp, 0, sizeof(dp));
	int i, j, k, l;
	int s=INT_MAX;

	REP(k, K+1){
		REP(i, 3*K+1)
			REP(j, (3*K)/2+1)
				REP(l, K+1){
					if (k==0)dp[i][j][l][k]=1;
					else dp[i][j][l][k]=(checkit(i-3, j, l, k-1)||checkit(i-1, j-1, l, k-1)||checkit(i, j, l-1, k-1))&&(checkit(i-2, j, l, k-1)||checkit(i, j-1, l, k-1))&&checkit(i-1, j, l, k-1);
					if (k==K && dp[i][j][l][k])s=min(s, i+j+l);
				}
	}

	return s;
}

int solve(){
	if (c==1)return K;
	else if (c==2) return solvea();
	else return solveb();


}


int main(){
	int t, tn;
	cin>>tn;

	FOR(t, 1, tn){
		cin>>K>>c;
		printf("Case #%d: %d\n", t, solve());
	}


	return EXIT_SUCCESS;
}
