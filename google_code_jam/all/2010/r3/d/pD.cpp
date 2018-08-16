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
const ull MOD=1000000007;
const int MAX_B=75;
const int MAX_C=73;


ll cpos[MAX_B][MAX_B*MAX_B];
ll dp[MAX_C][MAX_B][MAX_B];//column, number of summands active at the current column, carry
ll fact[MAX_B];
ll C[MAX_B][MAX_B];
vector<int> dc;
ll n;
int b;

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


void procFact(int a, ll prev){
	if (a==MAX_B+1)return;
	fact[a]=(a*prev)%MOD;
	procFact(a+1, fact[a]);
}

vector<int> decomp(ll n, int b){
	vector<int> nb;
	while(n!=0){
		nb.pb(n%b);
		n/=b;
	}
	return nb;
}


void procCpos(){
	int i, j, k, m;

	memset(cpos, 0, sizeof(cpos));
	cpos[0][0]=1;
	FOR(i, 1, b-1){
		m=i*(i+1)/2;
		REPV(j, b)
			REP(k, m)
				cpos[j+1][k+i]+=cpos[j][k], cpos[j+1][k+i]%=MOD;
	}
}

ll F(int i, int h, int c){
	int j, k, z, nc;
	if (i==SZ(dc))
		return (c==0 && h==0);
	

	ll &r=dp[i][h][c];
	if (r!=-1)return r;
	r=0;


	int num=dc[i]-c;
	if (num<0)num+=b;

	ll ca, cb, cc;
	ca=fact[h];


	REP(z, 2){
		if (h==0 && z==1)continue;
		for (j=num; j<=h*b+num; j+=b){
			nc=(j+c)/b;
			cb=(cpos[h-z][j]*ca)%MOD;

			if (cb==0)continue;
			FOR(k, z, h){
				cc=(C[h-z][h-k]*cb)%MOD;
				r=(r+(F(i+1, k, nc)*cc)%MOD)%MOD;
			//	printf("%d for %d %d => %d %d %Ld=> %Ld\n", i, z, j, k, nc, cc, F(i+1, k, nc));
			}
		}
	}



	//printf("%d %d %d=> %Ld\n", i, h, c, r);
	return r;
}

ll solve(){

	int i;
	procCpos();


	ll s=0;
	memset(dp, -1, sizeof(dp));
	REP(i, b){
		s=mod(s+F(0, i+1, 0)*inv(fact[i+1], MOD), MOD);

	}


	return s;
}

int main(){
	int t, T;
	int i, j, k;
	fact[0]=1;
	procFact(1, 1);
	memset(C, 0, sizeof(C));

	C[0][0]=1;
	REP(i, MAX_B-1)
		REP(j, MAX_B-1)
		C[i+1][j+1]=(C[i+1][j+1]+C[i][j])%MOD, C[i+1][j]=(C[i+1][j]+C[i][j])%MOD;//C[n][k]

	cin>>T;
	REP(t, T){
		scanf("%Ld %d\n", &n, &b);
		//if (t!=2)continue;
		//printf("%d %d\n", n, b);
		dc=decomp(n, b);
		printf("Case #%d: %Ld\n", t+1, solve());
	}


	return EXIT_SUCCESS;
}

