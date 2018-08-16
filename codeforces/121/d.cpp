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
const int maxm=333333;

int n, m;
vi e[maxn];
int C[maxn];
vi cycle[maxn];
int vis[maxn];
int nc;
int stk[maxn], na;
int dp[maxn];
int has[maxn];

void dfs(int a, int p=-1){
    stk[na++]=a;
    vis[a]=1;

    REP(i,e[a].size()){
        int b=e[a][i];
        if (b==p) continue;
        if (vis[b]){
            if (C[a]!=-1) continue;
            for (int j=na-1; stk[j]!=b; --j) C[stk[j]]=nc, cycle[nc].pb(stk[j]);
            C[b]=nc; cycle[nc].pb(b); ++nc;
        }else dfs(b,a);
    }
    if (C[a]==-1) C[a]=nc, cycle[nc].pb(a), ++nc;
    --na;
}

int go(int a, int p=-1){
    int &r=dp[a];
    if (r!=-1) return r;
    vi &c=cycle[C[a]];
    int x=0;

    r=0;
    vi next;
    REP(i,c.size()){
        int u=c[i];
        REP(j,e[u].size()){
            int v=e[u][j];
            if (C[v]==p) ++has[u];
            else if (C[v]==C[u]) continue;
            else ++has[u], r+=go(v,C[a]);
        }
        if (has[u]) next.pb(u);
    }

    int tmp=0;
    REP(i,next.size()) tmp+=(1+has[next[i]])/2;
    if (p!=-1) --tmp;
    if (c.size()==1) return r+=(has[c[0]]+1)/2-(p!=-1);
    
    ++tmp;
    int add=r;
    r=tmp;

    tmp=0;
    if (next.size()>1){
        REP(i,next.size()) tmp+=1+(max(0,has[next[i]]-2)+1)/2;
        if (p!=-1) --tmp;
        r=min(r,tmp);
    }
    return r+=add;

}




int main(){
    cin>>n>>m;
    REP(i,m){ int a, b; scanf(" %d%d", &a,&b); --a; --b; e[a].pb(b); e[b].pb(a); }
    memset(C,-1,sizeof(C));
    dfs(0);
    memset(dp,-1,sizeof(dp));
    int res=go(0);
    printf("%d %d\n", res, m);
    return 0;
}


