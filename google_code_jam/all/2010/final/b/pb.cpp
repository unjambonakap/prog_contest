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



#define REP(i,n) for(i = 0; i < (n); ++i)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); ++i)

#define REPV(i, n) for (i = (n) - 1; i >= 0; --i)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); --i)
#define FOR(i, a, b) for(i = (a); i <= (b); ++i)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); ++i)
#define FORV(i, a, b) for(i = (a); i >= (b); --i)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); --i)

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
const int MAX_P=1010;



int used[MAX_P];
int g[MAX_P][MAX_P];

int n;
int res;

void setC(int a, int b, int c){ g[a][b]=g[b][a]=c; }

int proc(int a, int b){
	int i, j, k, sl, ns, fl;

	if (g[a][b]==0)return 0;
	fl=2;
	sl=0;


	assert(a<b);
	FOR(i, max(a, b)+1, n){
		if (g[a][i]*g[b][i]>0){
			ns=proc(a, i)+proc(b, i)-1;
			if (ns>fl)
				sl=fl, fl=ns;
			else if (ns>sl)
				sl=ns;

		}
	}
	

	res=max(res, fl+sl-2);
	return fl;

}

int main(){
	int t, tn;
	int i, j, k;

	cin>>tn;
	REP(t, tn){

		cin>>n;
		memset(g, 0, sizeof(g));
		setC(1, 2, 1); setC(2, 3, 1); setC(1, 3, 1);
		FOR(i, 4, n){
			cin>>j>>k;
			setC(i, j, 1), setC(i, k, 1);
		}

		res=-1;
		FORV(i, n-1, 1){
			FORV(j, n, i+1)
				proc(i, j);
		}
		printf("Case #%d: %d\n", t+1, res);



			

	}



	return EXIT_SUCCESS;
}

