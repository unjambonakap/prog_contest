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
const int maxb=20;



vector<pii> e[maxn];
int res[maxn];
int n;
int par[maxn][maxb];
int st[maxn];
int d[maxn];

void dfs(int a, int p=-1){
    par[a][0]=p==-1?a:p;
    d[a]=p==-1?0:d[p]+1;
    REP(i,e[a].size()) if (e[a][i].ST!=p) dfs(e[a][i].ST,a);
}

int dfs2(int a, int p=-1){
    int u=st[a];
    REP(i,e[a].size()){
        int b=e[a][i].ST;
        if (b==p) continue;
        int x=dfs2(b,a);
        res[e[a][i].ND]+=x;
        u+=x;
    }
    return u;
}

int lca(int a, int b){
    if (d[a]>d[b]) swap(a,b);
    for (int i=maxb-1; i>=0; --i) if (d[par[b][i]]>=d[a]) b=par[b][i];
    for (int i=maxb-1; i>=0; --i) if (par[a][i]!=par[b][i]) a=par[a][i], b=par[b][i];
    if (a!=b) a=par[a][0];
    return a;
}


int main(){
    cin>>n;
    REP(i,n-1){
        int a, b; scanf(" %d%d", &a,&b);
        --a; --b;
        e[a].pb(MP(b,i));
        e[b].pb(MP(a,i));
    }
    dfs(0);
    FOR(i,1,maxb) REP(j,n) par[j][i]=par[par[j][i-1]][i-1];

    int nk; cin>>nk;
    REP(i,nk){
        int a, b; scanf(" %d%d", &a,&b); --a; --b;
        int c=lca(a,b);
        ++st[a]; ++st[b];
        st[c]-=2;
    }
    dfs2(0);
    REP(i,n-2) printf("%d ", res[i]); printf("%d\n", res[n-2]);

    return 0;
}


