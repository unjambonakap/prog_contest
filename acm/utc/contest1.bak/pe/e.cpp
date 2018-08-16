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
const int maxb=22;

vector<pii> e[maxn];
int par[maxn][maxb];
int d[maxn];
int u[maxn];
int n;
pii best;

void dfs(int a, int p=-1){
    par[a][0]=p==-1?a:p;
    d[a]=p==-1?0:d[p]+1;
    REP(i,e[a].size()){
        int b=e[a][i].ST;
        if (b!=p) dfs(b,a);
    }
}

int go(int a, int p=-1){
    int c=0;

    REP(i,e[a].size()){
        int x=go(e[a][i].ST,a);
        c+=x;
        best=min(best,MP(x,e[a][i].ND));
    }
    return c+u[a];
}

int lca(int a, int b){
    if (d[a]<d[b]) swap(a,b);
    for (int i=maxb-1; i>=0; --i) if (d[par[a][i]]>=d[b]) a=par[a][i];
    assert(d[a]==d[b]);
    if (a==b) return a;
    for (int i=maxb-1; i>=0; --i) if (par[a][i]!=par[b][i]) a=par[a][i], b=par[b][i];
    return par[a][0];
}

int main(){
    int k;
    cin>>n>>k;
    REP(i,n-1){int a, b; scanf(" %d", &a,&b); --a; --b; e[a].pb(MP(b,i)); e[b].pb(MP(a,i));}
    dfs(0);
    FOR(i,1,maxb) REP(j,n) par[j][i]=par[par[j-1][i]][j-1];

    REP(i,k){
        int a,b,c; scanf(" %d%d%d", &a,&b,&c); --a; --b;
        int x=lca(a,b);
        u[a]+=c; u[b]+=c;
        u[c]-=2*c;
    }

    best=MP(INT_MAX,maxn);
    go(0);
    printf("%d %d\n", best.ST, best.ND+1);
    return 0;
}


