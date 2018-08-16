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
#define SZ(a) (ll((a).size()))
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

typedef long long  ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pii;
typedef vector<ll> vi;
typedef vector<string> vs;
typedef queue<ll> qi;

inline ll count_bit(ll n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(ll x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(ll a, ll b){return (a&two(b));}

const double INF=1e20;
const ll MAX_D=6;


ll mod(ll a, ll p){ return (a%p+p)%p; }
ll _bezout(ll a, ll b, ll ua, ll va, ll ub, ll vb, ll *ur, ll *vr){
	ll nr=a%b;
	if (nr==0){
		*ur=ub, *vr=vb;
		return b;
	}//nr=a-(a/b)*b

	return _bezout(b, nr, ub, vb, ua-(a/b)*ub, va-(a/b)*vb, ur, vr);
}

ll bezout(ll a, ll b, ll *ur, ll *vr){ 
	if (a<b)swap(a, b), swap(ur, vr);
	return _bezout(a, b, 1, 0, 0, 1, ur, vr); 
}

ll inv(ll a, ll p){
	ll xa, xb;
	a=(a+p)%p;
	bezout(a, p, &xa, &xb);
	assert(mod(a*xa, p)==1);
	return xa;
}

void buildPrime(ll m, vector<ll>& l){
	l.clear();
	ll i, sq, sqa;

	sq=1, sqa=3;
	l.pb(2);
	for(i=3; i<=m; i+=2){
		if (sqa<i) ++sq, sqa=sq*sq;
		FE(it, l)
			if (sq<*it)break;
			else if(i%*it==0)goto notprime;
		l.pb(i);
notprime:;
	}
}

ll getNext(ll x, ll y, ll z, ll p, ll *sa=NULL, ll *sb=NULL){
/*
	   s=x
	   a*x+b=y
	   a*y+b=z

	   a*(x-y)=y-z
	   >>> a=(y-z)*(x-y)^-1
	   b=y-a*x

	   */
	ll a, b;
	a=mod((y-z)*inv(x-y, p), p);
	b=mod(y-a*x, p);
	if (sa)*sa=a, *sb=b;
	return mod(a*z+b, p);




}
ll solve(const vector<ll>& pl, vector<ll>& l, ll d){

	if (SZ(l)==1)return -1;
	if (l.back()==l[l.size()-2])return l.back();
	if (SZ(l)==2)return -1;

	
	ll x, y, z, a, b, i;
	ll next, ma, nn;

	ma=*max_element(ALL(l));
	//FE(it, l)
	//	printf("%d ", *it);
	//printf("\n");

	x=l[SZ(l)-3], y=l[SZ(l)-2], z=l.back();
	next=-1;
	FE(it, pl){
		if (*it<=ma)continue;
		else if (*it>pow(10, d))break;

		nn=getNext(x, y, z, *it, &a, &b);
		FOR(i, 1, SZ(l)-1)
			if (l[i]!=mod(a*l[i-1]+b, *it))
				goto incorrect;

		if (0){
			incorrect:
					  continue;
		}

		if (next!=-1 && nn!=next)return -1;
		next=nn;
	}
	return next;

}


int main(){
	vector<ll> pl;
	vector<ll> l;
	ll d;
	buildPrime(pow(10, MAX_D), pl);
	ll t, T, n, i, j;
	cin>>T;
	REP(t, T){
		l.clear();

		cin>>d>>n;
		REP(i, n)
			cin>>j, l.pb(j);
		printf("Case #%Ld: ", t+1);
		j=solve(pl, l, d);
		if (j==-1)printf("I don't know.\n");
		else printf("%Ld\n", j);
		
	}

	return EXIT_SUCCESS;
}

