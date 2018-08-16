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

const int maxn=55555;
int n;
vector<pii> e[maxn];
int f[maxn];
int A[maxn];
ll B[maxn];
ll best;
vi res;

int dfs(int a, int p=-1){
    int u=f[a];ll v=0;
    REP(i,e[a].size()){
        int b=e[a][i].ST, t=e[a][i].ND;
        if (b!=p) u+=dfs(b,a), v+=B[b]+1ll*A[b]*t;
    }
    B[a]=v;
    return A[a]=u;
}

void go(int a, int u, ll c, int p=-1){
    REP(i,e[a].size()){
        int b=e[a][i].ST, t=e[a][i].ND;
        if (b==p) continue;
        c+=B[b]+1ll*A[b]*t; u+=A[b];
    }
    if (c<best) best=c, res.clear();
    if (c==best) res.pb(a);

    REP(i,e[a].size()){
        int b=e[a][i].ST, t=e[a][i].ND;
        if (b==p) continue;
        int nu=u-A[b]+f[a]; ll nc=c-1ll*A[b]*t-B[b]+1ll*nu*t;
        go(b,nu,nc,a);
    }
}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        cin>>n;
        REP(i,n-1){
            int a,b,t; scanf(" %d%d%d",&a,&b,&t);
            --a; --b;
            e[a].pb(MP(b,t));
            e[b].pb(MP(a,t));
        }
        memset(f,0,sizeof(f));
        int m; cin>>m;
        REP(i,m){
            int a,x; scanf(" %d%d",&a,&x);
            f[a-1]+=x;
        }

        dfs(0);
        best=1e18;
        res.clear();
        go(0,0,0);

        sort(ALL(res));
        cout<<2*best<<endl;
        REP(i,res.size()-1) printf("%d ",res[i]+1);
        printf("%d\n",res.back()+1);

        REP(i,n) e[i].clear();
    }
    return 0;
}

