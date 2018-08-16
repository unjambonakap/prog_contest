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

const int mod=1e9+7;
const ll maxn=1e10+11;
const int maxm=1000000;

int isp[maxm];
ll pl[maxm];
ll sqpl[maxm];
int np;
ll ord[maxm];
vector<pii> sieve[maxm];



ll mul(ll a, ll b, ll mod){
    ll res=(a>>16)*b%mod;
    res=(res<<16)%mod+b*(a&0xffff)%mod;
    return res%mod;
}

ll fastea(ll a, ll p, ll mod){
    ll x=1;
    for (; p; p>>=1, a=mul(a,a,mod)){
        if (p&1) x=mul(x,a,mod);
    }
    return x;
}
ll fasteb(ll a, ll p, ll mod){
    ll x=1;
    for (; p; p>>=1, a=a*a%mod){
        if (p&1) x=x*a%mod;
    }
    return x;
}

ll faste(ll a, ll p, ll mod){
    assert(p>=0);
    if (mod>1e9+10) return fastea(a,p,mod);
    return fasteb(a,p,mod);
}

ll gcd(ll a, ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a, ll b){return 1ll*a/gcd(max(a,b),min(a,b))*b; }


ll _getord(ll v, ll p){
    ll ov=v;
    for (int i=0; i<np && sqpl[i]<=ov; ++i){
        int cnt=0;
        while(ov%pl[i]==0) ov/=pl[i], ++cnt;
        REP(j, cnt){
            if (faste(2, v/pl[i], p)==1) v/=pl[i];
            else break;
        }
    }
    if (ov>1){ if (faste(2, v/ov, p)==1) v/=ov; }
  //  ll z=faste(2,v,p);
  //  assert(z==1);
    return v;
}


ll getord(ll v, ll p){
    if (p<maxm) return ord[p];
    return _getord(v, p);
}

vector<pii> fact;
ll go(ll p, ll a, ll o, ll phi){
    if (p==fact.size()){
        assert(phi%o==0);
        return phi/o;
    }
    assert(o<1e10);
    

    ll res=go(p+1, a, o, phi);
    int pa=pl[fact[p].ST];
    ll px=pa;
    ll u=pa-1;
    ll ordx=getord(u,px);
    REP(i, fact[p].ND){
        if (faste(2,ordx,px)!=1) ordx*=pa;
        res+=go(p+1, a/pa, lcm(o, getord(u, px)), phi*u);
        px*=pa;
        u*=pa;
    }
    return res%mod;
}

ll doit(ll a, ll l){
    ll na=a;
    fact=sieve[a-l];
    FE(it, fact) REP(i, it->ND) na/=pl[it->ST];


    ll res=0;
    res+=go(0, a, 1, 1);

    if (na>1) res+=go(0, a/na, getord(na-1, na), na-1);
    return res%mod;
}


int main(){
    np=0;
    memset(isp, 1, sizeof(isp));
    FOR(i, 2, maxm) if (isp[i]){
        for (ll j=1ll*i*i; j<maxm; j+=i) isp[j]=0;
        sqpl[np]=1ll*i*i;
        pl[np++]=i;
    }
    REP(i, maxm) ord[i]=1;
    FOR(i, 1, np){
        int cx=1;
        for (ll j=pl[i]; j<maxm; j=j*pl[i], ++cx){
            int phi=j/pl[i]*(pl[i]-1);
            int a=_getord(phi, j);
            for (int k=j, cnt=1; k<maxm; k+=j, ++cnt) if (cnt%pl[i]) ord[k]=lcm(a,ord[k]);
        }
    }

    int tn; cin>>tn;
    REP(ti, tn){
        ll l, r;
        cin>>l>>r;
        REP(i, r+3-l) sieve[i].clear();
        REP(i, np){
            ll j=l-(l%pl[i]);
            if (j<l) j+=pl[i];
            for (; j<=r+10; j+=pl[i]){
                int px=pl[i]*pl[i];
                int cnt=1;
                while(j%px==0) px*=pl[i], ++cnt;
                sieve[j-l].pb(MP(i, cnt));
            }

        }

        ll res=0;
        int step=0;
        for (ll i=l-(l&1); i<=r; i+=2){

            //if (step++!=6222) continue;
            ll z=doit(i+1, l);
            if (i>=l) res+=faste(26, z-1, mod);
            if (i+1<=r) res+=faste(26, z, mod);
        }
        printf("%Ld\n", res%mod);
    }
    return 0;
}



