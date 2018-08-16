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
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

const int MAX_N=20;

int store[2*MAX_N];
int cross[MAX_N][MAX_N], above[MAX_N][MAX_N];
int start[MAX_N], end[MAX_N];
int res[MAX_N];

vs sl;
int n;


int proc(int a, int s){
	if (res[a] != -1)return res[a];
	int i;
	res[a]=1;
	REP(i, n) if (a != n && bit_set(s, i) == bit_set(s, a) && above[a][i])
		res[a]=MAX(res[a], proc(i, s)+1);
	
	return res[a];

}
int solve(){
	int i, j, k;


	memset(cross, 0, sizeof(cross));
	memset(above, 0, sizeof(above));

	REP(i, n){
		FOR(j, i+1, n-1){
			if (end[i] > end[j])
				above[i][j]=1;
			
			
			
			else if (end[i] > start[j])
				cross[i][j]=cross[j][i]=1;
			
			
		}
	}
	int m=-1, ml, mh, a;
	REP(i, two(n)){

		REP(j, n){
			FOR(k, j+1, n-1){
				if (bit_set(i, j) == bit_set(i, k) && cross[j][k])
					break;
				
			}
			if (k != n)break;
		}
		if (j != n)continue;

		mh=ml=0;
		memset(res, -1, sizeof(res));
		REP(j, n){
			if (!bit_set(i, j))
				ml=MAX(ml, proc(j, i));
			else
				mh=MAX(mh, proc(j, i));
		}

		if (m == -1 || m > ml+mh)
			m=ml+mh;
	}
	


	return m;
}

int main(){
	int i, j, k, T, tx;
	string s;

	scanf("%d", &T);

	REP(tx, T){
		scanf("%d\n", &n);

		CLR(sl);
		memset(start, -1, sizeof(start));
		memset(end, -1, sizeof(end));
		REP(i, 2*n){
			cin >> s;

			REP(j, SZ(sl))
				if (s == sl[j])
					break;
			if (j == SZ(sl))
				sl.pb(s);
			store[i]=j;
		
			if (start[j] == -1)start[j]=i;
			else end[j]=i;
			
		}
		printf("Case #%d: %d\n", tx+1, solve());




	}


	return EXIT_SUCCESS;
}

