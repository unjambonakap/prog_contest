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

typedef int64_t ll;
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

const int maxn=55;
ll a[maxn], b[maxn], c[maxn];
int perm[maxn];
int n, m, k;
map<ll,ll> dp[maxn][maxn];//pos,rem,#ex


ll go(int p, int ax, ll bx){
    if (!ax) return 0;
    if (p==m) return -1e18;
    if (dp[p][ax].count(bx)) return dp[p][ax][bx];
    ll &r=dp[p][ax][bx];
    r=go(p+1,ax,bx);
    int np=p+1;
    while(np<m && c[np]==c[p]) ++np;

    if (ax==n) for (ll i=a[p]; i<=b[p]; ++i){
            if (ax<n && bx+k!=i && bx*k!=i) continue;
            checkmax(r,i+go(np,ax-1,i));
    }else{
        if (bx+k>=a[p]&&bx+k<=b[p]) checkmax(r,bx+k+go(np,ax-1,bx+k));
        if (bx*k>=a[p]&&bx*k<=b[p]) checkmax(r,bx*k+go(np,ax-1,bx*k));
    }
    return r;
}

void build(int p, int ax, ll bx){
    if (!ax) return;
    ll r=dp[p][ax][bx];
    if (r==go(p+1,ax,bx)) return build(p+1,ax,bx);

    int np=p+1;
    while(np<m && c[np]==c[p]) ++np;

    for (ll i=a[p]; i<=b[p]; ++i){
        if (ax<n && bx+k!=i && bx*k!=i) continue;
        if (r==i+go(np,ax-1,i)){printf("%d ", 1+perm[p]); cout<<i<<endl; return build(np,ax-1,i);}
    }
    assert(0);
}




int main(){
    cin>>n>>m>>k;
    REP(i,m) cin>>a[i]>>b[i]>>c[i], perm[i]=i;
    REP(i,m) REP(j,m) if (c[i]<c[j]) swap(a[i],a[j]),swap(b[i],b[j]),swap(c[i],c[j]),swap(perm[i],perm[j]);
    ll res=go(0,n,0);
    if (res<0) printf("NO\n");
    else{
        printf("YES\n");
        build(0,n,0);
    }

    return 0;
}



