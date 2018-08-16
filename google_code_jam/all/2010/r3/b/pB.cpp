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
inline ll sqr(ll x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;

ll l;
vector<ll> bl;
const int MAX_Q=100000;
int w[MAX_Q];
int added[MAX_Q];


struct Vertex{
		int w;
		int p;
		ll tot;
		bool operator<(const Vertex& a)const{return w<a.w;}
};

ll solve(){
//
//	ll i, j, k;
//	ll md=SZ(bl)*sqr(bl.back())+250;
//	assert(md<MAX_P);
//
//	tb[0]=0;
//	FOR(i, 1, md){
//		tb[i]=-1;
//		REP(j, SZ(bl)){
//			if (bl[j]>i)break;
//			if (tb[i-bl[j]]==-1)continue;
//			if (tb[i]==-1 || tb[i]>tb[i-bl[j]]+1)
//				tb[i]=tb[i-bl[j]]+1;
//		}
//	}
//
//
//
//
//	
//	k=l%bl.back();
//	ll d=l/bl.back();
//	assert(bl.back()*d+k==l);
//   	ll s=-1;
//	while(k<=md){
//		if (tb[k]!=-1 && s==-1 || s>d+tb[k])
//			s=d+tb[k];
//		k+=bl.back(), --d;
//	}
//
//	return s;

	
	int q=l%bl.back();
	int i, a, nw, nt, na;
	memset(w, -1, sizeof(w));
	memset(added, 0, sizeof(added));

	priority_queue<int> pq;
	pq.push(0);
	w[0]=0;
	added[0]=1;
	while(!pq.empty()){
		a=pq.top(); pq.pop();
		added[a]=0;

		REP(i, SZ(bl)-1){
			nw=w[a]+1, na=a+bl[i];
			if (na>=bl.back())--nw;
			na%=bl.back();

			if (w[na]==-1 || w[na]>nw){
				w[na]=nw;
				if (!added[na])
					pq.push(na), added[na]=1;
			}
		}
	}
	if (w[q]==-1)return -1;
	
	return w[q]+l/bl.back();



}

int main(){
	int t, T, n, i;
	ll s;
	cin>>T;
	REP(t, T){
		CLR(bl);
		scanf("%Ld %d", &l, &n);
		REP(i, n)
			cin>>s, bl.pb(s);

		sort(ALL(bl));

		s=solve();
		printf("Case #%d: ", t+1);
		if (s==-1)printf("IMPOSSIBLE\n");
		else printf("%Ld\n", s);
	}


	return EXIT_SUCCESS;
}

