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
#include <sstream>
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



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

ll mod;
int MOD;
int mod2,mod5;
ll ra, rb;
int prod[11111111];

void bezout(int a, ll ua, ll ub, int b, ll va, ll vb){
    if (!b){ra=ua; rb=ub; return;}
    int k=a/b;
    bezout(b,va,vb,a-k*b,(ua-k*va)%MOD,(ub-k*vb)%MOD);
}

ll inv(int a){ bezout(a,1,0,MOD,0,1); return (MOD+ra)%MOD; }

int faste(int a, ll p){ int x=1; for (; p; p>>=1, a=1ll*a*a%MOD) if (p&1) x=1ll*x*a%MOD; return x; }


int fact(ll n, int a){
    if (n<=1) return 1;
    ll res=fact(n/a,a);
    res=res*faste(prod[MOD],n/MOD)%MOD;
    res=res*prod[n%MOD]%MOD;
    return res;
}

int doit(ll n, ll k, int a, int mod){
    MOD=mod;
    ll cnta=0;
    for (ll u=a; u<=n; u*=a) cnta+=n/u-k/u-(n-k)/u;
    if (cnta>=10) return 0;

    prod[0]=1;
    for (int i=1; i<=mod; ++i) prod[i]=1ll*prod[i-1]*(i%a?i:1)%mod;

    ll res=1ll*fact(n,a)*inv(fact(k,a))%mod*inv(fact(n-k,a))%mod;
    REP(i,cnta) res=res*a%mod;
    return res;
}

ll go(ll n, ll k){
    int a=doit(n,k,2,mod2), b=doit(n,k,5,mod5);

    //now crm
    MOD=mod5;
    int x=inv(mod2);
    ll res=a+1ll*x*mod2%mod*(b-a)%mod;
    if (res<0) res+=mod;
    return res;
}


int main(){
    ll n,k;
    while(cin>>n>>k,!cin.eof()){
        mod=mod2=mod5=1;
        REP(j,10) mod=mod*10, mod2=mod2*2, mod5=mod5*5;

        if (k>n-k) k=n-k;

        ll x=1;
        int f=0;
        for (int i=0; i<k; ++i){ 
            x=x*(n-i)/(i+1);
            if (x>=mod){f=1; break;}
        }

        ll res=go(n,k);
        if (f) printf("...%010Ld\n",res);
        else printf("%Ld\n",res);
    }
    return 0;
}

