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

const int maxn=111;
const int m=10;
const int mod=1e9+7;

int a[maxn], na[maxn], b[m];
int n;
int fact[maxn], ifact[maxn];

int faste(int a, int p=mod-2){int x=1; for (; p; p>>=1, a=1ll*a*a%mod) if (p&1) x=1ll*x*a%mod; return x;}
int cnk(int n, int k){return 1ll*fact[n]*ifact[k]%mod*ifact[n-k]%mod;}

int main(){
    cin>>n;
    fact[0]=ifact[0]=1;
    FOR(i,1,maxn) fact[i]=1ll*i*fact[i-1]%mod, ifact[i]=faste(fact[i]);
    REP(i,m) cin>>b[i];
    a[0]=1;
    for (int i=m-1; i>=0; --i){
        memset(na,0,sizeof(na));
        REP(j,n+1-b[i]) FOR(k,b[i],n-j+1) if (!k || j || i) na[j+k]=(na[j+k]+1ll*a[j]*cnk(j+k-(i==0 && k),k))%mod;
        memcpy(a,na,sizeof(a));
    }
    ll res=0;
    FOR(i,1,n+1) res+=a[i];
    cout<<res%mod<<endl;
    return 0;
}


