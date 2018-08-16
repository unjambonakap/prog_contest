#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
//#include <ext/hash_map>
#include <cmath>
#include <cassert>


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

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

#define MOD 1000000007
#define MAX_R 10e13
#define MAX_N 15

char l[MAX_N], r[MAX_N];
int nl, nr;
vector<ll> plist;


int tb[MAX_N];


int gen(int a, int l){
	int i, r;

	if (a == ceil(l/2.)){
		ll s=0;
		REPV(i, l)
			s=s*10+tb[i];
		plist.pb(s);
	}else{
		FOR(i, (a == 0)?1:0, 9){
			tb[a]=tb[l-a-1]=i;
			gen(a+1, l);
		}
	}
}


ll solve(){
	
	int i, j;
	int H, L, M;
	int lid, rid;
	ll lv, rv;

	lv=rv=0;

	REP(i, nl)
		lv=lv*10+l[i]-'0';
	REP(i, nr)
		rv=rv*10+r[i]-'0';
	
	lv--;

	L=0, H=SZ(plist);
	while(H > L){
		M=(H+L)/2.;
		if (plist[M] < lv)
			L=M+1;
		else
			H=M;
	}
	lid=L;


	L=0, H=SZ(plist);
	while(H > L){
		M=ceil((H+L)/2.);
		if (plist[M] > rv)
			H=M-1;
		else
			L=M;
	}
	rid=L;
	if (lid > rid)
		return (rv-lv)*(rv-lv+1)/2;

	printf("number %Ld %Ld\n", plist[lid], plist[rid]);
	
	ll a, b;
	a=b=0;
	FOR(i, lid+1, rid){
		if (i&1)
			a+=plist[i]-plist[i-1], a%=MOD;
		else
			b+=plist[i]-plist[i-1], b%=MOD;
	}
	printf("raw %Ld\n", b);
	if (lid&1)
		a=(a+plist[lid]-lv)%MOD;
	else
		b=(b+plist[lid]-lv)%MOD;
	printf("raw %Ld\n", b);

	if (rid&1)
		b=(b+rv-plist[rid]+1)%MOD;
	else
		a=(a+rv-plist[rid]+1)%MOD;
	
	printf("%Ld %Ld over %Ld\n", b, a, a+b);
	return ((a*a+b*b-a-b)/2)%MOD;

	
}


int main(){
	int i, T;
	REP(i, MAX_N)
		gen(0, i);


	cin >> T;
	REP(i, T){
		cin >> l >> r;
		nl=strlen(l), nr=strlen(r);

		printf("Case #%d: %Ld\n", i+1, solve());


	}


	return EXIT_SUCCESS;
}

