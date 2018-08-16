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

ll n;
int mod;
ll u, v, l, r;

int go(ll s, ll d, ll a, ll b){
    if (a+b<=l || a>r) return 0;
    if (a>=l&& a+b-1<=r){
        ll na, nb;
        if (s>v) return 0;
        na=(u-s+d-1)/d; nb=(v-s)/d+1;
        if (na<0) na=0; if (nb>b) nb=b;
        nb-=na;
        if (nb<=0) return 0;

        nb%=mod; na%=mod; d%=mod;
        return ((s+d*na%mod)*nb+nb*(nb-1)/2%mod*d)%mod;
    }
    ll m=(b+1)/2;
    return (go(s,2*d,a,m)+go(s+d,2*d,a+m,b-m))%mod;
}
//1 3 2 4


int main(){
    int m; cin>>n>>m>>mod;
    REP(i,m){
        //scanf("%Ld %Ld %Ld %Ld", &l,&r,&u,&v);
        scanf("%I64d %I64d %I64d %I64d", &l,&r,&u,&v);
        ll res=go(1,1,1,n);
        //printf("%Ld\n", res);
        printf("%I64d\n", res);
    }

}

