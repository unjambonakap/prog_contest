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

const int maxn=111111;
const int mod=1e9+9;
int xa[maxn], ya[maxn];
int n;
int l[maxn], r[maxn];
int nexta[maxn], nextb[maxn];
pii dp[maxn];

pii go0(int u){
    if (u==-1) return MP(0,-1);
    pii x=go0(l[u]), y=go0(r[u]);
    return dp[u]=MP(max(x.ST+y.ND+1,x.ND+y.ST+1),x.ST+y.ST);
}

pii go(int u, int a, int b){
    if (u==-1) return MP(0,-1);
    if (a==-1 && b==-1) return dp[u];
    if (a!=-1 && xa[u]<a) return go(r[u],a,b);
    if (b!=-1 && xa[u]>b) return go(l[u],a,b);
    pii x=go(l[u],a,-1), y=go(r[u],-1,b);
    return MP(max(x.ST+y.ND+1,x.ND+y.ST+1),x.ST+y.ST);
}


int main(){
    int k;
    cin>>n>>k;
    REP(i,k) cin>>xa[i]>>ya[i];
    int a, b, c, d;
    cin>>a>>b>>c>>d;
    REP(i,n-k) xa[i+k]=(1ll*xa[i+k-1]*a+b)%mod;
    REP(i,n-k) ya[i+k]=(1ll*ya[i+k-1]*c+d)%mod;
    vector<pii> pl;
    REP(i,n) pl.pb(MP(xa[i],ya[i]));
    sort(ALL(pl));
    REP(i,n) xa[i]=pl[i].ST, ya[i]=pl[i].ND;

    memset(l,-1,sizeof(l)); memset(r,-1,sizeof(r));
    memset(nexta,-1,sizeof(nexta)); memset(nextb,-1,sizeof(nextb));

    vector<pii> stk;
    REP(i,n){
        while(stk.size() && stk.back().ST<ya[i]) stk.pop_back();
        if (stk.size()) nexta[i]=stk.back().ND;
        stk.pb(MP(ya[i],i));
    }
    stk.clear();
    for (int i=n-1; i>=0; --i){
        while(stk.size() && stk.back().ST<ya[i]) stk.pop_back();
        if (stk.size()) nextb[i]=stk.back().ND;
        stk.pb(MP(ya[i],i));
    }
    memset(l,-1,sizeof(l));
    memset(r,-1,sizeof(r));
    int root=-1;
    REP(i,n){
        int va=nexta[i]==-1?INT_MAX:ya[nexta[i]];
        int vb=nextb[i]==-1?INT_MAX:ya[nextb[i]];

        if (nexta[i]==-1 && nextb[i]==-1) root=i;
        else if (vb<va) l[nextb[i]]=i;
        else r[nexta[i]]=i;
    }
    assert(root!=-1);

    go0(root);

    int m;
    cin>>m;
    REP(i,m){
        int a, b; scanf(" %d%d", &a, &b);
        pii res=go(root,a,b);
        printf("%d\n", max(res.ST,res.ND));
    }
    return 0;
}


