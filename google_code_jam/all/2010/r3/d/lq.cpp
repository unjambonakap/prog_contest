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
const int MOD=1000000007;

vector<int> decomp(int n, int b){
	vector<int> nb;
	while(n!=0){
		nb.pb(n%b);
		n/=b;
	}
	return nb;
}
bool checkit(const vector<vi>& a, const vector<int>& b){
	int i;
	FE(it, a)
		REP(i, min(SZ(*it), SZ(b)))
			if ((*it)[i]==b[i])return 0;
	
	return 1;

}

int recurs(int aa, int ab, int n, int b, int low, vector<vi> dec){
	int i, high, s, ns;

	if (n<0)return 0;
	if (aa==ab-1){
		if (n<=low)return 0;
		vi nd=decomp(n, b);
	//	printf("test: remaining %d: %d\n", n, nd.back());
		return checkit(dec, nd);
	}

	high=(n-low)/(ab-aa);

	s=0;
	FOR(i, low+1, n){
		vi nd=decomp(i, b);
		if (!checkit(dec, nd))continue;
		dec.pb(nd);
		ns=recurs(aa+1, ab, n-i, b, i, dec);
	//	printf("%d %d => try %d > %d\n", aa, ab, i, ns);
		s+=ns;
		dec.pop_back();
	}
	return s;

}

int solve(int n, int b){
	int s;
	int i, j, k;
	s=1;
	vector<vi> dec;


	FOR(i, 2, b){//i summands
		s+=recurs(0, i, n, b, 0, dec);
	}


	return s;
}

int main(){
	int t, T;
	int i, j, k;
	int n, b;

	cin>>T;
	REP(t, T){
		cin>>n>>b;
		printf("Case #%d: %d\n", t+1, solve(n, b));
	}


	return EXIT_SUCCESS;
}

