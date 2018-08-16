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
const int MAX_N=32;

int n;
vector<ll> m;
ll f;

int used[MAX_N];

vector<ll> la, lb;

void reca(int s, int l, ll ov){
	ll r=0;
	int i;

	if (s==-1){
		if (l==2 && ov<=f)la.pb(ov);
		return;
	}
	

	for(i=2; i>=-2 && l+i>0; i-=2)
		reca(s-1, l+i, ov+(m[s+1]-m[s])*(l+i));
		
}


void recb(int s, int l, ll ov){
	int i;

	if (s==n-1){
		if (l==2 && ov<=f)lb.pb(ov);
		return;
	}

	for(i=2; i>=-2 && l+i>0; i-=2)
		recb(s+1, l+i, ov+(m[s+1]-m[s])*(l+i));
}

int main(){
	int tn, t;
	int i, j;
	ll ta;
	vector<ll>::iterator ita;

	cin>>tn;
	FOR(t, 1, tn){
		cin>>n;
		CLR(m);

		REP(i, n){ cin>>ta; m.pb(ta); }
		sort(ALL(m));

		cin>>f;
		//if (t!=49)continue;
		ta=0;
		for(i=2; i<=2*n; i+=2){
			CLR(la); CLR(lb);
			reca((n-1)/2-1, i, (m[(n-1)/2+1]-m[(n-1)/2])*i);
			recb((n-1)/2+1, i, 0);
			sort(ALL(la));
			sort(ALL(lb), greater<ll>());

			FE(it, la){
				ita=lower_bound(ALL(lb), f-*it, greater<ll>());

				if (ita!=lb.end()){
					ta=max(ta, *it+*ita);
				}
			}
		}



		if (ta==0)
			printf("Case #%d: NO SOLUTION\n", t);
		else
			printf("Case #%d: %Ld\n", t, ta);
	}


	return EXIT_SUCCESS;
}

